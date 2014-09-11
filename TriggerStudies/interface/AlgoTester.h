// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TrigStudies_AlgoTester_H
#define VBFHiggsToInvisible_TrigStudies_AlgoTester_H

// CMSSW includes
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// My includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1ExtraPayload.h"

// system include files
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

class AlgoTester{
public:
  
  AlgoTester(const edm::ParameterSet &pset);
  ~AlgoTester();
  
  std::vector<std::string> getAlgoNames();
  std::vector<bool>        runAlgos(L1ExtraPayload &l1extra);
  
private:
  
  // Private variables
  bool m_runAlgoTester;
  
  std::vector< std::string >                                       m_algoNames;
  std::vector< std::function<bool (AlgoTester*,L1ExtraPayload&)> > m_algos;
    
  // Private methods
  bool l1tAlgo_L1_ETM40                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM45                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM50                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM55                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM60                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM65                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM70                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM75                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_ETM80                       (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_DoubleJetC60_ETM60          (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_DoubleJet60_ETM60           (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_DoubleJet40_DEta3p0_ETM40   (L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_DoubleVBFJet40_DEta3p0_ETM40(L1ExtraPayload &l1extra);
  bool l1tAlgo_L1_DoubleJet30_Mjj400_ETM40    (L1ExtraPayload &l1extra);
//   bool l1tAlgo_L1_MHTOverHTT0p6_HTT110        (L1ExtraPayload &l1extra);
  
};

#endif