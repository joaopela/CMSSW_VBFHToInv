// -*- C++ -*-
//
// Package:    TracksAnalyser
// Class:      TracksAnalyser
// 
/**\class TracksAnalyser TracksAnalyser.cc t/TracksAnalyser/src/TracksAnalyser.cc
 * 
 D *escription: [one line class summary]
 
 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Joao Arnauth Pela,510 1-002,+41227679913,
//         Created:  Tue May  6 12:37:33 CEST 2014
// $Id$
//
//


// system include files
#include <memory>


#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

#include <string>
#include <vector>
#include <map>

class TracksAnalyser : public edm::EDAnalyzer {
public:
  explicit TracksAnalyser(const edm::ParameterSet&);
  ~TracksAnalyser();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  void printEvSummary();
  void doTracksHist    (TDirectory* d);
  void doTracksAnalysis(TDirectory* d,double minTrackPt);
  void doTracksDisplay (TDirectory* f,int n,double minTrackPt);  
  bool pu_id_mva_loose (double mvaValue,double pt,double eta);
  bool cjvPass         ();
  //____________________________________
  bool m_verbose;
  
  int cBarrel; 
  
  unsigned cEvCount,cEvPass,cEvBBPass,cEvBEPass,cEvEEPass;
  unsigned nEvDraw;
  
  // Handles for event content
  edm::Handle<reco::VertexCollection> vertexCollection;
  edm::Handle<reco::TrackCollection>  trackCollection;
  edm::Handle<std::vector<pat::Jet> > jetCollection;
  edm::Handle<edm::ValueMap<float> >  puJetIdMVA;
  
  const reco::Vertex *pV;
  const pat::Jet     *jet0,*jet1;
  
  TFile *outFile;
  TH1D  *hCount;
  
  std::map<std::string,TH1D*>       m_h1D; 
  std::map<std::string,TDirectory*> m_dirs;
    
  
  // ----------member data ---------------------------
};