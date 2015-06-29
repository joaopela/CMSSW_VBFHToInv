// -*- C++ -*-
#ifndef VBFHiggsToInvisible_HLTSimpleAnalyser_H
#define VBFHiggsToInvisible_HLTSimpleAnalyser_H

// -*- C++ -*-
//
// Package:    HLTSimpleAnalyser
// Class:      HLTSimpleAnalyser
// 
/**\class HLTSimpleAnalyser HLTSimpleAnalyser.cc VBFHiggsToInvisible/HLTSimpleAnalyser/src/HLTSimpleAnalyser.cc
 * 
 * Description: TODO
 * 
 * Implementation:
 *     TODO
 */
//
// Original Author:  Joao Arnauth Pela,510 1-002,+41227679913,
//         Created:  Thu Apr 10 14:39:33 CEST 2014
// $Id$
//
//

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

#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerEvmReadoutRecord.h"

#include "CondFormats/L1TObjects/interface/L1GtPrescaleFactors.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>

//
// class declaration
//

class HLTSimpleAnalyser : public edm::EDAnalyzer {
public:
  
  HLTSimpleAnalyser(const edm::ParameterSet&);
  ~HLTSimpleAnalyser();
  
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
  
  std::vector<std::string> m_hltPaths;
  
  edm::EDGetTokenT<edm::TriggerResults> m_inputTag_HLTResults;
  
  TFile* m_fileOut;
  
  TH1D* m_hEventCount;
  TH1D* m_hHLTPathCount;
  TH2D* m_hHLTCorrelation;
  
};


#endif