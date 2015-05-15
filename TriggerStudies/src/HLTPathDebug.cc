#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTPathDebug.h"

#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObject.h"

#include <stdio.h>
#include <math.h>

using namespace std;

HLTPathDebug::HLTPathDebug(const edm::ParameterSet& pset){
  
  // Getting InputTag from configuration file
  m_InputTag_L1GTReadoutRecord      = pset.getUntrackedParameter("inputTag_L1GTReadoutRecord",     edm::InputTag("gtDigis"));
  //   m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",     edm::InputTag("l1extraParticles","MET"));  
  m_InputTag_L1Extra_mets           = pset.getUntrackedParameter("inputTag_L1Extra_mets",          edm::InputTag("l1extraParticles","MET"));
  m_InputTag_L1Extra_mhts           = pset.getUntrackedParameter("inputTag_L1Extra_mhts",          edm::InputTag("l1extraParticles","MHT"));
  m_InputTag_HLTResults             = pset.getUntrackedParameter("inputTag_HLTResults",            edm::InputTag("TriggerResults","HLT"));
  m_InputTag_L1CaloRegionCollection = pset.getUntrackedParameter("inputTag_L1CaloRegionCollection",edm::InputTag("gctDigis"));
  m_InputTag_EcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_EcalTriggerPrimitives", edm::InputTag("ecalDigis","EcalTriggerPrimitives"));
  m_InputTag_HcalTriggerPrimitives  = pset.getUntrackedParameter("inputTag_HcalTriggerPrimitives", edm::InputTag("valHcalTriggerPrimitiveDigis"));
  
  // Getting other parameters from configuration file
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",       false);

  
  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","HLTPathDebugResults.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");
  
}

HLTPathDebug::~HLTPathDebug(){
  
  fOut->Write();
}

void HLTPathDebug::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
//   hEventCount->Fill(1);
    
  edm::Handle<edm::TriggerResults> hltresults;
  iEvent.getByLabel(m_InputTag_HLTResults, hltresults);
  
  printFiredHLT(iEvent,hltresults);
  
  //___________________________________________________________________________________________  
  // Get the PAT TriggerEvent
  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( "patTriggerEvent", triggerEvent );
  
  // Get a vector of all HLT paths
  std::vector<pat::TriggerPath> const* paths = triggerEvent->paths();
  
  // Find the full label of the chosen HLT path (i.e. with the version number)
  bool fired = true;
  std::string full_name;
  for (unsigned i = 0; i < paths->size(); ++i) {
    std::string name = paths->at(i).name();
    if (name.find("HLT_DiPFJet10_PFMETnoMu10_MJJ100VBF_LeadingJets_v1") != name.npos) {
      full_name = name;
      if (!(paths->at(i).wasAccept())) fired = false;
      break; // Stop loop after we find the first match
    }
  }
  
  if (!fired) return;
  
  std::cout << "Found Path: " << full_name << std::endl;
  
  // Get a vector of the objects used in the chosen path
  pat::TriggerObjectRefVector pathObjects = triggerEvent->pathObjects(full_name, false);
  for (unsigned j = 0; j < pathObjects.size(); ++j) {

    vector<int> objType = pathObjects[j]->triggerObjectTypes();
    for(unsigned i=0; i<objType.size(); i++){
      cout << "obj #" << j << " type=" << objType[i];
      if(objType[i] == +81){cout << " - TriggerPhoton" << endl;}
      if(objType[i] == +82){cout << " - TriggerElectron" << endl;}
      if(objType[i] == +83){cout << " - TriggerMuon" << endl;}
      if(objType[i] == +84){cout << " - TriggerTau" << endl;}         
      if(objType[i] == +85){cout << " - TriggerJet" << endl;}           
      if(objType[i] == +86){cout << " - TriggerBJet" << endl;}          
      if(objType[i] == +87){cout << " - TriggerMET" << endl;}           
      if(objType[i] == +88){cout << " - TriggerTET" << endl;}    
      if(objType[i] == +89){cout << " - TriggerTHT" << endl;}        
      if(objType[i] == +90){cout << " - TriggerMHT" << endl;}      
      if(objType[i] == +91){cout << " - TriggerTrack" << endl;}   
      if(objType[i] == +92){cout << " - TriggerCluster" << endl;}
      if(objType[i] == +93){cout << " - TriggerMETSig" << endl;}
      if(objType[i] == +94){cout << " - TriggerELongit" << endl;}
      if(objType[i] == +95){cout << " - TriggerMHTSig" << endl;}
      if(objType[i] == +96){cout << " - TriggerHLongit" << endl;}
    }

    cout << "obj #" << j << " pt =" << pathObjects[j]->pt() << endl;
    cout << "obj #" << j << " eta=" << pathObjects[j]->eta() << endl;
    cout << "obj #" << j << " phi=" << pathObjects[j]->phi() << endl;
    cout << "obj #" << j << " e  =" << pathObjects[j]->energy() << endl;
    
    std::vector<std::size_t> filter_labels;
    //std::cout << j << "\t" << (pathObjects)[j]->collection() << "\tpt: " << (pathObjects)[j]->pt() << "\teta: " << (pathObjects)[j]->eta() << std::endl;
    
    // Get the filters this object was used in
    pat::TriggerFilterRefVector filters = triggerEvent->objectFilters((pathObjects)[j], false);
    for (unsigned k = 0; k < filters.size(); ++k) {
      
      // Only store the filter label if the filter was used in the chosen path
      if (!triggerEvent->filterInPath(filters[k],full_name, false)) continue;
      //std::cout << "--" << filters[k]->label() << std::endl;
      
      cout << "obj #" << j <<  "Filter label: " << filters[k]->label() << endl;
    }
  }
}

void HLTPathDebug::beginJob(){}

void HLTPathDebug::endJob(){}

void HLTPathDebug::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  //currentRunNumber = iRun.run();

}

void HLTPathDebug::endRun(edm::Run const&, edm::EventSetup const&){}

void HLTPathDebug::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

void HLTPathDebug::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){}

// TODO: This function can be optimised by caching the trigger names once per run (not once per event)
bool HLTPathDebug::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
  
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

void HLTPathDebug::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
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
DEFINE_FWK_MODULE(HLTPathDebug);