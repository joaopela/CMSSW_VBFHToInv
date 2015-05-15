#!/bin/bash

# This script will add all the results from the jobs produced with the script 'createJobs.sh'
# this will be done with ROOT hadd command

hadd OfflineFilterAnalyzer_QCD_Pt-30to50.root   QCD_Pt-30to50/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-50to80.root   QCD_Pt-50to80/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-80to120.root  QCD_Pt-80to120/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-120to170.root QCD_Pt-120to170/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-170to300.root QCD_Pt-170to300/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-300to470.root QCD_Pt-300to470/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-470to600.root QCD_Pt-470to600/OfflineFilterAnalyzer_*.root
hadd OfflineFilterAnalyzer_QCD_Pt-600to800.root QCD_Pt-600to800/OfflineFilterAnalyzer_*.root
