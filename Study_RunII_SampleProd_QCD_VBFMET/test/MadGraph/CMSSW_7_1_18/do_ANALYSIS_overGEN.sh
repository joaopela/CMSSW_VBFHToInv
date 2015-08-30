#!/bin/bash

# cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:lheSIM.root outputFile=file:PartonGenJetAnalyzer_Results_mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root maxEvents=-1

# Run over version 0 files
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v0/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v0/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v0/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v0/PartonGenJetAnalyzer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 1 files
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v1/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1 dijetPt=30 dijetMjj=800
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v1/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1 dijetPt=30 dijetMjj=800
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v1/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1 dijetPt=30 dijetMjj=800
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v1/PartonGenJetAnalyzer_QCD_VBFLike_all.root  maxEvents=-1 dijetPt=30 dijetMjj=800

# Run over version 2 files
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v2/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1 dijetPt=30 dijetMjj=800 dijetEta=2.5
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v2/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1 dijetPt=30 dijetMjj=800 dijetEta=2.5
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v2/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1 dijetPt=30 dijetMjj=800 dijetEta=2.5
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v2/PartonGenJetAnalyzer_QCD_VBFLike_all.root  maxEvents=-1 dijetPt=30 dijetMjj=800 dijetEta=2.5

# Run over version 3 files
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v3/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1 dijetPt=40 dijetMjj=800 dijetEta=3.0
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v3/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1 dijetPt=40 dijetMjj=800 dijetEta=3.0
# cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v3/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1 dijetPt=40 dijetMjj=800 dijetEta=3.0
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v3/PartonGenJetAnalyzer_QCD_VBFLike_all.root  maxEvents=-1 dijetPt=40 dijetMjj=800 dijetEta=3.0