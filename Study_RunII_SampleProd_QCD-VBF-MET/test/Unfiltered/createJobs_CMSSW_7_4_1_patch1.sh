#!/bin/bash 

hepfwMakeBatchJobs -jobType cmssw -jobName QCD_30to50   -jobQueue 2nd -cmsswCfg QCD_Pt-30to50_CMSSW_7_4_1_patch1_step1_cfg.py   -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_50to80   -jobQueue 2nd -cmsswCfg QCD_Pt-50to80_CMSSW_7_4_1_patch1_step1_cfg.py   -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_80to120  -jobQueue 2nd -cmsswCfg QCD_Pt-80to120_CMSSW_7_4_1_patch1_step1_cfg.py  -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_120to170 -jobQueue 2nd -cmsswCfg QCD_Pt-120to170_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_170to300 -jobQueue 2nd -cmsswCfg QCD_Pt-170to300_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_300to470 -jobQueue 2nd -cmsswCfg QCD_Pt-300to470_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_470to600 -jobQueue 2nd -cmsswCfg QCD_Pt-470to600_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_600to800 -jobQueue 2nd -cmsswCfg QCD_Pt-600to800_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100