// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TrigStudies_HLTPathStudies
#define VBFHiggsToInvisible_TrigStudies_HLTPathStudies

// CMSSW includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPlots.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTAlgoPFDijet.h"

// ROOT includes
#include "TH1I.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>

class HLTPathStudies : public edm::EDAnalyzer {
public:
  
  HLTPathStudies(const edm::ParameterSet&);
  ~HLTPathStudies();
  
private:
  void beginJob() ;
  void endJob() ;
  
  void beginRun(edm::Run const&, edm::EventSetup const&);
  void endRun(edm::Run const&, edm::EventSetup const&);
  
  void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  void analyze(const edm::Event&, const edm::EventSetup&);
  
  void printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT);
  bool testTrigger  (const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, std::string iTriggerName);
  
  // ----------member data ---------------------------
  
  bool m_verbose;
  bool m_doL1TAnalysis;
  bool m_vetoHLTPFMET170;
  
  edm::ParameterSet ps;
  
  edm::InputTag m_InputTag_L1GTReadoutRecord;
  edm::InputTag m_InputTag_L1Extra_mets;
  edm::InputTag m_InputTag_L1Extra_mhts;
  edm::InputTag m_InputTag_HLTResults;
  edm::InputTag m_InputTag_L1CaloRegionCollection;
  edm::InputTag m_InputTag_EcalTriggerPrimitives; 
  edm::InputTag m_InputTag_HcalTriggerPrimitives;
  
  std::vector<std::string> m_hltAlgos;
  std::vector< std::pair<HLTAlgo*,HLTPlots*> > m_algos;
  
  TFile* fOut;
  
  TH1I* hEventCount;
  TH1I* hHLTPathCount;
  TH1D* hHLT_jet_eta;
  TH1D* hHLT_L1TETM;
  
};


#endif
