// -*- C++ -*-
#ifndef VBFHiggsToInvisible_L1AlgoWPStudies_H
#define VBFHiggsToInvisible_L1AlgoWPStudies_H

// CMSSW includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerEvmReadoutRecord.h"

#include "CondFormats/L1TObjects/interface/L1GtPrescaleFactors.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

// ROOT includes
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMath.h"

// My includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1ExtraPayload.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/AlgoTester.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>

class L1TPlots{
public:

  L1TPlots(){
    l1t_etm     = 0;
    dijet_pt0   = 0;
    dijet_pt1   = 0; 
    dijet_eta0  = 0; 
    dijet_eta1  = 0; 
    dijet_deta  = 0; 
    dijet_dphi  = 0; 
    dijet_mjj   = 0; 
    
    jet0_met_dphi    = 0;
    jet1_met_dphi    = 0;
    jets_met_mindphi = 0;
    jets_met_maxdphi = 0;
    
    MHToverHTT       = 0;
    
  }
  
  L1TPlots(TDirectory* d){
    l1t_etm = new TH1D("L1T_ETM",   "L1T ETM"  , 500,-0.5,495.5);                   
    l1t_etm->GetXaxis()->SetTitle("L1T ETM [GeV]");
    l1t_etm->GetYaxis()->SetTitle("Entries");    
    l1t_etm->SetDirectory(d);   
    
    dijet_pt0 = new TH1D("dijet_pt0 ","dijet_pt0", 500,-0.5,495.5);                   
    dijet_pt0->GetXaxis()->SetTitle("Dijet p_{#perp}^{Jet0}");  
    dijet_pt0->GetYaxis()->SetTitle("Entries");
    dijet_pt0->SetDirectory(d); 
    
    dijet_pt1 = new TH1D("dijet_pt1 ","dijet_pt1", 500,-0.5,495.5);                   
    dijet_pt1->GetXaxis()->SetTitle("Dijet p_{#perp}^{Jet1}");  
    dijet_pt1->GetYaxis()->SetTitle("Entries");  
    dijet_pt1->SetDirectory(d); 
    
    dijet_eta0 = new TH1D("dijet_eta0","dijet_eta0",100,-5.0,5.0);                   
    dijet_eta0->GetXaxis()->SetTitle("Dijet #eta^{Jet0}"); 
    dijet_eta0->GetYaxis()->SetTitle("Entries"); 
    dijet_eta0->SetDirectory(d);
    
    dijet_eta1 = new TH1D("dijet_eta1","dijet_eta1",100,-5.0,5.0);                   
    dijet_eta1->GetXaxis()->SetTitle("Dijet #eta^{Jet0}"); 
    dijet_eta1->GetYaxis()->SetTitle("Entries"); 
    dijet_eta1->SetDirectory(d);
    
    dijet_deta = new TH1D("dijet_deta","dijet_deta",100,0,10.0);                 
    dijet_deta->GetXaxis()->SetTitle("Dijet #Delta#eta"); 
    dijet_deta->GetYaxis()->SetTitle("Entries"); 
    dijet_deta->SetDirectory(d);
    
    dijet_dphi = new TH1D("dijet_dphi","dijet_dphi",32,0,TMath::Pi()); 
    dijet_dphi->GetXaxis()->SetTitle("Dijet #Delta#phi"); 
    dijet_dphi->GetYaxis()->SetTitle("Entries"); 
    dijet_dphi->SetDirectory(d);
    
    dijet_mjj = new TH1D("dijet_mjj ","dijet_mjj",500,0,2000);                   
    dijet_mjj->GetXaxis()->SetTitle("Dijet M_{jj}");  
    dijet_mjj->GetYaxis()->SetTitle("Entries");  
    dijet_mjj->SetDirectory(d);
    
    jet0_met_dphi = new TH1D("jet0_met_dphi",   "jet0_met_dphi",   32,0,TMath::Pi());  
    jet0_met_dphi->GetXaxis()->SetTitle("#Delta#phi(met,jet_{0})");
    jet0_met_dphi->GetYaxis()->SetTitle("Entries");
    jet0_met_dphi->SetDirectory(d);
    
    jet1_met_dphi = new TH1D("jet1_met_dphi",   "jet1_met_dphi",   32,0,TMath::Pi()); 
    jet1_met_dphi->GetXaxis()->SetTitle("#Delta#phi(met,jet_{1})");
    jet1_met_dphi->GetYaxis()->SetTitle("Entries");
    jet1_met_dphi->SetDirectory(d);
    
    jets_met_mindphi = new TH1D("jets_met_mindphi","jets_met_mindphi",32,0,TMath::Pi()); 
    jets_met_mindphi->GetXaxis()->SetTitle("Min(#Delta#phi(met,jets))");
    jets_met_mindphi->GetYaxis()->SetTitle("Entries");
    jets_met_mindphi->SetDirectory(d);
    
    jets_met_maxdphi = new TH1D("jets_met_maxdphi","jets_met_maxdphi",32,0,TMath::Pi()); 
    jets_met_maxdphi->GetXaxis()->SetTitle("Max(#Delta#phi(met,jets))");
    jets_met_maxdphi->GetYaxis()->SetTitle("Entries");
    jets_met_maxdphi->SetDirectory(d);
    
    MHToverHTT = new TH1D("MHToverHTT ","MHToverHTT",100,0,1.0);
    MHToverHTT->GetXaxis()->SetTitle("MHT over HTT");
    MHToverHTT->GetYaxis()->SetTitle("Entries");
    MHToverHTT->SetDirectory(d);
    
  }
  
  void doEff(double entries){
    TDirectory *d    = l1t_etm->GetDirectory();
    TDirectory *dEff = d->mkdir("Efficiency");

    doPlotEff(l1t_etm,         entries,dEff);
    doPlotEff(dijet_pt0,   entries,dEff);
    doPlotEff(dijet_pt1,   entries,dEff);
    doPlotEff(dijet_deta,  entries,dEff);
    doPlotEff(dijet_dphi,  entries,dEff);
    doPlotEff(dijet_mjj,   entries,dEff);
    doPlotEff(jet0_met_dphi,   entries,dEff);
    doPlotEff(jet1_met_dphi,   entries,dEff);
    doPlotEff(jets_met_mindphi,entries,dEff);
    doPlotEff(jets_met_maxdphi,entries,dEff);
    doPlotEff(MHToverHTT,      entries,dEff);
    
  }
  
  void doPlotEff(TH1D *h,double entries,TDirectory *d){
    TH1D *eff = (TH1D*) h ->Clone(Form("eff_%s",h->GetTitle())); 
    for(int i=0; i<=eff->GetNbinsX()+1; i++){
      eff->SetBinContent(i,eff->Integral(i,eff->GetNbinsX()+1));
    }
    eff->Scale(1/entries);
    eff->SetDirectory(d);
  }
  
  ~L1TPlots(){
    delete l1t_etm;  
    delete dijet_pt0;
    delete dijet_pt1;
    delete dijet_eta0;
    delete dijet_eta1;
    delete dijet_deta;
    delete dijet_dphi;
    delete dijet_mjj;
  }
  
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
  TH1D *jets_met_mindphi;
  TH1D *jets_met_maxdphi;
  
  TH1D *MHToverHTT;
  
};
  
class L1AlgoWPStudies : public edm::EDAnalyzer {
public:
  
  L1AlgoWPStudies(const edm::ParameterSet&);
  ~L1AlgoWPStudies();
  
private:
  void beginJob() ;
  void endJob() ;
  
  void beginRun(edm::Run const&, edm::EventSetup const&);
  void endRun(edm::Run const&, edm::EventSetup const&);
  
  void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  void analyze(const edm::Event&, const edm::EventSetup&);
  
  // ----------member data ---------------------------
  
  bool      m_verbose;
  int       currentRunNumber;
  long long evCount;
  
  TFile *fOut;  
  TH1I  *hEventCount;
 
  std::vector<TH1D*> vDijet_Mjj;
  
  std::map<std::string,L1TPlots*> m_wpPlots; 
  
  edm::InputTag m_InputTag_L1GTReadoutRecord;
  edm::InputTag m_InputTag_L1Extra_mets;
  edm::InputTag m_InputTag_L1Extra_mhts;
  edm::InputTag m_InputTag_HLTResults;
  edm::InputTag m_InputTag_L1CaloRegionCollection;
  edm::InputTag m_InputTag_EcalTriggerPrimitives; 
  edm::InputTag m_InputTag_HcalTriggerPrimitives;
  
  edm::ParameterSet ps;
  
};

#endif