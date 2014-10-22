#!/bin/bash

cd PU40bx25_VBFInv
./submitJobs.sh
cd ..

cd PU40bx25_NeutrinoGun
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-1000to1400/
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-120to170
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-1400to1800
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-170to300
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-300to470
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-30to50
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-470to600
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-50to80
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-600to800
./submitJobs.sh
cd ..

cd PU40bx25_QCD_Pt-800to1000
./submitJobs.sh
cd ..
