// -*- C++ -*-
#ifndef VBFHiggsToInvisible_TrigStudies_L1ExtraPayload_H
#define VBFHiggsToInvisible_TrigStudies_L1ExtraPayload_H

// CMSSW included
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1HFRings.h"
#include "DataFormats/L1Trigger/interface/L1HFRingsFwd.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"

// System include files
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

/***********************************************/
/** \brief L1 Extra payload container
 * 
 * This class is a container for the L1 extra particles and quantities.
 * 
 * WARNING: This class will not store a copy of the L1 extra particles
 * it just stores the handles for them. So it should only exist in the
 * scope of the analyse method.
 ***********************************************/ 
class L1ExtraPayload{
public:
  
  L1ExtraPayload();
  L1ExtraPayload(const edm::ParameterSet&, const edm::Event& iEvent);
  
  ~L1ExtraPayload();
  
  bool isValid();
  
  // Get all jets (Central and forward)
  l1extra::L1JetParticleCollection* getL1TAllJets();
  
  // Public variable
  bool variablesLoaded;
  
  edm::Handle<l1extra::L1EmParticleCollection>     m_L1EmParticle_Isolated;
  edm::Handle<l1extra::L1EmParticleCollection>     m_L1EmParticle_NonIsolated;
  edm::Handle<l1extra::L1EtMissParticleCollection> m_L1EtMissParticle_MET;
  edm::Handle<l1extra::L1EtMissParticleCollection> m_L1EtMissParticle_MHT;
  edm::Handle<l1extra::L1HFRingsCollection>        m_L1HFRings;
  edm::Handle<l1extra::L1JetParticleCollection>    m_L1JetParticle_Central;
  edm::Handle<l1extra::L1JetParticleCollection>    m_L1JetParticle_Forward;
  edm::Handle<l1extra::L1JetParticleCollection>    m_L1JetParticle_Tau;
  edm::Handle<l1extra::L1MuonParticleCollection>   m_L1MuonParticle;
  
  
private:
  
  bool                              m_l1tAllJet_cached;
  l1extra::L1JetParticleCollection* m_l1tAllJet;
  
};

#endif