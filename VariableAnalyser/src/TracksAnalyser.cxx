#include "VBFHiggsToInvisible/VariableAnalyser/interface/TracksAnalyser.h"

// CMSSW includes


#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

// ROOT included
#include "TCanvas.h"
#include "TDirectory.h"
#include "TMath.h"
#include "TStyle.h"
#include "TEllipse.h"

using namespace std;
using namespace edm;

TracksAnalyser::TracksAnalyser(const edm::ParameterSet& iConfig) : 
dirBB(fs->mkdir("BB")), 
dirBE(fs->mkdir("BE")), 
dirEE(fs->mkdir("EE")){
  
  for(unsigned i=0; i<3; i++){
  
    TFileDirectory *d;
    if(i==0){d=&dirBB;}
    if(i==1){d=&dirBE;}
    if(i==2){d=&dirEE;}
    
    hOutsideTrackNumber     .push_back(d->make<TH1D>("hOutsideTrackNumber",     "hOutsideTrackNumber",     100,-0.5, 99));
    hOutsideTrackNumberRatio.push_back(d->make<TH1D>("hOutsideTrackNumberRatio","hOutsideTrackNumberRatio",100,   0,  1));
    hOutsideTrackEnergy     .push_back(d->make<TH1D>("hOutsideTrackEnergy",     "hOutsideTrackEnergy",     200,   0,200));
    hOutsideTrackEnergyRatio.push_back(d->make<TH1D>("hOutsideTrackEnergyRatio","hOutsideTrackEnergyRatio",100,   0,  1));

  }
  nEvDraw = iConfig.getUntrackedParameter<unsigned>("nEvDraw",10);
  
  outFile = new TFile("out.root","RECREATE");
  
  // Variable initialisation
  cEvCount  = 0;
  cEvPass   = 0;
  cEvBBPass = 0; 
  cEvBEPass = 0; 
  cEvEEPass = 0;
  
}


TracksAnalyser::~TracksAnalyser(){}


//
// member functions
//

// ------------ method called for each event  ------------
void
TracksAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  edm::Handle<reco::VertexCollection> vertexCollection;
  edm::Handle<reco::TrackCollection>  trackCollection;
  edm::Handle<std::vector<pat::Jet> > jetCollection;
  
  iEvent.getByLabel(edm::InputTag("selectedAndFilteredPatJets"),jetCollection);
  iEvent.getByLabel(edm::InputTag("goodOfflinePrimaryVertices"),vertexCollection);
  iEvent.getByLabel("generalTracks",trackCollection);
  
  reco::Vertex pV = vertexCollection->at(0);
  
  bool evPass = false;
  
  int    nTracksIn       = 0;
  int    nTracksOut      = 0;
  double energyTracksIn  = 0;
  double energyTracksOut = 0;
  
  const pat::Jet *jet0,*jet1;
  
  if(jetCollection->size()>2){
    
    jet0 = &(*jetCollection)[0];
    jet1 = &(*jetCollection)[1];
    
    math::XYZTLorentzVector dijet = jet0->p4()+jet1->p4();
    
    double dEta = abs(jet1->eta() - jet0->eta()); 
    double mjj  = dijet.mass();

    if(jet1->pt()>50 && dEta>3.5 && mjj>700){
      evPass = true;
      cout << "Dijet dEta = " << dEta << endl;
      cout << "Dijet mjj  = " << mjj  << endl;
    }    
  }
  
  if(evPass){
  
    std::vector<pat::Jet>::const_iterator iter;
    for (iter = jetCollection->begin(); iter != jetCollection->end(); ++iter) {
      cout << "Jet pt=" << iter->pt() << " eta=" << iter->eta() << endl;  
    }  

    cout << "Vertex size            : " << vertexCollection->size() << endl;
    cout << "Tracks size            : " << trackCollection ->size() << endl;
    cout << "Primary vertex nTracks : " << pV.tracksSize() << endl;
    
    int cBarrel=0;
    if(abs(jet0->eta())<2.4){cBarrel++;}
    if(abs(jet1->eta())<2.4){cBarrel++;}
    
    bool fillTracks = false;
    TCanvas *cPvTrackPt;
    TH2D    *hTrack;
    TH2D    *hTrackPt;
    TH2D    *hPvTrack;
    TH2D    *hPvTrackPt;
    
    if(cEvBBPass<nEvDraw && cBarrel==2){
      fillTracks = true;
      
      char* nName;
      nName = Form("Event%d_Track",cEvBBPass);
      hTrack   = dirBB.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("Event%d_TrackPt",cEvBBPass);
      hTrackPt = dirBB.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());    
      
      nName = Form("Event%d_PvTrack",cEvBBPass);
      hPvTrack    = dirBB.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("Event%d_PvTrackPt",cEvBBPass);
      hPvTrackPt = dirBB.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("BB_Event%d_cPvTrackPt",cEvBBPass);
      cPvTrackPt = new TCanvas(nName);

      cEvBBPass++;
 
    }
    else if(cEvBEPass<nEvDraw && cBarrel==1){
      fillTracks = true;
      
      char* nName;
      nName = Form("Event%d_Track",cEvBEPass);
      hTrack   = dirBE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("Event%d_TrackPt",cEvBEPass);
      hTrackPt = dirBE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());    
      
      nName = Form("Event%d_PvTrack",cEvBEPass);
      hPvTrack    = dirBE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("Event%d_PvTrackPt",cEvBEPass);
      hPvTrackPt = dirBE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("BE_Event%d_cPvTrackPt",cEvBEPass);
      cPvTrackPt = new TCanvas(nName);
      
      cEvBEPass++;      
    }
    else if(cEvEEPass<nEvDraw && cBarrel==0){
      fillTracks = true;
      
      char* nName;
      nName = Form("Event%d_Track",cEvEEPass);
      hTrack   = dirEE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("Event%d_TrackPt",cEvEEPass);
      hTrackPt = dirEE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());    
      
      nName = Form("Event%d_PvTrack",cEvEEPass);
      hPvTrack    = dirEE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("Event%d_PvTrackPt",cEvEEPass);
      hPvTrackPt = dirEE.make<TH2D>(nName,nName,100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
      nName = Form("EE_Event%d_cPvTrackPt",cEvEEPass);
      cPvTrackPt = new TCanvas(nName);
      
      cEvEEPass++;      
    }
    
    if(fillTracks){
      
      for(unsigned i=0; i<trackCollection->size();i++){
        
        hTrack  ->Fill((*trackCollection)[i].eta(),(*trackCollection)[i].phi());
        hTrackPt->Fill((*trackCollection)[i].eta(),(*trackCollection)[i].phi(),(*trackCollection)[i].pt());
      }
      
      for(reco::Vertex::trackRef_iterator it = pV.tracks_begin(); it!=pV.tracks_end(); it++){
        
        hPvTrack  ->Fill((*it)->eta(),(*it)->phi());
        hPvTrackPt->Fill((*it)->eta(),(*it)->phi(),(*it)->pt());
       
        bool inJet = false;
        if(deltaR((*it)->eta(),(*it)->phi(),jet0->eta(),jet0->phi()) < 0.5){inJet = true;}
        
        // Avoid calculating deltaR a second time if already inJet
        if(!inJet){if(deltaR((*it)->eta(),(*it)->phi(),jet1->eta(),jet1->phi()) < 0.5){inJet = true;}          }
        
        if(inJet){
          nTracksIn++;
          energyTracksIn  += (*it)->pt();
        }else{
          nTracksOut++;    
          energyTracksOut += (*it)->pt();
        }
        
      }
      
      if(cBarrel==2){
        hOutsideTrackNumber     [0]->Fill(nTracksOut);
        hOutsideTrackNumberRatio[0]->Fill(double(nTracksOut)/double(nTracksIn+nTracksOut));
        hOutsideTrackEnergy     [0]->Fill(energyTracksOut);
        hOutsideTrackEnergyRatio[0]->Fill(energyTracksOut/(energyTracksIn+energyTracksOut));
      }
      if(cBarrel==1){
        hOutsideTrackNumber     [1]->Fill(nTracksOut);
        hOutsideTrackNumberRatio[1]->Fill(double(nTracksOut)/double(nTracksIn+nTracksOut));
        hOutsideTrackEnergy     [1]->Fill(energyTracksOut);
        hOutsideTrackEnergyRatio[1]->Fill(energyTracksOut/(energyTracksIn+energyTracksOut));
      }
      if(cBarrel==0){
        hOutsideTrackNumber     [2]->Fill(nTracksOut);
        hOutsideTrackNumberRatio[2]->Fill(double(nTracksOut)/double(nTracksIn+nTracksOut));
        hOutsideTrackEnergy     [2]->Fill(energyTracksOut);
        hOutsideTrackEnergyRatio[2]->Fill(energyTracksOut/(energyTracksIn+energyTracksOut));
      }
      
      TStyle st;
      st.SetPalette(1);
      
      cPvTrackPt->cd();
      hPvTrackPt->Draw("colz");
      TEllipse *ell0 = new TEllipse(jet0->eta(),jet0->phi(),0.5,0.5);
      TEllipse *ell1 = new TEllipse(jet1->eta(),jet1->phi(),0.5,0.5);
      ell0->SetLineColor(kRed); ell0->SetFillStyle(4000);
      ell1->SetLineColor(kRed); ell1->SetFillStyle(4000);
      ell0->Draw();
      ell1->Draw();     
      outFile->Append(cPvTrackPt);
    }

    cEvPass++;
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
  
  cEvCount++;
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
TracksAnalyser::endRun(edm::Run const&, edm::EventSetup const&){
  
  cout << "Event Count   : " << cEvCount << endl;
  cout << "Event Pass    : " << cEvPass  << endl;
  cout << "Event BB Pass : " << cEvBBPass << endl;
  cout << "Event BE Pass : " << cEvBEPass << endl; 
  cout << "Event EE Pass : " << cEvEEPass << endl;
  cout << "Efficiency    : " << double(cEvPass)/double(cEvCount) << endl;
  outFile->Write();
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
