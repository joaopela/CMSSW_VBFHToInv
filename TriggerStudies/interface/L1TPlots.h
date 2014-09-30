// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_L1Plots_H
#define VBFHiggsToInvisible_TriggerStudies_L1Plots_H

// ROOT includes
#include "TH1D.h"

// System include files
#include <string>
#include <utility>

class L1TPlotsData{
public:
  
  L1TPlotsData(){
    l1t_etm.first           = false;  
    dijet_pt0.first         = false;
    dijet_pt1.first         = false;
    dijet_eta0.first        = false;
    dijet_eta1.first        = false;
    dijet_deta.first        = false;
    dijet_dphi.first        = false;
    dijet_mjj.first         = false;
    jet0_met_dphi.first     = false;
    jet1_met_dphi.first     = false;
    dijet_met_mindphi.first = false;
    dijet_met_maxdphi.first = false;
    jets_met_mindphi.first  = false;
    jets_met_maxdphi.first  = false; 
    MHToverHTT.first        = false; 
  }
  
  std::pair<bool,double> l1t_etm;  
  std::pair<bool,double> dijet_pt0;
  std::pair<bool,double> dijet_pt1;
  std::pair<bool,double> dijet_eta0;
  std::pair<bool,double> dijet_eta1;
  std::pair<bool,double> dijet_deta;
  std::pair<bool,double> dijet_dphi;
  std::pair<bool,double> dijet_mjj;
  
  std::pair<bool,double> jet0_met_dphi;
  std::pair<bool,double> jet1_met_dphi;
  std::pair<bool,double> dijet_met_mindphi;
  std::pair<bool,double> dijet_met_maxdphi;
  std::pair<bool,double> jets_met_mindphi;
  std::pair<bool,double> jets_met_maxdphi;
  
  std::pair<bool,double> MHToverHTT;
  
};

class L1TPlots{
public:

  L1TPlots();
  L1TPlots(TDirectory* d);

  ~L1TPlots();
  
  void doEff    (double entries);
  void doPlotEff(TH1D *h,double entries,TDirectory *d);
  void fill(L1TPlotsData data);
  
  // Class member objects  
  TH1D *l1t_etm;  
  TH1D *dijet_pt0;
  TH1D *dijet_pt1;
  TH1D *dijet_eta0;
  TH1D *dijet_eta1;
  TH1D *dijet_deta;
  TH1D *dijet_dphi;
  TH1D *dijet_mjj;
  
  TH1D *jet0_met_dphi;
  TH1D *jet1_met_dphi;
  TH1D *dijet_met_mindphi;
  TH1D *dijet_met_maxdphi;
  TH1D *jets_met_mindphi;
  TH1D *jets_met_maxdphi;
  
  TH1D *MHToverHTT;
  
};

#endif