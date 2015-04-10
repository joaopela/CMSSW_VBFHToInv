// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_HLTPlots_H
#define VBFHiggsToInvisible_TriggerStudies_HLTPlots_H

// CMSSW includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTEventData.h"

// ROOT includes
#include "TH1D.h"

// System include files
#include <string>
#include <utility>
#include <iostream>

class HLTPlotsData{
public:
  
  HLTPlotsData();
  HLTPlotsData(HLTEventData* data);

  void getData(HLTEventData* data);
  
  void setBasePathNamePFObjects(std::string pathName);
  void setBaseJetFilterPFJets  (std::string filterName);
  void setBaseJetFilterPFMET   (std::string filterName);

  void setBasePathNameCaloObjects(std::string pathName);
  void setBaseJetFilterCaloJets  (std::string filterName);
  void setBaseJetFilterCaloMET   (std::string filterName);

  std::pair<bool,double> pf_met;
  std::pair<bool,double> pf_dijet_maxDEta;
  std::pair<bool,double> pf_dijet_maxMjj;
  
  std::pair<bool,double> calo_met;
  std::pair<bool,double> calo_dijet_maxDEta;
  std::pair<bool,double> calo_dijet_maxMjj;
  
private:
  
  void init();
  
  std::string m_BasePathNamePFObjects;
  std::string m_BaseJetFilterPFJets;
  std::string m_BaseJetFilterPFMET;
  
  std::string m_BasePathNameCaloObjects;
  std::string m_BaseJetFilterCaloJets;
  std::string m_BaseJetFilterCaloMET;
  
};

class HLTPlots{
public:

  HLTPlots();
  HLTPlots(TDirectory* d);

  ~HLTPlots();

  void fill(HLTPlotsData data);
  
  // Class member objects  
  TH1D *pf_met;
  TH1D *pf_dijet_maxDEta;
  TH1D *pf_dijet_maxMjj;
  
  TH1D *calo_met;
  TH1D *calo_dijet_maxDEta;
  TH1D *calo_dijet_maxMjj;
  
};

#endif