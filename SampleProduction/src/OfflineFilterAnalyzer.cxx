#include "VBFHiggsToInvisible/SampleProduction/interface/OfflineFilterAnalyzer.h"

#include <stdio.h>
#include <math.h>

using namespace std;

OfflineFilterAnalyzer::OfflineFilterAnalyzer(const edm::ParameterSet& pset){
  
  ps = pset;
  
  // Getting input tags
  edm::InputTag inputTag_HLTResults   = pset.getUntrackedParameter("inputTag_HLTResults",  edm::InputTag("TriggerResults",  "HLT"));
  edm::InputTag inputTag_L1Extra_mets = pset.getUntrackedParameter("inputTag_L1Extra_mets",edm::InputTag("l1extraParticles","MET"));
  
  // Creating tokens
  m_InputTag_HLTResults   = consumes<edm::TriggerResults>                (inputTag_HLTResults);
  m_InputTag_L1Extra_mets = consumes<l1extra::L1EtMissParticleCollection>(inputTag_L1Extra_mets);
  
  // Creating output file
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","OfflineFilterAnalyzer_Results.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // This histogram will be used to count our events (for normalisation later)
  m_EventCount  = new TH1D("EventCount", "EventCount",   4,-0.5,3.5); m_EventCount ->SetDirectory(fOut);
  m_L1Extra_MET = new TH1D("L1Extra_MET","L1Extra_MET",500,   0,500); m_L1Extra_MET->SetDirectory(fOut);
}

OfflineFilterAnalyzer::~OfflineFilterAnalyzer(){
  
  fOut->Write();
  delete m_EventCount;
  delete m_L1Extra_MET;
}

void OfflineFilterAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  // Counting the current event
  m_EventCount->Fill(0);
  
  edm::Handle<edm::TriggerResults> handleTriggerResults;
  iEvent.getByToken(m_InputTag_HLTResults, handleTriggerResults);
  
  edm::Handle<l1extra::L1EtMissParticleCollection> mets;
  iEvent.getByToken(m_InputTag_L1Extra_mets,mets);
  
  //printHLTMenu (iEvent,handleTriggerResults);
  //printFiredHLT(iEvent,handleTriggerResults);
  
  if(testTrigger(iEvent,handleTriggerResults,"HLT_PFMET170_NoiseCleaned_v1")){m_EventCount->Fill(1);}
  if(testTrigger(iEvent,handleTriggerResults,"HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_v1")){m_EventCount->Fill(2);}
  if(testTrigger(iEvent,handleTriggerResults,"HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_v1")) {m_EventCount->Fill(3);}
  
  if(mets.isValid()){
    if (mets->size()!=0){

      m_L1Extra_MET->Fill(mets->begin()->et());
      
    }//else{cout << "[OfflineFilterAnalyzer] ERROR: l1extraParticles MET has size zero." << endl;}
  }//else{cout << "[OfflineFilterAnalyzer] ERROR: l1extraParticles MET is not valid." << endl;}
  
  
}

void OfflineFilterAnalyzer::beginJob(){}

void OfflineFilterAnalyzer::endJob(){}

void OfflineFilterAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void OfflineFilterAnalyzer::endRun(edm::Run const&, edm::EventSetup const&){}

void OfflineFilterAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void OfflineFilterAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// TODO: This function can be optimised by caching the trigger names once per run (not once per event)
bool OfflineFilterAnalyzer::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
  
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

void OfflineFilterAnalyzer::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
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

void OfflineFilterAnalyzer::printHLTMenu(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
  int ntrigs = iHLT->size();
  
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
  
  for (int itrig = 0; itrig != ntrigs; ++itrig){
    
    string trigName = m_triggerNames.triggerName(itrig); 
    
    if( !iHLT->wasrun(itrig) ) ;
    cout << itrig << " - " << trigName ;
    
    if(!iHLT->wasrun(itrig)){cout << " -> Was run!";}
    cout << endl;
  }
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(OfflineFilterAnalyzer);