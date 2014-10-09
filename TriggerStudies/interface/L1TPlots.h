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
    l1t_ett.first           = false;
    l1t_mht.first           = false;
    l1t_htt.first           = false;
    
    nJets_total.first       = false;
    nJets_central.first     = false;
    nJets_forward.first     = false;
    
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

    jets_mindphi.first     = false;
    jets_maxdphi.first     = false;
    jets_mindeta.first     = false;
    jets_maxdeta.first     = false;
    jets_minmjj .first     = false;
    jets_maxmjj .first     = false;
    
    jets_met_mindphi.first = false;
    jets_met_maxdphi.first = false;
    jets40_met_mindphi.first = false;
    jets40_met_maxdphi.first = false;
    
    MHToverHTT.first        = false;
  }
  
  std::pair<bool,double> l1t_etm;
  std::pair<bool,double> l1t_ett;
  std::pair<bool,double> l1t_mht;
  std::pair<bool,double> l1t_htt;
  
  std::pair<bool,double> nJets_total;
  std::pair<bool,double> nJets_central;
  std::pair<bool,double> nJets_forward;
  
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
  
  std::pair<bool,double> jets_mindphi;
  std::pair<bool,double> jets_maxdphi;
  std::pair<bool,double> jets_mindeta;
  std::pair<bool,double> jets_maxdeta;
  std::pair<bool,double> jets_minmjj;
  std::pair<bool,double> jets_maxmjj;
  
  std::pair<bool,double> jets_met_mindphi;
  std::pair<bool,double> jets_met_maxdphi;
  std::pair<bool,double> jets40_met_mindphi;
  std::pair<bool,double> jets40_met_maxdphi;
  
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
  TH1D *l1t_ett;
  TH1D *l1t_etm;
  TH1D *l1t_htt;
  TH1D *l1t_mht;
  
  TH1D *nJets_total;
  TH1D *nJets_central;
  TH1D *nJets_forward;
  
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
  
  TH1D *jets_mindeta;
  TH1D *jets_maxdeta;
  TH1D *jets_mindphi;
  TH1D *jets_maxdphi;
  TH1D *jets_minmjj;
  TH1D *jets_maxmjj;
  
  TH1D *jets_met_mindphi;
  TH1D *jets_met_maxdphi;
  TH1D *jets40_met_mindphi;
  TH1D *jets40_met_maxdphi;
  
  TH1D *MHToverHTT;
  
};

#endif