#!/bin/bash 


source  /afs/cern.ch/cms/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/p/pela/work/cms/vbfinv/slc6/prodTest1/CMSSW_7_2_0_patch1/src/VBFHiggsToInvisible/SampleProduction/test/13TeV/VBFQCD/GenFilterEff_Both/
eval `scram runtime -sh`

cat /proc/cpuinfo
cat /proc/meminfo

cmsRun QCD_Pt-470to600_step1_cfg.py | tee QCD_Pt-470to600_step1.log

