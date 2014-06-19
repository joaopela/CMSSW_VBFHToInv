#!/bin/bash

mkdir results
mkdir results/PU20bx25/
mkdir results/PU40bx25/
mkdir results/PU40bx50/
mkdir results/PU80bx50/

hadd results/PU20bx25/Neutrino_Pt-2to20_gun.root RateAnalysis/PU20bx25_Neutrino_Pt-2to20_gun/res/*.root
hadd results/PU40bx25/Neutrino_Pt-2to20_gun.root RateAnalysis/PU40bx25_Neutrino_Pt-2to20_gun/res/*.root
hadd results/PU40bx50/Neutrino_Pt-2to20_gun.root RateAnalysis/PU40bx50_Neutrino_Pt-2to20_gun/res/*.root

hadd results/PU20bx25/WToENu_Tune4C_13TeV-pythia8.root RateAnalysis/PU20bx25_WToENu_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx50/WToENu_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx50_WToENu_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx25/WToENu_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx25_WToENu_Tune4C_13TeV-pythia8/res/*.root

hadd results/PU20bx25/WToMuNu_Tune4C_13TeV-pythia8.root RateAnalysis/PU20bx25_WToMuNu_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx50/WToMuNu_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx50_WToMuNu_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx25/WToMuNu_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx25_WToMuNu_Tune4C_13TeV-pythia8/res/*.root

hadd results/PU20bx25/DYToEE_Tune4C_13TeV-pythia8.root RateAnalysis/PU20bx25_DYToEE_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx50/DYToEE_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx50_DYToEE_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx25/DYToEE_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx25_DYToEE_Tune4C_13TeV-pythia8/res/*.root

hadd results/PU20bx25/DYToMuMu_Tune4C_13TeV-pythia8.root RateAnalysis/PU20bx25_DYToMuMu_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx50/DYToMuMu_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx50_DYToMuMu_Tune4C_13TeV-pythia8/res/*.root
hadd results/PU40bx25/DYToMuMu_Tune4C_13TeV-pythia8.root RateAnalysis/PU40bx25_DYToMuMu_Tune4C_13TeV-pythia8/res/*.root

hadd results/PU20bx25/DYJetsToLL_M-50_13TeV-pythia6.root RateAnalysis/PU20bx25_DYJetsToLL_M-50_13TeV-pythia6/res/*.root
hadd results/PU40bx50/DYJetsToLL_M-50_13TeV-pythia6.root RateAnalysis/PU40bx50_DYJetsToLL_M-50_13TeV-pythia6/res/*.root
hadd results/PU40bx25/DYJetsToLL_M-50_13TeV-pythia6.root RateAnalysis/PU40bx25_DYJetsToLL_M-50_13TeV-pythia6/res/*.root
hadd results/PU80bx50/DYJetsToLL_M-50_13TeV-pythia6.root RateAnalysis/PU80bx50_DYJetsToLL_M-50_13TeV-pythia6/res/*.root

hadd results/PU20bx25/DYJetsToLL_M-50_13TeV-madgraph-pythia8.root RateAnalysis/PU20bx25_DYJetsToLL_M-50_13TeV-madgraph-pythia8/res/*.root
hadd results/PU40bx50/DYJetsToLL_M-50_13TeV-madgraph-pythia8.root RateAnalysis/PU40bx50_DYJetsToLL_M-50_13TeV-madgraph-pythia8/res/*.root
hadd results/PU40bx25/DYJetsToLL_M-50_13TeV-madgraph-pythia8.root RateAnalysis/PU40bx25_DYJetsToLL_M-50_13TeV-madgraph-pythia8/res/*.root

hadd results/PU20bx25/TT_Tune4C_13TeV-pythia8-tauola.root RateAnalysis/PU20bx25_TT_Tune4C_13TeV-pythia8-tauola/res/*.root
hadd results/PU40bx50/TT_Tune4C_13TeV-pythia8-tauola.root RateAnalysis/PU40bx50_TT_Tune4C_13TeV-pythia8-tauola/res/*.root
hadd results/PU40bx25/TT_Tune4C_13TeV-pythia8-tauola.root RateAnalysis/PU40bx25_TT_Tune4C_13TeV-pythia8-tauola/res/*.root

hadd results/PU20bx25/VBF_HToInv_M-125_13TeV_powheg-pythia6.root RateAnalysis/PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/res/*.root
hadd results/PU40bx50/VBF_HToInv_M-125_13TeV_powheg-pythia6.root RateAnalysis/PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/res/*.root
hadd results/PU40bx25/VBF_HToInv_M-125_13TeV_powheg-pythia6.root RateAnalysis/PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/res/*.root

hadd results/PU20bx25/EWKZjj_mqq120_mll50_13TeV_madgraph-pythia8.root RateAnalysis/PU20bx25_EWKZjj_mqq120_mll50_13TeV_madgraph-pythia8/res/*.root
hadd results/PU40bx25/EWKZjj_mqq120_mll50_13TeV_madgraph-pythia8.root RateAnalysis/PU40bx25_EWKZjj_mqq120_mll50_13TeV_madgraph-pythia8/res/*.root
hadd results/PU40bx50/EWKZjj_mqq120_mll50_13TeV_madgraph-pythia8.root RateAnalysis/PU40bx50_EWKZjj_mqq120_mll50_13TeV_madgraph-pythia8/res/*.root

hadd results/PU20bx25/EWKWmin_mqq120_mnl50_13TeV_madgraph-pythia8.root RateAnalysis/PU20bx25_EWKWmin_mqq120_mnl50_13TeV_madgraph-pythia8/res/*.root
hadd results/PU40bx25/EWKWmin_mqq120_mnl50_13TeV_madgraph-pythia8.root RateAnalysis/PU40bx25_EWKWmin_mqq120_mnl50_13TeV_madgraph-pythia8/res/*.root
hadd results/PU40bx50/EWKWmin_mqq120_mnl50_13TeV_madgraph-pythia8.root RateAnalysis/PU40bx50_EWKWmin_mqq120_mnl50_13TeV_madgraph-pythia8/res/*.root

hadd results/PU20bx25/EWKWplus_mqq120_mnl50_13TeV_madgraph-pythia8.root RateAnalysis/PU20bx25_EWKWplus_mqq120_mnl50_13TeV_madgraph-pythia8/res/*.root
hadd results/PU40bx25/EWKWplus_mqq120_mnl50_13TeV_madgraph-pythia8.root RateAnalysis/PU40bx25_EWKWplus_mqq120_mnl50_13TeV_madgraph-pythia8/res/*.root
hadd results/PU40bx50/EWKWplus_mqq120_mnl50_13TeV_madgraph-pythia8.root RateAnalysis/PU40bx50_EWKWplus_mqq120_mnl50_13TeV_madgraph-pythia8/res/*.root
