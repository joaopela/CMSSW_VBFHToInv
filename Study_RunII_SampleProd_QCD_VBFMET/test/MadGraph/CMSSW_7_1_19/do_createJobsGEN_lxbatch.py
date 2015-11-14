#!/bin/python

import os
import stat
from subprocess import call

sJobs     = 0
nJobs     = 200
fileIndex = 0

fSubmit = open('submitJobs.sh','w')
fSubmit.write("#!/bin/sh\n")
fSubmit.write("\n")

for x in range(sJobs,nJobs):
  
  path = 'runJob'+str(x)+'.sh';

  with open(path,'w') as fOut:
    fOut.write("#!/bin/bash\n")
    fOut.write("\n")
    fOut.write("");
    fOut.write("EVENTS=10000\n")
    fOut.write("JOB="+str(x)+"\n")
    fOut.write("\n")
    fOut.write("cd $TMPDIR\n")
    fOut.write("\n")
    fOut.write("scramv1 p CMSSW CMSSW_7_1_19\n")
    fOut.write("\n")
    fOut.write("cd CMSSW_7_1_19/src\n")
    fOut.write("eval `scramv1 runtime -sh`\n")
    fOut.write("\n")
    fOut.write("tar -xvaf /afs/cern.ch/work/p/pela/public/qcd_vbf_samples/gridpack_v2/qcd_vbf_tarball.tar.xz\n")
    fOut.write("./runcmsgrid.sh $EVENTS $JOB 1\n")
    fOut.write("\n")
    fOut.write("mv cmsgrid_final.lhe /afs/cern.ch/work/p/pela/public/qcd_vbf_samples/gridpack_v2/events/ev_seed${JOB}_n${EVENTS}.lhe\n")

    os.chmod(path, stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)

    fSubmit.write("bsub -q 1nd runJob"+str(x)+".sh\n")

