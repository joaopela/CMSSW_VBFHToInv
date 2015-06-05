#!/bin/bash

# This script will call a python script that will produce for each QCD pT hat:
# create automatically:
# * Working directories where all the relevant files will be stored
# * 40 CMSSW configuration files for 25k events (with different random number initialisation)
# * 40 Job executables (written in bash) one for each CMSSW job
# * 1 submit all executable that will submit all jobs to lxbatch 8nh queue

hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-30to50   -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-30to50_cfg.py   -nJobs 2000 -jobNEvents 100000 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-50to80   -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-50to80_cfg.py   -nJobs  400 -jobNEvents 100000 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-80to120  -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-80to120_cfg.py  -nJobs  400 -jobNEvents  19000 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-120to170 -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-120to170_cfg.py -nJobs  400 -jobNEvents  12000 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-170to300 -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-170to300_cfg.py -nJobs  400 -jobNEvents   3500 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-300to470 -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-300to470_cfg.py -nJobs  400 -jobNEvents   2300 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-470to600 -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-470to600_cfg.py -nJobs  400 -jobNEvents   1600 -itText JOBNUMBER
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_Pt-600to800 -jobQueue 1nd -cmsswCfg CMSSW_7_4_1_patch1_ak4/QCD_Pt-600to800_cfg.py -nJobs  400 -jobNEvents   1350 -itText JOBNUMBER