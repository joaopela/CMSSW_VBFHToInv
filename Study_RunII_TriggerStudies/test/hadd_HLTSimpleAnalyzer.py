#!/bin/python

import os
import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('-puScenario',required=True,help='Select PU scenario from: Phys14_PU40bx25, Phys14_PU20bx25 or Phys14_PU30bx50')
parser.add_argument("-hcalMethod",required=True,help="Select HCAL Method")

if args['puScenario']=='Phys14_PU20bx25' and args['hcalMethod']=='0':

  # HLTSimpleAnalyser PU20bx25 HCALMethod0
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_VBF_HToInv_M-125.root  HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_VBF_HToInv_M-125_PU20bx25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-30to50.root     HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-30to50_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-50to80.root     HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-50to80_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-80to120.root    HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-80to120_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-120to170.root   HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-120to170_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-170to300.root   HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-170to300_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-300to470.root   HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-300to470_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-470to600.root   HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-470to600_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-600to800.root   HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-600to800_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-800to1000.root  HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-800to1000_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-1000to1400.root HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-1000to1400_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-1400to1800.root HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-1400to1800_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-1800.root       HLTSimpleAnalyser/PU20bx25/HCALMethod0/crab_QCD_Pt-1800_AVE20BX25/results/*.root")

elif args['puScenario']=='Phys14_PU20bx25' and args['hcalMethod']=='2':

  # HLTSimpleAnalyser PU20bx25 HCALMethod2
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_VBF_HToInv_M-125.root  HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_VBF_HToInv_M-125/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-30to50.root     HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-30to50/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-50to80.root     HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-50to80/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-80to120.root    HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-80to120/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-120to170.root   HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-120to170/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-170to300.root   HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-170to300/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-300to470.root   HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-300to470/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-470to600.root   HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-470to600/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-600to800.root   HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-600to800/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-800to1000.root  HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-800to1000/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-1000to1400.root HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-1000to1400/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-1400to1800.root HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-1400to1800/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod2_QCD_Pt-1800.root       HLTSimpleAnalyser/PU20bx25/HCALMethod2/crab_QCD_Pt-1800/results/*.root")

elif args['puScenario']=='Phys14_PU20bx25' and args['hcalMethod']=='3':

  # HLTSimpleAnalyser PU20bx25 HCALMethod3
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_VBF_HToInv_M-125.root  HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_VBF_HToInv_M-125_PU20bx25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-30to50.root     HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-30to50_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-50to80.root     HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-50to80_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-80to120.root    HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-80to120_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-120to170.root   HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-120to170_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-170to300.root   HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-170to300_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-300to470.root   HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-300to470_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-470to600.root   HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-470to600_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-600to800.root   HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-600to800_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-800to1000.root  HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-800to1000_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-1000to1400.root HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-1000to1400_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-1400to1800.root HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-1400to1800_AVE20BX25/results/*.root")
  os.system("hadd HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-1800.root       HLTSimpleAnalyser/PU20bx25/HCALMethod3/crab_QCD_Pt-1800_AVE20BX25/results/*.root")

