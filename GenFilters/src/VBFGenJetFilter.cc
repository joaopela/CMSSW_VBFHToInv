#include "CMSSW_VBFHToInv/GenFilters/interface/VBFGenJetFilter.h"


#include <HepMC/GenVertex.h>

// ROOT includes
#include "TMath.h"

// C++ includes
#include <iostream>

using namespace edm;
using namespace std;


VBFGenJetFilter::VBFGenJetFilter(const edm::ParameterSet& iConfig) :
oppositeHemisphere(iConfig.getUntrackedParameter<bool>  ("bool",   true)),
ptMin             (iConfig.getUntrackedParameter<double>("MinPt",    20)),
etaMin            (iConfig.getUntrackedParameter<double>("MinEta", -5.0)),
etaMax            (iConfig.getUntrackedParameter<double>("MaxEta",  5.0)),
minInvMass        (iConfig.getUntrackedParameter("MinInvMass",    0.)),
maxInvMass        (iConfig.getUntrackedParameter("MaxInvMass",    14000.)),
minDeltaPhi       (iConfig.getUntrackedParameter("MinDeltaPhi",   0.)),
maxDeltaPhi       (iConfig.getUntrackedParameter("MaxDeltaPhi",   3.2)),
minDeltaEta       (iConfig.getUntrackedParameter("MinDeltaEta",   0.)),
maxDeltaEta       (iConfig.getUntrackedParameter("MaxDeltaEta",   10000.)),
minDeltaR         (iConfig.getUntrackedParameter("MinDeltaR",     0.)),
maxDeltaR         (iConfig.getUntrackedParameter("MaxDeltaR",     10000.))
{
  
  m_inputTag_GenJetCollection = consumes<reco::GenJetCollection>(iConfig.getUntrackedParameter<edm::InputTag>("inputTag_GenJetCollection",edm::InputTag("ak5GenJetsNoNu")));
  
}

VBFGenJetFilter::~VBFGenJetFilter(){
  
}

vector<const reco::GenJet*> VBFGenJetFilter::filterGenJets(const vector<reco::GenJet>* jets){
  
  vector<const reco::GenJet*> out;
  
  for(unsigned i=0; i<jets->size(); i++){
    
    const reco::GenJet* j = &((*jets)[i]);
    
    if(j->p4().pt() >ptMin &&  j->p4().eta()>etaMin && j->p4().eta()<etaMax)
    {
      out.push_back(j);
    }
  }
  
  return out;
}


// ------------ method called to skim the data  ------------
bool VBFGenJetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  Handle< vector<reco::GenJet> > handleGenJets;
  iEvent.getByToken(m_inputTag_GenJetCollection, handleGenJets);
  const vector<reco::GenJet>* genJets = handleGenJets.product();
  
  // Getting filtered generator jets
  vector<const reco::GenJet*> filGenJets = filterGenJets(genJets);
  
  // If we do not find at least 2 jets veto the event
  if(filGenJets.size()<2){return false;}
  
  for(unsigned a=0; a<filGenJets.size(); a++){
    for(unsigned b=a+1; b<filGenJets.size(); b++){    
      
      const reco::GenJet* pA = filGenJets[a];
      const reco::GenJet* pB = filGenJets[b];
      
      // Getting the dijet vector
      math::XYZTLorentzVector diJet = pA->p4() + pB->p4();
      
      // Testing opposite hemispheres
      double dijetProd = pA->p4().eta()*pB->p4().eta();
      if(oppositeHemisphere && dijetProd>=0){continue;}

      // Testing dijet mass
      double invMass = diJet.mass();
      if(invMass<=minInvMass || invMass>=maxInvMass){continue;}
      
      // Testing dijet delta eta
      double dEta = fabs(pA->p4().eta()-pB->p4().eta());
      if(dEta<=minDeltaEta || dEta>=maxDeltaEta){continue;}

      // Testing dijet delta phi
      double dPhi = fabs(pA->p4().phi()-pB->p4().phi());
      if(dPhi<=minDeltaPhi || dPhi>=maxDeltaPhi){continue;}
      
      return true;
    }
  }
  
  return false;
}

//define this as a plug-in
DEFINE_FWK_MODULE(VBFGenJetFilter);