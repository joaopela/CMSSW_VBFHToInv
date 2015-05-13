#include "CMSSW-VBFHToInv/TriggerStudies/interface/L1TAdditionalRateStudies.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "CMSSW-VBFHToInv/TriggerStudies/interface/L1ExtraPayload.h"
#include "CMSSW-VBFHToInv/TriggerStudies/interface/L1TDijet.h"

#include <stdio.h>
#include <math.h>

using namespace std;

L1TAdditionalRateStudies::L1TAdditionalRateStudies(const edm::ParameterSet& pset){
  
  ps      = pset;
  evCount = 0;
  
  // Getting InputTag from configuration file
//   m_InputTag_L1GTReadoutRecord      = pset.getUntrackedParameter("inputTag_L1GTReadoutRecord",     InputTag("gtDigis"));
//   m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          InputTag("l1extraParticles","MET"));
//   m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter("inputTag_L1Extra_mhts",          InputTag("l1extraParticles","MHT"));
//   m_InputTag_HLTResults             = pset.getUntrackedParameter("inputTag_HLTResults",            InputTag("TriggerResults","HLT"));
//   m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter("inputTag_L1CaloRegionCollection",InputTag("gctDigis"));
//   m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_EcalTriggerPrimitives", InputTag("ecalDigis","EcalTriggerPrimitives"));
//   m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_HcalTriggerPrimitives", InputTag("valHcalTriggerPrimitiveDigis"));
  
  m_l1GtDataDaqInputTag = ps.getParameter<edm::InputTag>("inputTagL1GtDataDaq");
  
  // Getting other parameters from configuration file
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",false);
  
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","L1TAdditionalRateStudiesResults.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  hEventCount = new TH1I("EventCount","EventCount",1,0.5,1.5); hEventCount->SetDirectory(fOut);
  hMenu       = new TH1I("Menu","Menu",7,0.5,7.5); hMenu->SetDirectory(fOut);
  
  myL1TSim = new L1TSimulator();
  
}

L1TAdditionalRateStudies::~L1TAdditionalRateStudies(){
  
  delete myL1TSim;
  fOut->Write();
  
  delete hEventCount;
}

void L1TAdditionalRateStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  evCount++;
  hEventCount->Fill(1);
  
  edm::Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecordData;
  iEvent.getByLabel(m_l1GtDataDaqInputTag, gtReadoutRecordData);
  
  DecisionWord dw;
  
  // Getting the prescale index used when this event was triggered
  if(gtReadoutRecordData.isValid()){
    
    // Getting Final Decision Logic (FDL) Data from GT
    
    const vector<L1GtFdlWord>& gtFdlVectorData = gtReadoutRecordData->gtFdlVector();
    
    // Running over FDL results to get which bits fired
    for(unsigned int a=0 ; a<gtFdlVectorData.size() ; a++){
      
      // Selecting the FDL that triggered
      if(gtFdlVectorData[a].bxInEvent() == 0){
        dw = gtFdlVectorData[a].gtDecisionWord();
      }
    }
  }
  
  bool l1t = myL1TSim->l1tResult(dw);
  
  bool l1Seed_ETM70       = false;
  bool l1Seed_Dijet_ETM50 = false;
  bool l1Seed_Dijet_Jet96 = false;
  
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
  
  if(l1t)                       {hMenu->Fill(1);}
  if(l1Seed_ETM70)              {hMenu->Fill(2);}
  if(l1Seed_ETM70 && !l1t)      {hMenu->Fill(3);}
  if(l1Seed_Dijet_ETM50)        {hMenu->Fill(4);}
  if(l1Seed_Dijet_ETM50 && !l1t){hMenu->Fill(5);}
  if(l1Seed_Dijet_Jet96)        {hMenu->Fill(6);}
  if(l1Seed_Dijet_Jet96 && !l1t){hMenu->Fill(7);}
  
}

void L1TAdditionalRateStudies::beginJob(){
  
  
  
}

void L1TAdditionalRateStudies::endJob(){
  
  
  
}

void L1TAdditionalRateStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  myL1TSim->getMenu(iSetup);
  
}

void L1TAdditionalRateStudies::endRun(edm::Run const&, edm::EventSetup const&){
  
  
  
}

void L1TAdditionalRateStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){
  
  
  
}

void L1TAdditionalRateStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){
  
  
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TAdditionalRateStudies);
