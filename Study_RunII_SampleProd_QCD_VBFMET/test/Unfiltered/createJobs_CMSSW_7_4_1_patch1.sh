#!/bin/bash 

hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-30to50_step1   -jobQueue 2nd -cmsswCfg QCD_Pt-30to50_step1_CMSSW_7_4_1_patch1_cfg.py   -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-50to80_step1   -jobQueue 2nd -cmsswCfg QCD_Pt-50to80_step1_CMSSW_7_4_1_patch1_cfg.py   -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-80to120_step1  -jobQueue 2nd -cmsswCfg QCD_Pt-80to120_step1_CMSSW_7_4_1_patch1_cfg.py  -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-120to170_step1 -jobQueue 2nd -cmsswCfg QCD_Pt-120to170_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-170to300_step1 -jobQueue 2nd -cmsswCfg QCD_Pt-170to300_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-300to470_step1 -jobQueue 2nd -cmsswCfg QCD_Pt-300to470_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-470to600_step1 -jobQueue 2nd -cmsswCfg QCD_Pt-470to600_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-600to800_step1 -jobQueue 2nd -cmsswCfg QCD_Pt-600to800_step1_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100

hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-30to50_step2   -jobQueue 8nh -cmsswCfg QCD_Pt-30to50_step2_CMSSW_7_4_1_patch1_cfg.py   -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-50to80_step2   -jobQueue 8nh -cmsswCfg QCD_Pt-50to80_step2_CMSSW_7_4_1_patch1_cfg.py   -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-80to120_step2  -jobQueue 8nh -cmsswCfg QCD_Pt-80to120_step2_CMSSW_7_4_1_patch1_cfg.py  -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-120to170_step2 -jobQueue 8nh -cmsswCfg QCD_Pt-120to170_step2_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-170to300_step2 -jobQueue 8nh -cmsswCfg QCD_Pt-170to300_step2_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-300to470_step2 -jobQueue 8nh -cmsswCfg QCD_Pt-300to470_step2_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-470to600_step2 -jobQueue 8nh -cmsswCfg QCD_Pt-470to600_step2_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100
hepfwMakeBatchJobs -jobType cmssw -getCpuLog -getMemLog -jobName QCD_Pt-600to800_step2 -jobQueue 8nh -cmsswCfg QCD_Pt-600to800_step2_CMSSW_7_4_1_patch1_cfg.py -nJobs 1 -jobNEvents 100




