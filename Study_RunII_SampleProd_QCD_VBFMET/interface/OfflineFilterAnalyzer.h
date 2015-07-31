#ifndef VBFHiggsToInvisible_Study_RunII_SampleProd_QCD_VBF_MET_OfflineFilterAnalyzer
#define VBFHiggsToInvisible_Study_RunII_SampleProd_QCD_VBF_MET_OfflineFilterAnalyzer

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
#include "TFile.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>

class OfflineFilterAnalyzer : public edm::EDAnalyzer {
public:
  
  OfflineFilterAnalyzer(const edm::ParameterSet&);
  ~OfflineFilterAnalyzer();
  
private:
  void beginJob() ;
  void endJob() ;
  
  void beginRun(edm::Run const&, edm::EventSetup const&);
  void endRun(edm::Run const&, edm::EventSetup const&);
  
  void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  void analyze(const edm::Event&, const edm::EventSetup&);
  
  void printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT);
  void printHLTMenu (const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT);
  bool testTrigger  (const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, std::string iTriggerName);
  
  double getGenNeutrinoMET(const edm::Event& iEvent);
  
  // ----------member data ---------------------------
  
  bool m_verbose;
  
  // Parameter related variables
  edm::ParameterSet ps;
  edm::EDGetTokenT<edm::HepMCProduct>                   m_InputTag_HepMCProduct;
  edm::EDGetTokenT<reco::GenJetCollection>              m_InputTag_GenJetCollection;
  edm::EDGetTokenT<l1extra::L1EtMissParticleCollection> m_InputTag_L1Extra_mets;
  edm::EDGetTokenT<edm::TriggerResults>                 m_InputTag_HLTResults;

  // Output file
  TFile* fOut;
  
  // Histograms
  TH1D* m_EventCount;
  TH1D* m_L1Extra_MET;
  TH1D* m_GenNeutrinoMET;
  TH1D* m_GenNeutrinoMET_L1MET40;
  TH1D* m_GenNeutrinoMET_L1MET60;
  TH1D* m_GenNeutrinoMET_L1MET70;
  TH2D* m_GenNeutrinoMET_L1MET;
};


#endif
