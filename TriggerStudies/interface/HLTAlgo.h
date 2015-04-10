// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTAlgo_H
#define VBFHiggsToInvisible_TriggerStudies_HLTAlgo_H

#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTEventData.h"

#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"

// System include files
#include <string>
#include <utility>

class HLTAlgo{
public:
  
  HLTAlgo();
  virtual ~HLTAlgo();
  
  virtual bool evaluate(HLTEventData *hltData);
  
  std::string getName();
  
protected:
  
  std::string m_algoName;
  
};

#endif
