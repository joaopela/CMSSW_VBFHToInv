#!/usr/bin/env python

import argparse
parser = argparse.ArgumentParser(description='Run CMSSW GEN step over LHE Files')
parser.add_argument('-d',type=str,help='Target directory')
args = parser.parse_args()

import os, sys
import stat
files = os.listdir(args.d)

# Doing jobs directory
jobsDir = args.d+"jobs/LHEtoGEN/"

if not os.path.isdir(jobsDir):
  os.makedirs(jobsDir,0755);

runDir = os.getcwd()

fSubmit = open(jobsDir+'submitJobs.sh','w')
fSubmit.write("#!/bin/sh\n")
fSubmit.write("\n")

jobNumber=0
for f in files:
  
  path = jobsDir+'runJob'+str(jobNumber)+'.sh'

  with open(path,'w') as fOut:
    fOut.write("#!/bin/bash\n")
    fOut.write("\n")
    fOut.write("");
    fOut.write("cd "+runDir+"\n")
    fOut.write("scramv1 p CMSSW CMSSW_7_1_19\n")
    fOut.write("\n")
    fOut.write("cmsRun run_GEN_overLHE_cfg.py print inputFiles=file:"+args.d+"/"+f+" outputFile="+args.d+"/CMSSW_7_1_19_Hadronizer_"+str(jobNumber)+".root maxEvents=-1")

  os.chmod(path, stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
  fSubmit.write("bsub -q 1nh runJob"+str(jobNumber)+".sh\n")

  jobNumber+=1

os.chmod(jobsDir+'submitJobs.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
