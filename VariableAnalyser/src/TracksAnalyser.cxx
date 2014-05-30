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

  m_verbose = false;
  
  outFile = new TFile("out.root","RECREATE");

  TDirectory *d;
  d = outFile->mkdir("BB"); m_dirs["BB"] = d;
  d = outFile->mkdir("BE"); m_dirs["BE"] = d;
  d = outFile->mkdir("EE"); m_dirs["EE"] = d;
  
  for(int i=0; i<4; i++){
    d = outFile     ->mkdir(Form("Tracks%1d",i)); doTracksHist(d);
    d = m_dirs["BB"]->mkdir(Form("Tracks%1d",i)); doTracksHist(d);
    d = m_dirs["BE"]->mkdir(Form("Tracks%1d",i)); doTracksHist(d);
    d = m_dirs["EE"]->mkdir(Form("Tracks%1d",i)); doTracksHist(d);
  }
  
  m_h1D["count"] = new TH1D("count","count",7,-0.5, 6.5);
  m_h1D["count"]->SetDirectory(outFile);
  m_h1D["count"]->GetXaxis()->SetBinLabel(1,"Count");
  m_h1D["count"]->GetXaxis()->SetBinLabel(2,"Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(3,"BB Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(4,"BE Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(5,"EE Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(6,"CJV Pass");
  m_h1D["count"]->GetXaxis()->SetBinLabel(7,"CJV Fail");
  
  nEvDraw = iConfig.getUntrackedParameter<unsigned>("nEvDraw",10);  
}


TracksAnalyser::~TracksAnalyser(){}

void TracksAnalyser::doTracksHist(TDirectory* d){
  
  TH1D *h;
  h = new TH1D("TrackOutN",     "TrackOutN",     250,-0.5,249); h->SetDirectory(d); 
  h = new TH1D("TrackOutNRatio","TrackOutNRatio",100,   0,  1); h->SetDirectory(d);
  h = new TH1D("TrackOutE",     "TrackOutE",     500,   0,500); h->SetDirectory(d);
  h = new TH1D("TrackOutERatio","TrackOutERatio",100,   0,  1); h->SetDirectory(d);
  
  TDirectory* CJVFail = d->mkdir("CJVFail");
  h = new TH1D("TrackOutN",     "TrackOutN",     250,-0.5,249); h->SetDirectory(CJVFail); 
  h = new TH1D("TrackOutNRatio","TrackOutNRatio",100,   0,  1); h->SetDirectory(CJVFail);
  h = new TH1D("TrackOutE",     "TrackOutE",     500,   0,500); h->SetDirectory(CJVFail);
  h = new TH1D("TrackOutERatio","TrackOutERatio",100,   0,  1); h->SetDirectory(CJVFail);
  
}

void TracksAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
 
  iEvent.getByLabel(edm::InputTag("selectedAndFilteredPatJets"), jetCollection);
  iEvent.getByLabel(edm::InputTag("goodOfflinePrimaryVertices"), vertexCollection);
  iEvent.getByLabel(edm::InputTag("generalTracks"),              trackCollection);
  iEvent.getByLabel(edm::InputTag("puJetMva","fullDiscriminant"),puJetIdMVA);
  
  pV = &(vertexCollection->at(0));
  
  if(m_verbose){printEvSummary();}
  
  bool evPass = false;
  
  const pat::Jet *jet0,*jet1;
  
  if(jetCollection->size()>2){
    
    jet0 = &(*jetCollection)[0];
    jet1 = &(*jetCollection)[1];
    
    double jet0ID = (*puJetIdMVA)[jet0->originalObjectRef()];
    double jet1ID = (*puJetIdMVA)[jet1->originalObjectRef()];
    
    bool passJet0MVALoose = pu_id_mva_loose(jet0ID,jet0->pt(),jet0->eta());
    bool passJet1MVALoose = pu_id_mva_loose(jet1ID,jet1->pt(),jet1->eta());
    
    // Jet selection
    if(passJet0MVALoose && passJet1MVALoose && jet1->pt()>50){
      
      math::XYZTLorentzVector dijet = jet0->p4()+jet1->p4();
      
      double dEta = abs(jet1->eta() - jet0->eta()); 
      double mjj  = dijet.mass();
    
      // Dijet selection
      if(dEta>3.5 && mjj>700){evPass = true;}       
    }
  }
  
  if(evPass){
     
    int cBarrel=0;
    if(abs(jet0->eta())<2.4){cBarrel++;}
    if(abs(jet1->eta())<2.4){cBarrel++;}
    
    bool cjv = cjvPass();
    
    doTracksAnalysis((TDirectory*) outFile->Get("Tracks0"),0);
    doTracksAnalysis((TDirectory*) outFile->Get("Tracks1"),1);
    doTracksAnalysis((TDirectory*) outFile->Get("Tracks2"),2);
    doTracksAnalysis((TDirectory*) outFile->Get("Tracks3"),3);

    if(cjv){m_h1D["count"]->Fill("CJV Pass",1);}
    else{
      m_h1D["count"]->Fill("CJV Fail",1);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks0/CJVFail"),0);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks1/CJVFail"),1);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks2/CJVFail"),2);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks3/CJVFail"),3);
    }
    
    if(cBarrel==2){
      m_h1D["count"]->Fill("BB Pass",1);
      
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks0"),0);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks1"),1);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks2"),2);
      doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks3"),3);
      
      if(!cjv){
        doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks0/CJVFail"),0);
        doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks1/CJVFail"),1);
        doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks2/CJVFail"),2);
        doTracksAnalysis((TDirectory*) outFile->Get("BB/Tracks3/CJVFail"),3);        
      }
    }
    else if(cBarrel==1){
      m_h1D["count"]->Fill("BE Pass",1);

      doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks0"),0);
      doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks1"),1);
      doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks2"),2);
      doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks3"),3);
      if(!cjv){
        doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks0/CJVFail"),0);
        doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks1/CJVFail"),1);
        doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks2/CJVFail"),2);
        doTracksAnalysis((TDirectory*) outFile->Get("BE/Tracks3/CJVFail"),3);        
      }
    }    
    else if(cBarrel==0){
      m_h1D["count"]->Fill("EE Pass",1);
      
      doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks0"),0);
      doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks1"),1);
      doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks2"),2);
      doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks3"),3);
      if(!cjv){
        doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks0/CJVFail"),0);
        doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks1/CJVFail"),1);
        doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks2/CJVFail"),2);
        doTracksAnalysis((TDirectory*) outFile->Get("EE/Tracks3/CJVFail"),3);        
      }
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
      
    }*/

    m_h1D["count"]->Fill("Pass",1);
  }  

  m_h1D["count"]->Fill("Count",1);
}

void TracksAnalyser::doTracksDisplay(TDirectory* f,int n,double minTrackPt){
  
  const pat::Jet *jet0,*jet1;
  jet0 = &(*jetCollection)[0];
  jet1 = &(*jetCollection)[1];
  
  TStyle st;
  st.SetPalette(1);
  
  TH2D *hPvTrackPt = new TH2D("hPvTrackPt","hPvTrackPt",100,-5.0,5.0,32,-TMath::Pi(),TMath::Pi());
  hPvTrackPt->Draw("colz");
  
  TEllipse *ell0 = new TEllipse(jet0->eta(),jet0->phi(),0.5,0.5);
  TEllipse *ell1 = new TEllipse(jet1->eta(),jet1->phi(),0.5,0.5);
  ell0->SetLineColor(kRed); ell0->SetFillStyle(4000);
  ell1->SetLineColor(kRed); ell1->SetFillStyle(4000);
  ell0->Draw();
  ell1->Draw();     
  
  outFile->Append(hPvTrackPt);
}

void TracksAnalyser::doTracksAnalysis(TDirectory* d,double minTrackPt){
  
  int    nTracks    = 0;
  int    nTracksOut = 0;
  double eTracks    = 0;
  double eTracksOut = 0;
  
  const pat::Jet *jet0,*jet1;
  jet0 = &(*jetCollection)[0];
  jet1 = &(*jetCollection)[1];
  
  for(reco::Vertex::trackRef_iterator it = pV->tracks_begin(); it!=pV->tracks_end(); it++){
        
    if((*it)->pt() < minTrackPt){continue;}
      
    nTracks++;
    eTracks += (*it)->pt();
    
    if(deltaR((*it)->eta(),(*it)->phi(),jet0->eta(),jet0->phi()) < 0.5){continue;}
    if(deltaR((*it)->eta(),(*it)->phi(),jet1->eta(),jet1->phi()) < 0.5){continue;}
    
    nTracksOut++;
    eTracksOut += (*it)->pt();
  }
  
  TH1D *h; 
  h = (TH1D*) d->Get("TrackOutN");      h->Fill(nTracksOut);
  h = (TH1D*) d->Get("TrackOutNRatio"); h->Fill(double(nTracksOut)/double(nTracks));
  h = (TH1D*) d->Get("TrackOutE");      h->Fill(eTracksOut);
  h = (TH1D*) d->Get("TrackOutERatio"); h->Fill(eTracksOut/eTracks); 
  
}


bool TracksAnalyser::pu_id_mva_loose(double mvaValue,double pt,double eta){ 
  // Pt2030_Loose   = cms.vdouble(-0.80,-0.85,-0.84,-0.85),
  // Pt3050_Loose   = cms.vdouble(-0.80,-0.74,-0.68,-0.77)
  // #4 Eta Categories  0-2.5 2.5-2.75 2.75-3.0 3.0-5.0
  double abs_eta = fabs(eta);
  if(pt > 20. && pt <= 30){
    if     (abs_eta < 2.5 ){return (mvaValue > -0.80);} 
    else if(abs_eta < 2.75){return (mvaValue > -0.85);} 
    else if(abs_eta < 3.0) {return (mvaValue > -0.84);} 
    else if(abs_eta < 5.0) {return (mvaValue > -0.85);} 
    else return true;
  } 
  else if(pt > 30.){
    if     (abs_eta < 2.5) {return (mvaValue > -0.80);} 
    else if(abs_eta < 2.75){return (mvaValue > -0.74);} 
    else if(abs_eta < 3.0) {return (mvaValue > -0.68);} 
    else if(abs_eta < 5.0) {return (mvaValue > -0.77);} 
    else return true;
  } 
  else return true;
}

bool TracksAnalyser::cjvPass(){
  
  bool   pass=true;
  double valL=0,valR=0;
  
  jet0 = &(*jetCollection)[0];
  jet1 = &(*jetCollection)[1];
  
  if(jet0->eta() < jet1->eta()){
    valL = jet0->eta();
    valR = jet1->eta();
  }else{
    valL = jet1->eta();
    valR = jet0->eta();
  }
  
  for (unsigned i=2; i<jetCollection->size();i++) {
    
    const pat::Jet *jet = &((*jetCollection)[i]);
    
    double jetID            = (*puJetIdMVA)[jet->originalObjectRef()];
    bool   passJet0MVALoose = pu_id_mva_loose(jetID,jet->pt(),jet->eta());
    
    if(jet->pt()>30 && jet->eta()>valL && jet->eta()<valR && passJet0MVALoose){
      pass=false; 
      break; 
    }
  }  
  
  return pass;
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
