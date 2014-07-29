#include "VBFHiggsToInvisible/TriggerStudies/interface/TrigStudies.h"

#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"

#include "CondFormats/DataRecord/interface/L1CaloEcalScaleRcd.h"
#include "CondFormats/DataRecord/interface/L1CaloHcalScaleRcd.h"

#include "CondFormats/L1TObjects/interface/L1CaloEcalScale.h"
#include "CondFormats/L1TObjects/interface/L1CaloHcalScale.h"

// #include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"
// #include "DataFormats/L1CaloTrigger/interface/L1CaloRegionDetId.h"

#include <stdio.h>
#include <math.h>

using namespace std;
using namespace edm;

TrigStudies::TrigStudies(const edm::ParameterSet& pset){

  // Getting InputTag from configuration file
  m_InputTag_L1GTReadoutRecord      = pset.getUntrackedParameter("inputTag_L1GTReadoutRecord",     InputTag("gtDigis"));
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter("inputTag_L1Extra_mhts",          InputTag("l1extraParticles","MHT"));
  m_InputTag_HLTResults             = pset.getUntrackedParameter("inputTag_HLTResults",            InputTag("TriggerResults","HLT"));
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter("inputTag_L1CaloRegionCollection",InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_EcalTriggerPrimitives", InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_HcalTriggerPrimitives", InputTag("valHcalTriggerPrimitiveDigis"));

  // Getting other parameters from configuration file
  m_verbose      = pset.getUntrackedParameter<bool>("verbose",false);
  m_selHLTrigger = pset.getParameter<std::vector<string> >("selHLTrigger");
  
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","TrigStudiesResults.root");
  
  // Initialising other variables 
  currentRunNumber = 0;
  fOut = new TFile(outputFilename.c_str(),"RECREATE");

}

TrigStudies::~TrigStudies(){
  fOut->Write();
}

void TrigStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  hEventCount->Fill(1);

  nEcalTT_NSaturated    = 0;
  nHcalTT_NSaturated    = 0;
  nRCTRegion_NSaturated = 0;
  nTotal_NSaturated     = 0;
  
  // Getting Final Decision Logic (FDL) Data from GT
  Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecordData;
  iEvent.getByLabel(m_InputTag_L1GTReadoutRecord, gtReadoutRecordData);
  
  edm::Handle<l1extra::L1EtMissParticleCollection> mets;
  iEvent.getByLabel(m_InputTag_L1Extra_mets,mets);
  
  edm::Handle<l1extra::L1EtMissParticleCollection> mhts;
  iEvent.getByLabel(m_InputTag_L1Extra_mhts,mhts);
                                                                                    
  edm::Handle<L1CaloRegionCollection>     caloRegions;
  edm::Handle<EcalTrigPrimDigiCollection> lEcalDigiHandle;
  edm::Handle<HcalTrigPrimDigiCollection> lHcalDigiHandle;
  iEvent.getByLabel(m_InputTag_L1CaloRegionCollection, caloRegions );
  iEvent.getByLabel(m_InputTag_EcalTriggerPrimitives,  lEcalDigiHandle);
  iEvent.getByLabel(m_InputTag_HcalTriggerPrimitives,  lHcalDigiHandle);
 
  edm::ESHandle<L1CaloEcalScale>          lEcalScaleHandle;
  edm::ESHandle<L1CaloHcalScale>          lHcalScaleHandle;
  iSetup.get<L1CaloEcalScaleRcd>().get( lEcalScaleHandle );
  iSetup.get<L1CaloHcalScaleRcd>().get( lHcalScaleHandle );
  
  if(mets.isValid()){
    if (mets->size()!=0){
      
      if(m_verbose){cout << "=> Event ETM " << mets->begin()->et() << endl;}
      hL1ETM->Fill(mets->begin()->et());
      
    }else{cout << "[TrigStudies] ERROR: l1extraParticles MET has size zero." << endl;}
  }else{cout << "[TrigStudies] ERROR: l1extraParticles MET is not valid." << endl;}
  
  
  if(mhts.isValid()){
    if(mhts->size()!=0){
      
      if(m_verbose){cout << "=> Event HTT " << mhts->begin()->etTotal() << endl;}
      hL1HTT->Fill(mhts->begin()->etTotal());
      
    }else{cout << "[TrigStudies] ERROR: l1extraParticles MHT has size zero." << endl;}
  }else{cout << "[TrigStudies] ERROR: l1extraParticles MHT is not valid." << endl;}
  
  if(caloRegions.isValid()){
    if(m_verbose){cout << "=> Got RCT Regions! They are " << caloRegions->size() << endl;}
     
      for(unsigned int iRCT=0;iRCT < caloRegions->size(); ++iRCT ) {
        
        double rctRegionVal = caloRegions->at(iRCT).et();
        double rctRegionET  = 0.5*rctRegionVal;
        
        hRCTRegion_Val->Fill(rctRegionVal);
        hRCTRegion_Et ->Fill(rctRegionET);
        
        
        
        //double RCTiEta = caloRegions->at(iRCT).gctEta();
        //double RCTiPhi = caloRegions->at(iRCT).gctPhi();
       
  
        
        
       //printf("RCT i=%d eta=%8.4f phi=%8.4f et=%8.4f",iRCT,RCTiEta,RCTiPhi,RCTRegionET);
        if(rctRegionVal==1023){
          if(m_verbose){cout << "=> Found saturated RCT" << endl;}
          nRCTRegion_NSaturated++;
          nTotal_NSaturated++;
        }
     }
  }
  
  if(lEcalDigiHandle.isValid()){
    if(m_verbose){cout << "=> Got ECAL TT! They are " << lEcalDigiHandle->size() << endl;}
    
    TH1D* hECALTT_Barrel_CompressedEt         = h1D_ECALTT["ECALTT_Barrel_CompressedEt"];
    TH1D* hECALTT_Endcap_CompressedEt         = h1D_ECALTT["ECALTT_Endcap_CompressedEt"];
    TH2D* hECALTT_CompressedEt127_EtaPhiTotal = h2D_ECALTT["ECALTT_CompressedEt127_EtaPhiTotal"];
    
    for ( EcalTrigPrimDigiCollection::const_iterator lEcalTPItr = lEcalDigiHandle->begin(); lEcalTPItr != lEcalDigiHandle->end(); ++lEcalTPItr ){
      
      int     ecalVal = lEcalTPItr->compressedEt();
      int32_t lET = 4 * lEcalScaleHandle->et( lEcalTPItr->compressedEt(), abs( lEcalTPItr->id().ieta() ),  ( lEcalTPItr->id().ieta() > 0 ? +1 : -1 ) );                     
      
      //cout << "ECAL TT et="<<lET<<endl; 
      hEcalTT_Val->Fill(ecalVal);
      hEcalTT_Et ->Fill(lET);
      
      for(int i=0; i<lEcalTPItr->size(); i++){
        hECALTTSamples_Val->Fill(lEcalTPItr->sample(i).compressedEt());
      }
      
      // Barrel-Endcap overlap are TT 16 and 17
      if(abs(lEcalTPItr->id().ieta())<17){
        hECALTT_Barrel_CompressedEt->Fill(lEcalTPItr->compressedEt());
      }
      else{
        hECALTT_Endcap_CompressedEt->Fill(lEcalTPItr->compressedEt());
      }
      
      // For the investigation of the 127 saturation point 
      if(ecalVal==127){
        hECALTT_CompressedEt127_EtaPhiTotal->Fill(Form("%d",lEcalTPItr->id().ieta()),Form("%d",lEcalTPItr->id().iphi()),1);
      }
      
      
      
//       if(ecalVal==127){
//         cout << "ECAL id.eta=" <<  
//                             << " id.phi=" <<  
//                             << " ttFlag=" << lEcalTPItr->ttFlag()
//                             << "sampleOfInterest=" << lEcalTPItr->sampleOfInterest()
//                             << " fineGrain="  << lEcalTPItr->fineGrain() << " sFGVB="  << lEcalTPItr->sFGVB() << endl;
//       }
      
      if(ecalVal==255){
        if(m_verbose){cout << "=> Found saturated ECAL TT" << endl;}
        nEcalTT_NSaturated++;
        nTotal_NSaturated++;
      }
    }
  }
  
  if(lHcalDigiHandle.isValid()){
    if(m_verbose){cout << "=> Got HCAL TT! They are " << lHcalDigiHandle->size() << endl;}
    
    for ( HcalTrigPrimDigiCollection::const_iterator lHcalTPItr = lHcalDigiHandle->begin(); lHcalTPItr != lHcalDigiHandle->end(); ++lHcalTPItr ){
      
      int     hcalVal = lHcalTPItr->SOI_compressedEt();
      int32_t lET = 4 * lHcalScaleHandle->et( lHcalTPItr->SOI_compressedEt(), abs( lHcalTPItr->id().ieta() ),  ( lHcalTPItr->id().ieta() > 0 ? +1 : -1 ) );
      hHcalTT_Val->Fill(hcalVal);
      hHcalTT_Et ->Fill(lET);
      
      if(hcalVal==255){
        if(m_verbose){cout << "=> Found saturated HCAL TT" << endl;}
        nHcalTT_NSaturated++;
        nTotal_NSaturated++;
      }
    }
  }

  // Need this in this scope for HLT seeds later
  DecisionWord l1Word;
  
  if(gtReadoutRecordData.isValid()){
    
    const vector<L1GtFdlWord>& gtFdlVectorData = gtReadoutRecordData->gtFdlVector();
      
    // Running over FDL results to get which bits fired
    for(unsigned int a=0 ; a<gtFdlVectorData.size() ; a++){
        
      // Selecting the FDL that triggered
      if(gtFdlVectorData[a].bxInEvent() == 0){
          
        const L1GtFdlWord* fdl = &(gtFdlVectorData[a]);  
        l1Word = fdl->gtDecisionWord();
        
        for(int bit=0; bit<128; bit++){
          if(l1Word[bit]){hL1AlgoCounts->Fill(bit);}
        }
      }
    }
  }else{cout << "[TrigStudies] ERROR: GT Readout Record Data is not valid." << endl;}
    
  Handle<TriggerResults> hltresults;
  iEvent.getByLabel(m_InputTag_HLTResults, hltresults);
    
  for(unsigned i=0; i<m_selHLTrigger.size(); i++){
 
    string pName = m_selHLTrigger[i];
      
    if(testTrigger(iEvent,hltresults,pName)){
      hHLTAlgoCounts->Fill(pName.c_str(),1);
      
      if(pName=="HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v"){
        if(l1Word[m_l1Alias["L1_ETM40"]]) {hHLTNewAlgoCounts->Fill("L1_ETM40 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM50"]]) {hHLTNewAlgoCounts->Fill("L1_ETM50 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM70"]]) {hHLTNewAlgoCounts->Fill("L1_ETM70 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM100"]]){hHLTNewAlgoCounts->Fill("L1_ETM100 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",1);}        
      }
      else if(pName=="HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v"){
        if(l1Word[m_l1Alias["L1_ETM40"]]) {hHLTNewAlgoCounts->Fill("L1_ETM40 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM50"]]) {hHLTNewAlgoCounts->Fill("L1_ETM50 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM70"]]) {hHLTNewAlgoCounts->Fill("L1_ETM70 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM100"]]){hHLTNewAlgoCounts->Fill("L1_ETM100 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",1);}        
      }
      else if(pName=="HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v"){
        if(l1Word[m_l1Alias["L1_ETM40"]]) {hHLTNewAlgoCounts->Fill("L1_ETM40 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM50"]]) {hHLTNewAlgoCounts->Fill("L1_ETM50 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM70"]]) {hHLTNewAlgoCounts->Fill("L1_ETM70 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM100"]]){hHLTNewAlgoCounts->Fill("L1_ETM100 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v",1);}        
      }
      else if(pName=="HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v"){
        if(l1Word[m_l1Alias["L1_ETM40"]]) {hHLTNewAlgoCounts->Fill("L1_ETM40 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM50"]]) {hHLTNewAlgoCounts->Fill("L1_ETM50 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM70"]]) {hHLTNewAlgoCounts->Fill("L1_ETM70 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v",1);}
        if(l1Word[m_l1Alias["L1_ETM100"]]){hHLTNewAlgoCounts->Fill("L1_ETM100 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v",1);}        
      }
 
      // Filling seeds list
      vector<string> l1SeedsETM;
      vector<string> l1SeedsHTT;
      if     (pName=="HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v"   ) {l1SeedsETM.push_back("L1_ETM40");}
      else if(pName=="HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v"){l1SeedsETM.push_back("L1_ETM40");}
      else if(pName=="HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v")    {l1SeedsETM.push_back("L1_ETM40");}
      else if(pName=="HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v"){l1SeedsETM.push_back("L1_ETM40");}     
      else if(pName=="HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v"){
        l1SeedsHTT.push_back("L1_HTT200");
        l1SeedsHTT.push_back("L1_HTT175");
        l1SeedsETM.push_back("L1_ETM40");
        l1SeedsETM.push_back("L1_ETM50");
      }
      else if(pName=="HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v"){
        l1SeedsHTT.push_back("L1_HTT200");
        l1SeedsHTT.push_back("L1_HTT175");
        l1SeedsETM.push_back("L1_ETM40");
        l1SeedsETM.push_back("L1_ETM50");
      }
      else if(pName=="HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v"){
        l1SeedsHTT.push_back("L1_HTT200");
        l1SeedsHTT.push_back("L1_HTT175");
        l1SeedsHTT.push_back("L1_HTT150");
        l1SeedsETM.push_back("L1_ETM40");
      }
      else if(pName=="HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v"){
        l1SeedsHTT.push_back("L1_HTT200");
        l1SeedsHTT.push_back("L1_HTT175");
        l1SeedsETM.push_back("L1_ETM40");
      }
      else if(pName=="HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v"){
        l1SeedsHTT.push_back("L1_HTT200");
        l1SeedsHTT.push_back("L1_HTT175");
        l1SeedsETM.push_back("L1_ETM40");
      }
      
      if(m_verbose){cout << "=> Fired HLT: " << pName.c_str() << endl;}
      
      bool firedETM = false;
      bool firedHTT = false;
      
      // TODO: This can be optimized with seed bit caching or bit mask and straight AND compare.
      for(unsigned iSeed=0; iSeed<l1SeedsETM.size(); iSeed++){

        int thisBit = m_l1Alias[ l1SeedsETM[iSeed] ];

        if(m_verbose){cout << "=> Testing if bit=" << thisBit<< " alias=" << l1SeedsETM[iSeed] << " fired... ";}
           
        if(l1Word[thisBit]){
          if(m_verbose){cout << "Yes!" << endl;}
          firedETM = true;
          break;
        }else{
          if(m_verbose){cout << "No!"<< endl;}
        }
      }

      // TODO: This can be optimized with seed bit caching or bit mask and straight AND compare.
      for(unsigned iSeed=0; iSeed<l1SeedsHTT.size(); iSeed++){

        int thisBit = m_l1Alias[ l1SeedsHTT[iSeed] ];
        if(m_verbose){cout << "=> Testing if bit=" << thisBit<< " alias=" << l1SeedsHTT[iSeed] << " fired... ";}        
        
        if(l1Word[thisBit]){
          if(m_verbose){cout << "Yes!" << endl;}
          firedHTT = true;
          break;
        }else{
          if(m_verbose){cout << "No!"<< endl;}
        }
      }
  
      if(m_verbose){cout << "=> Fired Seeds ETM: " << firedETM << " HTT: " << firedHTT << endl;}
      
      if( firedETM && !firedHTT){hHLTAlgoCounts_ETM ->Fill(pName.c_str(),1);}
      if(!firedETM &&  firedHTT){hHLTAlgoCounts_HTT ->Fill(pName.c_str(),1);}
      if( firedETM &&  firedHTT){hHLTAlgoCounts_Both->Fill(pName.c_str(),1);}
      if(!firedETM && !firedHTT){hHLTAlgoCounts_None->Fill(pName.c_str(),1);}
      
    }
  }
  
  // Filling saturation counts
  hEcalTT_NSaturated   ->Fill(nEcalTT_NSaturated);
  hHcalTT_NSaturated   ->Fill(nHcalTT_NSaturated);
  hRCTRegion_NSaturated->Fill(nRCTRegion_NSaturated);
  hTotal_NSaturated    ->Fill(nTotal_NSaturated);

  if(nTotal_NSaturated>0){
    hL1ETM_Saturated->Fill(mets->begin()->et());
    hL1HTT_Saturated->Fill(mhts->begin()->etTotal());
  }
}

void TrigStudies::beginJob(){}

void TrigStudies::endJob(){}

void TrigStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  currentRunNumber    = iRun.run();
  double nSelHLTAlgos = m_selHLTrigger.size();
  
  TDirectory* runDir  = fOut  ->mkdir(Form("Run_%d",currentRunNumber));
  TDirectory* ecalDir = runDir->mkdir("EcalTT");
  
  // General plots
  hEventCount    = new TH1I("EventCount",   "EventCount"   ,   1, 0.5,  1.5); hEventCount  ->SetDirectory(runDir);

  hEcalTT_NSaturated    = new TH1I("hEcalTT_NSaturated   ","hEcalTT_NSaturated   ",11,-0.5,10.5); hEcalTT_NSaturated   ->SetDirectory(runDir);
  hHcalTT_NSaturated    = new TH1I("hHcalTT_NSaturated   ","hHcalTT_NSaturated   ",11,-0.5,10.5); hHcalTT_NSaturated   ->SetDirectory(runDir);
  hRCTRegion_NSaturated = new TH1I("hRCTRegion_NSaturated","hRCTRegion_NSaturated",11,-0.5,10.5); hRCTRegion_NSaturated->SetDirectory(runDir);
  hTotal_NSaturated     = new TH1I("hTotal_NSaturated    ","hTotal_NSaturated    ",11,-0.5,10.5); hTotal_NSaturated    ->SetDirectory(runDir);
  
  h1D_ECALTT["ECALTT_Barrel_CompressedEt"]         = new TH1D("ECALTT_Barrel_CompressedEt",        "ECALTT Barrel CompressedEt",         512,-0.5,511.5); 
  h1D_ECALTT["ECALTT_Endcap_CompressedEt"]         = new TH1D("ECALTT_Endcap_CompressedEt",        "ECALTT Endcap CompressedEt",         512,-0.5,511.5); 
  h2D_ECALTT["ECALTT_CompressedEt127_EtaPhiTotal"] = new TH2D("ECALTT_CompressedEt127_EtaPhiTotal","ECALTT CompressedEt=127 EtaPhiTotal",56,0.5,56.5,72,0.5,72.5);
  
  for(int i=0; i<28; i++){
    h2D_ECALTT["ECALTT_CompressedEt127_EtaPhiTotal"]->GetXaxis()->SetBinLabel(i+1, Form("%d",-28+i));
    h2D_ECALTT["ECALTT_CompressedEt127_EtaPhiTotal"]->GetXaxis()->SetBinLabel(56-i,Form("%d", 28-i));    
  }
  for(int i=1; i<=72; i++){
    h2D_ECALTT["ECALTT_CompressedEt127_EtaPhiTotal"]->GetYaxis()->SetBinLabel(i,Form("%d",i));
  }
 
  for(auto it=h1D_ECALTT.begin(); it!=h1D_ECALTT.end(); it++){it->second->SetDirectory(ecalDir);}
  for(auto it=h2D_ECALTT.begin(); it!=h2D_ECALTT.end(); it++){it->second->SetDirectory(ecalDir);}
  
  //hECALTT
  
  // TPG Plots
  hEcalTT_Val        = new TH1D("hEcalTT_Val",       "hEcalTT_Val",        512,-0.5,511.5); hEcalTT_Val->SetDirectory(runDir);
  hECALTTSamples_Val = new TH1D("hECALTTSamples_Val","hECALTTSamples_Val", 512,-0.5,511.5); hECALTTSamples_Val->SetDirectory(runDir);
  hEcalTT_Et         = new TH1D("hEcalTT_Et",        "hEcalTT_Et",        1024,   0,1024);  hEcalTT_Et ->SetDirectory(runDir);
  
  hHcalTT_Val    = new TH1D("hHcalTT_Val","hHcalTT_Val", 512,-0.5,511.5); hHcalTT_Val->SetDirectory(runDir);
  hHcalTT_Et     = new TH1D("hHcalTT_Et", "hHcalTT_Et", 1024,   0,1024);  hHcalTT_Et ->SetDirectory(runDir);     

  // RCT Plots
  hRCTRegion_Val        = new TH1D("hRCTRegion_Val","hRCTRegion_Val",1024,-0.5,1023.5);               hRCTRegion_Val->SetDirectory(runDir);
  hRCTRegion_Et         = new TH1D("hRCTRegion_Et", "hRCTRegion_Et", 1024,   0,1024);                 hRCTRegion_Et->SetDirectory(runDir);
  
  
  // L1T Plots
  hL1AlgoCounts    = new TH1I("L1AlgoCounts",    "L1AlgoCounts",     128,-0.5,127.5); hL1AlgoCounts->SetDirectory(runDir);
  hL1ETM           = new TH1D("L1ETM",           "L1ETM",            500,   0, 1000);   hL1ETM->SetDirectory(runDir);
  hL1HTT           = new TH1D("L1HTT",           "L1HTT",           1000,   0, 2000);   hL1HTT->SetDirectory(runDir); 
  hL1ETM_Saturated = new TH1D("hL1ETM_Saturated","hL1ETM_Saturated", 500,   0, 1000);   hL1ETM_Saturated->SetDirectory(runDir);
  hL1HTT_Saturated = new TH1D("hL1HTT_Saturated","hL1HTT_Saturated",1000,   0, 2000);   hL1HTT_Saturated->SetDirectory(runDir);
  
  // HLT Plots
  hHLTAlgoCounts      = new TH1I("HLTAlgoCounts",     "HLTAlgoCounts",     nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts     ->SetDirectory(runDir);
  hHLTAlgoCounts_ETM  = new TH1I("HLTAlgoCounts_ETM", "HLTAlgoCounts_ETM", nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_ETM ->SetDirectory(runDir);
  hHLTAlgoCounts_HTT  = new TH1I("HLTAlgoCounts_HTT", "HLTAlgoCounts_HTT", nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_HTT ->SetDirectory(runDir);
  hHLTAlgoCounts_Both = new TH1I("HLTAlgoCounts_Both","HLTAlgoCounts_Both",nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_Both->SetDirectory(runDir);
  hHLTAlgoCounts_None = new TH1I("HLTAlgoCounts_None","HLTAlgoCounts_None",nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_None->SetDirectory(runDir);
  
  hHLTNewAlgoCounts = new TH1I("hHLTNewAlgoCounts",     "hHLTNewAlgoCounts",16,-0.5,16-0.5); hHLTNewAlgoCounts->SetDirectory(runDir);
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 1,"L1_ETM40 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v");  
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 2,"L1_ETM50 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 3,"L1_ETM70 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 4,"L1_ETM100 + HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 5,"L1_ETM40 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 6,"L1_ETM50 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 7,"L1_ETM70 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 8,"L1_ETM100 + HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel( 9,"L1_ETM40 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v");  
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(10,"L1_ETM50 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(11,"L1_ETM70 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(12,"L1_ETM100 + HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(13,"L1_ETM40 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(14,"L1_ETM50 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(15,"L1_ETM70 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v");
  hHLTNewAlgoCounts->GetXaxis()->SetBinLabel(16,"L1_ETM100 + HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v");
  
  ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);
  const L1GtTriggerMenu* menu = menuRcd.product();
    
  m_l1Alias.clear();
  
  if(m_verbose){cout << "=====> The L1 Menu: " << endl;}
  
  // Filling Alias-Bit Map
  for (CItAlgo algo = menu->gtAlgorithmAliasMap().begin(); algo!=menu->gtAlgorithmAliasMap().end(); ++algo){
    
    if(m_verbose){cout << " => key=" << algo->first << " bit=" << (algo->second).algoBitNumber() << " alias=" << (algo->second).algoAlias() << endl;}
    
    hL1AlgoCounts->GetXaxis()->SetBinLabel((algo->second).algoBitNumber()+1,(algo->second).algoAlias().c_str());
    m_l1Alias[(algo->second).algoAlias()] = (algo->second).algoBitNumber();
  }
    
  for(unsigned i=0; i<m_selHLTrigger.size(); i++){
    string trigName = m_selHLTrigger[i];
    
    hHLTAlgoCounts     ->GetXaxis()->SetBinLabel(i+1,trigName.c_str());
    hHLTAlgoCounts_ETM ->GetXaxis()->SetBinLabel(i+1,trigName.c_str());
    hHLTAlgoCounts_HTT ->GetXaxis()->SetBinLabel(i+1,trigName.c_str());
    hHLTAlgoCounts_Both->GetXaxis()->SetBinLabel(i+1,trigName.c_str());
    hHLTAlgoCounts_None->GetXaxis()->SetBinLabel(i+1,trigName.c_str());
    cout << "Looking for HLT: " << trigName << endl;
  }    
}

void TrigStudies::endRun(edm::Run const&, edm::EventSetup const&){}

void TrigStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void TrigStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// TODO: This function can be optimised by caching the trigger names once per run (not once per event)
bool TrigStudies::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
  
  bool Triggered = false;
  
  if( !iHLT.isValid() ) Triggered = false;
  int ntrigs = iHLT->size();
  if(ntrigs==0) Triggered = false;
  
  //check if trigger names are active
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
  //m_triggerNames.init( *iHLT.product() );
  
  for (int itrig = 0; itrig != ntrigs; ++itrig) 
  {
    if( !iHLT->wasrun(itrig) ) continue;
    if( iHLT->error(itrig) ) continue;
    string trigName = m_triggerNames.triggerName(itrig); 
    if( trigName.find(iTriggerName)==std::string::npos ) continue;
    if( !iHLT->accept(itrig) ) continue; 
    Triggered = true;
  }
  
  return Triggered;
  
}

void TrigStudies::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
  int ntrigs = iHLT->size();
  
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
  
  for (int itrig = 0; itrig != ntrigs; ++itrig) 
  {
    if( !iHLT->wasrun(itrig) ) continue;
    if(  iHLT->error(itrig) )  continue;
    
    string trigName = m_triggerNames.triggerName(itrig); 
    
    if( !iHLT->accept(itrig) )        continue;
    
    cout << "Fired: " << trigName << endl;    
    
  }
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrigStudies);
