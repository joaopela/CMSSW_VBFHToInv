// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_L1TDijet_H
#define VBFHiggsToInvisible_TriggerStudies_L1TDijet_H

#include "DataFormats/Math/interface/deltaPhi.h"

// System include files
#include <string>
#include <utility>

class L1TDijet{
public:
  
  L1TDijet(){
    m_jet0 = 0;
    m_jet1 = 0;
    
    cached_vbf  = false;
    cached_deta = false;
    cached_dphi = false;
    cached_mjj  = false;
  }
  
  L1TDijet(l1extra::L1JetParticle *jet0,l1extra::L1JetParticle *jet1){
    m_jet0 = jet0;
    m_jet1 = jet1;
    
    cached_vbf  = false;
    cached_deta = false;
    cached_dphi = false;
    cached_mjj  = false;
  }
  
  bool vbf(){
    
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

  double deta(){
    
    if(!cached_deta){
      m_deta = abs( m_jet0->eta() - m_jet1->eta() );
      cached_deta = true;
    }
    return m_deta;
  }
  
  double dphi(){
    if(!cached_dphi){
      m_dphi = abs(reco::deltaPhi(m_jet0->phi(),m_jet1->phi()));
      cached_dphi = true;
    }
    return m_dphi;
  }
  
  double mjj(){
    
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
  
  l1extra::L1JetParticle* j0(){return m_jet0;}
  l1extra::L1JetParticle* j1(){return m_jet1;}
  
private:

  l1extra::L1JetParticle *m_jet0;
  l1extra::L1JetParticle *m_jet1;
  
  bool cached_vbf;  bool   m_vbf;
  bool cached_deta; double m_deta;
  bool cached_dphi; double m_dphi;
  bool cached_mjj;  double m_mjj;
  
};

#endif
