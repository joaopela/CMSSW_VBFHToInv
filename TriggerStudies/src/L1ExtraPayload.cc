#include "VBFHiggsToInvisible/TriggerStudies/interface/L1ExtraPayload.h"
 
#include "FWCore/Utilities/interface/InputTag.h"

#include <stdio.h>
 
using namespace std;
 
struct less_l1ExtraJet{
  bool operator() (const l1extra::L1JetParticle &j1,const l1extra::L1JetParticle &j2) {
    return (j1.pt() < j2.pt());
  }
};

struct greater_l1ExtraJet{
  bool operator() (const l1extra::L1JetParticle &j1,const l1extra::L1JetParticle &j2) {
    return (j1.pt() > j2.pt());
  }
};

L1ExtraPayload::L1ExtraPayload(){
  variablesLoaded    = false;
  m_l1tAllJet_cached = false;
}

L1ExtraPayload::L1ExtraPayload(const edm::ParameterSet& pset, const edm::Event& iEvent){

  variablesLoaded    = true;
  m_l1tAllJet_cached = false;
  
  edm::InputTag inputTag_L1EmParticle_Isolated    = pset.getUntrackedParameter("inputTag_L1EmParticle_Isolated",   edm::InputTag("l1extraParticles","Isolated"   ));
  edm::InputTag inputTag_L1EmParticle_NonIsolated = pset.getUntrackedParameter("inputTag_L1EmParticle_NonIsolated",edm::InputTag("l1extraParticles","NonIsolated"));
  edm::InputTag inputTag_L1EtMissParticle_MET     = pset.getUntrackedParameter("inputTag_L1EtMissParticle_MET",    edm::InputTag("l1extraParticles","MET"        ));
  edm::InputTag inputTag_L1EtMissParticle_MHT     = pset.getUntrackedParameter("inputTag_L1EtMissParticle_MHT",    edm::InputTag("l1extraParticles","MHT"        ));
  edm::InputTag inputTag_L1HFRings                = pset.getUntrackedParameter("inputTag_L1HFRings",               edm::InputTag("l1extraParticles",""           ));
  edm::InputTag inputTag_L1JetParticle_Central    = pset.getUntrackedParameter("inputTag_L1JetParticle_Central",   edm::InputTag("l1extraParticles","Central"    ));
  edm::InputTag inputTag_L1JetParticle_Forward    = pset.getUntrackedParameter("inputTag_L1JetParticle_Forward",   edm::InputTag("l1extraParticles","Forward"    ));
  edm::InputTag inputTag_L1JetParticle_Tau        = pset.getUntrackedParameter("inputTag_L1JetParticle_Tau",       edm::InputTag("l1extraParticles","Tau"        ));
  edm::InputTag inputTag_L1MuonParticle           = pset.getUntrackedParameter("inputTag_L1MuonParticle",          edm::InputTag("l1extraParticles",""           ));
  
  // Retrieving information from the event 
  iEvent.getByLabel(inputTag_L1EmParticle_Isolated,   m_L1EmParticle_Isolated);
  iEvent.getByLabel(inputTag_L1EmParticle_NonIsolated,m_L1EmParticle_NonIsolated);
  iEvent.getByLabel(inputTag_L1EtMissParticle_MET,    m_L1EtMissParticle_MET);
  iEvent.getByLabel(inputTag_L1EtMissParticle_MHT,    m_L1EtMissParticle_MHT);
  iEvent.getByLabel(inputTag_L1HFRings,               m_L1HFRings);
  iEvent.getByLabel(inputTag_L1JetParticle_Central,   m_L1JetParticle_Central);
  iEvent.getByLabel(inputTag_L1JetParticle_Forward,   m_L1JetParticle_Forward);
  iEvent.getByLabel(inputTag_L1JetParticle_Tau,       m_L1JetParticle_Tau);
  iEvent.getByLabel(inputTag_L1MuonParticle,          m_L1MuonParticle);
  
  if(!m_L1EmParticle_Isolated.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1EmParticle_Isolated getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  if(!m_L1EmParticle_NonIsolated.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1EmParticle_NonIsolated getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  if(!m_L1EtMissParticle_MET.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1EtMissParticle_MET getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;    
  }
  if(!m_L1EtMissParticle_MHT.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1EtMissParticle_MHT getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;    
  }
  if(!m_L1HFRings.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1HFRings getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  if(!m_L1JetParticle_Central.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1JetParticle_Central getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  if(!m_L1JetParticle_Forward.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1JetParticle_Forward getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  if(!m_L1JetParticle_Tau.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1JetParticle_Tau getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  if(!m_L1MuonParticle.isValid()){
    cout << "[L1ExtraPayload:] ERROR: Unable to retrieve L1MuonParticle getByLabel(...) result is not valid!" << endl;
    variablesLoaded=false;
  }
  
}

L1ExtraPayload::~L1ExtraPayload(){
  
  if(m_l1tAllJet_cached){delete m_l1tAllJet;}
  
}


l1extra::L1JetParticleCollection* L1ExtraPayload::getL1TAllJets(){

  if(m_l1tAllJet_cached){return m_l1tAllJet;}
  else{

    m_l1tAllJet = new l1extra::L1JetParticleCollection();
    
    // Protecting from accessing unsigned handles if not loaded 
    if(!variablesLoaded){
      cout << "[L1ExtraPayload:] ERROR: Unable to getL1TAllJets() since variablesLoaded=false." << endl;
      return m_l1tAllJet;
    }
    
    for(unsigned i=0; i<m_L1JetParticle_Central->size(); i++){
      m_l1tAllJet->push_back((*m_L1JetParticle_Central)[i]);
    }
    for(unsigned i=0; i<m_L1JetParticle_Forward->size(); i++){
      m_l1tAllJet->push_back((*m_L1JetParticle_Forward)[i]);
    }
//     for(unsigned i=0; i<m_L1JetParticle_Tau->size(); i++){
//       m_l1tAllJet->push_back((*m_L1JetParticle_Tau)[i]);
//     }
    
    sort(m_l1tAllJet->begin(),m_l1tAllJet->end(),greater_l1ExtraJet());
    
    m_l1tAllJet_cached = true;
    return m_l1tAllJet;
  }

}

bool L1ExtraPayload::isValid(){
  return variablesLoaded;
}

