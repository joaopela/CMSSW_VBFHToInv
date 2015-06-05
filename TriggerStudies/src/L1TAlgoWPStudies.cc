#include "CMSSW_VBFHToInv/TriggerStudies/interface/L1AlgoWPStudies.h"

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
  
  ps      = pset;
  evCount = 0;
  
  // Getting InputTag from configuration file
  m_InputTag_L1GTReadoutRecord      = pset.getUntrackedParameter("inputTag_L1GTReadoutRecord",     InputTag("gtDigis"));
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter("inputTag_L1Extra_mhts",          InputTag("l1extraParticles","MHT"));
  m_InputTag_HLTResults             = pset.getUntrackedParameter("inputTag_HLTResults",            InputTag("TriggerResults","HLT"));
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter("inputTag_L1CaloRegionCollection",InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_EcalTriggerPrimitives", InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_HcalTriggerPrimitives", InputTag("valHcalTriggerPrimitiveDigis"));
  
  // Getting other parameters from configuration file
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",false);
  
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
  
  L1TPlotsData evData;
  std::vector<L1TDijet> m_allL1TDijets;
  
  bool   vbf               = false;
  double jetPt             = -1;
  
  double jets_mindeta       =   100;
  double jets_maxdeta       =  -100;
  double jets_mindphi       =    10;
  double jets_maxdphi       =   -10;
  double jets_minmjj        = 50000;
  double jets_maxmjj        =   -10;
  double jets_met_mindphi   =    10;
  double jets_met_maxdphi   =   -10;
  double jets40_met_mindphi =    10;
  double jets40_met_maxdphi =   -10;
  
  evData.l1t_ett.first = true; evData.l1t_ett.second = evL1Extra.m_L1EtMissParticle_MET->begin()->etTotal();
  evData.l1t_etm.first = true; evData.l1t_etm.second = evL1Extra.m_L1EtMissParticle_MET->begin()->et();
  evData.l1t_htt.first = true; evData.l1t_htt.second = evL1Extra.m_L1EtMissParticle_MHT->begin()->etTotal();
  evData.l1t_mht.first = true; evData.l1t_mht.second = evL1Extra.m_L1EtMissParticle_MHT->begin()->etMiss();
  
  evData.nJets_total.first   = true; evData.nJets_total  .second = l1tJets->size();
  evData.nJets_central.first = true; evData.nJets_central.second = evL1Extra.m_L1JetParticle_Central->size();
  evData.nJets_forward.first = true; evData.nJets_forward.second = evL1Extra.m_L1JetParticle_Forward->size();
  
  evData.MHToverHTT.first = true; evData.MHToverHTT.second = evL1Extra.m_L1EtMissParticle_MHT->begin()->etMiss()/evL1Extra.m_L1EtMissParticle_MHT->begin()->etTotal();

  if((*l1tJets).size()>0){
    evData.dijet_pt0 .first = true; evData.dijet_pt0.second  = (*l1tJets)[0].pt();
    evData.dijet_eta0.first = true; evData.dijet_eta0.second = (*l1tJets)[0].eta();
    
    for(unsigned i=0; i<l1tJets->size(); i++){
      
      double jet_met_dphi = abs(reco::deltaPhi((*l1tJets)[i].phi(),evL1Extra.m_L1EtMissParticle_MET->begin()->phi()));
      
      if     (i==0){evData.jet0_met_dphi.first = true; evData.jet0_met_dphi.second = jet_met_dphi;}
      else if(i==1){evData.jet1_met_dphi.first = true; evData.jet1_met_dphi.second = jet_met_dphi;}
      
      if(jet_met_dphi<jets_met_mindphi){jets_met_mindphi=jet_met_dphi;}
      if(jet_met_dphi>jets_met_maxdphi){jets_met_maxdphi=jet_met_dphi;}
      
      if((*l1tJets)[i].pt()>=40 && jet_met_dphi<jets40_met_mindphi){jets40_met_mindphi=jet_met_dphi;}
      if((*l1tJets)[i].pt()>=40 && jet_met_dphi>jets40_met_maxdphi){jets40_met_maxdphi=jet_met_dphi;}
    }
    evData.jets_met_mindphi.first = true; evData.jets_met_mindphi.second = jets_met_mindphi;
    evData.jets_met_maxdphi.first = true; evData.jets_met_maxdphi.second = jets_met_maxdphi;
    
    evData.jets40_met_mindphi.first = true; evData.jets40_met_mindphi.second = jets40_met_mindphi;
    evData.jets40_met_maxdphi.first = true; evData.jets40_met_maxdphi.second = jets40_met_maxdphi;
  }

  if((*l1tJets).size()>1){
    
    evData.dijet_pt1 .first = true; evData.dijet_pt1 .second = (*l1tJets)[1].pt();
    evData.dijet_eta1.first = true; evData.dijet_eta1.second = (*l1tJets)[1].eta();
    
    // Running over all possible jet pairs
    for(unsigned j0=0; j0<(*l1tJets).size() ; j0++){
      for(unsigned j1=j0+1; j1<(*l1tJets).size() ; j1++){
        
        m_allL1TDijets.push_back(L1TDijet(&(*l1tJets)[j0],&(*l1tJets)[j1]));
        
        L1TDijet* dijet = &(m_allL1TDijets.back());
        
        // Checking VBF condition
        if( dijet->vbf() ){vbf = true;}
        
        // Checking deta conditions
        if(dijet->deta()<jets_mindeta){jets_mindeta=dijet->deta();}
        if(dijet->deta()>jets_maxdeta){jets_maxdeta=dijet->deta();}
        
        // Checking dphi conditions
        if(dijet->dphi()<jets_mindphi){jets_mindphi=dijet->dphi();}
        if(dijet->dphi()>jets_maxdphi){jets_maxdphi=dijet->dphi();}
        
        // Checking mjj conditions
        if(dijet->mjj()<jets_minmjj){jets_minmjj=dijet->mjj();}
        if(dijet->mjj()>jets_maxmjj){jets_maxmjj=dijet->mjj();}
      }
    }

    evData.jets_mindeta.first = true; evData.jets_mindeta.second = jets_mindeta;
    evData.jets_maxdeta.first = true; evData.jets_maxdeta.second = jets_maxdeta;
    
    evData.jets_mindphi.first = true; evData.jets_mindphi.second = jets_mindphi;
    evData.jets_maxdphi.first = true; evData.jets_maxdphi.second = jets_maxdphi;
    
    evData.jets_minmjj.first = true; evData.jets_minmjj.second = jets_minmjj;
    evData.jets_maxmjj.first = true; evData.jets_maxmjj.second = jets_maxmjj;
    
    jetPt = (*l1tJets)[1].pt();
    evData.dijet_deta.first = true; evData.dijet_deta.second = abs( (*l1tJets)[0].eta() - (*l1tJets)[1].eta() );
    evData.dijet_dphi.first = true; evData.dijet_dphi.second = abs(reco::deltaPhi((*l1tJets)[0].phi(),(*l1tJets)[1].phi()));
    
    evData.dijet_met_mindphi.first = true; 
    evData.dijet_met_maxdphi.first = true; 
    if(evData.jet0_met_dphi.second > evData.jet1_met_dphi.second){
      evData.dijet_met_mindphi.second = evData.jet1_met_dphi.second;
      evData.dijet_met_maxdphi.second = evData.jet0_met_dphi.second;
    }else{
      evData.dijet_met_mindphi.second = evData.jet0_met_dphi.second;
      evData.dijet_met_maxdphi.second = evData.jet1_met_dphi.second;
    }
    
    double px = (*l1tJets)[0].px() + (*l1tJets)[1].px();
    double py = (*l1tJets)[0].py() + (*l1tJets)[1].py();
    double pz = (*l1tJets)[0].pz() + (*l1tJets)[1].pz();
    double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
    
    evData.dijet_mjj.first = true; evData.dijet_mjj.second = sqrt(pow((*l1tJets)[0].energy()+(*l1tJets)[1].energy(),2) - normaP);

  }

  m_wpPlots["NoCuts"]->fill(evData);
  
  // MET based triggers
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=40){m_wpPlots["L1T_ETM40"]->fill(evData);}
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=50){m_wpPlots["L1T_ETM50"]->fill(evData);}
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=60){
    m_wpPlots["L1T_ETM60"]->fill(evData);
    if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
      m_wpSameDijetNotETM70Plots["L1T_ETM60"]->fill(evData);
    }
  }
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=70){m_wpPlots["L1T_ETM70"]->fill(evData);}

  // HTT based triggers
  if(evL1Extra.m_L1EtMissParticle_MHT->begin()->etTotal()>= 70){
    m_wpPlots["L1T_HTT70"] ->fill(evData);
    if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
      m_wpSameDijetNotETM70Plots["L1T_HTT70"]->fill(evData);
    }
  }
  if(evL1Extra.m_L1EtMissParticle_MHT->begin()->etTotal()>=125){m_wpPlots["L1T_HTT125"]->fill(evData);}

  // MHT based triggers
  if(evL1Extra.m_L1EtMissParticle_MHT->begin()->et()>=40){m_wpPlots["L1T_MHT40"]->fill(evData);}
  if(evL1Extra.m_L1EtMissParticle_MHT->begin()->et()>=50){m_wpPlots["L1T_MHT50"]->fill(evData);}
  if(evL1Extra.m_L1EtMissParticle_MHT->begin()->et()>=60){m_wpPlots["L1T_MHT60"]->fill(evData);}
  if(evL1Extra.m_L1EtMissParticle_MHT->begin()->et()>=70){m_wpPlots["L1T_MHT70"]->fill(evData);}

  // Dijet based triggers
  if((*l1tJets).size()>=2){m_wpPlots["Dijet"]->fill(evData);}
  
  if((*l1tJets).size()>=2 && vbf){m_wpPlots["DijetVBF"]->fill(evData);};

  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=30){m_wpPlots["DijetVBF30"]->fill(evData);}
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=40){m_wpPlots["DijetVBF40"]->fill(evData);}
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=50){m_wpPlots["DijetVBF50"]->fill(evData);}

  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=30 && evData.jets_maxdeta.second>=3.0){m_wpPlots["DijetVBF30_DEta3p0"]->fill(evData);}
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=40 && evData.jets_maxdeta.second>=3.0){m_wpPlots["DijetVBF40_DEta3p0"]->fill(evData);}
  
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=30 && evData.jets_maxdeta.second>=3.5){m_wpPlots["DijetVBF30_DEta3p5"]->fill(evData);}
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=40 && evData.jets_maxdeta.second>=3.5){m_wpPlots["DijetVBF40_DEta3p5"]->fill(evData);}
  
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=30 && evData.jets_mindphi.second<=1.0){m_wpPlots["DijetVBF30_DPhiJJ1p0"]->fill(evData);}
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=40 && evData.jets_mindphi.second<=1.0){m_wpPlots["DijetVBF40_DPhiJJ1p0"]->fill(evData);}
  
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=30 && evData.jets_mindphi.second<=1.5){m_wpPlots["DijetVBF30_DPhiJJ1p5"]->fill(evData);}
  if((*l1tJets).size()>=2 && vbf && (*l1tJets)[1].pt()>=40 && evData.jets_mindphi.second<=1.5){m_wpPlots["DijetVBF40_DPhiJJ1p5"]->fill(evData);}
  
  //#######################################################################
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=30 && dijet->deta()>=3.0){
      m_wpSameDijetPlots["DijetVBF30_DEta3p0"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF30_DEta3p0"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=40 && dijet->deta()>=3.0){
      m_wpSameDijetPlots["DijetVBF40_DEta3p0"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF40_DEta3p0"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=30 && dijet->deta()>=3.5){
      m_wpSameDijetPlots["DijetVBF30_DEta3p5"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF30_DEta3p5"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=40 && dijet->deta()>=3.5){
      m_wpSameDijetPlots["DijetVBF40_DEta3p5"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF40_DEta3p5"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=30 && dijet->dphi()<=1.0){
      m_wpSameDijetPlots["DijetVBF30_DPhiJJ1p0"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF30_DPhiJJ1p0"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=40 && dijet->dphi()<=1.0){
      m_wpSameDijetPlots["DijetVBF40_DPhiJJ1p0"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF40_DPhiJJ1p0"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=30 && dijet->dphi()<=1.5){
      m_wpSameDijetPlots["DijetVBF30_DPhiJJ1p5"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF30_DPhiJJ1p5"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<m_allL1TDijets.size(); i++){
    L1TDijet* dijet = &(m_allL1TDijets[i]);
    if(dijet->vbf() && dijet->j1()->pt()>=40 && dijet->dphi()<=1.5){
      m_wpSameDijetPlots["DijetVBF40_DPhiJJ1p5"]->fill(evData);
      if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()<70){
        m_wpSameDijetNotETM70Plots["DijetVBF40_DPhiJJ1p5"]->fill(evData);
      }
    }
    break;
  }
  
  for(unsigned i=0; i<vDijet_Mjj.size(); i++){
    
    double cut = double(i)*5;
    
    if(jetPt >= cut){vDijet_Mjj[i]->Fill(evData.dijet_mjj.second);}
  }
}

void L1AlgoWPStudies::beginJob(){}

void L1AlgoWPStudies::endJob(){
  
  TParameter<Long64_t> outEvCount("evCount",evCount);
  fOut->WriteTObject(&outEvCount);

// WARNING: fix this.
//   for(auto it=m_wpPlots.begin(); it!=m_wpPlots.end(); it++){
//     it->second->doEff(evCount);
//   }

}

void L1AlgoWPStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  currentRunNumber = iRun.run();
  
  TDirectory* runDir  = fOut  ->mkdir(Form("Run_%d",currentRunNumber));
  hEventCount = new TH1I("EventCount",   "EventCount"   ,   1, 0.5,  1.5); hEventCount  ->SetDirectory(runDir);

  TDirectory* dirDiffDijet = runDir->mkdir("DiffDijet");
  
  TDirectory* d = dirDiffDijet->mkdir("NoCuts");
  m_wpPlots["NoCuts"] = new L1TPlots(d);

  d = dirDiffDijet->mkdir("Dijet");
  m_wpPlots["Dijet"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF");
  m_wpPlots["DijetVBF"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_ETM40");
  m_wpPlots["L1T_ETM40"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_ETM50");
  m_wpPlots["L1T_ETM50"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_ETM60");
  m_wpPlots["L1T_ETM60"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_ETM70");
  m_wpPlots["L1T_ETM70"] = new L1TPlots(d);

  d = dirDiffDijet->mkdir("L1T_HTT70");
  m_wpPlots["L1T_HTT70"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_HTT125");
  m_wpPlots["L1T_HTT125"] = new L1TPlots(d);

  d = dirDiffDijet->mkdir("L1T_MHT40");
  m_wpPlots["L1T_MHT40"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_MHT50");
  m_wpPlots["L1T_MHT50"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_MHT60");
  m_wpPlots["L1T_MHT60"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("L1T_MHT70");
  m_wpPlots["L1T_MHT70"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF30");
  m_wpPlots["DijetVBF30"] = new L1TPlots(d);

  d = dirDiffDijet->mkdir("DijetVBF40");
  m_wpPlots["DijetVBF40"] = new L1TPlots(d);

  d = dirDiffDijet->mkdir("DijetVBF50");
  m_wpPlots["DijetVBF50"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF30_DEta3p0");
  m_wpPlots["DijetVBF30_DEta3p0"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF40_DEta3p0");
  m_wpPlots["DijetVBF40_DEta3p0"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF30_DEta3p5");
  m_wpPlots["DijetVBF30_DEta3p5"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF40_DEta3p5");
  m_wpPlots["DijetVBF40_DEta3p5"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF30_DPhiJJ1p0");
  m_wpPlots["DijetVBF30_DPhiJJ1p0"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF40_DPhiJJ1p0");
  m_wpPlots["DijetVBF40_DPhiJJ1p0"] = new L1TPlots(d);

  d = dirDiffDijet->mkdir("DijetVBF30_DPhiJJ1p5");
  m_wpPlots["DijetVBF30_DPhiJJ1p5"] = new L1TPlots(d);
  
  d = dirDiffDijet->mkdir("DijetVBF40_DPhiJJ1p5");
  m_wpPlots["DijetVBF40_DPhiJJ1p5"] = new L1TPlots(d);
  
  //####################################
 
  TDirectory* dirSameDijet = runDir->mkdir("SameDijet");
  
  d = dirSameDijet->mkdir("DijetVBF30_DEta3p0");
  m_wpSameDijetPlots["DijetVBF30_DEta3p0"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF40_DEta3p0");
  m_wpSameDijetPlots["DijetVBF40_DEta3p0"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF30_DEta3p5");
  m_wpSameDijetPlots["DijetVBF30_DEta3p5"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF40_DEta3p5");
  m_wpSameDijetPlots["DijetVBF40_DEta3p5"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF30_DPhiJJ1p0");
  m_wpSameDijetPlots["DijetVBF30_DPhiJJ1p0"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF40_DPhiJJ1p0");
  m_wpSameDijetPlots["DijetVBF40_DPhiJJ1p0"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF30_DPhiJJ1p5");
  m_wpSameDijetPlots["DijetVBF30_DPhiJJ1p5"] = new L1TPlots(d);
  
  d = dirSameDijet->mkdir("DijetVBF40_DPhiJJ1p5");
  m_wpSameDijetPlots["DijetVBF40_DPhiJJ1p5"] = new L1TPlots(d);
  
  //####################################
  
  TDirectory* dirSameDijetNotETM70 = runDir->mkdir("SameDijetNotETM70");
  
  d = dirSameDijetNotETM70->mkdir("L1T_ETM60");
  m_wpSameDijetNotETM70Plots["L1T_ETM60"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("L1T_HTT70");
  m_wpSameDijetNotETM70Plots["L1T_HTT70"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF30_DEta3p0");
  m_wpSameDijetNotETM70Plots["DijetVBF30_DEta3p0"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF40_DEta3p0");
  m_wpSameDijetNotETM70Plots["DijetVBF40_DEta3p0"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF30_DEta3p5");
  m_wpSameDijetNotETM70Plots["DijetVBF30_DEta3p5"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF40_DEta3p5");
  m_wpSameDijetNotETM70Plots["DijetVBF40_DEta3p5"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF30_DPhiJJ1p0");
  m_wpSameDijetNotETM70Plots["DijetVBF30_DPhiJJ1p0"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF40_DPhiJJ1p0");
  m_wpSameDijetNotETM70Plots["DijetVBF40_DPhiJJ1p0"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF30_DPhiJJ1p5");
  m_wpSameDijetNotETM70Plots["DijetVBF30_DPhiJJ1p5"] = new L1TPlots(d);
  
  d = dirSameDijetNotETM70->mkdir("DijetVBF40_DPhiJJ1p5");
  m_wpSameDijetNotETM70Plots["DijetVBF40_DPhiJJ1p5"] = new L1TPlots(d);
  
  //####################################
  //m_wpConsectivePlots
  
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
