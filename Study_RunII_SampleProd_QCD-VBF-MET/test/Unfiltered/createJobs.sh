#!/bin/bash 

hepfwMakeBatchJobs -jobType cmssw -jobName QCD_30to50   -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-30to50_step1_cfg.py   -jobNEvents 100 -outDir QCD_30to50  
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_50to80   -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-50to80_step1_cfg.py   -jobNEvents 100 -outDir QCD_50to80  
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_80to120  -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-80to120_step1_cfg.py  -jobNEvents 100 -outDir QCD_80to120 
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_120to170 -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-120to170_step1_cfg.py -jobNEvents 100 -outDir QCD_120to170
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_170to300 -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-170to300_step1_cfg.py -jobNEvents 100 -outDir QCD_170to300
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_300to470 -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-300to470_step1_cfg.py -jobNEvents 100 -outDir QCD_300to470
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_470to600 -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-470to600_step1_cfg.py -jobNEvents 100 -outDir QCD_470to600
hepfwMakeBatchJobs -jobType cmssw -jobName QCD_600to800 -nJobs 1 -jobQueue 2nd -cmsswCfg QCD_Pt-600to800_step1_cfg.py -jobNEvents 100 -outDir QCD_600to800