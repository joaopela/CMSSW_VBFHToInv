#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTObject.h"

#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

#include <iostream>

using namespace std;

HLTObject::HLTObject(){}

HLTObject::HLTObject(double pt,double eta,double phi,double energy){
  p4.SetPt(pt);
  p4.SetEta(eta);
  p4.SetPhi(phi);
  p4.SetE(energy);
}

double HLTObject::pt(){return p4.pt();}
double HLTObject::px(){return p4.px();}
double HLTObject::py(){return p4.py();}
double HLTObject::pz(){return p4.pz();}

double HLTObject::eta(){return p4.eta();}
double HLTObject::phi(){return p4.phi();}
double HLTObject::energy(){return p4.energy();}

ROOT::Math::PtEtaPhiEVector HLTObject::getP4(){return p4;}

void HLTObject::addFilter(std::string filterName){
  m_filters.push_back(filterName);
}

bool HLTObject::isJet(){
  for(unsigned i=0; i<m_types.size(); i++){
    if(m_types[i] == trigger::TriggerObjectType::TriggerJet){return true;}
  }
  return false;
}

bool HLTObject::isMET(){
  for(unsigned i=0; i<m_types.size(); i++){
    if(m_types[i] == trigger::TriggerObjectType::TriggerMET){return true;}
  }
  return false;
}

bool HLTObject::passedFilter(std::string filterName){
  
  bool out = false;
  for(unsigned i=0; i<m_filters.size(); i++){
    if(m_filters[i]==filterName){
      out = true;
      break;
    }
  }
  return out;
}

void HLTObject::addType(int type){
  m_types.push_back(type);
}

void HLTObject::print(){
  
  cout << "HLT object pt: " << p4.pt() << " eta:" << p4.eta() << " phi:" << p4.phi() << endl;
  cout << "HLT is of objects types:" << endl;
  for(unsigned i=0; i<m_types.size(); i++){
    cout << " * " << m_types[i];
    if     (m_types[i] == +81){cout << " - TriggerPhoton"   << endl;}
    else if(m_types[i] == +82){cout << " - TriggerElectron" << endl;}
    else if(m_types[i] == +83){cout << " - TriggerMuon"     << endl;}
    else if(m_types[i] == +84){cout << " - TriggerTau"      << endl;}
    else if(m_types[i] == +85){cout << " - TriggerJet"      << endl;}
    else if(m_types[i] == +86){cout << " - TriggerBJet"     << endl;}
    else if(m_types[i] == +87){cout << " - TriggerMET"      << endl;}
    else if(m_types[i] == +88){cout << " - TriggerTET"      << endl;}
    else if(m_types[i] == +89){cout << " - TriggerTHT"      << endl;}
    else if(m_types[i] == +90){cout << " - TriggerMHT"      << endl;}
    else if(m_types[i] == +91){cout << " - TriggerTrack"    << endl;}
    else if(m_types[i] == +92){cout << " - TriggerCluster"  << endl;}
    else if(m_types[i] == +93){cout << " - TriggerMETSig"   << endl;}
    else if(m_types[i] == +94){cout << " - TriggerELongit"  << endl;}
    else if(m_types[i] == +95){cout << " - TriggerMHTSig"   << endl;}
    else if(m_types[i] == +96){cout << " - TriggerHLongit"  << endl;}
    else                      {cout << " - Unknown"  << endl;}
    
  }
  cout << "HLT filters passed:" << endl;
  for(unsigned i=0; i<m_filters.size(); i++){
    cout << " * " << m_filters[i] << endl;
  }
}

