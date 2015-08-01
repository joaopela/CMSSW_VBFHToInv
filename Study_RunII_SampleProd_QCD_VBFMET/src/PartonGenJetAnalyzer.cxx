#include "CMSSW_VBFHToInv/Study_RunII_SampleProd_QCD_VBFMET/interface/PartonGenJetAnalyzer.h"

#include "DataFormats/Math/interface/deltaR.h"

#include <stdio.h>
#include <math.h>

using namespace std;

PartonGenJetAnalyzer::PartonGenJetAnalyzer(const edm::ParameterSet& pset){
  
  ps = pset;
  
  // Getting input tags
  edm::InputTag inputTag_HepMCProduct     = pset.getUntrackedParameter("inputTag_HepMCProduct",edm::InputTag("generator"));
  edm::InputTag inputTag_GenJetCollection = pset.getUntrackedParameter<edm::InputTag>("inputTag_GenJetCollection",edm::InputTag("ak4GenJetsNoNu"));
  
  // Creating tokens
  m_InputTag_HepMCProduct     = consumes<edm::HepMCProduct>     (inputTag_HepMCProduct);
  m_inputTag_GenJetCollection = consumes<reco::GenJetCollection>(inputTag_GenJetCollection);
  
  // Creating output file
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","PartonGenJetAnalyzer_Results.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // This histogram will be used to count our events (for normalisation later)
  m_EventCount  = new TH1D("EventCount", "EventCount",   4,-0.5,3.5); m_EventCount ->SetDirectory(fOut);
  
  m_MatchingResults = new TH1D("MatchingResults","MatchingResults",4,0.5,4.5); m_MatchingResults->SetDirectory(fOut);
  m_MatchingResults->GetXaxis()->SetBinLabel(1,"Matched 2");
  m_MatchingResults->GetXaxis()->SetBinLabel(2,"Matched 1");
  m_MatchingResults->GetXaxis()->SetBinLabel(3,"Matched 0");
  m_MatchingResults->GetXaxis()->SetBinLabel(4,"Jet Matched not lowest DeltaR");
  
  m_Parton_N = new TH1D("Parton_N","Parton_N",11,-0.5,10.5); m_Parton_N->SetDirectory(fOut);
  
  m_Profile_PartonvsGenJet_DiffPt  = new TProfile("Profile_PartonvsGenJet_DiffPt", "Profile_PartonvsGenJet_DiffPt" ,500,  0,500); m_Profile_PartonvsGenJet_DiffPt ->SetDirectory(fOut);
  m_Profile_PartonvsGenJet_DiffEta = new TProfile("Profile_PartonvsGenJet_DiffEta","Profile_PartonvsGenJet_DiffEta",100, -5,  5); m_Profile_PartonvsGenJet_DiffEta->SetDirectory(fOut);
  
  m_PartonvsGenJet_Pt  = new TH2D("PartonvsGenJet_Pt", "PartonvsGenJet_Pt",  500,  0,500, 500,  0,500); m_PartonvsGenJet_Pt ->SetDirectory(fOut);
  m_PartonvsGenJet_Eta = new TH2D("PartonvsGenJet_Eta","PartonvsGenJet_Eta", 100, -5,  5, 100, -5,  5); m_PartonvsGenJet_Eta->SetDirectory(fOut);
  
  m_PartonvsGenJet_minDr_Pt  = new TH2D("PartonvsGenJet_minDr_Pt", "PartonvsGenJet_Pt",  500,  0,500, 500,  0,500); m_PartonvsGenJet_minDr_Pt ->SetDirectory(fOut);
  m_PartonvsGenJet_minDr_Eta = new TH2D("PartonvsGenJe_minDrt_Eta","PartonvsGenJet_Eta", 100, -5,  5, 100, -5,  5); m_PartonvsGenJet_minDr_Eta->SetDirectory(fOut);
  
}

PartonGenJetAnalyzer::~PartonGenJetAnalyzer(){
  
  fOut->Write();
  delete m_EventCount;
}

void PartonGenJetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  // Counting the current event
  m_EventCount->Fill(0);
  
//   cout << "==> Stating analysis" << endl;

  edm::Handle<edm::HepMCProduct> handle_genEvent;
  iEvent.getByToken(m_InputTag_HepMCProduct, handle_genEvent);
  const HepMC::GenEvent* genEvent = handle_genEvent->GetEvent();
  
  edm::Handle< vector<reco::GenJet> > handleGenJets;
  iEvent.getByToken(m_inputTag_GenJetCollection, handleGenJets);
  const vector<reco::GenJet>* genJets = handleGenJets.product();
  
  vector<HepMC::GenParticle*> hardScatterParticles;
  
  for ( HepMC::GenEvent::particle_const_iterator p = genEvent->particles_begin(); p != genEvent->particles_end(); ++p ) {
//     cout << "Particle st=" << (*p)->status() << " id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
    if((*p)->status()==23){
      hardScatterParticles.push_back(*p);
      //cout << "Particle st=23 id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
    }
    if((*p)->status()==24){
      hardScatterParticles.push_back(*p);
      //cout << "Particle st=24 id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
    }
  }
  
  m_Parton_N->Fill(hardScatterParticles.size());
  if(hardScatterParticles.size()!=2){return;}
  
  int totalMatched = 0;
  
  for(unsigned i=0; i<hardScatterParticles.size(); i++) {
    
    HepMC::GenParticle *parton = hardScatterParticles[i];
    vector<const reco::GenJet*> genJets_matched;
    const reco::GenJet* genJet_matched = 0;
    
    for(unsigned a=0; a<genJets->size(); a++){
      
      const reco::GenJet* genJet = &((*genJets)[a]);
      double dR = deltaR(parton->momentum().eta(),parton->momentum().phi(),genJet->eta(),genJet->phi());
      
      if(dR<0.4){
//         cout << "Fount a match for parton=" << i << " pt=" << parton->momentum().perp() << " eta=" << parton->momentum().eta() << " phi=" << parton->momentum().phi() 
//         << " genJet pt=" << genJet->pt() << " eta=" << genJet->eta() << " phi=" << genJet->phi() << " dR=" << dR << endl;
        genJets_matched.push_back(genJet);
      }
    }
    
    if(genJets_matched.size()==0){
//       cout << "=> Did not find a match for parton " << i << endl;
      continue;
    }
    
    totalMatched++;
    
    double minDiffPt = 999999;
    double minDiffDr = 999999;
    
    const reco::GenJet* genJet_minDiffPt = 0;
    const reco::GenJet* genJet_minDiffDr = 0;
    
    for(unsigned a=0; a<genJets_matched.size(); a++){
      const reco::GenJet* genJet = genJets_matched[a];
      
      double diffPt  = fabs(parton->momentum().perp()-genJet->pt());
      double dR      = deltaR(parton->momentum().eta(),parton->momentum().phi(),genJet->eta(),genJet->phi());
      
      if(diffPt<minDiffPt){
        minDiffPt=diffPt;
        genJet_minDiffPt = genJet;
      }
      if(dR<minDiffDr){
        minDiffDr=dR;
        genJet_minDiffDr = genJet;
      }
      
    }
    
    if(genJet_minDiffPt!=genJet_minDiffDr){
//       cout << "Found a match but its not the minDr!" << endl;
      genJet_matched = genJet_minDiffPt;
      m_MatchingResults->Fill(4);
    }else{
//       cout << "Found a match." << endl;
      genJet_matched = genJet_minDiffDr;
    }
    
    m_PartonvsGenJet_minDr_Pt ->Fill(parton->momentum().perp(),genJet_minDiffDr->pt());
    m_PartonvsGenJet_minDr_Eta->Fill(parton->momentum().eta(), genJet_minDiffDr->eta());
    
    m_PartonvsGenJet_Pt ->Fill(parton->momentum().perp(),genJet_matched->pt());
    m_PartonvsGenJet_Eta->Fill(parton->momentum().eta(), genJet_matched->eta());
    
    m_Profile_PartonvsGenJet_DiffPt ->Fill(parton->momentum().perp(),parton->momentum().perp()-genJet_matched->pt());
    m_Profile_PartonvsGenJet_DiffEta->Fill(parton->momentum().eta(), parton->momentum().eta()-genJet_matched->eta());
  }
  
  if     (totalMatched==0){m_MatchingResults->Fill(3);}
  else if(totalMatched==1){m_MatchingResults->Fill(2);}
  else if(totalMatched==2){m_MatchingResults->Fill(1);}
}

void PartonGenJetAnalyzer::beginJob(){}

void PartonGenJetAnalyzer::endJob(){}

void PartonGenJetAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void PartonGenJetAnalyzer::endRun(edm::Run const&, edm::EventSetup const&){}

void PartonGenJetAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void PartonGenJetAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}


//define this as a plug-in
DEFINE_FWK_MODULE(PartonGenJetAnalyzer);