#include "VBFHiggsToInvisible/TriggerStudies/interface/L1TAdditionalRateStudies.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

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
  
  myL1TSim = new L1TSimulator();
  
}

L1TAdditionalRateStudies::~L1TAdditionalRateStudies(){
  
  delete myL1TSim;
  fOut->Write();
}

void L1TAdditionalRateStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  evCount++;
  //hEventCount->Fill(1);
  
  edm::Handle<L1GlobalTriggerReadoutRecord>   gtReadoutRecordData;
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
  
  cout << "FDL: ";
  for(unsigned i=0; i<dw.size(); i++){cout << dw[i];}
  cout << endl;
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
