// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTPlots_H
#define VBFHiggsToInvisible_TriggerStudies_HLTPlots_H

// ROOT includes
#include "TH1D.h"

// System include files
#include <string>
#include <utility>

class HLTPlotsData{
public:
  
  HLTPlotsData(){
    met.first = false;
  }
  
  std::pair<bool,double> met;

};

class HLTPlots{
public:

  HLTPlots();
  HLTPlots(TDirectory* d);

  ~HLTPlots();

  void fill(HLTPlotsData data);
  
  // Class member objects  
  TH1D *met;

  
};

#endif