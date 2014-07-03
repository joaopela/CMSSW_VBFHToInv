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
  m_InputTag_L1GTReadoutRecord      = pset.getParameter<InputTag>("inputTag_L1GTReadoutRecord");
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter ("inputTag_L1Extra_mets",InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter ("inputTag_L1Extra_mhts",InputTag("l1extraParticles","MHT"));
  m_InputTag_HLTResults             = pset.getParameter<InputTag>("inputTag_HLTResults");
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter ("inputTag_L1CaloRegionCollection",InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter ("inputTag_EcalTriggerPrimitives", InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter ("inputTag_HcalTriggerPrimitives", InputTag("valHcalTriggerPrimitiveDigis"));

  // Getting other parameters from configuration file
  m_verbose      = pset.getUntrackedParameter<bool>("verbose",false);
  m_selHLTrigger = pset.getParameter<std::vector<string> >("selHLTrigger");
  
  // Initialising other variables 
  currentRunNumber = 0;
  fOut = new TFile("TrigStudiesResults.root","RECREATE");

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
  
  if(caloRegions.isValid()){
    if(m_verbose){cout << "=> Got RCT Regions! They are " << caloRegions->size() << endl;}
     
      for(unsigned int iRCT=0;iRCT < caloRegions->size(); ++iRCT ) {

       double RCTRegionET  = 0.5*caloRegions->at(iRCT).et();
//        double RCTiEta      = caloRegions->at(iRCT).gctEta();
//        double RCTiPhi      = caloRegions->at(iRCT).gctPhi();
       
       //printf("RCT i=%d eta=%8.4f phi=%8.4f et=%8.4f",iRCT,RCTiEta,RCTiPhi,RCTRegionET);
       hRCTRegion_Et->Fill(RCTRegionET);
       if(RCTRegionET==511){
         cout << "=> Found saturated RCT";
         nRCTRegion_NSaturated++;
         nTotal_NSaturated++;
       }
     }
  }
  
  if(lEcalDigiHandle.isValid()){
    if(m_verbose){cout << "=> Got ECAL TT! They are " << lEcalDigiHandle->size() << endl;}
    
    for ( EcalTrigPrimDigiCollection::const_iterator lEcalTPItr = lEcalDigiHandle->begin(); lEcalTPItr != lEcalDigiHandle->end(); ++lEcalTPItr ){
      int32_t lET = 4 * lEcalScaleHandle->et( lEcalTPItr->compressedEt(), abs( lEcalTPItr->id().ieta() ),  ( lEcalTPItr->id().ieta() > 0 ? +1 : -1 ) );                     
      //cout << "ECAL TT et="<<lET<<endl; 
      hEcalTT_Et->Fill(lET);
      if(lET==255){
        cout << "=> Found saturated ECAL TT";
        nEcalTT_NSaturated++;
        nTotal_NSaturated++;
      }
    }
  }
  
  if(lHcalDigiHandle.isValid()){
    if(m_verbose){cout << "=> Got HCAL TT! They are " << lHcalDigiHandle->size() << endl;}
    
    for ( HcalTrigPrimDigiCollection::const_iterator lHcalTPItr = lHcalDigiHandle->begin(); lHcalTPItr != lHcalDigiHandle->end(); ++lHcalTPItr ){
      int32_t lET = 4 * lHcalScaleHandle->et( lHcalTPItr->SOI_compressedEt(), abs( lHcalTPItr->id().ieta() ),  ( lHcalTPItr->id().ieta() > 0 ? +1 : -1 ) );                 
      hHcalTT_Et->Fill(lET);
      if(lET==255){
        cout << "=> Found saturated HCAL TT";
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

  
  Handle<TriggerResults> hltresults;
  iEvent.getByLabel(m_InputTag_HLTResults, hltresults);
    
  for(unsigned i=0; i<m_selHLTrigger.size(); i++){
 
    string pName = m_selHLTrigger[i];
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
    
    if(testTrigger(iEvent,hltresults,pName)){
      hHLTAlgoCounts->Fill(pName.c_str(),1);
      
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
  
}

void TrigStudies::beginJob(){}

void TrigStudies::endJob(){}

void TrigStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  currentRunNumber    = iRun.run();
  double nSelHLTAlgos = m_selHLTrigger.size();
  
  TDirectory* runDir = fOut->mkdir(Form("Run_%d",currentRunNumber));
  
  // General plots
  hEventCount    = new TH1D("EventCount",   "EventCount"   ,   1, 0.5,  1.5); hEventCount  ->SetDirectory(runDir);

  hEcalTT_NSaturated    = new TH1D("hEcalTT_NSaturated   ","hEcalTT_NSaturated   ",11,-0.5,10.5); hEcalTT_NSaturated   ->SetDirectory(runDir);
  hHcalTT_NSaturated    = new TH1D("hHcalTT_NSaturated   ","hHcalTT_NSaturated   ",11,-0.5,10.5); hHcalTT_NSaturated   ->SetDirectory(runDir);
  hRCTRegion_NSaturated = new TH1D("hRCTRegion_NSaturated","hRCTRegion_NSaturated",11,-0.5,10.5); hRCTRegion_NSaturated->SetDirectory(runDir);
  hTotal_NSaturated     = new TH1D("hTotal_NSaturated    ","hTotal_NSaturated    ",11,-0.5,10.5); hTotal_NSaturated    ->SetDirectory(runDir);
  
  // TPG Plots
  hEcalTT_Et     = new TH1D("hEcalTT_Et",   "hEcalTT_Et",   1024,   0, 1024); hEcalTT_Et   ->SetDirectory(runDir);
  hHcalTT_Et     = new TH1D("hHcalTT_Et",   "hHcalTT_Et",   1024,   0, 1024); hHcalTT_Et   ->SetDirectory(runDir);     

  // RCT Plots
  hRCTRegion_Et  = new TH1D("hRCTRegion_Et","hRCTRegion_Et",1024,   0, 1024); hRCTRegion_Et->SetDirectory(runDir);
  
  // L1T Plots
  hL1AlgoCounts  = new TH1D("L1AlgoCounts", "L1AlgoCounts",  128,-0.5,127.5); hL1AlgoCounts->SetDirectory(runDir);
  hL1ETM         = new TH1D("L1ETM","L1ETM",500,  0,500);                     hL1ETM->SetDirectory(runDir);
  hL1HTT         = new TH1D("L1HTT","L1HTT",500,  0,500);                     hL1HTT->SetDirectory(runDir);
  
  // HLT Plots
  hHLTAlgoCounts      = new TH1D("HLTAlgoCounts",     "HLTAlgoCounts",     nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts     ->SetDirectory(runDir);
  hHLTAlgoCounts_ETM  = new TH1D("HLTAlgoCounts_ETM", "HLTAlgoCounts_ETM", nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_ETM ->SetDirectory(runDir);
  hHLTAlgoCounts_HTT  = new TH1D("HLTAlgoCounts_HTT", "HLTAlgoCounts_HTT", nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_HTT ->SetDirectory(runDir);
  hHLTAlgoCounts_Both = new TH1D("HLTAlgoCounts_Both","HLTAlgoCounts_Both",nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_Both->SetDirectory(runDir);
  hHLTAlgoCounts_None = new TH1D("HLTAlgoCounts_None","HLTAlgoCounts_None",nSelHLTAlgos,-0.5,nSelHLTAlgos-0.5); hHLTAlgoCounts_None->SetDirectory(runDir);
  
  
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
    hHLTAlgoCounts->GetXaxis()->SetBinLabel(i+1,m_selHLTrigger[i].c_str());
    cout << "Looking for HLT: " << m_selHLTrigger[i] << endl;
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
