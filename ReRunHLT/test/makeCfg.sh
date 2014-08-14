#!/bin/bash

cmsDriver.py HLT2 --conditions POSTLS162_V2::All -n 10 --eventcontent HLTDEBUG -s DIGI,L1,HLT --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --geometry Extended2015 --magField 38T_PostLS1 --no_exec --filein /store/mc/Fall13dr/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM-RAW/tsg_PU20bx25_POSTLS162_V2-v1/00000/001A6D13-E16C-E311-BE56-00266CFAE7C4.root --fileout file:hltReRunResults.root
