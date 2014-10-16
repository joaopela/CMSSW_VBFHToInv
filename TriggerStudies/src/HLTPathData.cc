#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPathData.h"

#include <iostream>

using namespace std;

HLTPathData::HLTPathData(string pathName){

  m_pathName = pathName;
}

HLTPathData::~HLTPathData(){
  
  for(unsigned i=0; i<m_objects.size(); i++){
    delete m_objects[i];
  }
}

void HLTPathData::addObject(HLTObject *object){m_objects.push_back(object);}

vector<HLTObject*> HLTPathData::getObjects(){
  return m_objects;
}

vector<HLTObject*> HLTPathData::getJets(){

  vector<HLTObject*> out;
  for(unsigned i=0; i<m_objects.size(); i++){
    if(m_objects[i]->isJet()){
      out.push_back(m_objects[i]);
    }
  }
  return out;
}

vector<HLTObject*> HLTPathData::getMET(){
  
  vector<HLTObject*> out;
  for(unsigned i=0; i<m_objects.size(); i++){
    if(m_objects[i]->isMET()){
      out.push_back(m_objects[i]);
    }
  }
  return out;
}

vector<HLTObject*> HLTPathData::getFilterObjects(std::string filterName){
  
  vector<HLTObject*> out;
  for(unsigned i=0; i<m_objects.size(); i++){
    if(m_objects[i]->passedFilter(filterName)){
      out.push_back(m_objects[i]);
    }
  }
  return out;

}

void HLTPathData::print(){
  
  cout << "==> Printing information for path: " << m_pathName << endl;
  cout << "This path contains " << m_objects.size() << " objects" << endl;
  cout << "This path contains " << getJets().size() << " jets"<< endl;
  cout << "This path contains " << getMET().size()  << " METs"<< endl;
  
  if(m_objects.size() == 0){return;}
  
  for(unsigned i=0; i<m_objects.size(); i++){
    cout << "=> Object " << i << " information:" << endl;
    m_objects[i]->print();
  }
}