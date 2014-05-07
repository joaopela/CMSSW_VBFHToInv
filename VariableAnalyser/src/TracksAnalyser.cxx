#include "VBFHiggsToInvisible/VariableAnalyser/interface/TracksAnalyser.h"

// CMSSW includes
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// ROOT included
#include "TDirectory.h"
#include "TMath.h"

using namespace std;
using namespace edm;

TracksAnalyser::TracksAnalyser(const edm::ParameterSet& iConfig){

  nEventsTrackDistribution = iConfig.getUntrackedParameter<unsigned>("nEventsTrackDistribution",10);
  
  // Variable initialisation
  eventCount = 0;
  
  edm::Service<TFileService> fs;
 
  double pi = TMath::Pi();
 

  
  for(unsigned i=0; i<nEventsTrackDistribution; i++){
    
    char* nName;
    nName = Form("Event%d_TrackDistribution",i);
    hEvTrackDistribution  .push_back(fs->make<TH2D>(nName,nName,48,-2.4,2.4,32,-pi,pi));
    nName = Form("Event%d_TrackPtDistribution",i);
    hEvTrackPtDistribution.push_back(fs->make<TH2D>(nName,nName,48,-2.4,2.4,32,-pi,pi));    
    
    nName = Form("Event%d_PvTrackDistribution",i);
    hEvPvTrackDistribution   .push_back(fs->make<TH2D>(nName,nName,48,-2.4,2.4,32,-pi,pi));
    nName = Form("Event%d_PvTrackPtDistribution",i);
    hEvPvTrackPtDistribution .push_back(fs->make<TH2D>(nName,nName,48,-2.4,2.4,32,-pi,pi));
    
  }

  
}


TracksAnalyser::~TracksAnalyser()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TracksAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  edm::Handle<reco::VertexCollection> vertexCollection;
  edm::Handle<reco::TrackCollection>  trackCollection;
  
  iEvent.getByLabel(edm::InputTag("goodOfflinePrimaryVertices"),vertexCollection);
  iEvent.getByLabel("generalTracks",trackCollection);
    
  reco::Vertex pV = vertexCollection->at(0);
  
  cout << "Vertex size            : " << vertexCollection->size() << endl;
  cout << "Tracks size            : " << trackCollection ->size() << endl;
  cout << "Primary vertex nTracks : " << pV.tracksSize() << endl;
  
  TH2D* hEvTrackDist   = hEvTrackDistribution[eventCount];
  TH2D* hEvTrackPtDist = hEvTrackPtDistribution[eventCount];
  
  TH2D* hEvPvTrackDist   = hEvPvTrackDistribution[eventCount];
  TH2D* hEvPvTrackPtDist = hEvPvTrackPtDistribution[eventCount];
  
  
  
  if(eventCount<nEventsTrackDistribution){
  
    for(unsigned i=0; i<trackCollection->size();i++){
    
      hEvTrackDist  ->Fill((*trackCollection)[i].eta(),(*trackCollection)[i].phi());
      hEvTrackPtDist->Fill((*trackCollection)[i].eta(),(*trackCollection)[i].phi(),(*trackCollection)[i].pt());
    }

    for(reco::Vertex::trackRef_iterator it = pV.tracks_begin(); it!=pV.tracks_end(); it++){
      
      hEvPvTrackDist  ->Fill((*it)->eta(),(*it)->phi());
      hEvPvTrackPtDist->Fill((*it)->eta(),(*it)->phi(),(*it)->pt());
    }    
        
  }
  

  /* 
   // Tracks Outside Cone Jet  
   edm::View<reco::Track>::const_iterator track      = trackColl.begin();
   edm::View<reco::Track>::const_iterator tracks_end = trackColl.end();
   
   
   
   
   for (; track != tracks_end; ++track)
     
     
   {
     if ((deltaR(track->eta(),track->phi(),jet1.eta(),jet1.phi()) > 0.5) && (deltaR(track->eta(),track->phi(),jet2.eta(),jet2.phi()) > 0.5))
       
       
     {
       goodTracksCount++;
     }
     
     
     
   }*/
  
  eventCount++;
}


// ------------ method called once each job just before starting event loop  ------------
void 
TracksAnalyser::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TracksAnalyser::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TracksAnalyser::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TracksAnalyser::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TracksAnalyser::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TracksAnalyser::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TracksAnalyser::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TracksAnalyser);
