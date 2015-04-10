// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTObject_H
#define VBFHiggsToInvisible_TriggerStudies_HLTObject_H

#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"

// System include files
#include <string>
#include <vector>

class HLTObject{
public:
  
  HLTObject();
  HLTObject(double pt,double eta,double phi,double energy);

  double pt();
  double px();
  double py();
  double pz();
  
  double eta();
  double phi();
  double energy();
  
  bool isJet();
  bool isMET();
  
  bool passedFilter(std::string);
  
  ROOT::Math::PtEtaPhiEVector getP4();
  void addFilter(std::string filterName);
  void addType  (int         type);
  
  void print();
  
private:

  ROOT::Math::PtEtaPhiEVector p4;
  std::vector<int>         m_types;
  std::vector<std::string> m_filters;
};

#endif
