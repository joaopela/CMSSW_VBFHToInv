// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TrigStudies_H
#define VBFHiggsToInvisible_TrigStudies_H

// -*- C++ -*-
//
// Package:    TrigStudies
// Class:      TrigStudies
// 
/**\class TrigStudies TrigStudies.cc VBFHiggsToInvisible/TrigStudies/src/TrigStudies.cc
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
#include "TH2D.h"
#include "TFile.h"

//
// class declaration
//

class TrigStudies : public edm::EDAnalyzer {
public:
  
  TrigStudies(const edm::ParameterSet&);
  ~TrigStudies();
  
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
  
  std::map<std::string,TH1D*> h1D_ECALTT;  
  std::map<std::string,TH2D*> h2D_ECALTT;
  std::map<std::string,TH1D*> hHCALTT;
  
  TH1I* hEventCount;
  
  TH1I* hL1AlgoCounts;
  TH1D* hL1ETM;
  TH1D* hL1HTT;
  
  TH1D* hL1ETM_Saturated;
  TH1D* hL1HTT_Saturated;
  
  TH1I* hHLTAlgoCounts;
  TH1I* hHLTNewAlgoCounts;  
  TH1I* hHLTAlgoCounts_ETM;
  TH1I* hHLTAlgoCounts_HTT;
  TH1I* hHLTAlgoCounts_Both;
  TH1I* hHLTAlgoCounts_None;
  
  TH1D* hRCTRegion_Val;
  TH1D* hEcalTT_Val;
  TH1D* hECALTTSamples_Val;
  TH1D* hHcalTT_Val;
  
  TH1D* hRCTRegion_Et;
  TH1D* hEcalTT_Et;
  TH1D* hHcalTT_Et;
  
  TH1I* hEcalTT_NSaturated;
  TH1I* hHcalTT_NSaturated;
  TH1I* hRCTRegion_NSaturated;
  TH1I* hTotal_NSaturated;
  
  bool m_verbose;
  
  int nEcalTT_NSaturated;
  int nHcalTT_NSaturated;
  int nRCTRegion_NSaturated;
  int nTotal_NSaturated;

  int currentRunNumber;
   
  std::vector<std::string> m_selHLTrigger;
  
  std::map<std::string,int> cL1T;  
  std::map<std::string,int> m_l1Alias;
  
  edm::InputTag m_InputTag_L1GTReadoutRecord;
  edm::InputTag m_InputTag_L1Extra_mets;
  edm::InputTag m_InputTag_L1Extra_mhts;
  edm::InputTag m_InputTag_HLTResults;
  edm::InputTag m_InputTag_L1CaloRegionCollection;
  edm::InputTag m_InputTag_EcalTriggerPrimitives; 
  edm::InputTag m_InputTag_HcalTriggerPrimitives;
  
};


#endif