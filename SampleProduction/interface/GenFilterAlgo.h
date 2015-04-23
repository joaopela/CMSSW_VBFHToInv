#ifndef VBFHiggsToInvisible_GenFilters_GenFilterAlgo_h
#define VBFHiggsToInvisible_GenFilters_GenFilterAlgo_h

// CMSSW include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

// ROOT includes
#include "TDirectory.h"
#include "TFile.h"
#include "TH1D.h"

// C++ include files
#include <memory>
#include <vector>
#include <string>

class GenFilterAlgo{
public:
  
  GenFilterAlgo();
  GenFilterAlgo(edm::ParameterSet& pset);
  ~GenFilterAlgo();
  
  void init();
  
  bool evaluate(const std::vector<reco::GenJet>* genJets);
  
  void buildPlots(TDirectory* dir);
  void print();
  
private:
  
  std::vector<const reco::GenJet*> filterGenJets(const std::vector<reco::GenJet>* jets);
  
private:

  std::string m_name;
  
  // Options
  bool  m_doPlots;
  TH1D* m_Jets_Multiplicity;
  TH1D* m_Jet0_Pt;
  TH1D* m_Jet1_Pt;
  TH1D* m_Dijet_EtaProduct;
  TH1D* m_Dijet_MaxMjj;
  TH1D* m_Dijet_MaxDEta;
  TH1D* m_Dijet_MinDPhi;
  
  // Jet cuts
  bool m_doJetMinPt;         double m_valJetMinPt;
  bool m_doJetMaxEta;        double m_valJetMaxEta;

  // Dijet cuts
  bool m_doOppositeHemisphere;
  bool m_doDijetMinDeltaEta; double m_valDijetMinDeltaEta;
  bool m_doDijetMaxDeltaPhi; double m_valDijetMaxDeltaPhi;
  bool m_doDijetMinMjj;      double m_valDijetMinMjj;
  
};

#endif
