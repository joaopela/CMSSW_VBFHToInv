#include "VBFHiggsToInvisible/TriggerStudies/interface/L1AlgoWPStudies.h"

#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"

#include "CondFormats/DataRecord/interface/L1CaloEcalScaleRcd.h"
#include "CondFormats/DataRecord/interface/L1CaloHcalScaleRcd.h"

#include "CondFormats/L1TObjects/interface/L1CaloEcalScale.h"
#include "CondFormats/L1TObjects/interface/L1CaloHcalScale.h"

#include "DataFormats/Math/interface/deltaPhi.h"

// #include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"
// #include "DataFormats/L1CaloTrigger/interface/L1CaloRegionDetId.h"

#include "TParameter.h"

#include <stdio.h>
#include <math.h>

using namespace std;
using namespace edm;

L1AlgoWPStudies::L1AlgoWPStudies(const edm::ParameterSet& pset){
  
  ps = pset;
  
  evCount = 0;
  
  // Getting InputTag from configuration file
  m_InputTag_L1GTReadoutRecord      = pset.getUntrackedParameter("inputTag_L1GTReadoutRecord",     InputTag("gtDigis"));
  //   m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          InputTag("l1extraParticles","MET"));  
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter("inputTag_L1Extra_mhts",          InputTag("l1extraParticles","MHT"));
  m_InputTag_HLTResults             = pset.getUntrackedParameter("inputTag_HLTResults",            InputTag("TriggerResults","HLT"));
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter("inputTag_L1CaloRegionCollection",InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_EcalTriggerPrimitives", InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_HcalTriggerPrimitives", InputTag("valHcalTriggerPrimitiveDigis"));
  
  // Getting other parameters from configuration file
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",       false);
  
  // Initialising other variables 
  currentRunNumber = 0;
  
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","L1AlgoWPStudiesResults.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
}

L1AlgoWPStudies::~L1AlgoWPStudies(){
  
  fOut->Write();
}

void L1AlgoWPStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  evCount++;
  hEventCount->Fill(1);
  
  L1ExtraPayload evL1Extra(ps,iEvent);
  l1extra::L1JetParticleCollection *l1tJets = evL1Extra.getL1TAllJets();
  
  bool   vbf   = false;
  double jetPt = -1;
  double mjj   = -1;
  double deta  =  0;
  double dphi  =  0;
  
  double jet0_met_dphi    = 0;
  double jet1_met_dphi    = 0;
  double jets_met_mindphi = 0;
  double jets_met_maxdphi = 0;
  
  double MHToverHTT       = 0;
  
  if((*l1tJets).size()>2){
    
    vbf = ( (*l1tJets)[0].eta()>0 && (*l1tJets)[1].eta()<0 ) || ( (*l1tJets)[0].eta()<0 && (*l1tJets)[1].eta()>0 );
    
    jetPt = (*l1tJets)[1].pt();
    deta  = abs( (*l1tJets)[0].eta() - (*l1tJets)[1].eta() );

    dphi             = abs(reco::deltaPhi((*l1tJets)[0].phi(),(*l1tJets)[1].phi()));
    jet0_met_dphi    = abs(reco::deltaPhi((*l1tJets)[0].phi(),evL1Extra.m_L1EtMissParticle_MET->begin()->phi()));
    jet1_met_dphi    = abs(reco::deltaPhi((*l1tJets)[1].phi(),evL1Extra.m_L1EtMissParticle_MET->begin()->phi()));
    if(jet0_met_dphi > jet1_met_dphi){
      jets_met_mindphi = jet1_met_dphi;
      jets_met_maxdphi = jet0_met_dphi;
    }else{
      jets_met_mindphi = jet0_met_dphi;
      jets_met_maxdphi = jet1_met_dphi;
    }
    
    MHToverHTT = evL1Extra.m_L1EtMissParticle_MHT->begin()->etMiss()/evL1Extra.m_L1EtMissParticle_MHT->begin()->etTotal();
    
    double px = (*l1tJets)[0].px() + (*l1tJets)[1].px(); 
    double py = (*l1tJets)[0].py() + (*l1tJets)[1].py(); 
    double pz = (*l1tJets)[0].pz() + (*l1tJets)[1].pz(); 
    double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
    mjj    = sqrt(pow((*l1tJets)[0].energy()+(*l1tJets)[1].energy(),2) - normaP);
    
  }else{return;}

  L1TPlots *p = m_wpPlots["NoCuts"];
  p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
  p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
  p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
  p->dijet_eta0->Fill((*l1tJets)[0].eta());
  p->dijet_eta1->Fill((*l1tJets)[1].eta());
  p->dijet_deta->Fill(deta);
  p->dijet_dphi->Fill(dphi);
  p->dijet_mjj ->Fill(mjj);
  p->jet0_met_dphi   ->Fill(jet0_met_dphi);
  p->jet1_met_dphi   ->Fill(jet1_met_dphi);
  p->jets_met_mindphi->Fill(jets_met_mindphi);
  p->jets_met_maxdphi->Fill(jets_met_maxdphi);
  p->MHToverHTT      ->Fill(MHToverHTT);
  
  if(vbf){
    L1TPlots *p = m_wpPlots["DijetVBF"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }

  if(vbf && (*l1tJets)[1].pt()>=30){
    L1TPlots *p = m_wpPlots["DijetVBF30"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }

  if(vbf && (*l1tJets)[1].pt()>=40){
    L1TPlots *p = m_wpPlots["DijetVBF40"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }

  if(vbf && (*l1tJets)[1].pt()>=30 && deta>=3.0){
    L1TPlots *p = m_wpPlots["DijetVBF30_DEta3p0"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }

  if(vbf && (*l1tJets)[1].pt()>=40 && deta>=3.0){
    L1TPlots *p = m_wpPlots["DijetVBF40_DEta3p0"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }
  
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=40){
    L1TPlots *p = m_wpPlots["L1T_ETM40"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }
  
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=70){
    L1TPlots *p = m_wpPlots["L1T_ETM70"];
    p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
    p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
    p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
    p->dijet_eta0->Fill((*l1tJets)[0].eta());
    p->dijet_eta1->Fill((*l1tJets)[1].eta());
    p->dijet_deta->Fill(deta);
    p->dijet_dphi->Fill(dphi);
    p->dijet_mjj ->Fill(mjj);
    p->jet0_met_dphi   ->Fill(jet0_met_dphi);
    p->jet1_met_dphi   ->Fill(jet1_met_dphi);
    p->jets_met_mindphi->Fill(jets_met_mindphi);
    p->jets_met_maxdphi->Fill(jets_met_maxdphi);
    p->MHToverHTT      ->Fill(MHToverHTT);
  }
   
   if(evL1Extra.m_L1EtMissParticle_MHT->begin()->etTotal()>=125){
     L1TPlots *p = m_wpPlots["L1T_HTT125"];
     p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
     p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
     p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
     p->dijet_eta0->Fill((*l1tJets)[0].eta());
     p->dijet_eta1->Fill((*l1tJets)[1].eta());
     p->dijet_deta->Fill(deta);
     p->dijet_dphi->Fill(dphi);
     p->dijet_mjj ->Fill(mjj);
     p->jet0_met_dphi   ->Fill(jet0_met_dphi);
     p->jet1_met_dphi   ->Fill(jet1_met_dphi);
     p->jets_met_mindphi->Fill(jets_met_mindphi);
     p->jets_met_maxdphi->Fill(jets_met_maxdphi);
     p->MHToverHTT      ->Fill(MHToverHTT);
   }

   if(evL1Extra.m_L1EtMissParticle_MHT->begin()->et()>=40){
     L1TPlots *p = m_wpPlots["L1T_MHT40"];
     p->l1t_etm   ->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());  
     p->dijet_pt0 ->Fill((*l1tJets)[0].pt());
     p->dijet_pt1 ->Fill((*l1tJets)[1].pt());
     p->dijet_eta0->Fill((*l1tJets)[0].eta());
     p->dijet_eta1->Fill((*l1tJets)[1].eta());
     p->dijet_deta->Fill(deta);
     p->dijet_dphi->Fill(dphi);
     p->dijet_mjj ->Fill(mjj);
     p->jet0_met_dphi   ->Fill(jet0_met_dphi);
     p->jet1_met_dphi   ->Fill(jet1_met_dphi);
     p->jets_met_mindphi->Fill(jets_met_mindphi);
     p->jets_met_maxdphi->Fill(jets_met_maxdphi);
     p->MHToverHTT      ->Fill(MHToverHTT);
   }
   
  for(unsigned i=0; i<vDijet_Mjj.size(); i++){
    
    double cut = double(i)*5;
    
    if(jetPt >= cut){vDijet_Mjj[i]->Fill(mjj);}
  }
}

void L1AlgoWPStudies::beginJob(){}

void L1AlgoWPStudies::endJob(){
  
  TParameter<Long64_t> outEvCount("evCount",evCount);
  fOut->WriteTObject(&outEvCount);

  for(auto it=m_wpPlots.begin(); it!=m_wpPlots.end(); it++){
    it->second->doEff(evCount);
  }
  
}

void L1AlgoWPStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  currentRunNumber    = iRun.run();
  
  TDirectory* runDir  = fOut  ->mkdir(Form("Run_%d",currentRunNumber));
  hEventCount = new TH1I("EventCount",   "EventCount"   ,   1, 0.5,  1.5); hEventCount  ->SetDirectory(runDir);

  TDirectory* d = runDir->mkdir("NoCuts");
  m_wpPlots["NoCuts"] = new L1TPlots(d);

  d = runDir->mkdir("DijetVBF");
  m_wpPlots["DijetVBF"] = new L1TPlots(d);
  
  d = runDir->mkdir("L1T_ETM40");
  m_wpPlots["L1T_ETM40"] = new L1TPlots(d);
  
  d = runDir->mkdir("L1T_ETM70");
  m_wpPlots["L1T_ETM70"] = new L1TPlots(d);

  d = runDir->mkdir("L1T_HTT125");
  m_wpPlots["L1T_HTT125"] = new L1TPlots(d);

  d = runDir->mkdir("L1T_MHT40");
  m_wpPlots["L1T_MHT40"] = new L1TPlots(d);
  
  d = runDir->mkdir("DijetVBF30");
  m_wpPlots["DijetVBF30"] = new L1TPlots(d);

  d = runDir->mkdir("DijetVBF40");
  m_wpPlots["DijetVBF40"] = new L1TPlots(d);

  d = runDir->mkdir("DijetVBF30_DEta3p0");  
  m_wpPlots["DijetVBF30_DEta3p0"] = new L1TPlots(d);

  d = runDir->mkdir("DijetVBF40_DEta3p0");
  m_wpPlots["DijetVBF40_DEta3p0"] = new L1TPlots(d);
  
  for(double i=0; i<=60; i=i+5){
  
    string title = Form("Dijet%.0f_Mjj",i);
    TH1D* h = new TH1D(title.c_str(),title.c_str(),3000,0,15000);
    h->SetDirectory(runDir);
    vDijet_Mjj.push_back(h);
  }

  for(double i=0; i<=60; i=i+5){
  
    string title = Form("Dijet%.0f_Mjj",i);
    TH1D* h = new TH1D(title.c_str(),title.c_str(),3000,0,15000);
    h->SetDirectory(runDir);
    vDijet_Mjj.push_back(h);
  }
  
  
}

void L1AlgoWPStudies::endRun(edm::Run const&, edm::EventSetup const&){
  

  
}

void L1AlgoWPStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void L1AlgoWPStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

//define this as a plug-in
DEFINE_FWK_MODULE(L1AlgoWPStudies);
