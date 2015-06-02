#!/bin/bash

cd QCD_30to50
./submitJobs.sh
cd ..

cd QCD_50to80
./submitJobs.sh
cd ..

cd QCD_80to120 
./submitJobs.sh
cd ..

cd QCD_120to170
./submitJobs.sh
cd ..

cd QCD_170to300
./submitJobs.sh
cd ..

cd QCD_300to470
./submitJobs.sh
cd ..

cd QCD_470to600
./submitJobs.sh
cd ..

cd QCD_600to800
./submitJobs.sh
cd ..

echo "done!"
