#!/bin/bash 

CMSSW_DIR=
CMSSW_JOB_DIR=
CMSSW_JOB_CFG=

# Setting core file size to zero
ulimit -c 0

cd $CMSSW_DIR
cd $CMSSW_JOB_DIR

if [ -e  $CMSSW_JOB_CFG.status.running ]; then 
  # Updating job status
  rm -f $CMSSW_JOB_CFG.status.*
  touch $CMSSW_JOB_CFG.status.failed_job
fi
