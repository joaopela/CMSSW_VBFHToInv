// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_L1TSimulator_H
#define VBFHiggsToInvisible_TriggerStudies_L1TSimulator_H

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

// System include files
#include <string>
#include <vector>
#include <map>

class L1TSimulator{
public:
  
  L1TSimulator();
  ~L1TSimulator();
  
  void getMenu(const edm::EventSetup& iSetup);
  bool l1tResult(DecisionWord &dw);
  
private:
  
  std::map<std::string,int> m_menuPrescales;
  std::vector<int>          m_prescales;
  std::vector<int>          m_prescalesCount;
  
};

#endif
