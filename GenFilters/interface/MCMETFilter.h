#ifndef MCMETFilter_h
#define MCMETFilter_h
// -*- C++ -*-
//
// Package:    MCMETFilter
// Class:      MCMETFilter
// 
/* 

 Description: filter events based on the Pythia particle information

 Implementation: inherits from generic EDFilter
     
*/
//
// Original Author:  Fabian Stoeckli
//         Created:  Mon Sept 11 10:57:54 CET 2006
// $Id: MCMETFilter.h,v 1.3 2010/07/21 04:23:23 wmtan Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "TFile.h"
#include "TH1D.h"

//
// class decleration
//

class MCMETFilter : public edm::EDFilter {
   public:
      explicit MCMETFilter(const edm::ParameterSet&);
      ~MCMETFilter();


      virtual bool filter(edm::Event&, const edm::EventSetup&);
   private:

     // ----------memeber function----------------------
       double neutrinosMET(const HepMC::GenEvent*);
       
      // ----------member data ---------------------------
       std::string label_;
       double mcMet_;
       std::string outFile_;
       
       TFile* outFile;
       TH1D*  hNeutrinoMET;
};
#endif
