#!/bin/bash

bsub -q 1nw runQCD_Pt-30to50.sh
bsub -q 1nw runQCD_Pt-50to80.sh
bsub -q 1nw runQCD_Pt-80to120.sh
bsub -q 1nw runQCD_Pt-120to170.sh
bsub -q 1nw runQCD_Pt-170to300.sh
bsub -q 1nw runQCD_Pt-300to470.sh
bsub -q 1nw runQCD_Pt-470to600.sh
bsub -q 1nw runQCD_Pt-600to800.sh
