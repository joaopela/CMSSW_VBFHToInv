#ifndef VBFHiggsToInvisible_GenFilters_GenFilterAnalyzer_h
#define VBFHiggsToInvisible_GenFilters_GenFilterAnalyzer_h

// CMSSW include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

// My code
#include "VBFHiggsToInvisible/SampleProduction/interface/GenFilterAlgo.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"

// C++ include files
#include <memory>
#include <vector>

class GenFilterAnalyzer : public edm::EDAnalyzer {
public:
  explicit GenFilterAnalyzer(const edm::ParameterSet&);
  ~GenFilterAnalyzer();
  
private:
//   virtual void beginJob() ;
//   virtual void endJob();
  
//   virtual void beginRun(edm::Run const&, edm::EventSetup const&);
//   virtual void endRun(edm::Run const&, edm::EventSetup const&);

//   virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
//   virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
private:
  
  bool m_verbose;
  
  TFile *m_fileOutput;
  
  // Input tags
  edm::EDGetTokenT< reco::GenJetCollection > m_inputTag_GenJetCollection;
  
  std::vector<GenFilterAlgo*> m_algos;
  
  // Declaring histograms
  TH1D*  m_EventCount;
  
  TH1D*  m_Jets_Multiplicity;
  TH1D*  m_Jet0_Pt;
  TH1D*  m_Jet1_Pt;
  TH1D*  m_Dijet_MaxMjj;
  TH1D*  m_Dijet_MaxDEta;
  TH1D*  m_Dijet_MinDPhi;

};

#endif
