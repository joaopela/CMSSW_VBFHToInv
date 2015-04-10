// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTPathData_H
#define VBFHiggsToInvisible_TriggerStudies_HLTPathData_H

// CMSSW includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTObject.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTDiobject.h"

// System include files
#include <string>
#include <vector>
#include <map>

class HLTPathData{
public:
  
  HLTPathData(std::string pathName);
  ~HLTPathData();

  void addObject(HLTObject *object);
  
  std::vector<HLTObject*>   getObjects();
  std::vector<HLTObject*>   getJets();
  std::vector<HLTObject*>   getMET();
  std::vector<HLTObject*>   getFilterObjects  (std::string filterName);
  std::vector<HLTDiobject*> getFilterDiobjects(std::string filterName);
  
  void print();
  
private:
  
  std::string m_pathName;
  std::vector<HLTObject*> m_objects;
  
  std::map<std::string, std::vector<HLTDiobject*> > m_diobjects;
  
};

#endif
