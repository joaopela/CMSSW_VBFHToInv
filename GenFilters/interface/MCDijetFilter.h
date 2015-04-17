#ifndef MCDijetFilter_h
#define MCDijetFilter_h

// CMSSW include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"

// C++ include files
#include <memory>
#include <map>

//
// class declaration
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

//**************************
// Private Member data *****
private:
  
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

  
  // Input tags
  edm::EDGetTokenT< reco::GenJetCollection > m_inputTag_GenJetCollection;
  
  // Declaring Files
  TFile* outFile;
  
  // Declaring histograms
  TH1D*  preFilter_Jets_Multiplicity;
  TH1D*  preFilter_Jet0_Pt;
  TH1D*  preFilter_Jet1_Pt;
  TH1D*  preFilter_Dijet_MaxMjj;
  TH1D*  preFilter_Dijet_MaxDEta;
  TH1D*  preFilter_Dijet_MinDPhi;
  
  TH1D*  posFilter_Jets_Multiplicity;
  TH1D*  posFilter_Jet0_Pt;
  TH1D*  posFilter_Jet1_Pt;
  TH1D*  posFilter_Dijet_Mjj;
  TH1D*  posFilter_Dijet_DEta;
  TH1D*  posFilter_Dijet_DPhi;

};
#endif
