#ifndef VBFHiggsToInvisible_SampleProduction_OfflineFilterAnalyzer
#define VBFHiggsToInvisible_SampleProduction_OfflineFilterAnalyzer

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

// ROOT includes
#include "TH1D.h"
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
  
  // ----------member data ---------------------------
  
  bool m_verbose;
  
  // Parameter related variables
  edm::ParameterSet ps;
  edm::EDGetTokenT<edm::TriggerResults>                 m_InputTag_HLTResults;
  edm::EDGetTokenT<l1extra::L1EtMissParticleCollection> m_InputTag_L1Extra_mets;
  
  // Output file
  TFile* fOut;
  
  // Histograms
  TH1D* m_EventCount;
  TH1D* m_L1Extra_MET;
  
  
};


#endif
