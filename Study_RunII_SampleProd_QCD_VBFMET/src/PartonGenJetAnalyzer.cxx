#include "CMSSW_VBFHToInv/Study_RunII_SampleProd_QCD_VBFMET/interface/PartonGenJetAnalyzer.h"

#include "DataFormats/Math/interface/deltaR.h"

#include <stdio.h>
#include <math.h>

using namespace std;

struct greater_GenParticle{
  bool operator() (const HepMC::GenParticle* j1,const HepMC::GenParticle* j2) {
    return (j1->momentum().perp() > j2->momentum().perp());
  }
};

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
  m_EventCount  = new TH1D("EventCount","EventCount",1,-0.5,0.5); m_EventCount->SetDirectory(fOut);
  m_Counters    = new TH1D("Counters",  "Counters",  1, 0.5,1.5); m_Counters  ->SetDirectory(fOut);
  m_Counters->GetXaxis()->SetBinLabel(1,"Jet Matched not lowest DeltaR");
  
  m_Parton_NMatched = new TH1D("Parton_NMatched","Parton_NMatched",10,-0.5,9.5); m_Parton_NMatched->SetDirectory(fOut);
  
  m_Parton_N    = new TH1D("Parton_N",   "Parton_N",   11,-0.5,10.5); m_Parton_N   ->SetDirectory(fOut);
  m_Parton_Type = new TH1D("Parton_Type","Parton_Type", 2,-0.5, 2.5); m_Parton_Type->SetDirectory(fOut);
  m_Parton_Type->GetXaxis()->SetBinLabel(1,"Status 23");
  m_Parton_Type->GetXaxis()->SetBinLabel(2,"Status 24");
  
  m_Parton_Jet1_Pt = new TH1D("Parton_Jet1_Pt","Parton_Jet1_Pt",500,  0,500); m_Parton_Jet1_Pt->SetDirectory(fOut);
  m_Parton_Jet2_Pt = new TH1D("Parton_Jet2_Pt","Parton_Jet2_Pt",500,  0,500); m_Parton_Jet2_Pt->SetDirectory(fOut);
  m_Parton_Jet3_Pt = new TH1D("Parton_Jet3_Pt","Parton_Jet3_Pt",500,  0,500); m_Parton_Jet3_Pt->SetDirectory(fOut);
  m_Parton_Jet4_Pt = new TH1D("Parton_Jet4_Pt","Parton_Jet4_Pt",500,  0,500); m_Parton_Jet4_Pt->SetDirectory(fOut);
  
  m_Parton_Jet1_Eta = new TH1D("Parton_Jet1_Eta","Parton_Jet1_Eta",100, -5,   5); m_Parton_Jet1_Eta->SetDirectory(fOut);
  m_Parton_Jet2_Eta = new TH1D("Parton_Jet2_Eta","Parton_Jet2_Eta",100, -5,   5); m_Parton_Jet2_Eta->SetDirectory(fOut);
  m_Parton_Jet3_Eta = new TH1D("Parton_Jet3_Eta","Parton_Jet3_Eta",100, -5,   5); m_Parton_Jet3_Eta->SetDirectory(fOut);
  m_Parton_Jet4_Eta = new TH1D("Parton_Jet4_Eta","Parton_Jet4_Eta",100, -5,   5); m_Parton_Jet4_Eta->SetDirectory(fOut);
  
  m_Parton_Dijet1_DEta = new TH1D("Parton_Dijet1_DEta","Parton_Dijet1_DEta",100,  0,  10); m_Parton_Dijet1_DEta->SetDirectory(fOut);
  m_Parton_Dijet1_Mjj  = new TH1D("Parton_Dijet1_Mjj" ,"Parton_Dijet1_Mjj" ,500,  0,5000); m_Parton_Dijet1_Mjj ->SetDirectory(fOut);
  
  m_PartonvsGenJet_DiffPt  = new TH1D("PartonvsGenJet_DiffPt", "PartonvsGenJet_DiffPt", 100, 0,100); m_PartonvsGenJet_DiffPt ->SetDirectory(fOut);
  m_PartonvsGenJet_DiffEta = new TH1D("PartonvsGenJet_DiffEta","PartonvsGenJet_DiffEta",200,-1,  1); m_PartonvsGenJet_DiffEta->SetDirectory(fOut);
  
  m_Profile_PartonvsGenJet_DiffPt  = new TProfile("Profile_PartonvsGenJet_DiffPt", "Profile_PartonvsGenJet_DiffPt" ,500,  0,500); m_Profile_PartonvsGenJet_DiffPt ->SetDirectory(fOut);
  m_Profile_PartonvsGenJet_DiffEta = new TProfile("Profile_PartonvsGenJet_DiffEta","Profile_PartonvsGenJet_DiffEta",100, -5,  5); m_Profile_PartonvsGenJet_DiffEta->SetDirectory(fOut);
  
  m_PartonvsGenJet_Pt  = new TH2D("PartonvsGenJet_Pt", "PartonvsGenJet_Pt",  500,  0,500, 500,  0,500); m_PartonvsGenJet_Pt ->SetDirectory(fOut);
  m_PartonvsGenJet_Eta = new TH2D("PartonvsGenJet_Eta","PartonvsGenJet_Eta", 100, -5,  5, 100, -5,  5); m_PartonvsGenJet_Eta->SetDirectory(fOut);
  
  m_PartonvsGenJet_minDr_Pt  = new TH2D("PartonvsGenJet_minDr_Pt", "PartonvsGenJet_Pt",  500,  0,500, 500,  0,500); m_PartonvsGenJet_minDr_Pt ->SetDirectory(fOut);
  m_PartonvsGenJet_minDr_Eta = new TH2D("PartonvsGenJet_minDr_Eta","PartonvsGenJet_Eta", 100, -5,  5, 100, -5,  5); m_PartonvsGenJet_minDr_Eta->SetDirectory(fOut);
  
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
      m_Parton_Type->Fill(0);
      hardScatterParticles.push_back(*p);
      //cout << "Particle st=23 id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
    }
    if((*p)->status()==24){
      m_Parton_Type->Fill(1);
      hardScatterParticles.push_back(*p);
      //cout << "Particle st=24 id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
    }
  }
  
  sort(hardScatterParticles.begin(),hardScatterParticles.end(),greater_GenParticle());
  
  m_Parton_N->Fill(hardScatterParticles.size());
  
  // Filling parton pT
  if(hardScatterParticles.size()>0){
    m_Parton_Jet1_Pt ->Fill(hardScatterParticles[0]->momentum().perp());
    m_Parton_Jet1_Eta->Fill(hardScatterParticles[0]->momentum().eta());
  }
  if(hardScatterParticles.size()>1){
    m_Parton_Jet2_Pt ->Fill(hardScatterParticles[1]->momentum().perp());
    m_Parton_Jet2_Eta->Fill(hardScatterParticles[1]->momentum().eta());
  }
  if(hardScatterParticles.size()>2){
    m_Parton_Jet3_Pt ->Fill(hardScatterParticles[2]->momentum().perp());
    m_Parton_Jet3_Eta->Fill(hardScatterParticles[2]->momentum().eta());
  }
  if(hardScatterParticles.size()>3){
    m_Parton_Jet4_Pt ->Fill(hardScatterParticles[3]->momentum().perp());
    m_Parton_Jet4_Eta->Fill(hardScatterParticles[3]->momentum().eta());
  }
  
  // Mow matching partons to jets
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
      m_Counters->Fill(1);
    }else{
//       cout << "Found a match." << endl;
      genJet_matched = genJet_minDiffDr;
    }
    
    m_PartonvsGenJet_minDr_Pt ->Fill(parton->momentum().perp(),genJet_minDiffDr->pt());
    m_PartonvsGenJet_minDr_Eta->Fill(parton->momentum().eta(), genJet_minDiffDr->eta());
    
    m_PartonvsGenJet_Pt ->Fill(parton->momentum().perp(),genJet_matched->pt());
    m_PartonvsGenJet_Eta->Fill(parton->momentum().eta(), genJet_matched->eta());
    
    m_PartonvsGenJet_DiffPt ->Fill(parton->momentum().perp()-genJet_matched->pt());
    m_PartonvsGenJet_DiffEta->Fill(parton->momentum().eta()-genJet_matched->eta());
    
    m_Profile_PartonvsGenJet_DiffPt ->Fill(parton->momentum().perp(),fabs(parton->momentum().perp()-genJet_matched->pt()));
    m_Profile_PartonvsGenJet_DiffEta->Fill(parton->momentum().eta(), fabs(parton->momentum().eta()-genJet_matched->eta()));
    
  }
  
  m_Parton_NMatched->Fill(totalMatched);
  
  // For next calculations we need at least 2 jets
  if(hardScatterParticles.size()<2){return;}
  
  // Filling lead dijet 
  m_Parton_Dijet1_DEta->Fill(getGenPaticle_deta(hardScatterParticles[0],hardScatterParticles[1]));
  m_Parton_Dijet1_Mjj ->Fill(getGenPaticle_mjj (hardScatterParticles[0],hardScatterParticles[1]));
  
}

void PartonGenJetAnalyzer::beginJob(){}

void PartonGenJetAnalyzer::endJob(){}

void PartonGenJetAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void PartonGenJetAnalyzer::endRun(edm::Run const&, edm::EventSetup const&){}

void PartonGenJetAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void PartonGenJetAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

double PartonGenJetAnalyzer::getGenPaticle_mjj(HepMC::GenParticle *p0, HepMC::GenParticle *p1){
  
  double px     = p0->momentum().px() + p1->momentum().px();
  double py     = p0->momentum().py() + p1->momentum().py();
  double pz     = p0->momentum().pz() + p1->momentum().pz();
  double energy = p0->momentum().e()  + p1->momentum().e();
  double mass   = sqrt(pow(energy,2) - (pow(px,2) + pow(py,2) + pow(pz,2)));
  
  return mass;
  
}

double PartonGenJetAnalyzer::getGenPaticle_deta(HepMC::GenParticle *p0, HepMC::GenParticle *p1){
  
  return fabs(p0->momentum().eta()-p1->momentum().eta());
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(PartonGenJetAnalyzer);