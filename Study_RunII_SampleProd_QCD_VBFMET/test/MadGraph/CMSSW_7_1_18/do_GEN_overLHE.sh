#!/bin/bash

# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.lhe outputFile=file:CMSSW_7_1_18_Hadronizer_mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root maxEvents=-1

# Run over version 0 files
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v0/QCD_VBFLike_jj_unweighted_events.lhe   outputFile=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v0/QCD_VBFLike_jjj_unweighted_events.lhe  outputFile=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v0/QCD_VBFLike_jjjj_unweighted_events.lhe outputFile=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v0/QCD_VBFLike_all_unweighted_events.lhe  outputFile=file:v0/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 1 files
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v1/QCD_VBFLike_jj_unweighted_events.lhe   outputFile=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v1/QCD_VBFLike_jjj_unweighted_events.lhe  outputFile=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v1/QCD_VBFLike_jjjj_unweighted_events.lhe outputFile=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v1/QCD_VBFLike_all_unweighted_events.lhe  outputFile=file:v1/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 2 files
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v2/QCD_VBFLike_jj_unweighted_events.lhe   outputFile=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v2/QCD_VBFLike_jjj_unweighted_events.lhe  outputFile=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v2/QCD_VBFLike_jjjj_unweighted_events.lhe outputFile=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v2/QCD_VBFLike_all_unweighted_events.lhe  outputFile=file:v2/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  maxEvents=-1

# Run over version 3 files
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v3/QCD_VBFLike_jj_unweighted_events.lhe   outputFile=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jj.root   maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v3/QCD_VBFLike_jjj_unweighted_events.lhe  outputFile=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjj.root  maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v3/QCD_VBFLike_jjjj_unweighted_events.lhe outputFile=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_jjjj.root maxEvents=-1
# cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:v3/QCD_VBFLike_all_unweighted_events.lhe  outputFile=file:v3/CMSSW_7_1_18_Hadronizer_QCD_VBFLike_all.root  maxEvents=-1

# Run over Production 0 files
cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:prod_v0/a/ev_seed101_n2500.lhe,file:prod_v0/a/ev_seed109_n2500.lhe,file:prod_v0/a/ev_seed113_n2500.lhe,file:prod_v0/a/ev_seed114_n2500.lhe,file:prod_v0/a/ev_seed116_n2500.lhe,file:prod_v0/a/ev_seed128_n2500.lhe,file:prod_v0/a/ev_seed136_n5000.lhe,file:prod_v0/a/ev_seed138_n2500.lhe,file:prod_v0/a/ev_seed149_n2500.lhe,file:prod_v0/a/ev_seed152_n2500.lhe,file:prod_v0/a/ev_seed154_n2500.lhe,file:prod_v0/a/ev_seed166_n2500.lhe,file:prod_v0/a/ev_seed182_n2500.lhe,file:prod_v0/a/ev_seed188_n5000.lhe,file:prod_v0/a/ev_seed191_n2500.lhe,file:prod_v0/a/ev_seed196_n5000.lhe,file:prod_v0/a/ev_seed197_n2500.lhe,file:prod_v0/a/ev_seed212_n2500.lhe,file:prod_v0/a/ev_seed213_n2500.lhe,file:prod_v0/a/ev_seed215_n2500.lhe,file:prod_v0/a/ev_seed224_n2500.lhe,file:prod_v0/a/ev_seed228_n2500.lhe,file:prod_v0/a/ev_seed238_n2500.lhe,file:prod_v0/a/ev_seed243_n2500.lhe,file:prod_v0/a/ev_seed247_n2500.lhe,file:prod_v0/a/ev_seed248_n2500.lhe,file:prod_v0/a/ev_seed250_n2500.lhe,file:prod_v0/a/ev_seed253_n2500.lhe,file:prod_v0/a/ev_seed254_n2500.lhe,file:prod_v0/a/ev_seed267_n2500.lhe,file:prod_v0/a/ev_seed277_n2500.lhe,file:prod_v0/a/ev_seed284_n2500.lhe,file:prod_v0/a/ev_seed294_n2500.lhe,file:prod_v0/a/ev_seed305_n2500.lhe,file:prod_v0/a/ev_seed309_n2500.lhe,file:prod_v0/a/ev_seed30_n2500.lhe,file:prod_v0/a/ev_seed310_n2500.lhe,file:prod_v0/a/ev_seed315_n2500.lhe,file:prod_v0/a/ev_seed31_n2500.lhe,file:prod_v0/a/ev_seed326_n2500.lhe,file:prod_v0/a/ev_seed32_n2500.lhe,file:prod_v0/a/ev_seed334_n2500.lhe,file:prod_v0/a/ev_seed335_n2500.lhe,file:prod_v0/a/ev_seed336_n2500.lhe,file:prod_v0/a/ev_seed33_n2500.lhe,file:prod_v0/a/ev_seed341_n2500.lhe,file:prod_v0/a/ev_seed343_n2500.lhe,file:prod_v0/a/ev_seed352_n2500.lhe,file:prod_v0/a/ev_seed369_n2500.lhe,file:prod_v0/a/ev_seed371_n2500.lhe,file:prod_v0/a/ev_seed38_n2500.lhe,file:prod_v0/a/ev_seed390_n2500.lhe,file:prod_v0/a/ev_seed391_n2500.lhe,file:prod_v0/a/ev_seed40_n2500.lhe,file:prod_v0/a/ev_seed54_n5000.lhe,file:prod_v0/a/ev_seed55_n5000.lhe,file:prod_v0/a/ev_seed57_n5000.lhe,file:prod_v0/a/ev_seed60_n2500.lhe,file:prod_v0/a/ev_seed61_n2500.lhe,file:prod_v0/a/ev_seed64_n2500.lhe,file:prod_v0/a/ev_seed66_n5000.lhe,file:prod_v0/a/ev_seed69_n2500.lhe,file:prod_v0/a/ev_seed70_n2500.lhe,file:prod_v0/a/ev_seed72_n2500.lhe,file:prod_v0/a/ev_seed91_n2500.lhe,file:prod_v0/a/ev_seed94_n5000.lhe outputFile=file:prod_v0/CMSSW_7_1_18_Hadronizer.root maxEvents=-1


