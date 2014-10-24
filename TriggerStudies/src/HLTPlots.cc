#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPlots.h"

#include "TDirectory.h"
#include "TMath.h"

using namespace std;

HLTPlotsData::HLTPlotsData(){
  this->init();
}

HLTPlotsData::HLTPlotsData(HLTEventData* data){
 
  this->init();
  this->getData(data);
}

void HLTPlotsData::init(){
  pf_met.first           = false;
  pf_dijet_maxDEta.first = false;
  pf_dijet_maxMjj.first  = false;
  
  calo_met.first            = false;
  calo_dijet_maxDEta.first  = false;
  calo_dijet_maxMjj.first   = false;
  
  m_BasePathNamePFObjects = "HLT_PFMET_PFVBF_Unseeded_v1";
  m_BaseJetFilterPFJets   = "hltDiPFJet20MJJ500AllJetsDEta2p5";
  m_BaseJetFilterPFMET    = "hltPFMET40";
  
  m_BasePathNameCaloObjects = "HLT_PFMET_PFVBF_Unseeded_v1";
  m_BaseJetFilterCaloJets   = "hltDiCaloJet20MJJ500AllJetsDEta2p5";
  m_BaseJetFilterCaloMET    = "hltMETCleanUsingJetID40";
  
}

void HLTPlotsData::getData(HLTEventData* data){
  
  // Getting variables from loose pf trigger
  if(data->getPathFired(m_BasePathNamePFObjects)){
    
    HLTPathData* thePath = data->getPathData(m_BasePathNamePFObjects);
    
    pf_met.first  = true;
    pf_met.second = thePath->getFilterObjects(m_BaseJetFilterPFMET).at(0)->pt();
    
    std::vector<HLTDiobject*> myDijet = thePath->getFilterDiobjects(m_BaseJetFilterPFJets);
    
    if(myDijet.size()>0){
      pf_dijet_maxDEta.first  = true;
      pf_dijet_maxDEta.second = myDijet[0]->deta();
      pf_dijet_maxMjj.first   = true;
      pf_dijet_maxMjj.second  = myDijet[0]->mjj();
    }
    
    for(unsigned i=1; i<myDijet.size(); i++){
      
      HLTDiobject* dijet = myDijet[i];
      if(dijet->deta()>pf_dijet_maxDEta.second){pf_dijet_maxDEta.second=dijet->deta();}
      if(dijet->mjj() >pf_dijet_maxMjj .second){pf_dijet_maxMjj .second=dijet->mjj();}
    }
  }
  
  // Getting variables from loose calo trigger
  if(data->getPathFired(m_BasePathNameCaloObjects)){
    
    HLTPathData* thePath = data->getPathData(m_BasePathNameCaloObjects);
    
    calo_met.first  = true; 
    calo_met.second = thePath->getFilterObjects(m_BaseJetFilterCaloMET).at(0)->pt();
    
    std::vector<HLTDiobject*> myDijet = thePath->getFilterDiobjects(m_BaseJetFilterCaloJets);
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

void HLTPlotsData::setBasePathNamePFObjects(std::string pathName){
  m_BasePathNamePFObjects = pathName;
}

void HLTPlotsData::setBaseJetFilterPFJets  (std::string filterName){
  m_BaseJetFilterPFJets = filterName;
}

void HLTPlotsData::setBaseJetFilterPFMET   (std::string filterName){
  m_BaseJetFilterPFMET = filterName;
}

void HLTPlotsData::setBasePathNameCaloObjects(std::string pathName){
  m_BasePathNameCaloObjects = pathName;
}

void HLTPlotsData::setBaseJetFilterCaloJets  (std::string filterName){
  m_BaseJetFilterCaloJets = filterName;
}

void HLTPlotsData::setBaseJetFilterCaloMET   (std::string filterName){
  m_BaseJetFilterCaloMET = filterName;
}

//##########################################################
//##########################################################

HLTPlots::HLTPlots(){

  pf_met           = 0;
  pf_dijet_maxDEta = 0;
  pf_dijet_maxMjj  = 0;
  
  calo_met           = 0;
  calo_dijet_maxDEta = 0;
  calo_dijet_maxMjj  = 0;

}

HLTPlots::HLTPlots(TDirectory* d){

  // PF plots
  pf_met = new TH1D("pf_met","HLT PF MET",500,0,500);
  pf_met->GetXaxis()->SetTitle("MET [GeV]");
  pf_met->GetYaxis()->SetTitle("Entries");
  pf_met->SetDirectory(d);
  
  pf_dijet_maxDEta = new TH1D("pf_dijet_maxDEta","HLT PF Dijet max(#Delta#eta)" ,100,0,10);
  pf_dijet_maxDEta->GetXaxis()->SetTitle("Dijet max(#Delta#eta)");
  pf_dijet_maxDEta->GetYaxis()->SetTitle("Entries");
  pf_dijet_maxDEta->SetDirectory(d);
  
  pf_dijet_maxMjj = new TH1D("pf_dijet_maxMjj","HLT PF Dijet max(m_{jj})"  , 400,  0,2000);
  pf_dijet_maxMjj->GetXaxis()->SetTitle("Dijet max(m_{jj} [GeV]");
  pf_dijet_maxMjj->GetYaxis()->SetTitle("Entries");
  pf_dijet_maxMjj->SetDirectory(d);
  
  // Calo plots
  calo_met = new TH1D("calo_met","HLT PF MET"  , 500, 0,500);
  calo_met->GetXaxis()->SetTitle("HLT MET [GeV]");
  calo_met->GetYaxis()->SetTitle("Entries");
  calo_met->SetDirectory(d);
  
  calo_dijet_maxDEta = new TH1D("calo_dijet_maxDEta","HLT PF Dijet max(#Delta#eta)" ,100,0,10);
  calo_dijet_maxDEta->GetXaxis()->SetTitle("Dijet max(#Delta#eta)");
  calo_dijet_maxDEta->GetYaxis()->SetTitle("Entries");
  calo_dijet_maxDEta->SetDirectory(d);
  
  calo_dijet_maxMjj = new TH1D("calo_dijet_maxMjj","HLT PF Dijet max(m_{jj})"  , 400, 0,2000);
  calo_dijet_maxMjj->GetXaxis()->SetTitle("Dijet max(m_{jj} [GeV]");
  calo_dijet_maxMjj->GetYaxis()->SetTitle("Entries");
  calo_dijet_maxMjj->SetDirectory(d);
  
}

void HLTPlots::fill(HLTPlotsData data){
  
  if(data.pf_met          .first){pf_met          ->Fill(data.pf_met          .second);}
  if(data.pf_dijet_maxDEta.first){pf_dijet_maxDEta->Fill(data.pf_dijet_maxDEta.second);}
  if(data.pf_dijet_maxMjj .first){pf_dijet_maxMjj ->Fill(data.pf_dijet_maxMjj .second);}
  
  if(data.calo_met          .first){calo_met          ->Fill(data.calo_met          .second);}
  if(data.calo_dijet_maxDEta.first){calo_dijet_maxDEta->Fill(data.calo_dijet_maxDEta.second);}
  if(data.calo_dijet_maxMjj .first){calo_dijet_maxMjj ->Fill(data.calo_dijet_maxMjj .second);}
  
}

HLTPlots::~HLTPlots(){
  delete pf_met;
  delete pf_dijet_maxDEta;
  delete pf_dijet_maxMjj;
  
  delete calo_met;
  delete calo_dijet_maxDEta;
  delete calo_dijet_maxMjj;
}
