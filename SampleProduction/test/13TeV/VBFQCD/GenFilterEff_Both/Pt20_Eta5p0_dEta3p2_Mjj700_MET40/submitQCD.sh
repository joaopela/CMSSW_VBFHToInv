#!/bin/bash

bsub -q 1nw run30to50.sh
bsub -q 1nw run50to80.sh
bsub -q 1nw run80to120.sh
bsub -q 1nw run120to170.sh
bsub -q 1nw run170to300.sh
bsub -q 1nw run300to470.sh
bsub -q 1nw run470to600.sh
bsub -q 1nw run600to800.sh
