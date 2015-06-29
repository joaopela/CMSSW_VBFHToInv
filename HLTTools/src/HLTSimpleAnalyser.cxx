#include "CMSSW_VBFHToInv/HLTTools/interface/HLTSimpleAnalyser.h"

#include <stdio.h>
#include <math.h>

using namespace std;
using namespace edm;

HLTSimpleAnalyser::HLTSimpleAnalyser(const edm::ParameterSet& pset){
  
  // Getting input tags
  edm::InputTag inputTag_HLTResults = pset.getUntrackedParameter("inputTag_HLTResults",edm::InputTag("TriggerResults",  "HLT"));
  
  // Creating tokens
  m_inputTag_HLTResults = consumes<edm::TriggerResults>(inputTag_HLTResults);
  
  m_hltPaths            = pset.getParameter< vector<string> >("HLTPaths");
  
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","HLTSimpleAnalyserResults.root");
  
  m_fileOut = new TFile(outputFilename.c_str(),"RECREATE");
  
  // Making histograms
  m_hEventCount = new TH1D("EventCount","EventCount",1,0.5,1.5); 
  m_hEventCount->SetDirectory(m_fileOut);

  m_hHLTPathCount = new TH1D("HLTPathCount","HLTPathCount",m_hltPaths.size(),-0.5,m_hltPaths.size());
  m_hHLTPathCount->SetDirectory(m_fileOut);
  
  m_hHLTCorrelation = new TH2D("HLTCorrelation","HLTCorrelation",m_hltPaths.size(),-0.5,m_hltPaths.size(),m_hltPaths.size(),-0.5,m_hltPaths.size());
  m_hHLTCorrelation->SetDirectory(m_fileOut);
  
  for(unsigned x=0; x<m_hltPaths.size(); x++){
    m_hHLTPathCount  ->GetXaxis()->SetBinLabel(x+1,m_hltPaths[x].c_str());
    m_hHLTCorrelation->GetXaxis()->SetBinLabel(x+1,m_hltPaths[x].c_str());
    m_hHLTCorrelation->GetYaxis()->SetBinLabel(x+1,m_hltPaths[x].c_str()); 
  }
  
}

HLTSimpleAnalyser::~HLTSimpleAnalyser(){
  
  m_fileOut->Write();
  delete m_hEventCount;
  delete m_hHLTPathCount;
}

void HLTSimpleAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  m_hEventCount->Fill(1);
  
  edm::Handle<edm::TriggerResults> handleTriggerResults;
  iEvent.getByToken(m_inputTag_HLTResults, handleTriggerResults);
  
  //printFiredHLT(iEvent,handleTriggerResults);
  
  vector<bool> hltResults;
  
  for(unsigned i=0; i<m_hltPaths.size(); i++){
    if(testTrigger(iEvent,handleTriggerResults,m_hltPaths[i])){
      hltResults.push_back(true);
      m_hHLTPathCount->Fill(i);
    }else{
      hltResults.push_back(false);
    }
  }
  
  for(unsigned x=0;x<m_hltPaths.size();x++){
    for(unsigned y=0;y<m_hltPaths.size();y++){
      
      if(hltResults[x] && hltResults[y]){m_hHLTCorrelation->Fill(x,y);}
    }
  }
}

void HLTSimpleAnalyser::beginJob(){}

void HLTSimpleAnalyser::endJob(){}

void HLTSimpleAnalyser::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}

void HLTSimpleAnalyser::endRun(edm::Run const&, edm::EventSetup const&){}

void HLTSimpleAnalyser::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void HLTSimpleAnalyser::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// TODO: This function can be optimised by caching the trigger names once per run (not once per event)
bool HLTSimpleAnalyser::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
  
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

void HLTSimpleAnalyser::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
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
DEFINE_FWK_MODULE(HLTSimpleAnalyser);
