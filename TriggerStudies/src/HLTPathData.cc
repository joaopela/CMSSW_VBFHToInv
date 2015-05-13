#include "CMSSW-VBFHToInv/TriggerStudies/interface/HLTPathData.h"

#include <iostream>

using namespace std;

HLTPathData::HLTPathData(string pathName){

  m_pathName = pathName;
}

HLTPathData::~HLTPathData(){
  
  for(unsigned i=0; i<m_objects.size(); i++){
    delete m_objects[i];
  }
  
  for(auto i=m_diobjects.begin(); i!=m_diobjects.end(); i++){
    
    vector<HLTDiobject*>* col = &(i->second);
    for(unsigned x=0; x<col->size(); x++){
      delete (*col)[x];
    }
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

vector<HLTDiobject*> HLTPathData::getFilterDiobjects(std::string filterName){
  
  auto it = m_diobjects.find(filterName);
  if(it!=m_diobjects.end()){return it->second;}
  
  vector<HLTObject*> objs = this->getFilterObjects(filterName);
  
  m_diobjects[filterName] = vector<HLTDiobject*>();
  vector<HLTDiobject*>* pCol = &(m_diobjects[filterName]);
  
  for(unsigned a=0; a<objs.size() ; a++){
    for(unsigned b=a+1; b<objs.size() ; b++){
      
      HLTObject* objA = objs[a];
      HLTObject* objB = objs[b];
      HLTDiobject* diobj;
      
      if(objA->pt()>objB->pt()){
        diobj = new HLTDiobject(objA,objB);
      }else{
        diobj = new HLTDiobject(objB,objA);
      }
      pCol->push_back(diobj);
    }
  }
  
  return m_diobjects[filterName];
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