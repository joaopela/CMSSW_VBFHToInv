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
  
  m_verbose                    = pset.getUntrackedParameter<bool>("verbose",false);

  m_InputTag_L1GTReadoutRecord      = pset.getParameter<InputTag>("inputTag_L1GTReadoutRecord");
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter ("inputTag_L1Extra_mets",InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter ("inputTag_L1Extra_mhts",InputTag("l1extraParticles","MHT"));
  m_InputTag_HLTResults             = pset.getParameter<InputTag>("inputTag_HLTResults");
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter ("inputTag_L1CaloRegionCollection",InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter ("inputTag_EcalTriggerPrimitives", InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter ("inputTag_HcalTriggerPrimitives", InputTag("hcalDigis"));

  m_selHLTrigger               = pset.getParameter<std::vector<string> >("selHLTrigger");
  
  for(unsigned i=0; i<m_selHLTrigger.size(); i++){
    cout << "Looking for HLT: " << m_selHLTrigger[i] << endl;
  }  

  currentRunNumber = 0;

  fOut = new TFile("TrigStudiesResults.root","RECREATE");
  
  hL1ETM = new TH1D("L1ETM","L1ETM",500,  0,500); hL1ETM->SetDirectory(fOut);
  hL1HTT = new TH1D("L1HTT","L1HTT",500,  0,500); hL1HTT->SetDirectory(fOut);
  
  hRCTRegion_Et = new TH1D("hRCTRegion_Et","hRCTRegion_Et",1024,  0,1024); hRCTRegion_Et->SetDirectory(fOut);
  hEcalTT_Et    = new TH1D("hEcalTT_Et","hEcalTT_Et",      1024,  0,1024); hEcalTT_Et   ->SetDirectory(fOut);
  hHcalTT_Et    = new TH1D("hHcalTT_Et","hHcalTT_Et",      1024,  0,1024); hHcalTT_Et   ->SetDirectory(fOut);  
}

TrigStudies::~TrigStudies(){
  
  unsigned nRuns = m_nEvents.size();
  TH1D* hRuns = new TH1D("Runs","Runs",nRuns,-0.5,nRuns-0.5);
  hRuns->SetDirectory(fOut);
  
  int bin=0;
  for(map<int,unsigned>::iterator i=m_nEvents.begin(); i!=m_nEvents.end(); i++){
    hRuns->GetXaxis()->SetBinLabel(bin+1,Form("%d",i->first));
    hRuns->SetBinContent(bin+1,i->second);
    bin++;
  }
  
  fOut->Write();
}

void TrigStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  currentRunNumber = iEvent.run();

  m_nEvents[currentRunNumber]++;
  TH1D* h = m_l1Counts[currentRunNumber];
        
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
    cout << "=> Got RCT Regions! They are " << caloRegions->size() << endl;    
     for(unsigned int iRCT=0;iRCT < caloRegions->size(); ++iRCT ) {

       double RCTRegionET  = 0.5*caloRegions->at(iRCT).et();
//        double RCTiEta      = caloRegions->at(iRCT).gctEta();
//        double RCTiPhi      = caloRegions->at(iRCT).gctPhi();
       
       //printf("RCT i=%d eta=%8.4f phi=%8.4f et=%8.4f",iRCT,RCTiEta,RCTiPhi,RCTRegionET);
       hRCTRegion_Et->Fill(RCTRegionET);
     }
  }
  
  if(lEcalDigiHandle.isValid()){
    
    cout << "=> Got ECAL TT! They are " << lEcalDigiHandle->size() << endl;
    for ( EcalTrigPrimDigiCollection::const_iterator lEcalTPItr = lEcalDigiHandle->begin(  ); lEcalTPItr != lEcalDigiHandle->end(  ); ++lEcalTPItr ){
      int32_t lET = 4 * lEcalScaleHandle->et( lEcalTPItr->compressedEt(), abs( lEcalTPItr->id().ieta() ),  ( lEcalTPItr->id().ieta() > 0 ? +1 : -1 ) );                     
      //cout << "ECAL TT et="<<lET<<endl; 
      hEcalTT_Et->Fill(lET);
    }
  }
  
  if(lHcalDigiHandle.isValid()){
    cout << "=> Got HCAL TT! They are " << lHcalDigiHandle->size() << endl;
    
    for ( HcalTrigPrimDigiCollection::const_iterator lHcalTPItr = lHcalDigiHandle->begin(); lHcalTPItr != lHcalDigiHandle->end(); ++lHcalTPItr ){
      int32_t lET = 4 * lHcalScaleHandle->et( lHcalTPItr->SOI_compressedEt(), abs( lHcalTPItr->id().ieta() ),  ( lHcalTPItr->id().ieta() > 0 ? +1 : -1 ) );                 
      cout << "HCAL TT et="<<lET<<endl;
      hHcalTT_Et->Fill(lET);
    }
  }

  if(gtReadoutRecordData.isValid()){
    
    const vector<L1GtFdlWord>& gtFdlVectorData = gtReadoutRecordData->gtFdlVector();
      
    // Running over FDL results to get which bits fired
    for(unsigned int a=0 ; a<gtFdlVectorData.size() ; a++){
        
      // Selecting the FDL that triggered
      if(gtFdlVectorData[a].bxInEvent() == 0){
          
        const L1GtFdlWord* fdl = &(gtFdlVectorData[a]);
          
        for(int bit=0; bit<128; bit++){
          if(fdl->gtDecisionWord()[bit]){h->Fill(bit);}
        }
      }
    }
  }else{cout << "[TrigStudies] ERROR: GT Readout Record Data is not valid." << endl;}
  
  if(mets.isValid()){
    if (mets->size()!=0){
      hL1ETM->Fill(mets->begin()->et());
    }else{cout << "[TrigStudies] ERROR: l1extraParticles MET has size zero." << endl;}
  }else{cout << "[TrigStudies] ERROR: l1extraParticles MET is not valid." << endl;}
  

  if(mhts.isValid()){
    if(mhts->size()!=0){
      hL1HTT->Fill(mhts->begin()->etTotal());
    }else{cout << "[TrigStudies] ERROR: l1extraParticles MHT has size zero." << endl;}
  }else{cout << "[TrigStudies] ERROR: l1extraParticles MHT is not valid." << endl;}

  
  Handle<TriggerResults> hltresults;
  iEvent.getByLabel(m_InputTag_HLTResults, hltresults);
  
  TH1D* cHLT = m_hltCounts[currentRunNumber];
  
  for(unsigned i=0; i<m_selHLTrigger.size(); i++){
    
    string pName = m_selHLTrigger[i];
    
    if(testTrigger(iEvent,hltresults,pName)){cHLT->Fill(pName.c_str(),1);}
  }
}

void TrigStudies::beginJob(){}

void TrigStudies::endJob(){}

void TrigStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  currentRunNumber = iRun.run();
  
  string hName = Form("L1AlgoCounts_Run%d",currentRunNumber);
  m_nEvents [currentRunNumber] = 0;
  
  TH1D* h = new TH1D(hName.c_str(),hName.c_str(),128,-0.5,127.5);
  h->SetDirectory(fOut);
  m_l1Counts[currentRunNumber] = h;
  
  ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);
  const L1GtTriggerMenu* menu = menuRcd.product();
    
  // Filling Alias-Bit Map
  for (CItAlgo algo = menu->gtAlgorithmAliasMap().begin(); algo!=menu->gtAlgorithmAliasMap().end(); ++algo){
    h->GetXaxis()->SetBinLabel((algo->second).algoBitNumber()+1,(algo->second).algoAlias().c_str());
  }
  
  hName = Form("HLTAlgoCounts_Run%d",currentRunNumber);
  h     = new TH1D(hName.c_str(),hName.c_str(),m_selHLTrigger.size(),-0.5,m_selHLTrigger.size()-0.5);
  h->SetDirectory(fOut);
  m_hltCounts[currentRunNumber] = h;
  
  for(unsigned i=0; i<m_selHLTrigger.size(); i++){
    h->GetXaxis()->SetBinLabel(i+1,m_selHLTrigger[i].c_str());
    cout << "Looking for HLT: " << m_selHLTrigger[i] << endl;
  }    
}

void TrigStudies::endRun(edm::Run const&, edm::EventSetup const&){}

void TrigStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void TrigStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

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
