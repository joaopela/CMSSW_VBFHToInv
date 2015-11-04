#!/bin/bash

# Run over version 0 files
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v0/FilterAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v0/FilterAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v0/FilterAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v0/FilterAnalyzer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 1 files
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v1/FilterAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v1/FilterAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v1/FilterAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v1/FilterAnalyzer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 2 files
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v2/FilterAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v2/FilterAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v2/FilterAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v2/FilterAnalyzer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 3 files
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v3/FilterAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  outputFile=file:v3/FilterAnalyzer_QCD_VBFLike_jjj.root  maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root outputFile=file:v3/FilterAnalyzer_QCD_VBFLike_jjjj.root maxEvents=-1
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  outputFile=file:v3/FilterAnalyzer_QCD_VBFLike_all.root  maxEvents=-1

