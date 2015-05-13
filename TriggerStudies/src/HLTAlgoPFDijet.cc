#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTAlgoPFDijet.h"

using namespace std;

HLTAlgoPFDijet::HLTAlgoPFDijet(){

  m_algoName = "";
  m_vbf  = false;
  m_jet0 = 0;
  m_jet1 = 0;
  m_mjj  = 0;
  m_deta = 0;
  m_dphi = 0;
}

HLTAlgoPFDijet::HLTAlgoPFDijet(std::string algoName){
  
  m_algoName = algoName;
  
  m_vbf  = false;
  m_jet0 = 0;
  m_jet1 = 0;
  m_mjj  = 0;
  m_deta = 0;
  m_dphi = 100;
  
  m_basePathName  = "HLT_PFMET_PFVBF_Unseeded_v1";
  m_baseJetFilter = "hltDiPFJet20MJJ500AllJetsDEta2p5";
  
}

HLTAlgoPFDijet::~HLTAlgoPFDijet(){}

bool HLTAlgoPFDijet::evaluate(HLTEventData *hltData){
  
  if(!hltData->getPathFired(m_basePathName)){return false;}
  
  bool out = false;
  
  HLTPathData* thePath = hltData->getPathData(m_basePathName);
  vector<HLTDiobject*> myDijet = thePath->getFilterDiobjects(m_baseJetFilter);
  
  for(unsigned i=0; i<myDijet.size(); i++){
    
    HLTDiobject* dijet = myDijet[i];
    
    // Checking jet pT conditions (dijet jets are pT sorted)
    if(dijet->j0()->pt()<m_jet0){continue;}
    if(dijet->j1()->pt()<m_jet1){continue;}
    
    // Checking VBF condition
    if(m_vbf){
      if(!dijet->vbf()){
        continue;
      }
    }

    if(dijet->mjj() <m_mjj) {continue;} // Checking VBF condition
    if(dijet->deta()<m_deta){continue;} // Checking Delta eta
    if(dijet->dphi()>m_dphi){continue;} // Checking Delta phi
    
    // If all conditions passed algo passed!
    out = true;
    break;
  }
  
  return out;
}

void HLTAlgoPFDijet::setVBF(bool vbf){
  m_vbf = vbf;
}

void HLTAlgoPFDijet::setJetsMinPt(double jet0,double jet1){
  m_jet0 = jet0;
  m_jet1 = jet1;
}

void HLTAlgoPFDijet::setDijetMinMjj(double mjj){
  m_mjj = mjj;
}

void HLTAlgoPFDijet::setDijetMinDEta(double deta){
  m_deta = deta;
}

void HLTAlgoPFDijet::setDijetMaxDPhi(double dphi){
  m_dphi = dphi;
}

void HLTAlgoPFDijet::setBasePathFilter(std::string basePathName){
  m_basePathName = basePathName;
}

void HLTAlgoPFDijet::setBaseJetFilter (std::string baseJetFilter){
  m_baseJetFilter = baseJetFilter;
}
