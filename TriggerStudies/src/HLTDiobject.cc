#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTDiobject.h"

using namespace std;

HLTDiobject::HLTDiobject(){
  m_jet0 = 0;
  m_jet1 = 0;
  
  cached_vbf  = false;
  cached_deta = false;
  cached_dphi = false;
  cached_mjj  = false;
}

HLTDiobject::HLTDiobject(HLTObject *jet0,HLTObject *jet1){
  m_jet0 = jet0;
  m_jet1 = jet1;
  
  cached_vbf  = false;
  cached_deta = false;
  cached_dphi = false;
  cached_mjj  = false;
}

HLTDiobject::~HLTDiobject(){}

bool HLTDiobject::vbf(){
  
  if(!cached_vbf){
    if( ( m_jet0->eta()>0 && m_jet1->eta()<0 ) || ( m_jet0->eta()<0 && m_jet1->eta()>0) ){
      m_vbf = true;
    }
    else{
      m_vbf = false;
    }
    cached_vbf = true;
  }
  return m_vbf;
}

double HLTDiobject::deta(){
  
  if(!cached_deta){
    m_deta = fabs( m_jet0->eta() - m_jet1->eta() );
    cached_deta = true;
  }
  return m_deta;
}

double HLTDiobject::dphi(){
  if(!cached_dphi){
    m_dphi = fabs(reco::deltaPhi(m_jet0->phi(),m_jet1->phi()));
    cached_dphi = true;
  }
  return m_dphi;
}

double HLTDiobject::mjj(){
  
  if(!cached_mjj){
    double px = m_jet0->px() + m_jet1->px();
    double py = m_jet0->py() + m_jet1->py();
    double pz = m_jet0->pz() + m_jet1->pz();
    double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
    m_mjj = sqrt(pow(m_jet0->energy()+m_jet1->energy(),2) - normaP);
    cached_mjj = true;
  }
  return m_mjj;
}

HLTObject* HLTDiobject::j0(){return m_jet0;}

HLTObject* HLTDiobject::j1(){return m_jet1;}
