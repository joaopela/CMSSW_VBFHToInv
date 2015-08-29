#!/bin/bash

# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.lhe outputFile=file:CMSSW_7_1_18_Hadronizer_mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root maxEvents=-1

# Run over version 1 files
cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v1/QCD_VBFLike_jj_unweighted_events.lhe  outputFile=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root maxEvents=-1
cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v1/QCD_VBFLike_jjj_unweighted_events.lhe outputFile=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root maxEvents=-1
