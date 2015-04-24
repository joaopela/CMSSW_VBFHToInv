=========================================
Generator Level Filter Efficiency Studies
=========================================

The scripts and code in this directory aim to preform a study on the efficiency of generator level jet filters. 

This work was made in the context of the feasibility study of QCD VBF-like + MET samples with LHC run II condition to be used bu the CMS VBF Higgs to Invisible Analysis.

Quick receipt (in bash command line):
```bash
./createJobs.sh
./submitJobs.sh 

#Wait a few hours
./haddJobs.sh
vbfinv_qcdSamplesRunII_extractResults
```

Description of commands
* **createJobs.sh**: Create all jobs for all QCD pT hats
* **submitJobs.sh**: Submit all jobs to CERN lxbatch
* **haddJobs.sh**: Add all histogram together for each QCD pT hat
* **vbfinv_qcdSamplesRunII_extractResults**: C++ code to extract plots and tables
