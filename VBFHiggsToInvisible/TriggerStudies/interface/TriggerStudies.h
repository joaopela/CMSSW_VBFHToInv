// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_H
#define VBFHiggsToInvisible_TriggerStudies_H

// -*- C++ -*-
//
// Package:    TriggerStudies
// Class:      TriggerStudies
// 
/**\class TriggerStudies TriggerStudies.cc VBFHiggsToInvisible/TriggerStudies/src/TriggerStudies.cc
 * 
 * Description: [one line class summary]
 * 
 * Implementation:
 *     [Notes on implementation]
 */
//
// Original Author:  Joao Arnauth Pela,510 1-002,+41227679913,
//         Created:  Thu Apr 10 14:39:33 CEST 2014
// $Id$
//
//

// system include files
#include <memory>
#include <string>
#include <vector>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

//DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerEvmReadoutRecord.h"

#include "CondFormats/L1TObjects/interface/L1GtPrescaleFactors.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

//
// class declaration
//

class TriggerStudies : public edm::EDAnalyzer {
public:
  
  TriggerStudies(const edm::ParameterSet&);
  ~TriggerStudies();
    
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
  bool m_doHLTAnalysis;
  
  int evCount;

  std::vector<std::string> m_selL1Trigger;  
  std::vector<std::string> m_selHLTrigger;
  
  std::map<std::string,int> cL1T;  
  std::map<std::string,int> cHLT;
  std::map<std::string,int> m_algoBit;
  
  edm::InputTag m_InputTag_L1GTReadoutRecord;
  edm::InputTag m_InputTag_HLTResults;
  
};


#endif