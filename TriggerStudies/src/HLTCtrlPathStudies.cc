#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTCtrlPathStudies.h"

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

HLTCtrlPathStudies::HLTCtrlPathStudies(const edm::ParameterSet& pset){
  
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
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","HLTCtrlPathStudiesResults.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // This histogram will be used to count our events (for normalisation later)
  hEventCount = new TH1I("EventCount","EventCount",1,0.5,1.5); hEventCount->SetDirectory(fOut);

  // Other histograms
  m_hltAlgos = pset.getParameter< vector<string> >("HLTPaths");
  
  hHLTPathCount = new TH1I("HLTPathCount","HLTPathCount",m_hltAlgos.size(),0.5,m_hltAlgos.size()+0.5); hEventCount->SetDirectory(fOut);
  for(unsigned i=0; i<m_hltAlgos.size(); i++){
    hHLTPathCount->GetXaxis()->SetBinLabel(i+1,m_hltAlgos[i].c_str());
  }
  hHLTPathCount->SetDirectory(fOut);
  
  hHLT_jet_eta = new TH1D("HLT_jet_eta","HLT_Jet_eta",100,-5.0,5.0); hHLT_jet_eta->SetDirectory(fOut);
  hHLT_L1TETM  = new TH1D("HLT_L1TETM", "HLT_L1TETM", 500,   0,500); hHLT_L1TETM ->SetDirectory(fOut);
  
  // Other variables
  valMin_l1Seed_ETM = pset.getUntrackedParameter<double>("valMin_l1Seed_ETM",50);
  
  // #################################################################
  // Initiating plots and algos for no L1T seeds
  // #################################################################
  TDirectory *dNoCuts = fOut->mkdir("L1T_NoCuts");
  
  vector< pair<double,double> > cutsDijetPt;
  cutsDijetPt.push_back(pair<double,double>(  0, 0));
  cutsDijetPt.push_back(pair<double,double>( 30,30));
  cutsDijetPt.push_back(pair<double,double>( 35,35));
  cutsDijetPt.push_back(pair<double,double>( 40,40));
  cutsDijetPt.push_back(pair<double,double>( 50,50));
  cutsDijetPt.push_back(pair<double,double>( 60,60));
  cutsDijetPt.push_back(pair<double,double>( 50,40));
  cutsDijetPt.push_back(pair<double,double>( 60,40));
  //cutsDijetPt.push_back(pair<double,double>( 70,40));
  //cutsDijetPt.push_back(pair<double,double>( 80,40));
  //cutsDijetPt.push_back(pair<double,double>( 90,40));
  //cutsDijetPt.push_back(pair<double,double>(100,40));
  
  vector<double> cutsDijetMjj;
  cutsDijetMjj.push_back(  0);
  cutsDijetMjj.push_back(500);
  cutsDijetMjj.push_back(600);
  cutsDijetMjj.push_back(700);
  cutsDijetMjj.push_back(800);
  //cutsDijetMjj.push_back(900);
  //cutsDijetMjj.push_back(1000);
  //cutsDijetMjj.push_back(1100);
  
  vector<double> cutsDijetDEta;
  cutsDijetDEta.push_back(  0);
  cutsDijetDEta.push_back(3.0);
  cutsDijetDEta.push_back(3.3);
  cutsDijetDEta.push_back(3.5);
  cutsDijetDEta.push_back(3.7);
  cutsDijetDEta.push_back(3.9);
  //cutsDijetDEta.push_back(4.1);
  //cutsDijetDEta.push_back(4.3);
  //cutsDijetDEta.push_back(4.5);
  
  for(unsigned iDijetPt=0; iDijetPt<cutsDijetPt.size(); iDijetPt++){
    for(unsigned iDijetMjj=0; iDijetMjj<cutsDijetMjj.size(); iDijetMjj++){
      for(unsigned iDijetDEta=0; iDijetDEta<cutsDijetDEta.size(); iDijetDEta++){

        string algoName = Form("HLT_DijetVBF%.0f-%.0f_DEta%.1f_MJJ%.0f",cutsDijetPt[iDijetPt].first,cutsDijetPt[iDijetPt].second,cutsDijetDEta[iDijetDEta],cutsDijetMjj[iDijetMjj]);
        //cout << "Creating HLT algo: " << algoName.c_str() << endl;
        
        // New HLT algo declaration
        HLTAlgoPFDijet* myAlgo  = new HLTAlgoPFDijet(algoName);
        
        // This is added to make ETM70+HLT analysis
	myAlgo->setBasePathFilter("HLT_L1ETM70_PFMET_PFVBF_v1");
	myAlgo->setBaseJetFilter ("hltDiPFJet20MJJ500AllJetsDEta2p5");
	// no L1 seeded
        //myAlgo->setBasePathFilter("HLT_PFMET_PFVBF_Unseeded_v1");
        //myAlgo->setBaseJetFilter ("hltDiPFJet20MJJ500AllJetsDEta2p5");
        
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

HLTCtrlPathStudies::~HLTCtrlPathStudies(){
  
  fOut->Write();
  
  for(unsigned i=0; i<m_algos.size(); i++){
    delete m_algos[i].first;
    delete m_algos[i].second;
  }
  
  delete hEventCount;
  delete hHLTPathCount;
}

void HLTCtrlPathStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  // Counting the current event
  hEventCount->Fill(1);

  // Evaluation of L1T conditions
  bool l1Seed_ETM_X  = false;
  L1ExtraPayload evL1Extra(ps,iEvent);
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=valMin_l1Seed_ETM){l1Seed_ETM_X = true;}

  // Getting HLT data
  HLTEventData myHLTData(ps,iEvent);
  
  // Filling HLT fire counts
  for(unsigned i=0; i<m_hltAlgos.size(); i++){
    if(myHLTData.getPathFired(m_hltAlgos[i])){
      hHLTPathCount->Fill(i+1);
    }
  }
  
  // Veto processing/filling event if ETM50 did not file
  if(!l1Seed_ETM_X){return;}
  
  hHLT_L1TETM->Fill(evL1Extra.m_L1EtMissParticle_MET->begin()->et());
  
  /*hHLT_L1TETM
  bool l1Seed_ETM70       = false;
  bool l1Seed_Dijet_ETM50 = false;
  bool l1Seed_Dijet_Jet96 = false;
  
  // WARNING: Plots are not being created yet when m_doL1TAnalysis is true
  if(m_doL1TAnalysis){
    
    // Extracting L1Extra information

    
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
  

  
  // Commented for ETM70+HLT analysis
  // HLTPlotsData evData(&myHLTData);

  // This is added to make ETM70+HLT analysis
  HLTPlotsData evData;
  //evData.setBasePathNameCaloObjects("HLT_L1ETM70_PFMET_PFVBF_v1");
  //evData.setBaseJetFilterCaloJets  ("hltDiCaloJet20MJJ500AllJetsDEta2p5");
  //evData.setBaseJetFilterCaloMET   ("hltMETCleanUsingJetID80");
  //evData.setBasePathNamePFObjects  ("HLT_L1ETM70_PFMET_PFVBF_v1");
  //evData.setBaseJetFilterPFJets    ("hltDiPFJet20MJJ500AllJetsDEta2p5");
  //evData.setBaseJetFilterPFMET     ("hltPFMET40");
  //evData.getData(&myHLTData);
  // no L1 seeded
  evData.setBasePathNameCaloObjects("HLT_CaloMET_CaloVBF_Unseeded_v1");
  evData.setBaseJetFilterCaloJets  ("hltDiCaloJet20MJJ500AllJetsDEta2p5");
  evData.setBaseJetFilterCaloMET   ("hltMETCleanUsingJetID40");
  evData.setBasePathNamePFObjects  ("HLT_PFMET_PFVBF_Unseeded_v1");
  evData.setBaseJetFilterPFJets    ("hltDiPFJet20MJJ500AllJetsDEta2p5");
  evData.setBaseJetFilterPFMET     ("hltPFMET40");
  evData.getData(&myHLTData);
  
  if(m_verbose){myHLTData.print();}

  // Global object plots
  //if(myHLTData.getPathFired("HLT_L1ETM70_PFMET_PFVBF_v1")){
  //  vector<HLTObject*> jets = myHLTData.getPathData("HLT_L1ETM70_PFMET_PFVBF_v1")->getFilterObjects("hltDiPFJet20MJJ500AllJetsDEta2p5");
  //  for(unsigned i=0; i<jets.size(); i++){hHLT_jet_eta->Fill(jets[i]->eta());}
  //}
  // no L1 seeded 
  if(myHLTData.getPathFired("HLT_PFMET_PFVBF_Unseeded_v1")){
   vector<HLTObject*> jets = myHLTData.getPathData("HLT_PFMET_PFVBF_Unseeded_v1")->getFilterObjects("hltDiPFJet20MJJ500AllJetsDEta2p5");
   for(unsigned i=0; i<jets.size(); i++){hHLT_jet_eta->Fill(jets[i]->eta());}
  }

  // Evaluating HLT algorithms
  for(auto i=m_algos.begin(); i<m_algos.end(); i++){

    if(i->first->evaluate(&myHLTData)){
      i->second->fill(evData);
    }
  }
}

void HLTCtrlPathStudies::beginJob(){}

void HLTCtrlPathStudies::endJob(){}

void HLTCtrlPathStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void HLTCtrlPathStudies::endRun(edm::Run const&, edm::EventSetup const&){}

void HLTCtrlPathStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void HLTCtrlPathStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// TODO: This function can be optimised by caching the trigger names once per run (not once per event)
bool HLTCtrlPathStudies::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
  
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

void HLTCtrlPathStudies::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
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
DEFINE_FWK_MODULE(HLTCtrlPathStudies);
