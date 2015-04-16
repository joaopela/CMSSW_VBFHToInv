
//-ap #include "Configuration/CSA06Skimming/interface/MCMETFilter.h"

#include "VBFHiggsToInvisible/GenFilters/interface/MCMETFilter.h"

#include <iostream>

using namespace edm;
using namespace std;


MCMETFilter::MCMETFilter(const edm::ParameterSet& iConfig) :
label_  (iConfig.getUntrackedParameter("moduleLabel",std::string("generator"))),
mcMet_  (iConfig.getUntrackedParameter("MCMET",0.)),
outFile_(iConfig.getUntrackedParameter("outFile",std::string("metFilter.root")))
{
  outFile      = new TFile(outFile_.c_str(),"RECREATE");
  hNeutrinoMET = new TH1D ("hNeutrinoMET","hNeutrinoMET",500,0,500);
}


MCMETFilter::~MCMETFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  
  outFile->WriteTObject(hNeutrinoMET);
  outFile->Close();
  
  delete hNeutrinoMET;
  
}


// ------------ method called to skim the data  ------------
bool MCMETFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  using namespace edm;

  Handle<HepMCProduct> evt;
  iEvent.getByLabel(label_, evt);
  const HepMC::GenEvent * myGenEvent = evt->GetEvent();
     
  double metNeutrino = neutrinosMET(myGenEvent);
  hNeutrinoMET->Fill(metNeutrino);
   
  if(metNeutrino > mcMet_){
     
     return true; 
  }else{
    return false;
  } 
}

double MCMETFilter::neutrinosMET(const HepMC::GenEvent* vGen){

  double neutrinoPx=0.;
  double neutrinoPy=0.;
  int    nNeutrino=0;
  for ( HepMC::GenEvent::particle_const_iterator p = vGen->particles_begin();
    p != vGen->particles_end(); ++p ) {
  
    if((*p)->status()==1 && abs((*p)->pdg_id()) == 12){
      //cout<<"---------> Neutrino "<<nNeutrino<<" el pt="<<(*p)->momentum().perp()<<endl;
      nNeutrino++;
      neutrinoPx += (*p)->momentum().px();
      neutrinoPy += (*p)->momentum().py();
    }
    else if((*p)->status()==1 && abs((*p)->pdg_id()) == 14){
      //cout<<"---------> Neutrino "<<nNeutrino<<" mu pt="<<(*p)->momentum().perp()<<endl;
      nNeutrino++;
      neutrinoPx += (*p)->momentum().px();
      neutrinoPy += (*p)->momentum().py();
    }
    else if((*p)->status()==1 && abs((*p)->pdg_id()) == 16){
      //cout<<"---------> Neutrino "<<nNeutrino<<" ta pt="<<(*p)->momentum().perp()<<endl;
      nNeutrino++;
      neutrinoPx += (*p)->momentum().px();
      neutrinoPy += (*p)->momentum().py();
    }      
  }

  if(nNeutrino>0){
    double neutrinoPt = sqrt(pow(neutrinoPx,2)+pow(neutrinoPy,2));
    //cout << "Accepted : Neutrino pT: " << neutrinoPt << endl;
    return neutrinoPt;
  }
  else{return 0.;}
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCMETFilter);