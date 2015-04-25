#!/usr/bin/env python

import os
import stat
import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('-py',     help='Python file',        required=True)
parser.add_argument('-job',    help='Job Executable',     required=True)
parser.add_argument('-jobPost',help='Post Job Executable',default="")
parser.add_argument('-n',      help='Number of jobs',     required=True)
parser.add_argument('-ev',     help='Events per jobs',    required=True)
parser.add_argument('-q',      help='Batch queue',        required=True)
parser.add_argument('-outDir', help='Output dir',         required=True)

args = vars(parser.parse_args())
print "###############################"
print "### Automatic job generator ###"
print "###############################"
print "Python file         :",args['py']
print "Job Executable      :",args['job']
print "Post Job Executable :",args['jobPost']
print "Number of jobs      :",args['n']
print "Events per job      :",args['ev']
print "Batch queue         :",args['q']
print "Output dir          :",args['outDir']
print ""

if not os.path.exists(args['outDir']):
  os.makedirs(args['outDir'])

outDir          = os.path.abspath(args['outDir'])
cmsswDir        = os.environ["CMSSW_BASE"]+"/src/"
cmsswOuputDir   = outDir.replace(cmsswDir,'')
eventsPerJob    = args['ev']
numberOfJobs    = int(args['n'])
batchQueue      = args['q']
cfgFilePath     = args['py']
jobFilePath     = args['job']
jobFilePostPath = args['jobPost']

fSubmit = open(outDir+'/submitJobs.sh','w')
fSubmit.write("#!/bin/sh\n")
fSubmit.write("\n")

for jobNumber in range(1,numberOfJobs+1):

  submitCmd = "bsub -q "+batchQueue

  cfgFileBasename    = os.path.basename(cfgFilePath)
  pointPosition      = cfgFileBasename.index('.')
  cfgOutFileBasename = cfgFileBasename[:pointPosition]+'_'+str(jobNumber)+cfgFileBasename[pointPosition:]
  cfgOutFilePath     = outDir+"/"+cfgOutFileBasename
  cfgOutFileBasenameA, cfgOutFileBasenameB = os.path.splitext(cfgOutFileBasename)

  with open(cfgOutFilePath,'w') as new_file:
    with open(cfgFilePath) as old_file:
      for line in old_file:
        line0 = line .replace("jobNumber=0", "jobNumber="+str(jobNumber))
        line1 = line0.replace("process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))",
                                "process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32("+eventsPerJob+"))")
        new_file.write(line1)
          
  new_file.close()
  old_file.close()
  
  # Making job executable 
  jobFileBasename    = os.path.basename(jobFilePath)
  pointPosition      = jobFileBasename.index('.')
  jobOutFileBasename = jobFileBasename[:pointPosition]+'_'+str(jobNumber)+jobFileBasename[pointPosition:]
  jobOutFilePath     = outDir+"/"+jobOutFileBasename
  
  with open(jobOutFilePath,'w') as new_file:
    with open(jobFilePath) as old_file:
      for line in old_file:
        
        line0 = line .replace("CMSSW_DIR=",    "CMSSW_DIR="+cmsswDir)
        line1 = line0.replace("CMSSW_JOB_CFG=","CMSSW_JOB_CFG="+cfgOutFileBasenameA)
        line2 = line1.replace("CMSSW_JOB_DIR=","CMSSW_JOB_DIR="+cmsswOuputDir)
        new_file.write(line2)

  old_file.close()
  new_file.close()
  os.chmod(jobOutFilePath, stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)

  

  # Making post job executable   
  if jobFilePostPath is not "":
    
    jobPostFileBasename     = os.path.basename(jobFilePostPath)
    pointPosition           = jobPostFileBasename.index('.')
    jobPostOutFileBasename  = jobPostFileBasename[:pointPosition]+'_'+str(jobNumber)+jobPostFileBasename[pointPosition:]
    jobPostOutFilePath      = outDir+"/"+jobPostOutFileBasename
    
    with open(jobPostOutFilePath,'w') as new_file:
      with open(jobFilePostPath) as old_file:
        for line in old_file:
          
          line0 = line .replace("CMSSW_DIR=",    "CMSSW_DIR="+cmsswDir)
          line1 = line0.replace("CMSSW_JOB_CFG=","CMSSW_JOB_CFG="+cfgOutFileBasenameA)
          line2 = line1.replace("CMSSW_JOB_DIR=","CMSSW_JOB_DIR="+cmsswOuputDir)
          new_file.write(line2)
    
    old_file.close()
    new_file.close()
    os.chmod(jobPostOutFilePath, stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    
    submitCmd += " -Ep "+jobPostFileBasename
  
  submitCmd += " \""+jobPostOutFilePath+"\"\n"
  fSubmit.write(submitCmd)
  
fSubmit.close()
os.chmod(outDir+'/submitJobs.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
