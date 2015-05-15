#include "VBFHiggsToInvisible/SampleProduction/interface/OfflineFilterAnalyzer.h"

#include <stdio.h>
#include <math.h>

using namespace std;

OfflineFilterAnalyzer::OfflineFilterAnalyzer(const edm::ParameterSet& pset){
  
  ps = pset;
  
  // Getting input tags
  edm::InputTag inputTag_HepMCProduct     = pset.getUntrackedParameter("inputTag_HepMCProduct",    edm::InputTag("generator"));
  edm::InputTag inputTag_HLTResults       = pset.getUntrackedParameter("inputTag_HLTResults",      edm::InputTag("TriggerResults",  "HLT"));
  edm::InputTag inputTag_L1Extra_mets     = pset.getUntrackedParameter("inputTag_L1Extra_mets",    edm::InputTag("l1extraParticles","MET"));
  edm::InputTag inputTag_GenJetCollection = pset.getUntrackedParameter("inputTag_GenJetCollection",edm::InputTag("ak5GenJetsNoNu"));
  
  // Creating tokens
  m_InputTag_HepMCProduct     = consumes<edm::HepMCProduct>                       (inputTag_HepMCProduct);
  m_InputTag_GenJetCollection = consumes<reco::GenJetCollection>             (inputTag_GenJetCollection);
  m_InputTag_L1Extra_mets     = consumes<l1extra::L1EtMissParticleCollection>(inputTag_L1Extra_mets);
  m_InputTag_HLTResults       = consumes<edm::TriggerResults>                (inputTag_HLTResults);
  
  // Creating output file
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","OfflineFilterAnalyzer_Results.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // This histogram will be used to count our events (for normalisation later)
  m_EventCount  = new TH1D("EventCount", "EventCount",   4,-0.5,3.5); m_EventCount ->SetDirectory(fOut);
  m_L1Extra_MET = new TH1D("L1Extra_MET","L1Extra_MET",500,   0,500); m_L1Extra_MET->SetDirectory(fOut);
  
  m_GenNeutrinoMET         = new TH1D("m_GenNeutrinoMET",      "m_GenNeutrinoMET",      1000,0,1000);            m_GenNeutrinoMET        ->SetDirectory(fOut);
  m_GenNeutrinoMET_L1MET40 = new TH1D("GenNeutrinoMET_L1MET40","GenNeutrinoMET_L1MET40",1000,0,1000);            m_GenNeutrinoMET_L1MET40->SetDirectory(fOut);
  m_GenNeutrinoMET_L1MET60 = new TH1D("GenNeutrinoMET_L1MET60","GenNeutrinoMET_L1MET60",1000,0,1000);            m_GenNeutrinoMET_L1MET60->SetDirectory(fOut);
  m_GenNeutrinoMET_L1MET70 = new TH1D("GenNeutrinoMET_L1MET70","GenNeutrinoMET_L1MET70",1000,0,1000);            m_GenNeutrinoMET_L1MET70->SetDirectory(fOut);
  m_GenNeutrinoMET_L1MET   = new TH2D("GenNeutrinoMET_L1MET","  GenNeutrinoMET_L1MET",   500,0,1000,500,0,1000); m_GenNeutrinoMET_L1MET  ->SetDirectory(fOut);
  
}

OfflineFilterAnalyzer::~OfflineFilterAnalyzer(){
  
  fOut->Write();
  delete m_EventCount;
  delete m_L1Extra_MET;
  delete m_GenNeutrinoMET_L1MET40;
  delete m_GenNeutrinoMET_L1MET60;
  delete m_GenNeutrinoMET_L1MET70;
  delete m_GenNeutrinoMET_L1MET;
}

void OfflineFilterAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  // Counting the current event
  m_EventCount->Fill(0);
  
  edm::Handle<edm::TriggerResults> handleTriggerResults;
  iEvent.getByToken(m_InputTag_HLTResults, handleTriggerResults);
  
  edm::Handle<l1extra::L1EtMissParticleCollection> mets;
  iEvent.getByToken(m_InputTag_L1Extra_mets,mets);
  
  double genNeutrinoMET = getGenNeutrinoMET(iEvent);
  
  //printHLTMenu (iEvent,handleTriggerResults);
  //printFiredHLT(iEvent,handleTriggerResults);
  
  if(testTrigger(iEvent,handleTriggerResults,"HLT_PFMET170_NoiseCleaned_v1")){m_EventCount->Fill(1);}
  if(testTrigger(iEvent,handleTriggerResults,"HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_v1")){m_EventCount->Fill(2);}
  if(testTrigger(iEvent,handleTriggerResults,"HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_v1")) {m_EventCount->Fill(3);}
  
  if(mets.isValid()){
    if (mets->size()!=0){

      double l1MET = mets->begin()->et();
      
      m_L1Extra_MET         ->Fill(l1MET);
      m_GenNeutrinoMET      ->Fill(genNeutrinoMET);
      m_GenNeutrinoMET_L1MET->Fill(genNeutrinoMET,l1MET);
      if(l1MET>=40){m_GenNeutrinoMET_L1MET40->Fill(genNeutrinoMET);}
      if(l1MET>=60){m_GenNeutrinoMET_L1MET60->Fill(genNeutrinoMET);}
      if(l1MET>=60){m_GenNeutrinoMET_L1MET70->Fill(genNeutrinoMET);}
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

double OfflineFilterAnalyzer::getGenNeutrinoMET(const edm::Event& iEvent){
  
  edm::Handle<edm::HepMCProduct> handle_genEvent;
  iEvent.getByToken(m_InputTag_HepMCProduct, handle_genEvent);
  const HepMC::GenEvent* genEvent = handle_genEvent->GetEvent();
  
  vector<HepMC::GenParticle*> vecNeutrino;
  
  for ( HepMC::GenEvent::particle_const_iterator p = genEvent->particles_begin(); p != genEvent->particles_end(); ++p ) {
    if     ((*p)->status()==1 && abs((*p)->pdg_id()) == 12){vecNeutrino.push_back(*p);}
    else if((*p)->status()==1 && abs((*p)->pdg_id()) == 14){vecNeutrino.push_back(*p);}
    else if((*p)->status()==1 && abs((*p)->pdg_id()) == 16){vecNeutrino.push_back(*p);}      
  }
  
  if(vecNeutrino.size()==0){return 0.;}
  if(vecNeutrino.size()==1){return vecNeutrino[0]->momentum().perp();}
  
  double nuPx=0.;
  double nuPy=0.;
  
  for(unsigned i=0; i<vecNeutrino.size(); i++) {
    nuPx += vecNeutrino[i]->momentum().px();
    nuPy += vecNeutrino[i]->momentum().py();
  }

  return sqrt(pow(nuPx,2)+pow(nuPy,2));
}


//define this as a plug-in
DEFINE_FWK_MODULE(OfflineFilterAnalyzer);