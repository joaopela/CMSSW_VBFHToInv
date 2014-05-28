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

TracksAnalyser::TracksAnalyser(const edm::ParameterSet& iConfig){
  
  outFile = new TFile("out.root","RECREATE");

  
  m_dirs["BB"] = outFile->mkdir("BB");
  m_dirs["BE"] = outFile->mkdir("BE");
  m_dirs["EE"] = outFile->mkdir("EE");
  
  m_h1D["count"] = new TH1D("count","count",5,-0.5, 4.5);
  m_h1D["count"]->SetDirectory(outFile);
  m_h1D["count"]->GetXaxis()->SetBinLabel(1,"Count");
  m_h1D["count"]->GetXaxis()->SetBinLabel(2,"Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(3,"BB Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(4,"BE Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(5,"EE Pass");
  
//   for(unsigned i=0; i<3; i++){
//   
//     TDirectory *d;
//     if(i==0){d=&dirBB;}
//     if(i==1){d=&dirBE;}
//     if(i==2){d=&dirEE;}
//     
//     hOutsideTrackNumber     .push_back(d->make<TH1D>("hOutsideTrackNumber",     "hOutsideTrackNumber",     100,-0.5, 99));
//     hOutsideTrackNumberRatio.push_back(d->make<TH1D>("hOutsideTrackNumberRatio","hOutsideTrackNumberRatio",100,   0,  1));
//     hOutsideTrackEnergy     .push_back(d->make<TH1D>("hOutsideTrackEnergy",     "hOutsideTrackEnergy",     200,   0,200));
//     hOutsideTrackEnergyRatio.push_back(d->make<TH1D>("hOutsideTrackEnergyRatio","hOutsideTrackEnergyRatio",100,   0,  1));
// 
//   }
//   nEvDraw = iConfig.getUntrackedParameter<unsigned>("nEvDraw",10);
    
}


TracksAnalyser::~TracksAnalyser(){}


//
// member functions
//

// ------------ method called for each event  ------------
void TracksAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
 
  iEvent.getByLabel(edm::InputTag("selectedAndFilteredPatJets"), jetCollection);
  iEvent.getByLabel(edm::InputTag("goodOfflinePrimaryVertices"), vertexCollection);
  iEvent.getByLabel(edm::InputTag("generalTracks"),              trackCollection);
  iEvent.getByLabel(edm::InputTag("puJetMva","fullDiscriminant"),puJetIdMVA);
  
  pV = &(vertexCollection->at(0));
  
  if(m_verbose){printEvSummary();}
  
  bool evPass = false;
  
  int    nTracksIn       = 0;
  int    nTracksOut      = 0;
  double energyTracksIn  = 0;
  double energyTracksOut = 0;
  
  const pat::Jet *jet0,*jet1;
  
  if(jetCollection->size()>2){
    
    jet0 = &(*jetCollection)[0];
    jet1 = &(*jetCollection)[1];
    
    double jet0ID = (*puJetIdMVA)[jet0->originalObjectRef()];
    double jet1ID = (*puJetIdMVA)[jet1->originalObjectRef()];
    
    math::XYZTLorentzVector dijet = jet0->p4()+jet1->p4();
    
    double dEta = abs(jet1->eta() - jet0->eta()); 
    double mjj  = dijet.mass();
    
    if(jet1->pt()>50 && dEta>3.5 && mjj>700){
      evPass = true;
    }    
  }
  
  if(evPass){
     
    int cBarrel=0;
    if(abs(jet0->eta())<2.4){cBarrel++;}
    if(abs(jet1->eta())<2.4){cBarrel++;}
    
    if(cBarrel==2){
      m_h1D["count"]->Fill("BB Pass",1);
    }
    else if(cBarrel==1){
      m_h1D["count"]->Fill("BE Pass",1);
    }    
    else if(cBarrel==0){
      m_h1D["count"]->Fill("EE Pass",1);
    }
    
    /*
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
    }*/

    m_h1D["count"]->Fill("Pass",1);
  }  

  m_h1D["count"]->Fill("Count",1);
}

void TracksAnalyser::printEvSummary(){
  
  cout << "===============================================" << endl;  
  cout << "Vertex size            : " << vertexCollection->size() << endl;
  cout << "Tracks size            : " << trackCollection ->size() << endl;
  cout << "Primary vertex nTracks : " << pV->tracksSize() << endl;
  
  cout << "===============================================" << endl;
  for (unsigned i=0; i<jetCollection->size();i++) {
    printf("Jet %d pt=%7.2f eta=%4.2f puMVA=%4.2f\n",i,(*jetCollection)[i].pt(),(*jetCollection)[i].eta(),(*puJetIdMVA)[(*jetCollection)[i].originalObjectRef()]);
  }  

  cout << "===============================================" << endl;
  if(jetCollection->size()>2){
    
    jet0 = &(*jetCollection)[0];
    jet1 = &(*jetCollection)[1];
    
    double jet0ID = (*puJetIdMVA)[jet0->originalObjectRef()];
    double jet1ID = (*puJetIdMVA)[jet1->originalObjectRef()];
    
    math::XYZTLorentzVector dijet = jet0->p4()+jet1->p4();
    
    double dEta = abs(jet1->eta() - jet0->eta()); 
    double mjj  = dijet.mass();
    
    printf("Jet 0 pt=%7.2f eta=%4.2f puMVA=%4.2f\n",jet0->pt(),jet0->eta(),jet0ID);
    printf("Jet 1 pt=%7.2f eta=%4.2f puMVA=%4.2f\n",jet1->pt(),jet1->eta(),jet1ID);
    printf("Dijet Mjj=%7.2f dEta=%4.2f\n",mjj,dEta);
    
  }
  

  
}

void TracksAnalyser::beginJob(){}
void TracksAnalyser::endJob(){}

void TracksAnalyser::beginRun(edm::Run const&, edm::EventSetup const&){}

void TracksAnalyser::endRun(edm::Run const&, edm::EventSetup const&){
  outFile->Write();
}

void TracksAnalyser::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}
void TracksAnalyser::endLuminosityBlock  (edm::LuminosityBlock const&, edm::EventSetup const&){}

void TracksAnalyser::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TracksAnalyser);
