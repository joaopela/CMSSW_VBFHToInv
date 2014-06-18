// -*- C++ -*-
#ifndef VBFHiggsToInvisible_L1RateEstimator_H
#define VBFHiggsToInvisible_L1RateEstimator_H

// -*- C++ -*-
//
// Package:    L1RateEstimator
// Class:      L1RateEstimator
// 
/**\class L1RateEstimator L1RateEstimator.cc VBFHiggsToInvisible/L1RateEstimator/src/L1RateEstimator.cc
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
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

//DataFormats
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerEvmReadoutRecord.h"

#include "CondFormats/L1TObjects/interface/L1GtPrescaleFactors.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

#include "TH1D.h"
#include "TFile.h"

//
// class declaration
//

class L1RateEstimator : public edm::EDAnalyzer {
public:
  
  L1RateEstimator(const edm::ParameterSet&);
  ~L1RateEstimator();
  
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
  
  TFile* fOut;
  
  std::map<int,unsigned> m_nEvents;
  std::map<int,TH1D*>    m_l1Counts;
  std::map<int,TH1D*>    m_hltCounts;
  
  TH1D* hL1ETM;
  TH1D* hL1HTT;
  
  bool m_verbose;
  
  int evCount;

  int currentRunNumber;
   
  std::vector<std::string> m_selHLTrigger;
  
  std::map<std::string,int> cL1T;  
  std::map<std::string,int> m_algoBit;
  
  edm::InputTag m_InputTag_L1GTReadoutRecord;
  edm::InputTag m_InputTag_L1Extra_mets;
  edm::InputTag m_InputTag_L1Extra_mhts;
  edm::InputTag m_InputTag_HLTResults;
  
};


#endif