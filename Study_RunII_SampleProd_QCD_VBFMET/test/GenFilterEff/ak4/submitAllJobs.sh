#!/bin/bash

cd QCD_Pt-30to50
./submitJobs.sh
cd ..

cd QCD_Pt-50to80
./submitJobs.sh
cd ..

cd QCD_Pt-80to120
./submitJobs.sh
cd ..

cd QCD_Pt-120to170
./submitJobs.sh
cd ..

cd QCD_Pt-170to300
./submitJobs.sh
cd ..

cd QCD_Pt-300to470
./submitJobs.sh
cd ..

cd QCD_Pt-470to600
./submitJobs.sh
cd ..

cd QCD_Pt-600to800
./submitJobs.sh
cd ..

echo "done!"
