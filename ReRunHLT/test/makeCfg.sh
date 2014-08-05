#!/bin/bash

hltGetConfiguration /dev/CMSSW_6_2_0/GRun --full --offline --mc --unprescale --process HLTv2 --globaltag auto:upgradePLS1 > ReRunHLT_cfg.py
