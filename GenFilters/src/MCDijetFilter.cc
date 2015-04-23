#include "VBFHiggsToInvisible/GenFilters/interface/MCDijetFilter.h"


#include <HepMC/GenVertex.h>

// ROOT includes
#include "TMath.h"

// C++ includes
#include <iostream>

using namespace edm;
using namespace std;


MCDijetFilter::MCDijetFilter(const edm::ParameterSet& iConfig) :
label_        (iConfig.getUntrackedParameter("moduleLabel",std::string("generator"))),
particleCharge(iConfig.getUntrackedParameter("ParticleCharge",0)),
minInvMass    (iConfig.getUntrackedParameter("MinInvMass",    0.)),
maxInvMass    (iConfig.getUntrackedParameter("MaxInvMass",    14000.)),
minDeltaPhi   (iConfig.getUntrackedParameter("MinDeltaPhi",   0.)),
maxDeltaPhi   (iConfig.getUntrackedParameter("MaxDeltaPhi",   3.2)),
minDeltaEta   (iConfig.getUntrackedParameter("MinDeltaEta",   0.)),
maxDeltaEta   (iConfig.getUntrackedParameter("MaxDeltaEta",   10000.)),
minDeltaR     (iConfig.getUntrackedParameter("MinDeltaR",     0.)),
maxDeltaR     (iConfig.getUntrackedParameter("MaxDeltaR",     10000.)),
outFile_(iConfig.getUntrackedParameter("outFile",std::string("dijetFilter.root")))
{

  m_inputTag_GenJetCollection = consumes<reco::GenJetCollection>(iConfig.getUntrackedParameter<edm::InputTag>("inputTag_GenJetCollection",edm::InputTag("ak5GenJetsNoNu")));

  //here do whatever other initialization is needed
  ptMin               = iConfig.getUntrackedParameter<double>("MinPt",    20);
  etaMin              = iConfig.getUntrackedParameter<double>("MinEta", -5.0);
  etaMax              = iConfig.getUntrackedParameter<double>("MaxEta",  5.0);
  oppositeHemisphere  = iConfig.getUntrackedParameter<bool>  ("bool",   true);
  
  outFile = new TFile(outFile_.c_str(),"RECREATE");
  TDirectory* dirPre = outFile->mkdir("preFilter");
  TDirectory* dirPos = outFile->mkdir("posFilter");
  
  preFilter_Jets_Multiplicity = new TH1D("Jets_Multiplicity","Jets_Multiplicity", 50,-0.5,       49.5); preFilter_Jets_Multiplicity->SetDirectory(dirPre);
  preFilter_Jet0_Pt           = new TH1D("Jet0_Pt",          "Jet0_Pt",          500,   0,       2500); preFilter_Jet0_Pt          ->SetDirectory(dirPre);
  preFilter_Jet1_Pt           = new TH1D("Jet1_Pt",          "Jet1_Pt",          500,   0,       2500); preFilter_Jet1_Pt          ->SetDirectory(dirPre);
  preFilter_Dijet_EtaProduct  = new TH1D("Dijet_EtaProduct", "Dijet_EtaProduct",  50, -25,         25); preFilter_Dijet_EtaProduct ->SetDirectory(dirPre);
  preFilter_Dijet_MaxMjj      = new TH1D("Dijet_MaxMjj",     "Dijet_MaxMjj",     500,   0,       2500); preFilter_Dijet_MaxMjj     ->SetDirectory(dirPre);
  preFilter_Dijet_MaxDEta     = new TH1D("Dijet_MaxDEta",    "Dijet_MaxDEta",    100,   0,         10); preFilter_Dijet_MaxDEta    ->SetDirectory(dirPre);
  preFilter_Dijet_MinDPhi     = new TH1D("Dijet_MinDPhi",    "Dijet_MinDPhi",     32,   0,TMath::Pi()); preFilter_Dijet_MinDPhi    ->SetDirectory(dirPre);

  posFilter_Jets_Multiplicity = new TH1D("Jets_Multiplicity","Jets_Multiplicity", 50,-0.5,       49.5); posFilter_Jets_Multiplicity->SetDirectory(dirPos);
  posFilter_Jet0_Pt           = new TH1D("Jet0_Pt",          "Jet0_Pt",          500,   0,       2500); posFilter_Jet0_Pt          ->SetDirectory(dirPos);
  posFilter_Jet1_Pt           = new TH1D("Jet1_Pt",          "Jet1_Pt",          500,   0,       2500); posFilter_Jet1_Pt          ->SetDirectory(dirPos);
  posFilter_Dijet_EtaProduct  = new TH1D("Dijet_EtaProduct", "Dijet_EtaProduct",  50, -25,         25); posFilter_Dijet_EtaProduct ->SetDirectory(dirPos);
  posFilter_Dijet_Mjj         = new TH1D("Dijet_Mjj",        "Dijet_Mjj",        500,   0,       2500); posFilter_Dijet_Mjj        ->SetDirectory(dirPos);
  posFilter_Dijet_DEta        = new TH1D("Dijet_DEta",       "Dijet_DEta",       100,   0,         10); posFilter_Dijet_DEta       ->SetDirectory(dirPos);
  posFilter_Dijet_DPhi        = new TH1D("Dijet_DPhi",       "Dijet_DPhi",        32,   0,TMath::Pi()); posFilter_Dijet_DPhi       ->SetDirectory(dirPos);
  
}

MCDijetFilter::~MCDijetFilter(){

  outFile->Write();
  outFile->Close();
  
}


std::vector<HepMC::GenParticle*> MCDijetFilter::getVisibleDecayProducts(HepMC::GenParticle* particle)
{
  
  
//   for(HepMC::GenEvent::particle_const_iterator p = event->particles_begin(); p != event->particles_end(); ++p ){
//   
//     if((*p)->status == 1){
//       
//       
//     }
//   }
  
  vector<HepMC::GenParticle*> decayProducts;
  vector<HepMC::GenParticle*> toDecay;
  toDecay.push_back(particle);
  
  bool finished = false; 
 
  cout << "Called getVisibleDecayProducts()" << endl;
  cout << "Mother st=" << particle->status() << " id=" << particle->pdg_id() << " pT=" << particle->momentum().perp() << endl;
  
  while(!finished){
    bool didSomething = false;
    
    cout << endl << "--> New decay cycle... " << toDecay.size() << " to decay!" << endl;
    
    vector<HepMC::GenParticle*> newToDecay;
    
    for(unsigned i=0; i<toDecay.size(); i++){
      
      HepMC::GenVertex* vtx = toDecay[i]->end_vertex();
      cout << "---> Decaying st=" << toDecay[i]->status() << " id=" << toDecay[i]->pdg_id() << " pT=" << toDecay[i]->momentum().perp() 
           << " nParents: " <<  vtx->particles_in_size() << endl;
	   
      if(vtx->particles_in_size() != 1){
	cout << "WTF_start______________" << endl;
	for(vector<HepMC::GenParticle*>::const_iterator p = vtx->particles_in_const_begin(); p != vtx->particles_in_const_end(); p++){
          cout << "parent st=" << (*p)->status() << " id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
	}
        cout << "WTF_end________________" << endl;
      }
      
      if(vtx){
        for(HepMC::GenVertex::particles_out_const_iterator p = vtx->particles_out_const_begin(); p != vtx->particles_out_const_end(); p++)
        {
	  if((*p)->status() == 1){
	    decayProducts.push_back(*p);
	    cout << "stable st=" << (*p)->status() << " id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
	  }
	  else{
	    newToDecay.push_back(*p);
	    didSomething = true;
	    cout << "toDecay st=" << (*p)->status() << " id=" << (*p)->pdg_id() << " pT=" << (*p)->momentum().perp() << endl;
	  }
	  
	  decayProducts.push_back(*p);
        }
      }else{cout << "No vertex!" << endl;}
    }
    
    
    if(!didSomething){finished=true;}
    else{toDecay = newToDecay;}
  } 
  
  cout << endl << "N stable particles: " << decayProducts.size() << endl;
  
  double pX=0;
  double pY=0;
  for(unsigned i=0; i<decayProducts.size(); i++){
    pX += decayProducts[i]->momentum().px();
    pY += decayProducts[i]->momentum().py();
  }
  double pT = sqrt(pow(pX,2)+pow(pY,2));
  cout << "Decay sum pT: " << pT << endl;
  
  return decayProducts;
  
}

vector<const reco::GenJet*> MCDijetFilter::filterGenJets(const vector<reco::GenJet>* jets){
  
  vector<const reco::GenJet*> out;
  
  for(unsigned i=0; i<jets->size(); i++){
    
    const reco::GenJet* j = &((*jets)[i]);
    
    if(j->p4().pt() >ptMin &&  j->p4().eta()>etaMin && j->p4().eta()<etaMax)
    {
      out.push_back(j);  
    }
  }
  
  return out;
}


// ------------ method called to skim the data  ------------
bool MCDijetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  bool pass = false;
  
  //Handle<HepMCProduct> evt;
  //iEvent.getByLabel(label_, evt);
  //const HepMC::GenEvent* myGenEvent = evt->GetEvent();

  Handle< vector<reco::GenJet> > handleGenJets;          
  iEvent.getByToken(m_inputTag_GenJetCollection, handleGenJets);
  const vector<reco::GenJet>* genJets = handleGenJets.product();  
  
  vector<const reco::GenJet*> filGenJets = filterGenJets(genJets);
  
  // This code will get the neutrino gen met
  //vector<HepMC::GenParticle*> colNu  = getNu (myGenEvent);
  //double met = nuMET(colNu);
 
  double maxdijetProd = -999;
  double minDPhi      =  999;
  double maxDEta      =    0;
  double maxMjj       =    0;
  
  for(unsigned a=0; a<filGenJets.size(); a++){
    for(unsigned b=a+1; b<filGenJets.size(); b++){    
    
      const reco::GenJet* pA = filGenJets[a];
      const reco::GenJet* pB = filGenJets[b];
     
      // Getting the dijet vector
      math::XYZTLorentzVector diJet = pA->p4() + pB->p4();

      // Calculating quantities
      double dijetProd = pA->p4().eta()*pB->p4().eta();
      double dPhi      = fabs(pA->p4().phi()-pB->p4().phi());
      double dEta      = fabs(pA->p4().eta()-pB->p4().eta());
      double invMass   = diJet.mass();

      // Updating max/min variables
      
      if(dijetProd>maxdijetProd){maxdijetProd=dijetProd;}
      if(dPhi     <minDPhi)     {minDPhi=dPhi;}
      if(dEta     >maxDEta)     {maxDEta=dEta;}
      if(invMass  >maxMjj)      {maxMjj=invMass;}
      
      // If this event has passed cuts already... continue
      if(pass){continue;}
      
      // Testing cuts
      if(oppositeHemisphere && dijetProd>=0){continue;}
      if(dPhi<=minDeltaPhi || dPhi>=maxDeltaPhi)                {continue;}
      if(dEta<=minDeltaEta || dEta>=maxDeltaEta)                {continue;}
      if(invMass<=minInvMass || invMass>=maxInvMass)            {continue;}

      // If we passed all cuts fill plots
      posFilter_Jets_Multiplicity->Fill(filGenJets.size());
      posFilter_Jet0_Pt          ->Fill(pA->pt());
      posFilter_Jet1_Pt          ->Fill(pB->pt());
      posFilter_Dijet_EtaProduct ->Fill(dijetProd);
      posFilter_Dijet_Mjj        ->Fill(invMass);
      posFilter_Dijet_DEta       ->Fill(dEta);
      posFilter_Dijet_DPhi       ->Fill(dPhi);
       
      pass = true;
    }
  }
  
  preFilter_Jets_Multiplicity->Fill(genJets->size());
  if(genJets->size()>=2){
    preFilter_Jet0_Pt         ->Fill((*genJets)[0].pt());
    preFilter_Jet1_Pt         ->Fill((*genJets)[1].pt());
    preFilter_Dijet_EtaProduct->Fill(maxdijetProd);
    preFilter_Dijet_MaxMjj    ->Fill(maxMjj);
    preFilter_Dijet_MaxDEta   ->Fill(maxDEta);
    preFilter_Dijet_MinDPhi   ->Fill(minDPhi);
  }
  
  return pass;
}

vector<HepMC::GenParticle*> MCDijetFilter::getSt3(const HepMC::GenEvent* vGen){

  vector<HepMC::GenParticle*> out;
  
  for ( HepMC::GenEvent::particle_const_iterator p = vGen->particles_begin(); p != vGen->particles_end(); ++p ) {
    if((*p)->status()==3){out.push_back(*p);}
  }

  return out;
}

vector<HepMC::GenParticle*> MCDijetFilter::getNu(const HepMC::GenEvent* vGen){

  vector<HepMC::GenParticle*> out;
  
  for ( HepMC::GenEvent::particle_const_iterator p = vGen->particles_begin(); p != vGen->particles_end(); ++p ) {
    if     ((*p)->status()==1 && abs((*p)->pdg_id()) == 12){out.push_back(*p);}
    else if((*p)->status()==1 && abs((*p)->pdg_id()) == 14){out.push_back(*p);}
    else if((*p)->status()==1 && abs((*p)->pdg_id()) == 16){out.push_back(*p);}      
  }

  return out;
}

void MCDijetFilter::printGenVector(std::vector<HepMC::GenParticle*> vec){
  
  for(unsigned i=0; i<vec.size(); i++){
    printf("#%3d - id=%4d st=%1d pt=%6.3f eta=%6.3f phi=%6.3f px=%6.3f py=%6.3f pz=%6.3f\n",i,
           vec[i]->pdg_id(), 
           vec[i]->status(),
           vec[i]->momentum().perp(),
           vec[i]->momentum().eta(),
           vec[i]->momentum().phi(),
           vec[i]->momentum().px(),
           vec[i]->momentum().py(),
           vec[i]->momentum().pz());
	
  } 
}

double MCDijetFilter::nuMET(vector<HepMC::GenParticle*> vNu){

  double nuPx=0.;
  double nuPy=0.;
 
  for(unsigned i=0; i<vNu.size(); i++) {
    nuPx += vNu[i]->momentum().px();
    nuPy += vNu[i]->momentum().py();
  }

  if(vNu.size()>0){
    double neutrinoPt = sqrt(pow(nuPx,2)+pow(nuPy,2));
    return neutrinoPt;
  }
  else{return 0.;}
}


int MCDijetFilter::charge(const int& Id){

  
  //...Purpose: to give three times the charge for a particle/parton.

  //      ID     = particle ID
  //      hepchg = particle charge times 3

  int kqa,kq1,kq2,kq3,kqj,irt,kqx,kqn;
  int hepchg;


  int ichg[109]={-1,2,-1,2,-1,2,-1,2,0,0,-3,0,-3,0,-3,0,
-3,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,3,6,0,0,3,6,0,0,-1,2,-1,2,-1,2,0,0,0,0,
-3,0,-3,0,-3,0,0,0,0,0,-1,2,-1,2,-1,2,0,0,0,0,
-3,0,-3,0,-3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


  //...Initial values. Simple case of direct readout.
  hepchg=0;
  kqa=abs(Id);
  kqn=kqa/1000000000%10;
  kqx=kqa/1000000%10;
  kq3=kqa/1000%10;
  kq2=kqa/100%10;
  kq1=kqa/10%10;
  kqj=kqa%10;
  irt=kqa%10000;

  //...illegal or ion
  //...set ion charge to zero - not enough information
  if(kqa==0 || kqa >= 10000000) {

    if(kqn==1) {hepchg=0;}
  }
  //... direct translation
  else if(kqa<=100) {hepchg = ichg[kqa-1];}
  //... KS and KL (and undefined)
  else if(kqj == 0) {hepchg = 0;}
  //C... direct translation
  else if(kqx>0 && irt<100)
    {
      hepchg = ichg[irt-1];
      if(kqa==1000017 || kqa==1000018) {hepchg = 0;}
      if(kqa==1000034 || kqa==1000052) {hepchg = 0;}
      if(kqa==1000053 || kqa==1000054) {hepchg = 0;}
      if(kqa==5100061 || kqa==5100062) {hepchg = 6;}
    }
  //...Construction from quark content for heavy meson, diquark, baryon.
  //...Mesons.
  else if(kq3==0)
    {
      hepchg = ichg[kq2-1]-ichg[kq1-1];
      //...Strange or beauty mesons.
      if((kq2==3) || (kq2==5)) {hepchg = ichg[kq1-1]-ichg[kq2-1];}
    }
  else if(kq1 == 0) {
    //...Diquarks.
    hepchg = ichg[kq3-1] + ichg[kq2-1];
  }

  else{
    //...Baryons
    hepchg = ichg[kq3-1]+ichg[kq2-1]+ichg[kq1-1];
  }

  //... fix sign of charge
  if(Id<0 && hepchg!=0) {hepchg = -1*hepchg;}

  // cout << hepchg<< endl;
  return hepchg;
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCDijetFilter);