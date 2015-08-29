#!/bin/bash

cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:lheSIM.root outputFile=file:PartonGenJetAnalyzer_Results_mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root maxEvents=-1

# Run over version 1 files
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root  outputFile=file:v1/PartonGenJetAnalyzer_QCD_VBFLike_jj.root  maxEvents=-1
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root outputFile=file:v1/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root maxEvents=-1
