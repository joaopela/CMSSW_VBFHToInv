#!/bin/bash 


source  /afs/cern.ch/cms/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/p/pela/work/cms/vbfinv/slc6/prodTest2/CMSSW_7_4_1_patch1/src/CMSSW-VBFHToInv/Study_RunII_SampleProd_QCD-VBF-MET/test/Unfiltered
eval `scram runtime -sh`

cat /proc/cpuinfo
cat /proc/meminfo

cmsRun QCD_Pt-80to120_step1_cfg.py | tee QCD_Pt-80to120_step1.log
cmsRun QCD_Pt-80to120_step2_cfg.py | tee QCD_Pt-80to120_step2.log
