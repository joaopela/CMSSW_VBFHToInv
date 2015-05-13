// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTAlgoPFDijet_H
#define VBFHiggsToInvisible_TriggerStudies_HLTAlgoPFDijet_H

#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTAlgo.h"
#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTEventData.h"

#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"

// System include files
#include <string>
#include <utility>

class HLTAlgoPFDijet : public HLTAlgo{
public:
  
  HLTAlgoPFDijet();
  HLTAlgoPFDijet(std::string algoName);
  ~HLTAlgoPFDijet();

  bool evaluate(HLTEventData *hltData);
  
  void setVBF         (bool vbf);
  void setJetsMinPt   (double jet0,double jet1);
  void setDijetMinMjj (double mjj);
  void setDijetMinDEta(double deta);
  void setDijetMaxDPhi(double dphi);
  
  void setBasePathFilter(std::string basePathName);
  void setBaseJetFilter (std::string baseJetFilter);
  
private:
  
  bool   m_vbf;
  double m_jet0;
  double m_jet1;
  double m_mjj;
  double m_deta;
  double m_dphi;
  
  std::string m_basePathName;
  std::string m_baseJetFilter;
  
};

#endif
