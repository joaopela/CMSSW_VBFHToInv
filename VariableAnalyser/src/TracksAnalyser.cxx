#include "VBFHiggsToInvisible/VariableAnalyser/interface/TracksAnalyser.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/Math/interface/deltaR.h"

using namespace std;
using namespace edm;

TracksAnalyser::TracksAnalyser(const edm::ParameterSet& iConfig){


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
    
  cout << "Vertex size : " << vertexCollection->size() << endl;
  cout << "Tracks size : " << trackCollection ->size() << endl;
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
