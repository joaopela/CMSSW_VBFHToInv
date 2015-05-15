#include "CMSSW-VBFHToInv/SampleProduction/interface/GenFilterAnalyzer.h"

#include <HepMC/GenVertex.h>

// ROOT includes
#include "TMath.h"

// C++ includes
#include <iostream>

using namespace edm;
using namespace std;


GenFilterAnalyzer::GenFilterAnalyzer(const edm::ParameterSet& iConfig){
  
  m_fileOutput = new TFile(iConfig.getUntrackedParameter("outFile",std::string("GenFilterAnalyzer.root")).c_str(),"RECREATE");
  TDirectory* plots = m_fileOutput->mkdir("plots");
  
  m_inputTag_GenJetCollection = consumes<reco::GenJetCollection>(iConfig.getUntrackedParameter<edm::InputTag>("inputTag_GenJetCollection",edm::InputTag("ak5GenJetsNoNu")));
  
  edm::VParameterSet workingPoints = iConfig.getParameterSetVector("workingPoints");
  
  m_EventCount = new TH1D("EventCount","EventCount",workingPoints.size()+1,-1.5,workingPoints.size()-0.5);
  m_EventCount->GetXaxis()->SetBinLabel(1,"Total");
  for(unsigned i=0; i<workingPoints.size(); i++){
    
    string name = workingPoints[i].getUntrackedParameter<string>("name","Unnamed Algo");
    m_EventCount->GetXaxis()->SetBinLabel(i+2,name.c_str());
    
    GenFilterAlgo* iAlgo = new GenFilterAlgo(workingPoints[i]);
    
    TDirectory* d = m_fileOutput->mkdir(name.c_str());
    
    iAlgo->buildPlots(d);
    iAlgo->print();
    
    m_algos.push_back(iAlgo);
  }
  m_EventCount->SetDirectory(m_fileOutput);

  m_Jets_Multiplicity = new TH1D("Jets_Multiplicity","Jets_Multiplicity",  50,-0.5,       49.5); m_Jets_Multiplicity->SetDirectory(plots);
  m_Jet0_Pt           = new TH1D("Jet0_Pt",          "Jet0_Pt",          1000,   0,       2000); m_Jet0_Pt          ->SetDirectory(plots);
  m_Jet1_Pt           = new TH1D("Jet1_Pt",          "Jet1_Pt",          1000,   0,       2000); m_Jet1_Pt          ->SetDirectory(plots);
  m_Dijet_MaxMjj      = new TH1D("Dijet_MaxMjj",     "Dijet_MaxMjj",      500,   0,       5000); m_Dijet_MaxMjj     ->SetDirectory(plots);
  m_Dijet_MaxDEta     = new TH1D("Dijet_MaxDEta",    "Dijet_MaxDEta",     200,   0,         10); m_Dijet_MaxDEta    ->SetDirectory(plots);
  m_Dijet_MinDPhi     = new TH1D("Dijet_MinDPhi",    "Dijet_MinDPhi",     128,   0,TMath::Pi()); m_Dijet_MinDPhi    ->SetDirectory(plots);
  
}

GenFilterAnalyzer::~GenFilterAnalyzer(){
  
  m_fileOutput->Write();
  m_fileOutput->Close();
}

void GenFilterAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  using namespace edm;
  
  m_EventCount->Fill(-1);
  
  Handle< vector<reco::GenJet> > handleGenJets;
  iEvent.getByToken(m_inputTag_GenJetCollection, handleGenJets);
  const vector<reco::GenJet>* genJets = handleGenJets.product();
  
  for(unsigned i=0; i<m_algos.size(); i++){
    if(m_algos[i]->evaluate(genJets)){
      m_EventCount->Fill(i);
    }
  }
  
  double minDPhi = 999;
  double maxDEta =   0;
  double maxMjj  =   0;
  
  for(unsigned a=0; a<genJets->size(); a++){
    for(unsigned b=a+1; b<genJets->size(); b++){    
      
      const reco::GenJet* pA = &((*genJets)[a]);
      const reco::GenJet* pB = &((*genJets)[b]);
      
      // Getting the dijet vector
      math::XYZTLorentzVector diJet = pA->p4() + pB->p4();
      
      // Calculating quantities
      double dPhi    = fabs(pA->p4().phi()-pB->p4().phi());
      double dEta    = fabs(pA->p4().eta()-pB->p4().eta());
      double invMass = diJet.mass();
      
      // Updating max/min variables
      if(dPhi<minDPhi)  {minDPhi=dPhi;}
      if(dEta>maxDEta)  {maxDEta=dEta;}
      if(invMass>maxMjj){maxMjj=invMass;}
    }
  }
  
  m_Jets_Multiplicity->Fill(genJets->size());
  if(genJets->size()>1){
    m_Jet0_Pt      ->Fill((*genJets)[0].pt());
    m_Jet1_Pt      ->Fill((*genJets)[1].pt());
    m_Dijet_MaxMjj ->Fill(maxMjj);
    m_Dijet_MaxDEta->Fill(maxDEta);
    m_Dijet_MinDPhi->Fill(minDPhi);
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenFilterAnalyzer);