// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TriggerStudies_TriggerJet_H
#define VBFHiggsToInvisible_TriggerStudies_TriggerJet_H

#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"

// System include files
#include <string>
#include <utility>

class TriggerJet{
public:
  
  TriggerJet(){}
  TriggerJet(double pt,double eta,double phi,double energy){
    p4.SetPt(pt);
    p4.SetEta(eta);
    p4.SetPhi(phi);
    p4.SetE(energy);
  }

  double pt(){return p4.pt();}
  double px(){return p4.px();}
  double py(){return p4.py();}
  double pz(){return p4.pz();}
  
  double eta(){return p4.eta();}
  double phi(){return p4.phi();}
  double energy(){return p4.energy();}
  
  ROOT::Math::PtEtaPhiEVector p4;

};

#endif
