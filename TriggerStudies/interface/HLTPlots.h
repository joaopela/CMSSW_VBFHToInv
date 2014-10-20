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
  
  HLTPlotsData(){
    this->init();
  }

  HLTPlotsData(HLTEventData* data){

    this->init();
    
    // Getting variables from loose pf trigger
    if(data->getPathFired("HLT_PFMET_PFVBF_v1")){

      HLTPathData* thePath = data->getPathData("HLT_PFMET_PFVBF_v1");

      pf_met.first  = true;
      pf_met.second = thePath->getFilterObjects("hltPFMET80Filter").at(0)->pt();

      std::vector<HLTDiobject*> myDijet = thePath->getFilterDiobjects("hltDiPFJet10");
      if(myDijet.size()>0){
        pf_dijet_maxDEta.first  = true;
        pf_dijet_maxDEta.second = myDijet[0]->deta();
        pf_dijet_maxMjj.first   = true;
        pf_dijet_maxMjj.second  = myDijet[0]->mjj();
      }

      for(unsigned i=1; i<myDijet.size(); i++){
        
        HLTDiobject* dijet = myDijet[i];
        if(dijet->deta()>pf_dijet_maxDEta.second){pf_dijet_maxDEta.second=dijet->deta();}
        if(dijet->mjj() >pf_dijet_maxMjj.second) {pf_dijet_maxMjj .second=dijet->mjj();}
      }
    }
    
    // Getting variables from loose calo trigger
    if(data->getPathFired("HLT_CaloMET_CaloVBF_v1")){

      HLTPathData* thePath = data->getPathData("HLT_CaloMET_CaloVBF_v1");
 
      calo_met.first  = true; 
      calo_met.second = thePath->getFilterObjects("hltMET65").at(0)->pt();

      std::vector<HLTDiobject*> myDijet = thePath->getFilterDiobjects("hltDiCaloJet10");
      if(myDijet.size()>0){
        calo_dijet_maxDEta.first  = true;
        calo_dijet_maxDEta.second = myDijet[0]->deta();
        calo_dijet_maxMjj.first   = true;
        calo_dijet_maxMjj.second  = myDijet[0]->mjj();
      }

      for(unsigned i=1; i<myDijet.size(); i++){
        
        HLTDiobject* dijet = myDijet[i];
        if(dijet->deta()>calo_dijet_maxDEta.second){calo_dijet_maxDEta.second=dijet->deta();}
        if(dijet->mjj() >calo_dijet_maxMjj.second) {calo_dijet_maxMjj .second=dijet->mjj();}
      }
    }
  }
  
  void init(){
    pf_met.first           = false;
    pf_dijet_maxDEta.first = false;
    pf_dijet_maxMjj.first  = false;
    
    calo_met.first            = false;
    calo_dijet_maxDEta.first  = false;
    calo_dijet_maxMjj.first   = false;
  }
  
  std::pair<bool,double> pf_met;
  std::pair<bool,double> pf_dijet_maxDEta;
  std::pair<bool,double> pf_dijet_maxMjj;
  
  std::pair<bool,double> calo_met;
  std::pair<bool,double> calo_dijet_maxDEta;
  std::pair<bool,double> calo_dijet_maxMjj;
  
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