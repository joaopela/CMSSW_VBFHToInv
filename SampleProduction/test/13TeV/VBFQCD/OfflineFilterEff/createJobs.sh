#!/bin/bash

# This script will call a python script that will produce for each QCD pT hat:
# create automatically:
# * Working directories where all the relevant files will be stored
# * 40 CMSSW configuration files for 25k events (with different random number initialisation)
# * 40 Job executables (written in bash) one for each CMSSW job
# * 1 submit all executable that will submit all jobs to lxbatch 8nh queue

vbfinv_makeProdJobs.py -py QCD_Pt-30to50_step1_cfg.py   -job runJob.sh -jobPost runJobPost.sh -n 1000 -outDir "QCD_Pt-30to50"   -ev  80000 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-50to80_step1_cfg.py   -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-50to80"   -ev 100000 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-80to120_step1_cfg.py  -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-80to120"  -ev  19000 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-120to170_step1_cfg.py -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-120to170" -ev  12000 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-170to300_step1_cfg.py -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-170to300" -ev   3500 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-300to470_step1_cfg.py -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-300to470" -ev   2300 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-470to600_step1_cfg.py -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-470to600" -ev   1600 -q 1nd
vbfinv_makeProdJobs.py -py QCD_Pt-600to800_step1_cfg.py -job runJob.sh -jobPost runJobPost.sh -n  200 -outDir "QCD_Pt-600to800" -ev   1350 -q 1nd
