#!/usr/bin/env python

import argparse
parser = argparse.ArgumentParser(description='Run CMSSW ANALYSIS step over GEN Files')
parser.add_argument('-d',       type=str,help='Target directory')
parser.add_argument('-n',       type=str,help='Max events')
parser.add_argument('-dijetPt', type=str,help='dijet pT')
parser.add_argument('-dijetMjj',type=str,help='dijet Mjj')
args = parser.parse_args()

import os
files = os.listdir(args.d)

inputFiles = ''
for f in files:
  
  if "CMSSW_7_1_19_Hadronizer" in f and "all" not in f:
    if inputFiles is not '':
      inputFiles += ','
  
    inputFiles += 'file:'+args.d+'/'+f

outputFile  = "file:"+args.d+"/PartonGenJetAnalyzer_QCD_VBFLike_all.root"
bashCommand = "cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles="+inputFiles+" outputFile="+outputFile+" maxEvents="+args.n+" dijetPt="+args.dijetPt+" dijetMjj="+args.dijetMjj

print bashCommand

import subprocess
p = subprocess.Popen(bashCommand.split(), shell=True)
p.communicate()
