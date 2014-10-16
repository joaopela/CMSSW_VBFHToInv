#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTEventData.h"

#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObject.h"

#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTObject.h"

using namespace std;

HLTEventData::HLTEventData(const edm::ParameterSet& pset, const edm::Event& iEvent){
  
  vector<string> hltAlgos = pset.getParameter< vector<string> >("HLTPaths");
  
  // If there are no HLT paths to retrieve stop processing
  if(hltAlgos.size()==0){return;}

  // Get the PAT TriggerEvent
  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( "patTriggerEvent", triggerEvent );

  // Get a vector of all HLT paths
  vector<pat::TriggerPath> const* paths = triggerEvent->paths();
  
  for(unsigned i=0; i<hltAlgos.size(); i++){

    string *hltAlgoName = &(hltAlgos[i]);
    string fullName;
    
    bool fired = false;
    m_evPathFired[(*hltAlgoName)] = false;

    for (unsigned x=0; x<paths->size(); x++) {

      std::string name = paths->at(x).name();
      if (name.find((*hltAlgoName)) != name.npos) {
        fullName = name;
        if (paths->at(x).wasAccept()){fired = true;}
        break;
      }
    }
    
    m_evPathFired[(*hltAlgoName)] = fired;
    
    // If trigger has fired retrieve objects
    if(fired){
    
      HLTPathData *thisPath = new HLTPathData( *hltAlgoName );
      m_evPathData[(*hltAlgoName)] = thisPath;
      
      pat::TriggerObjectRefVector pathObjects = triggerEvent->pathObjects(fullName, false);
      for (unsigned j = 0; j < pathObjects.size(); ++j) {
        
        HLTObject* iObj = new HLTObject(pathObjects[j]->pt(),pathObjects[j]->eta(),pathObjects[j]->phi(),pathObjects[j]->energy());
        
        vector<int> objType = pathObjects[j]->triggerObjectTypes();
        for(unsigned k=0; k<objType.size(); k++){
          iObj->addType(objType[k]);
        }
        
        // Get the filters this object was used in
        pat::TriggerFilterRefVector filters = triggerEvent->objectFilters((pathObjects)[j], false);
        for (unsigned k = 0; k < filters.size(); ++k) {
          
          // Only store the filter label if the filter was used in the chosen path
          if (!triggerEvent->filterInPath(filters[k],fullName, false)){continue;}
          iObj->addFilter(filters[k]->label());
        }
        
        thisPath->addObject(iObj);
      }
    }
  }
}

HLTEventData::~HLTEventData(){
  
  for(auto i=m_evPathData.begin(); i!=m_evPathData.end(); i++){
    delete i->second;
  }
}


void HLTEventData::print(){
  
  cout << "==> Printing HLT information this event" << endl;
  for(auto i=m_evPathFired.begin(); i!=m_evPathFired.end(); i++){
    printf("%40s : %s\n",i->first.c_str(),i->second ? "true" : "false");
  }
  
  cout << "==> HLT objects details: ";
  for(auto i=m_evPathData.begin(); i!=m_evPathData.end(); i++){
    i->second->print();
  }
}