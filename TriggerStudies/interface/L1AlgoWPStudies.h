// -*- C++ -*-
#ifndef VBFHiggsToInvisible_L1AlgoWPStudies_H
#define VBFHiggsToInvisible_L1AlgoWPStudies_H

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
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMath.h"

// My includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1ExtraPayload.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/AlgoTester.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1TPlots.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>
  
class L1AlgoWPStudies : public edm::EDAnalyzer {
public:
  
  L1AlgoWPStudies(const edm::ParameterSet&);
  ~L1AlgoWPStudies();
  
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
  int       currentRunNumber;
  long long evCount;
  
  TFile *fOut;  
  TH1I  *hEventCount;
 
  std::vector<TH1D*> vDijet_Mjj;
  
  std::map<std::string,L1TPlots*> m_wpPlots; 
  
  edm::InputTag m_InputTag_L1GTReadoutRecord;
  edm::InputTag m_InputTag_L1Extra_mets;
  edm::InputTag m_InputTag_L1Extra_mhts;
  edm::InputTag m_InputTag_HLTResults;
  edm::InputTag m_InputTag_L1CaloRegionCollection;
  edm::InputTag m_InputTag_EcalTriggerPrimitives; 
  edm::InputTag m_InputTag_HcalTriggerPrimitives;
  
  edm::ParameterSet ps;
  
};

#endif