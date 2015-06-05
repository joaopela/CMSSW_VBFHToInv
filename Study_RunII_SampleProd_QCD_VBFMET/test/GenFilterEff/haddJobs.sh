#!/bin/bash

# This script will add all the results from the jobs produced with the script 'createJobs.sh'
# this will be done with ROOT hadd command

hadd GenFilterAnalyzer_QCD_Pt-30to50.root   QCD_Pt-30to50/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-50to80.root   QCD_Pt-50to80/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-80to120.root  QCD_Pt-80to120/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-120to170.root QCD_Pt-120to170/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-170to300.root QCD_Pt-170to300/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-300to470.root QCD_Pt-300to470/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-470to600.root QCD_Pt-470to600/GenFilterAnalyzer_*.root
hadd GenFilterAnalyzer_QCD_Pt-600to800.root QCD_Pt-600to800/GenFilterAnalyzer_*.root
