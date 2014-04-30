#ifndef MCDijetFilter_h
#define MCDijetFilter_h
// -*- C++ -*-
//
// Package:    MCDijetFilter
// Class:      MCDijetFilter
// 
/* 

 Description: filter events based on the Pythia particle information

 Implementation: inherits from generic EDFilter
     
*/
//
// Original Author:  Fabian Stoeckli
//         Created:  Mon Sept 11 10:57:54 CET 2006
// $Id: MCDijetFilter.h,v 1.3 2010/07/21 04:23:23 wmtan Exp $
//
//


// system include files
#include <memory>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

#include "TFile.h"
#include "TH1D.h"

//
// class decleration
//

class MCDijetFilter : public edm::EDFilter {
public:
  explicit MCDijetFilter(const edm::ParameterSet&);
  ~MCDijetFilter();

   virtual bool filter(edm::Event&, const edm::EventSetup&);
private:

  // ----------memeber function----------------------
  int    charge      (const int& Id);
  std::vector<HepMC::GenParticle*> getVisibleDecayProducts(HepMC::GenParticle* particle);
  std::vector<HepMC::GenParticle*> getNu (const HepMC::GenEvent* particles);
  std::vector<HepMC::GenParticle*> getSt3(const HepMC::GenEvent* particles);
  void printGenVector(std::vector<HepMC::GenParticle*> vec);
  double nuMET(std::vector<HepMC::GenParticle*> vNu);
  
  std::vector<const reco::GenJet*> filterGenJets(const std::vector<reco::GenJet>* jets);
//   std::vector<const reco::GenJet*> filterGenJets(const std::vector<reco::GenJet>* jets);
  
  // ----------member data ---------------------------
  std::string label_;
  std::vector<int> particleID1;
  std::vector<int> particleID2;
  double ptMin;
  double etaMin;  
  double etaMax;
  std::vector<int> status;
  int particleCharge;
  double minInvMass;
  double maxInvMass;
  double minDeltaPhi;
  double maxDeltaPhi;
  double minDeltaEta;
  double maxDeltaEta;
  double minDeltaR;
  double maxDeltaR;
  std::string outFile_;

  TFile* outFile;
  std::map<std::string,TH1D*> m_plots;
       
};
#endif
