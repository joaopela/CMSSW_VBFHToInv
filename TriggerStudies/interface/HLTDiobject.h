// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTDiobject_H
#define VBFHiggsToInvisible_TriggerStudies_HLTDiobject_H

#include "CMSSW_VBFHToInv/TriggerStudies/interface/HLTObject.h"

#include "DataFormats/Math/interface/deltaPhi.h"

// System include files
#include <cmath>
#include <string>
#include <utility>

// using namespace std;

class HLTDiobject{
public:
  
  HLTDiobject();
  HLTDiobject(HLTObject *jet0,HLTObject *jet1);
  
  ~HLTDiobject();
  
  bool   vbf();
  double deta();
  double dphi();
  double mjj();
  
  HLTObject* j0();
  HLTObject* j1();
  
private:

  HLTObject *m_jet0;
  HLTObject *m_jet1;
  
  bool cached_vbf;  bool   m_vbf;
  bool cached_deta; double m_deta;
  bool cached_dphi; double m_dphi;
  bool cached_mjj;  double m_mjj;
  
};

#endif
