#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPathStudies.h"

#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObject.h"


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
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",false);

  string outputFilename = pset.getUntrackedParameter<string>("outputFilename","HLTPathStudiesResults.root");
  fOut = new TFile(outputFilename.c_str(),"RECREATE");

}

HLTPathStudies::~HLTPathStudies(){
  
  fOut->Write();
}

void HLTPathStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  // Counting the current event
  hEventCount->Fill(1);

  // Extracting L1Extra information
  L1ExtraPayload evL1Extra(ps,iEvent);
  l1extra::L1JetParticleCollection *l1tJets = evL1Extra.getL1TAllJets();
  
  edm::Handle<edm::TriggerResults> hltresults;
  iEvent.getByLabel(m_InputTag_HLTResults, hltresults);
  
  // Debug function to print all HLT Path fired on each event
  //printFiredHLT(iEvent,hltresults);
  
  //___________________________________________________________________________________________  
  // Get the PAT TriggerEvent
  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( "patTriggerEvent", triggerEvent );
  
  // Get a vector of all HLT paths
  std::vector<pat::TriggerPath> const* paths = triggerEvent->paths();
  
  // Find the full label of the chosen HLT path (i.e. with the version number)
  bool fired = true;
  std::string full_name;
  
  bool        calo_fired = true;
  std::string calo_full_name;
  for (unsigned i = 0; i < paths->size(); ++i) {
    std::string name = paths->at(i).name();
    if (name.find("HLT_CaloMET_CaloVBF_v1") != name.npos) {
      calo_full_name = name;
      if (!(paths->at(i).wasAccept())) calo_fired = false;
    }
    if (name.find("HLT_PFMET_PFVBF_v1") != name.npos) {
      full_name = name;
      if (!(paths->at(i).wasAccept())) fired = false;
      // break; // Stop loop after we find the first match
    }
  }
  
  // If we did not fire pf or calo trigger stop processing this event
  // since we will not have all the necessary objects to do any calculations
   if (!fired && calo_fired) return;

   // #### Calo Objects ####################################################################################
   // Getting all the HLT objects from the calo based HLT path
   // ######################################################################################################
   vector<TriggerJet>   hltCaloJets;
   vector<TriggerDijet> hltCaloDijets;
   double calo_met_pt  = 0;
   bool   passTrigCalo = false;
   
   // Get a vector of the objects used in the chosen path
   pat::TriggerObjectRefVector pathObjects = triggerEvent->pathObjects(calo_full_name, false);
   for (unsigned j = 0; j < pathObjects.size(); ++j) {
     
     bool isMET = false;
     bool isJet = false;
     
     // Get the filters this object was used in
     pat::TriggerFilterRefVector filters = triggerEvent->objectFilters((pathObjects)[j], false);
     for (unsigned k = 0; k < filters.size(); ++k) {
       
       // Only store the filter label if the filter was used in the chosen path
       if (!triggerEvent->filterInPath(filters[k],calo_full_name, false)) continue;
       //std::cout << "--" << filters[k]->label() << std::endl;
       
       //       cout << "obj #" << j <<  "Filter label: " << filters[k]->label() << endl;
       
       if(filters[k]->label()=="hltDiCaloJet10"){isJet=true;}
       if(filters[k]->label()=="hltMET65")      {isMET=true;}
     }
     
     if(isMET){calo_met_pt  = pathObjects[j]->pt();}
     if(isJet){hltCaloJets.push_back(TriggerJet(pathObjects[j]->pt(),pathObjects[j]->eta(),pathObjects[j]->phi(),pathObjects[j]->energy()));}
   }
   
   // Here we check if the calo conditions are passed (on a CALO + PF trigger)
   if(calo_met_pt>=90){
     
     // Running over all possible HLT dijets on this event
     for(unsigned j0=0; j0<hltCaloJets.size() ; j0++){
       for(unsigned j1=j0+1; j1<hltCaloJets.size() ; j1++){
         
         TriggerDijet dijet(&(hltCaloJets[j0]),&(hltCaloJets[j1]));
         if(dijet.j0()->pt()>=40 && dijet.j1()->pt()>=40 && dijet.vbf()){
           passTrigCalo = true;
         }
         
       }
     }
   }
   
   // If event fails to pass calo conditions we stop processing the event
   if(!passTrigCalo){return;}
   
   // PF Objects ###########################################################################################
   // Getting all the HLT objects from the pf based HLT path
   // ######################################################################################################
   vector<TriggerJet>   hltJets;
   vector<TriggerDijet> hltDijets;
   double met_pt = 0;
   
  // Get a vector of the objects used in the chosen path
  pathObjects = triggerEvent->pathObjects(full_name, false);
  for (unsigned j = 0; j < pathObjects.size(); ++j) {

    bool isMET = false;
    bool isJet = false;
    
    // Get the filters this object was used in
    pat::TriggerFilterRefVector filters = triggerEvent->objectFilters((pathObjects)[j], false);
    for (unsigned k = 0; k < filters.size(); ++k) {
      
      // Only store the filter label if the filter was used in the chosen path
      if (!triggerEvent->filterInPath(filters[k],full_name, false)) continue;
      //std::cout << "--" << filters[k]->label() << std::endl;
      
      //cout << "obj #" << j <<  "Filter label: " << filters[k]->label() << endl;
      
      if(filters[k]->label()=="hltDiPFJet10")    {isJet=true;}
      if(filters[k]->label()=="hltPFMET80Filter"){isMET=true;}
    }

    if(isMET){met_pt  = pathObjects[j]->pt();}
    if(isJet){hltJets.push_back(TriggerJet(pathObjects[j]->pt(),pathObjects[j]->eta(),pathObjects[j]->phi(),pathObjects[j]->energy()));}
  }
  
  // Creating list of all possible HLT dijets on this event
  for(unsigned j0=0; j0<hltJets.size() ; j0++){
    for(unsigned j1=j0+1; j1<hltJets.size() ; j1++){
      
      hltDijets.push_back(TriggerDijet(&(hltJets[j0]),&(hltJets[j1])));
    }
  }
  
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
  
  bool l1Seed_ETM70       = false;
  bool l1Seed_Dijet_ETM50 = false;
  bool l1Seed_Dijet_Jet96 = false;
  
  if(evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=70)                {l1Seed_ETM70       = true;}
  if(passL1TDijet && evL1Extra.m_L1EtMissParticle_MET->begin()->et()>=50){l1Seed_Dijet_ETM50 = true;}
  if(passL1TDijet && (*l1tJets)[0].pt()>=96)                             {l1Seed_Dijet_Jet96 = true;}
  
  
  // ######################################################################################################
  // Now filling HLT NoCuts plots
  // ######################################################################################################
  fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"NoCuts",met_pt);
  
  // ######################################################################################################
  // Filling other plots
  // ######################################################################################################
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ500VBF_AllJets",met_pt); break;}
  }

  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ500VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ600VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ600VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ700VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ700VBF_AllJets",met_pt); break;}
  }

  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ800VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ800VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ900VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ900VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1000VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1000VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1100VBF_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1100VBF_AllJets",met_pt); break;}
  }
  
    //######################################################################################################################################################
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ500VBF_DEta3p5_AllJets",met_pt); break;}
  }

  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ500VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ600VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ600VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ700VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ700VBF_DEta3p5_AllJets",met_pt); break;}
  }

  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ800VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ800VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ900VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ900VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1000VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1000VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1100VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.5 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1100VBF_DEta3p5_AllJets",met_pt); break;}
  }
  
  //######################################################################################################################################################
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ500VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ500VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ600VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ600VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ700VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ700VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ800VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ800VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ900VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ900VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1000VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1000VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1100VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.7 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1100VBF_DEta3p7_AllJets",met_pt); break;}
  }
  
  //######################################################################################################################################################
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ500VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ500VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ600VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ600VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ700VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ700VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ800VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ800VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ900VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ900VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1000VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1000VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1100VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=3.9 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1100VBF_DEta3p9_AllJets",met_pt); break;}
  }
  
  //######################################################################################################################################################
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ500VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=500){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ500VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ600VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=600){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ600VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ700VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=700){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ700VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ800VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=800){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ800VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ900VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=900){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ900VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1000VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=1000){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1000VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=40 && dijet->j1()->pt()>=40 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet40_MJJ1100VBF_DEta4p1_AllJets",met_pt); break;}
  }
  
  for(unsigned i=0; i<hltDijets.size(); i++){
    TriggerDijet* dijet = &(hltDijets[i]);
    if(dijet->j0()->pt()>=50 && dijet->j1()->pt()>=50 && dijet->vbf() && dijet->deta()>=4.1 && dijet->mjj()>=1100){fillPlots(l1Seed_ETM70,l1Seed_Dijet_ETM50,l1Seed_Dijet_Jet96,"DiPFJet50_MJJ1100VBF_DEta4p1_AllJets",met_pt); break;}
  }
}

void HLTPathStudies::beginJob(){
  

  
}

void HLTPathStudies::endJob(){}

void HLTPathStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
  int currentRunNumber = iRun.run();
  
  TDirectory* runDir  = fOut  ->mkdir(Form("Run_%d",currentRunNumber));
  hEventCount = new TH1I("EventCount",   "EventCount"   ,   1, 0.5,  1.5); hEventCount  ->SetDirectory(runDir);
  
  //################################################
  // Creating plots
  //################################################
  
  vector<string> cutsDijetPt;
  cutsDijetPt.push_back("DiPFJet40_");
  cutsDijetPt.push_back("DiPFJet50_");
//   cutsDijetPt.push_back("DiPFJet60_");
  
  vector<string> cutsDijetMjj;
  cutsDijetMjj.push_back("MJJ500VBF_");
  cutsDijetMjj.push_back("MJJ600VBF_");
  cutsDijetMjj.push_back("MJJ700VBF_");
  cutsDijetMjj.push_back("MJJ800VBF_");
  cutsDijetMjj.push_back("MJJ900VBF_");
  cutsDijetMjj.push_back("MJJ1000VBF_");
  cutsDijetMjj.push_back("MJJ1100VBF_");
  
  vector<string> cutsDijetDEta;
  cutsDijetDEta.push_back("");
  cutsDijetDEta.push_back("DEta3p5_");
  cutsDijetDEta.push_back("DEta3p7_");
  cutsDijetDEta.push_back("DEta3p9_");
  cutsDijetDEta.push_back("DEta4p1_");
  
  vector<string> cutsDijetType;
  cutsDijetType.push_back("AllJets");
  
  
  //################################################
  //################################################
  TDirectory* dTopA = runDir->mkdir("NoCuts");
  
  TDirectory* d = dTopA->mkdir("NoCuts");
  m_hNoCuts["NoCuts"] = new HLTPlots(d);
  
  //################################################
  TDirectory* dTopB = runDir->mkdir("ETM70");
  
  d = dTopB->mkdir("NoCuts");
  m_hETM70["NoCuts"] = new HLTPlots(d);
  
  //################################################
  TDirectory* dTopC = runDir->mkdir("DijetVBF30_DEta3p5_ETM50");
  
  d = dTopC->mkdir("NoCuts");
  m_hDijetVBF30_DEta3p5_ETM50["NoCuts"] = new HLTPlots(d);

  //################################################
  TDirectory* dTopD = runDir->mkdir("DijetVBF30_DEta3p5_Jet96");
  
  d = dTopD->mkdir("NoCuts");
  m_hDijetVBF30_DEta3p5_Jet96["NoCuts"] = new HLTPlots(d);
  

  for(unsigned iDijetPt=0; iDijetPt<cutsDijetPt.size(); iDijetPt++){
    for(unsigned iDijetMjj=0; iDijetMjj<cutsDijetMjj.size(); iDijetMjj++){
      for(unsigned iDijetDEta=0; iDijetDEta<cutsDijetDEta.size(); iDijetDEta++){
        for(unsigned iDijetType=0; iDijetType<cutsDijetType.size(); iDijetType++){
          
          string hName = Form("%s%s%s%s",
                              cutsDijetPt[iDijetPt].c_str(),
                              cutsDijetMjj[iDijetMjj].c_str(),
                              cutsDijetDEta[iDijetDEta].c_str(),
                              cutsDijetType[iDijetType].c_str()
          );
          
//           cout << "Looking at: " << hName << endl;
          
          d = dTopA->mkdir(hName.c_str());
          m_hNoCuts[hName] = new HLTPlots(d);
          d = dTopB->mkdir(hName.c_str());
          m_hETM70[hName] = new HLTPlots(d);
          d = dTopC->mkdir(hName.c_str());
          m_hDijetVBF30_DEta3p5_ETM50[hName] = new HLTPlots(d);
          d = dTopD->mkdir(hName.c_str());
          m_hDijetVBF30_DEta3p5_Jet96[hName] = new HLTPlots(d);
        }
      }
    }
  }
  
}

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

void HLTPathStudies::fillPlots(bool seedA,bool seedB,bool seedC,string path,double met){
  
//   cout << "A: " << seedA << " B: " << seedB << "C: " << seedC << " path: " << path << " met: " << met << endl;
  
  HLTPlotsData evData;
  evData.met.first = true; evData.met.second = met;
  
  m_hNoCuts[path]->fill(evData);
  if(seedA){m_hETM70                   [path]->fill(evData);}
  if(seedB){m_hDijetVBF30_DEta3p5_ETM50[path]->fill(evData);}
  if(seedC){m_hDijetVBF30_DEta3p5_Jet96[path]->fill(evData);}
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTPathStudies);