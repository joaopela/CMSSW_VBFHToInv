// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTEventData_H
#define VBFHiggsToInvisible_TriggerStudies_HLTEventData_H

// CMSSW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// VBFHiggsToInvisible
#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTPathData.h"

// System include files
#include <string>
#include <utility>

class HLTEventData{
public:
  
  HLTEventData(const edm::ParameterSet& pset, const edm::Event& iEvent);
  ~HLTEventData();
  
  bool         getPathFired(std::string);
  HLTPathData* getPathData (std::string);
  
  void print();
  
private:

  std::map<std::string,bool>         m_evPathFired;
  std::map<std::string,HLTPathData*> m_evPathData;

};

#endif
