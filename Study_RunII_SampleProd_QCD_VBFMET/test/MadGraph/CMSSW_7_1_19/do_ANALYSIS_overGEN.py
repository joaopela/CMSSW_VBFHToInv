#!/usr/bin/env python

import argparse
parser = argparse.ArgumentParser(description='Run CMSSW ANALYSIS step over GEN Files')
parser.add_argument('-d',type=str,help='Target directory')
args = parser.parse_args()

import os
files = os.listdir(args.d)

inputFiles = ''
for f in files:
  
  if "CMSSW_7_1_19_Hadronizer" in f:
    if inputFiles is not '':
      inputFiles += ','
  
    inputFiles += 'file:'+args.d+'/'+f


outputFile  = "file:"+args.d+"/PartonGenJetAnalyzer_QCD_VBFLike_all.root"
bashCommand = "cmsRun run_GEN_overLHE_cfg.py print inputFiles="+inputFiles+" outputFile="+outputFile+" maxEvents=-1"

print bashCommand

import subprocess
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output = process.communicate()[0]