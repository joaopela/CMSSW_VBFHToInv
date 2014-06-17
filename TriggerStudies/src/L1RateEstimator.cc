#include "VBFHiggsToInvisible/TriggerStudies/interface/L1RateEstimator.h"

#include <stdio.h>
#include <math.h>

using namespace std;
using namespace edm;

L1RateEstimator::L1RateEstimator(const edm::ParameterSet& pset){
  
  m_verbose                    = pset.getUntrackedParameter<bool>("verbose",false);
  m_selL1Trigger               = pset.getParameter<vector<string> >("selL1Trigger");

  m_InputTag_L1GTReadoutRecord = pset.getParameter<InputTag>("inputTag_L1GTReadoutRecord");
  m_InputTag_L1Extra_mets      = pset.getUntrackedParameter ("inputTag_L1Extra_mets"    ,edm::InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts      = pset.getUntrackedParameter ("inputTag_L1Extra_mhts"    ,edm::InputTag("l1extraParticles","MHT"));

  currentRunNumber = 0;

  fOut = new TFile("L1RateEstimatorResults.root","RECREATE");
  
}

L1RateEstimator::~L1RateEstimator(){
  
  unsigned nRuns = m_nEvents.size();
  TH1D* hRuns = new TH1D("Runs","Runs",nRuns,-0.5,nRuns-0.5);
  hRuns->SetDirectory(fOut);
  
  int bin=0;
  for(map<int,unsigned>::iterator i=m_nEvents.begin(); i!=m_nEvents.end(); i++){
    hRuns->GetXaxis()->SetBinLabel(bin+1,Form("%d",i->first));
    hRuns->SetBinContent(bin+1,i->second);
    bin++;
  }
  
  fOut->Write();
}

void L1RateEstimator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  currentRunNumber = iEvent.run();

  m_nEvents[currentRunNumber]++;
  TH1D* h = m_l1Counts[currentRunNumber];
        
  // Getting Final Decision Logic (FDL) Data from GT
  Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecordData;
  iEvent.getByLabel(m_InputTag_L1GTReadoutRecord, gtReadoutRecordData);
  
  edm::Handle<l1extra::L1EtMissParticleCollection> mets;
  iEvent.getByLabel(m_InputTag_L1Extra_mets,mets);
  
  edm::Handle<l1extra::L1EtMissParticleCollection> mhts;
  iEvent.getByLabel(m_InputTag_L1Extra_mhts,mhts);
  
  if(gtReadoutRecordData.isValid()){
    
    const vector<L1GtFdlWord>& gtFdlVectorData = gtReadoutRecordData->gtFdlVector();
    
    // Running over selected triggers
    for(unsigned i=0; i<m_selL1Trigger.size(); i++){
      
      string pName = m_selL1Trigger[i];
      
      // Running over FDL results to get which bits fired
      for(unsigned int a=0 ; a<gtFdlVectorData.size() ; a++){
        
        // Selecting the FDL that triggered
        if(gtFdlVectorData[a].bxInEvent() == 0){
          
          const L1GtFdlWord* fdl = &(gtFdlVectorData[a]);
          
          for(int bit=0; bit<128; bit++){
            if(fdl->gtDecisionWord()[bit]){h->Fill(bit);}
          }
        }
      }
    }
  }else{cout << "[L1RateEstimator] ERROR: GT Readout Record Data is not valid." << endl;}
  
  if(mets.isValid()){
    if (mets->size()!=0){
      cout << "L1_ETM = " << mets->begin()->et() << endl;
    }else{cout << "[L1RateEstimator] ERROR: l1extraParticles MET has size zero." << endl;}
  }else{cout << "[L1RateEstimator] ERROR: l1extraParticles MET is not valid." << endl;}
  

  if(mhts.isValid()){
    if(mhts->size()!=0){
      cout << "L1_HTT = " << mhts->begin()->etTotal() << endl;    
    }else{cout << "[L1RateEstimator] ERROR: l1extraParticles MHT has size zero." << endl;}
  }else{cout << "[L1RateEstimator] ERROR: l1extraParticles MHT is not valid." << endl;}
}

void L1RateEstimator::beginJob(){}

void L1RateEstimator::endJob(){}

void L1RateEstimator::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  currentRunNumber = iRun.run();
  
  string hName = Form("L1AlgoCounts_Run%d",currentRunNumber);
  m_nEvents [currentRunNumber] = 0;
  m_l1Counts[currentRunNumber] = new TH1D(hName.c_str(),hName.c_str(),128,-0.5,127.5);
  TH1D* h = m_l1Counts[currentRunNumber];
  h->SetDirectory(fOut);
    
  ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);
  const L1GtTriggerMenu* menu = menuRcd.product();
    
  // Filling Alias-Bit Map
  for (CItAlgo algo = menu->gtAlgorithmAliasMap().begin(); algo!=menu->gtAlgorithmAliasMap().end(); ++algo){
    h->GetXaxis()->SetBinLabel((algo->second).algoBitNumber()+1,(algo->second).algoAlias().c_str());
  }
}

void L1RateEstimator::endRun(edm::Run const&, edm::EventSetup const&){}

void L1RateEstimator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void L1RateEstimator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

//define this as a plug-in
DEFINE_FWK_MODULE(L1RateEstimator);
