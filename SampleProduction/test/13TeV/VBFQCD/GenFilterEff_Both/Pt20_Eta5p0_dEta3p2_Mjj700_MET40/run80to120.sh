#!/bin/bash 


source  /afs/cern.ch/cms/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/p/pela/work/cms/vbfinv/slc6/prodTest1/CMSSW_7_2_0_patch1/src/
eval `scram runtime -sh`

cd VBFHiggsToInvisible/SampleProduction/test/13TeV/VBFQCD/GenFilterEff_Both/Pt20_Eta5p0_dEta3p2_Mjj700_MET40/

CMSSW_JOB_CFG="QCD_Pt-80to120_step1_cfg"

cat /proc/cpuinfo &> $CMSSW_JOB_CFG.cpu.log
cat /proc/meminfo &> $CMSSW_JOB_CFG.mem.log

# Making job status
touch $CMSSW_JOB_CFG.status.running

cmsRun $CMSSW_JOB_CFG.py | tee $CMSSW_JOB_CFG.job.log

# Updating job status
rm $CMSSW_JOB_CFG.job.status.running
touch $CMSSW_JOB_CFG.job.status.done
