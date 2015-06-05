#!/bin/bash

cd QCD_Pt-30to50_step1
./submitJobs.sh
cd ..

cd QCD_Pt-50to80_step1
./submitJobs.sh
cd ..

cd QCD_Pt-80to120_step1
./submitJobs.sh
cd ..

cd QCD_Pt-120to170_step1
./submitJobs.sh
cd ..

cd QCD_Pt-170to300_step1
./submitJobs.sh
cd ..

cd QCD_Pt-300to470_step1
./submitJobs.sh
cd ..

cd QCD_Pt-470to600_step1
./submitJobs.sh
cd ..

cd QCD_Pt-600to800_step1
./submitJobs.sh
cd ..

echo "done!"
