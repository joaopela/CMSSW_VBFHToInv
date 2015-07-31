#include "CMSSW_VBFHToInv/Study_RunII_SampleProd_QCD_VBFMET/interface/PartonGenJetAnalyzer.h"

#include <stdio.h>
#include <math.h>

using namespace std;

PartonGenJetAnalyzer::PartonGenJetAnalyzer(const edm::ParameterSet& pset){
  
  ps = pset;
  
  // Getting input tags
  edm::InputTag inputTag_HepMCProduct     = pset.getUntrackedParameter("inputTag_HepMCProduct",edm::InputTag("generator"));
  
  // Creating tokens
  m_InputTag_HepMCProduct     = consumes<edm::HepMCProduct>                       (inputTag_HepMCProduct);
  
  // Creating output file
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","PartonGenJetAnalyzer_Results.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // This histogram will be used to count our events (for normalisation later)
  m_EventCount  = new TH1D("EventCount", "EventCount",   4,-0.5,3.5); m_EventCount ->SetDirectory(fOut);
  
}

PartonGenJetAnalyzer::~PartonGenJetAnalyzer(){
  
  fOut->Write();
  delete m_EventCount;
}

void PartonGenJetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  // Counting the current event
  m_EventCount->Fill(0);
  

  edm::Handle<edm::HepMCProduct> handle_genEvent;
  iEvent.getByToken(m_InputTag_HepMCProduct, handle_genEvent);
  const HepMC::GenEvent* genEvent = handle_genEvent->GetEvent();
  
  for ( HepMC::GenEvent::particle_const_iterator p = genEvent->particles_begin(); p != genEvent->particles_end(); ++p ) {
    if((*p)->status()==3){cout << "Particle st=3 id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;}
  }
  
}

void PartonGenJetAnalyzer::beginJob(){}

void PartonGenJetAnalyzer::endJob(){}

void PartonGenJetAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void PartonGenJetAnalyzer::endRun(edm::Run const&, edm::EventSetup const&){}

void PartonGenJetAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void PartonGenJetAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}


//define this as a plug-in
DEFINE_FWK_MODULE(PartonGenJetAnalyzer);