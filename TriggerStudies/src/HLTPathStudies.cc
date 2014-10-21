#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPathStudies.h"

#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObject.h"

// VBFHiggsToInvisible includes
#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTEventData.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1ExtraPayload.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/L1TDijet.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/TriggerJet.h"
#include "VBFHiggsToInvisible/TriggerStudies/interface/TriggerDijet.h"

#include <stdio.h>
#include <math.h>

using namespace std;

HLTPathStudies::HLTPathStudies(const edm::ParameterSet& pset){
  
  ps = pset;
  
  // Getting InputTag from configuration file
  m_InputTag_L1GTReadoutRecord      = pset.getUntrackedParameter("inputTag_L1GTReadoutRecord",     edm::InputTag("gtDigis"));
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          edm::InputTag("l1ExtraLayer2","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter("inputTag_L1Extra_mhts",          edm::InputTag("l1ExtraLayer2","MHT"));
  m_InputTag_HLTResults             = pset.getUntrackedParameter("inputTag_HLTResults",            edm::InputTag("TriggerResults","HLT"));
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter("inputTag_L1CaloRegionCollection",edm::InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_EcalTriggerPrimitives", edm::InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_HcalTriggerPrimitives", edm::InputTag("valHcalTriggerPrimitiveDigis"));
  
  // Getting other parameters from configuration file
  m_doL1TAnalysis = pset.getUntrackedParameter<bool>("doL1TAnalysis",false);
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",      false);

  // Creating output file
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","HLTPathStudiesResults.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // This histogram will be used to count our events (for normalisation later)
  hEventCount = new TH1I("EventCount","EventCount",1,0.5,1.5); hEventCount->SetDirectory(fOut);

  // Other histograms
  hHLTPathCount = new TH1I("HLTPathCount","HLTPathCount",2,0.5,2.5); hEventCount->SetDirectory(fOut);
  hHLTPathCount->GetXaxis()->SetBinLabel(1,"HLT_PFMET_PFVBF_v1");
  hHLTPathCount->GetXaxis()->SetBinLabel(2,"HLT_CaloMET_CaloVBF_v1");
  hHLTPathCount->SetDirectory(fOut);
  
  hHLT_jet_eta =  new TH1D("HLT_jet_eta","HLT_Jet_eta",100,-5.0,5.0); hHLT_jet_eta->SetDirectory(fOut);
  
  // #################################################################
  // Initiating plots and algos for no L1T seeds
  // #################################################################
  TDirectory *dNoCuts = fOut->mkdir("L1T_NoCuts");
  
  vector< pair<double,double> > cutsDijetPt;
  cutsDijetPt.push_back(pair<double,double>(  0, 0));
  cutsDijetPt.push_back(pair<double,double>( 40,40));
  cutsDijetPt.push_back(pair<double,double>( 50,50));
  cutsDijetPt.push_back(pair<double,double>( 60,60));
  cutsDijetPt.push_back(pair<double,double>( 50,40));
  cutsDijetPt.push_back(pair<double,double>( 60,40));
  cutsDijetPt.push_back(pair<double,double>( 70,40));
  cutsDijetPt.push_back(pair<double,double>( 80,40));
  cutsDijetPt.push_back(pair<double,double>( 90,40));
  cutsDijetPt.push_back(pair<double,double>(100,40));
  
  vector<double> cutsDijetMjj;
  cutsDijetMjj.push_back(  0);
  cutsDijetMjj.push_back(500);
  cutsDijetMjj.push_back(600);
  cutsDijetMjj.push_back(700);
  cutsDijetMjj.push_back(800);
  cutsDijetMjj.push_back(900);
  cutsDijetMjj.push_back(1000);
  cutsDijetMjj.push_back(1100);
  
  vector<double> cutsDijetDEta;
  cutsDijetDEta.push_back(  0);
  cutsDijetDEta.push_back(3.5);
  cutsDijetDEta.push_back(3.7);
  cutsDijetDEta.push_back(3.9);
  cutsDijetDEta.push_back(4.1);
  cutsDijetDEta.push_back(4.3);
  cutsDijetDEta.push_back(4.5);
  
  for(unsigned iDijetPt=0; iDijetPt<cutsDijetPt.size(); iDijetPt++){
    for(unsigned iDijetMjj=0; iDijetMjj<cutsDijetMjj.size(); iDijetMjj++){
      for(unsigned iDijetDEta=0; iDijetDEta<cutsDijetDEta.size(); iDijetDEta++){

        string algoName = Form("HLT_DijetVBF%.0f-%.0f_DEta%.1f_MJJ%.0f",cutsDijetPt[iDijetPt].first,cutsDijetPt[iDijetPt].second,cutsDijetDEta[iDijetDEta],cutsDijetMjj[iDijetMjj]);
        
        // New HLT algo declaration
        HLTAlgoPFDijet* myAlgo  = new HLTAlgoPFDijet(algoName);
        myAlgo->setVBF         (true);
        myAlgo->setJetsMinPt   (cutsDijetPt[iDijetPt].first,cutsDijetPt[iDijetPt].second);
        myAlgo->setDijetMinDEta(cutsDijetDEta[iDijetDEta]);
        myAlgo->setDijetMinMjj (cutsDijetMjj[iDijetMjj]);
        
        TDirectory *d       = dNoCuts->mkdir(algoName.c_str());
        HLTPlots   *myPlots = new HLTPlots(d);
        
        m_algos.push_back(pair<HLTAlgo*,HLTPlots*>(myAlgo,myPlots));
      }
    }
  }
}

HLTPathStudies::~HLTPathStudies(){
  
  fOut->Write();
  
  for(unsigned i=0; i<m_algos.size(); i++){
    delete m_algos[i].first;
    delete m_algos[i].second;
  }
  
  delete hEventCount;
  delete hHLTPathCount;
}

void HLTPathStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  // Counting the current event
  hEventCount->Fill(1);
  
  /*
  bool l1Seed_ETM70       = false;
  bool l1Seed_Dijet_ETM50 = false;
  bool l1Seed_Dijet_Jet96 = false;
  
  // WARNING: Plots are not being created yet when m_doL1TAnalysis is true
  if(m_doL1TAnalysis){
    
    // Extracting L1Extra information
    L1ExtraPayload evL1Extra(ps,iEvent);
    l1extra::L1JetParticleCollection *l1tJets = evL1Extra.getL1TAllJets();
    
    // ######################################################################################################
    // Determining what L1 seeds (ETM70 and proposed) would have fired
    // ######################################################################################################
    
    bool             passL1TDijet = false;
    vector<L1TDijet> l1tDijets;
    
    // Looking at L1T dijet condition common to both proposed L1T Trigger DijetVBF30_DEta3p5
    // Running over all possible jet pairs
    for(unsigned j0=0; j0<(*l1tJets).size() ; j0++){
      for(unsigned j1=j0+1; j1<(*l1tJets).size() ; j1++){
        
        L1TDijet dijet(&(*l1tJets)[j0],&(*l1tJets)[j1]);
        
        // Checking VBF condition
        if(dijet.j0()->pt()>=30 && dijet.j1()->pt()>=30 && dijet.vbf() && dijet.deta()>=3.5){passL1TDijet = true; break;}
        
      }
      if(passL1TDijet){break;}
    }
    
    if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=70)                {l1Seed_ETM70       = true;}
    if(passL1TDijet && evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=50){l1Seed_Dijet_ETM50 = true;}
    if(passL1TDijet && (*l1tJets)[0].pt()>=96)                             {l1Seed_Dijet_Jet96 = true;}
    
  }
  */
  
  // Getting HLT data
  HLTEventData myHLTData(ps,iEvent);
  if(m_verbose){myHLTData.print();}

  // Filling HLT fire counts
  HLTPlotsData evData(&myHLTData);
  if(myHLTData.getPathFired("HLT_PFMET_PFVBF_v1")){
    hHLTPathCount->Fill(1);
    
    vector<HLTObject*> jets = myHLTData.getPathData("HLT_PFMET_PFVBF_v1")->getFilterObjects("hltDiPFJet10");
    
    for(unsigned i=0; i<jets.size(); i++){
      hHLT_jet_eta->Fill(jets[i]->eta());
    }
  }
  if(myHLTData.getPathFired("HLT_CaloMET_CaloVBF_v1")){hHLTPathCount->Fill(2);}

  // Evaluating HLT algorithms
  for(auto i=m_algos.begin(); i<m_algos.end(); i++){

    if(i->first->evaluate(&myHLTData)){
      i->second->fill(evData);
    }
  }
}

void HLTPathStudies::beginJob(){}

void HLTPathStudies::endJob(){}

void HLTPathStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void HLTPathStudies::endRun(edm::Run const&, edm::EventSetup const&){}

void HLTPathStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void HLTPathStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// TODO: This function can be optimised by caching the trigger names once per run (not once per event)
bool HLTPathStudies::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
  
  bool Triggered = false;
  
  if( !iHLT.isValid() ) Triggered = false;
  int ntrigs = iHLT->size();
  if(ntrigs==0) Triggered = false;
  
  //check if trigger names are active
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
  //m_triggerNames.init( *iHLT.product() );
  
  for (int itrig = 0; itrig != ntrigs; ++itrig) 
  {
    if( !iHLT->wasrun(itrig) ) continue;
    if( iHLT->error(itrig) ) continue;
    string trigName = m_triggerNames.triggerName(itrig); 
    if( trigName.find(iTriggerName)==std::string::npos ) continue;
    if( !iHLT->accept(itrig) ) continue; 
    Triggered = true;
  }
  
  return Triggered;
  
}

void HLTPathStudies::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
  int ntrigs = iHLT->size();
  
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
  
  for (int itrig = 0; itrig != ntrigs; ++itrig) 
  {
    if( !iHLT->wasrun(itrig) ) continue;
    if(  iHLT->error(itrig) )  continue;
    
    string trigName = m_triggerNames.triggerName(itrig); 
    
    if( !iHLT->accept(itrig) )        continue;
    
    cout << "Fired: " << trigName << endl;    
    
  }
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTPathStudies);