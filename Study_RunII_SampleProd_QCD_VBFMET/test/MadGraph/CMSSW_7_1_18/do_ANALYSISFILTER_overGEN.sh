#!/bin/bash

# Run over version 1 files
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   outputFile=file:v1/FilterAnalyzer_QCD_VBFLike_jj.root   maxEvents=-1
