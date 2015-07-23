
def submit(config,tasks):

  config.General.transferOutputs = True
  config.General.transferLogs    = True

  config.JobType.pluginName  = 'Analysis'
  config.JobType.outputFiles = ['hltReRunResults.root',]
  
  config.Data.inputDBS        = 'global'
  config.Data.unitsPerJob     = 10
  config.Data.splitting       = 'FileBased'
  config.Data.publication     = True
  
  config.Site.storageSite     = 'T2_UK_London_IC'
  
  if __name__ == '__main__':
  
      from CRABAPI.RawCommand import crabCommand
      from httplib import HTTPException
  
      # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
      # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
  
      def submit(config):
          try:
              crabCommand('submit', config = config)
          except HTTPException, hte:
              print HTTPException
              print hte.headers
  
      #############################################################################################
      ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
      #############################################################################################

      for task in tasks:
          print task[0]
          config.General.requestName  = task[0]
          config.Data.inputDataset    = task[1]
          submit(config)

import sys
import argparse

parser = argparse.ArgumentParser(description='This scripts will create and submit jobs to rerun HLT and produce PAT Trigger objects over a set of MC samples.')
parser.add_argument('-addFilters',required=True,help='Select if we are adding additional filters')
parser.add_argument('-mcCampaign',required=True,help='Select MC campaign from: Phys14 or Summer15')
parser.add_argument('-puScenario',required=True,help='Select PU scenario from: PU40bx25, PU20bx25 or PU30bx50')
parser.add_argument("-hcalMethod",required=True,help="Select HCAL Method")

args = vars(parser.parse_args())
print "mcCampaign :",args['mcCampaign']
print "puScenario :",args['puScenario']
print "hcalMethod :",args['hcalMethod']
print "addFilters :",args['addFilters']

addFilters = args['addFilters']
mcCampaign = args['mcCampaign']
puScenario = args['puScenario']
hcalMethod = args['hcalMethod']

#Making strings to DBS publishing
strFilters    = ''
if addFilters=='true':
  strFilters += "_withFiters"

strHCALMethod = 'HCALMethod'+hcalMethod
strHLTMenu    = 'dev_CMSSW_7_4_0_GRun_V79'

from WMCore.Configuration import Configuration

config = Configuration()
config.section_('General')
config.section_('Data')
config.section_('JobType')
config.section_('User')
config.section_('Site')

config.General.workArea     = 'HLT_PATTrigger'+strFilters+'/'+mcCampaign+'/'+puScenario+'/'+strHLTMenu+'/'+strHCALMethod+'/'
config.Data.outLFNDirBase   = '/store/user/pela/2015/HLT_PATTrigger'+strFilters+'/'+mcCampaign+'/'+puScenario+'/'+strHLTMenu+'/'+strHCALMethod+'/'
config.Data.publishDataName = 'HLT_PATTrigger'+strFilters+'_'+mcCampaign+'_'+puScenario+'_'+strHLTMenu+'_'+strHCALMethod

print "Working area : "+config.General.workArea
print "Out LFN dir  : "+config.Data.outLFNDirBase
print "Publish name : "+config.Data.publishDataName

if hcalMethod=='0' and addFilters=='false':
  config.JobType.psetName   = 'rerunHLT_Phys14_dev_CMSSW_7_4_0_GRun_V79_HCALMethod0_cfg.py'

elif hcalMethod=='2' and addFilters=='false':
  config.JobType.psetName   = 'rerunHLT_Phys14_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2_cfg.py'

elif hcalMethod=='3' and addFilters=='false':
  config.JobType.psetName   = 'rerunHLT_Phys14_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3_cfg.py'

elif hcalMethod=='0' and addFilters=='true':
  config.JobType.psetName   = 'rerunHLT_Phys14_dev_CMSSW_7_4_0_GRun_V79_HCALMethod0_PUFiltered_cfg.py'

elif hcalMethod=='3' and addFilters=='true':
  config.JobType.psetName   = 'rerunHLT_Phys14_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3_PUFiltered_cfg.py'

else:
  print "Unknown hcalMethod or addFilters option!"
  sys.exit(1)

print "pset name    : "+config.JobType.psetName

# Filling tasks with samples according to user requests
tasks=list()

if args['mcCampaign']=='Phys14' and args['puScenario']=='PU40bx25':
  
  tasks.append(('VBF_HToInv_M-125_PU40bx25', '/VBF_HToInv_M-125_13TeV_powheg-pythia6/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/GEN-SIM-RAW'))

elif args['mcCampaign']=='Phys14' and args['puScenario']=='PU20bx25':
  
  tasks.append(('VBF_HToInv_M-125',  '/VBF_HToInv_M-125_13TeV_powheg-pythia6/Phys14DR-AVE30BX50_tsg_PHYS14_ST_V1-v2/GEN-SIM-RAW'))

  # Inclusive QCD samples
  tasks.append(('QCD_Pt-15to30',    '/QCD_Pt-15to30_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v2/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-30to50',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v2/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-50to80',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-80to120',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-120to170',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-170to300',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-300to470',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-470to600',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-600to800',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-800to1000', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-1000to1400','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-1400to1800','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-1800',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW'))

  # QCD EMEnriched
  tasks.append(('QCD_Pt-30to80_EMEnriched', '/QCD_Pt-30to80_EMEnriched_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',))
  tasks.append(('QCD_Pt-80to170_EMEnriched','/QCD_Pt-80to170_EMEnriched_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',))

  # QCD Mu Enriched Pion and Kaon decay
  tasks.append(('QCD_Pt-30to50_MuEnrichedPt5_PionKaonDecay', '/QCD_Pt-30to50_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v2/GEN-SIM-RAW',))
  tasks.append(('QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay', '/QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/GEN-SIM-RAW',))
  tasks.append(('QCD_Pt-80to120_MuEnrichedPt5_PionKaonDecay','/QCD_Pt-80to120_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/GEN-SIM-RAW',))

  # DY to LL
  tasks.append(('DYToMuMu','/DYToMuMu_Tune4C_13TeV-pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/GEN-SIM-RAW',))
  tasks.append(('DYToEE',  '/DYToEE_Tune4C_13TeV-pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/GEN-SIM-RAW',))

  # W to L+nu
  tasks.append(('WToMuNu','/WToMuNu_Tune4C_13TeV-pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/GEN-SIM-RAW',))
  tasks.append(('WToENu', '/WToENu_Tune4C_13TeV-pythia8/Phys14DR-AVE20BX25_tsg_PHYS14_25_V3-v1/GEN-SIM-RAW',))

elif args['mcCampaign']=='Phys14' and args['puScenario']=='PU30bx50':

  tasks.append(('VBF_HToInv_M-125_AVE30BX50', '/VBF_HToInv_M-125_13TeV_powheg-pythia6/Phys14DR-PU40bx25_PHYS14_25_V1-v2/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-30to50_AVE30BX50',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v2/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-50to80_AVE30BX50',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-80to120_AVE30BX50',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-120to170_AVE30BX50',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-170to300_AVE30BX50',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-300to470_AVE30BX50',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-470to600_AVE30BX50',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-600to800_AVE30BX50',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-800to1000_AVE30BX50', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-1000to1400_AVE30BX50','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-1400to1800_AVE30BX50','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt-1800_AVE30BX50',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))

elif puScenario=='Spring15' and puScenario=='PU20bx25':

  tasks.append(('QCD_Pt_30to50',    '/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_50to80',    '/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_80to120',   '/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v2/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_120to170',  '/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_170to300',  '/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_300to470',  '/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_470to600',  '/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_600to800',  '/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_800to1000', '/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_1000to1400','/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_1400to1800','/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_1800to2400','/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_2400to3200','/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW'))
  tasks.append(('QCD_Pt_3200toInf', '/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIISpring15Digi74-AVE_20_BX_25ns_tsg_MCRUN2_74_V7-v1/GEN-SIM-RAW '))

else:
  print "Wrong PU Scenario"
  sys.exit(1)



submit(config,tasks)