// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_L1TAdditionalRateStudies_H
#define VBFHiggsToInvisible_TriggerStudies_L1TAdditionalRateStudies_H

// CMSSW includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// ROOT includes
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMath.h"

// My includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1TSimulator.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>
  
class L1TAdditionalRateStudies : public edm::EDAnalyzer {
public:
  
  L1TAdditionalRateStudies(const edm::ParameterSet&);
  ~L1TAdditionalRateStudies();
  
private:
  void beginJob() ;
  void endJob() ;
  
  void beginRun(edm::Run const&, edm::EventSetup const&);
  void endRun(edm::Run const&, edm::EventSetup const&);
  
  void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  void analyze(const edm::Event&, const edm::EventSetup&);
  
  // ----------member data ---------------------------
  
  bool      m_verbose;
  long long evCount;
  
  edm::ParameterSet ps;
  
  edm::InputTag m_l1GtDataDaqInputTag; // Where to get L1 GT Data DAQ
  
  TFile *fOut;
  TH1I  *hEventCount;
  
  L1TSimulator* myL1TSim;
  
};

#endif