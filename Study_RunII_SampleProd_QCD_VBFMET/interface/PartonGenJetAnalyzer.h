#ifndef VBFHiggsToInvisible_Study_RunII_SampleProd_QCD_VBF_MET_PartonGenJetAnalyzer
#define VBFHiggsToInvisible_Study_RunII_SampleProd_QCD_VBF_MET_PartonGenJetAnalyzer

// CMSSW includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

// ROOT includes
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TFile.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>

class PartonGenJetAnalyzer : public edm::EDAnalyzer {
public:
  
  PartonGenJetAnalyzer(const edm::ParameterSet&);
  ~PartonGenJetAnalyzer();
  
private:
  void beginJob() ;
  void endJob() ;
  
  void beginRun(edm::Run const&, edm::EventSetup const&);
  void endRun(edm::Run const&, edm::EventSetup const&);
  
  void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  void analyze(const edm::Event&, const edm::EventSetup&);
  
  double getGenPaticle_mjj (HepMC::GenParticle *p0, HepMC::GenParticle *p1);
  double getGenPaticle_deta(HepMC::GenParticle *p0, HepMC::GenParticle *p1);
  
  // ----------member data ---------------------------
  
  bool m_verbose;
  
  // Parameter related variables
  edm::ParameterSet ps;
  edm::EDGetTokenT<edm::HepMCProduct> m_InputTag_HepMCProduct;
  edm::EDGetTokenT< reco::GenJetCollection > m_inputTag_GenJetCollection;
  
  // Output file
  TFile* fOut;
  
  // Histograms
  TH1D *m_EventCount;
  TH1D *m_Counters;
  
  TH1D* m_Parton_N;
  TH1D *m_Parton_NMatched;
  TH1D* m_Parton_Type;
  
  TH1D *m_Parton_Jet1_Pt, *m_Parton_Jet2_Pt, *m_Parton_Jet3_Pt, *m_Parton_Jet4_Pt;
  TH1D *m_Parton_Jet1_Eta,*m_Parton_Jet2_Eta,*m_Parton_Jet3_Eta,*m_Parton_Jet4_Eta;
  
  TH1D* m_Parton_Dijet1_Mjj;
  TH1D* m_Parton_Dijet1_DEta;
  TH1D* m_Parton_Dijet1_DPhi;
  
  TH1D* m_PartonvsGenJet_DiffPt;
  TH1D* m_PartonvsGenJet_DiffEta;
  
  TProfile* m_Profile_PartonvsGenJet_DiffPt;
  TProfile* m_Profile_PartonvsGenJet_DiffEta;
  
  TH2D* m_PartonvsGenJet_Pt;
  TH2D* m_PartonvsGenJet_Eta;
  
  TH2D* m_PartonvsGenJet_minDr_Pt;
  TH2D* m_PartonvsGenJet_minDr_Eta;
  
};


#endif

