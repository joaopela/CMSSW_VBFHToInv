#include "CMSSW-VBFHToInv/Study_RunII_SampleProd_QCD_VBFMET/interface/GenFilterAlgo.h"

using namespace std;

#include "TMath.h"

GenFilterAlgo::GenFilterAlgo(){
  this->init();
}

GenFilterAlgo::GenFilterAlgo(edm::ParameterSet& pset){
  this->init();
  
  if(pset.exists("name"))     {m_name = pset.getUntrackedParameter<string>("name");}
  
  if(pset.exists("jetMinPt")) {m_doJetMinPt  = true; m_valJetMinPt  = pset.getUntrackedParameter<double>("jetMinPt");}
  if(pset.exists("jetMaxEta")){m_doJetMaxEta = true; m_valJetMaxEta = pset.getUntrackedParameter<double>("jetMaxEta");}
  
  if(pset.exists("dijetOppositeHemisphere")){m_doOppositeHemisphere = true;}
  if(pset.exists("dijetMinDeltaEta"))       {m_doDijetMinDeltaEta   = true; m_valDijetMinDeltaEta = pset.getUntrackedParameter<double>("dijetMinDeltaEta");}
  if(pset.exists("dijetMaxDeltaPhi"))       {m_doDijetMaxDeltaPhi   = true; m_valDijetMaxDeltaPhi = pset.getUntrackedParameter<double>("dijetMaxDeltaPhi");}
  if(pset.exists("dijetMinMjj"))            {m_doDijetMinMjj        = true; m_valDijetMinMjj      = pset.getUntrackedParameter<double>("dijetMinMjj");}
  
}

void GenFilterAlgo::init(){
  m_name                 = "Unnamed Algorithm";
  m_doJetMinPt           = false;
  m_doJetMaxEta          = false;
  m_doOppositeHemisphere = false;
  m_doDijetMinDeltaEta   = false;
  m_doDijetMaxDeltaPhi   = false;
  m_doDijetMinMjj        = false;
  
  // For plots
  m_doPlots           = false;
  m_Jets_Multiplicity = 0;
  m_Jet0_Pt           = 0;
  m_Jet1_Pt           = 0;
  m_Dijet_EtaProduct  = 0;
  m_Dijet_MaxMjj      = 0;
  m_Dijet_MaxDEta     = 0;
  m_Dijet_MinDPhi     = 0;
  
}

void GenFilterAlgo::buildPlots(TDirectory* dir){
  
  m_doPlots = true;
  
  m_Jets_Multiplicity = new TH1D("Jets_Multiplicity","Jets_Multiplicity",  50,-0.5,       49.5); m_Jets_Multiplicity->SetDirectory(dir);
  m_Jet0_Pt           = new TH1D("Jet0_Pt"          ,"Jet0_Pt"          ,1000,   0,       2000); m_Jet0_Pt          ->SetDirectory(dir);
  m_Jet1_Pt           = new TH1D("Jet1_Pt"          ,"Jet1_Pt"          ,1000,   0,       2000); m_Jet1_Pt          ->SetDirectory(dir);
  m_Dijet_EtaProduct  = new TH1D("Dijet_EtaProduct" ,"Dijet_EtaProduct" ,  50, -25,         25); m_Dijet_EtaProduct ->SetDirectory(dir);
  m_Dijet_MaxMjj      = new TH1D("Dijet_MaxMjj"     ,"Dijet_MaxMjj"     , 500,   0,       5000); m_Dijet_MaxMjj     ->SetDirectory(dir);
  m_Dijet_MaxDEta     = new TH1D("Dijet_MaxDEta"    ,"Dijet_MaxDEta"    , 200,   0,         10); m_Dijet_MaxDEta    ->SetDirectory(dir);
  m_Dijet_MinDPhi     = new TH1D("Dijet_MinDPhi"    ,"Dijet_MinDPhi"    , 128,   0,TMath::Pi()); m_Dijet_MinDPhi    ->SetDirectory(dir);
  
}

GenFilterAlgo::~GenFilterAlgo(){
  
  if(m_Jets_Multiplicity){delete m_Jets_Multiplicity;}
  if(m_Jet0_Pt)          {delete m_Jet0_Pt;}
  if(m_Jet1_Pt)          {delete m_Jet1_Pt;}
  if(m_Dijet_EtaProduct) {delete m_Dijet_EtaProduct;}
  if(m_Dijet_MaxMjj)     {delete m_Dijet_MaxMjj;}
  if(m_Dijet_MaxDEta)    {delete m_Dijet_MaxDEta;}
  if(m_Dijet_MinDPhi)    {delete m_Dijet_MinDPhi;}
  
}
  
bool GenFilterAlgo::evaluate(const vector<reco::GenJet>* genJets){
  
  vector<const reco::GenJet*> filGenJets = filterGenJets(genJets);
  
  for(unsigned a=0; a<filGenJets.size(); a++){
    for(unsigned b=a+1; b<filGenJets.size(); b++){
      
      const reco::GenJet* pA = filGenJets[a];
      const reco::GenJet* pB = filGenJets[b];
      
      double etaProd = 0;
      double dPhi    = 0;
      double dEta    = 0;
      double invMass = 0;
      
      // Dijet cut: Opposite hemispheres
      if(m_doOppositeHemisphere){ 
        etaProd = pA->p4().eta()*pB->p4().eta();
        if(etaProd>=0){continue;}
      }

      // Dijet cut: Max delta(phi)
      if(m_doDijetMaxDeltaPhi){
        dPhi = fabs(pA->p4().phi()-pB->p4().phi());
        if(dPhi>=m_valDijetMaxDeltaPhi){continue;}
      }
      
      // Dijet cut: Max delta(eta)
      if(m_doDijetMinDeltaEta){
        dEta = fabs(pA->p4().eta()-pB->p4().eta());
        if(dEta<=m_valDijetMinDeltaEta){continue;}
      }

      // Dijet cut: Max delta(eta)
      if(m_doDijetMinMjj){
        
        // Getting the dijet vector
        math::XYZTLorentzVector diJet = pA->p4() + pB->p4();
        invMass = diJet.mass();
        if(invMass<=m_valDijetMinMjj){continue;}
      }
      
      if(m_doPlots){
        m_Jets_Multiplicity->Fill(filGenJets.size());
        m_Jet0_Pt          ->Fill(pA->pt());
        m_Jet1_Pt          ->Fill(pB->pt());
        m_Dijet_EtaProduct ->Fill(etaProd);
        m_Dijet_MaxDEta    ->Fill(dEta);
        m_Dijet_MinDPhi    ->Fill(dPhi);
        m_Dijet_MaxMjj     ->Fill(invMass);
      }
      
      return true;
    }
  }
  
  return false;
}

void GenFilterAlgo::print(){
  
  cout << "############################" << endl;
  cout << "###### GenFilterAlgo #######" << endl;
  cout << "############################" << endl;
  cout << "# Algo Name          : " << m_name << endl;
  if(m_doJetMinPt)          {cout << "# Jet Min Pt         : " << m_valJetMinPt << endl;}
  if(m_doJetMaxEta)         {cout << "# Jet Max Eta        : " << m_valJetMaxEta << endl;}
  if(m_doOppositeHemisphere){cout << "# Dijet Opp. Hem.    : True" << endl;}
  if(m_doDijetMinDeltaEta)  {cout << "# Dijet Min DeltaEta : " << m_valDijetMinDeltaEta << endl;}
  if(m_doDijetMaxDeltaPhi)  {cout << "# Dijet Max DeltaPhi : " << m_valDijetMaxDeltaPhi << endl;}
  if(m_doDijetMinMjj)       {cout << "# Dijet Min Mjj      : " << m_valDijetMinMjj << endl;}
  cout << "############################" << endl;
  cout << endl;
  
}

vector<const reco::GenJet*> GenFilterAlgo::filterGenJets(const vector<reco::GenJet>* jets){
  
  vector<const reco::GenJet*> out;
  
  for(unsigned i=0; i<jets->size(); i++){
    
    const reco::GenJet* j = &((*jets)[i]);
    
    if(m_doJetMinPt) {if(j->p4().pt() <=m_valJetMinPt) {continue;}}
    if(m_doJetMaxEta){if(j->p4().eta()>=m_valJetMaxEta){continue;}}
    
    out.push_back(j);
  }
  
  return out;
}