
def submitTask(config,tasks):

  config.General.transferOutputs = True
  config.General.transferLogs    = True

  config.JobType.psetName    = 'runTest.py'
  config.JobType.pluginName  = 'Analysis'
  config.JobType.outputFiles = ['HLTSimpleAnalysis.root',]

  config.Data.inputDBS        = 'phys03'
  config.Data.unitsPerJob     = 20
  config.Data.splitting       = 'FileBased'
  config.Data.publication     = False
  
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


      for task in tasks:
        print task[0]
        config.General.requestName  = task[0]
        config.Data.inputDataset    = task[1]
        submit(config)


#############################
# Main code starts here
#############################
import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('-puScenario',required=True,help='Select PU scenario from: Phys14_PU40bx25, Phys14_PU20bx25 or Phys14_PU30bx50')
parser.add_argument("-hcalMethod",required=True,help="Select HCAL Method")

args = vars(parser.parse_args())
print "puScenario :",args['puScenario']
print "hcalMethod :",args['hcalMethod']

from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.section_('Data')
config.section_('JobType')
config.section_('User')
config.section_('Site')

tasks=list()

if args['puScenario']=='Phys14_PU20bx25' and args['hcalMethod']=='0':
  
  config.General.workArea    = 'HLTSimpleAnalyser/PU20bx25/HCALMethod0'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU20bx25/HCALMethod0/'

  tasks.append(('VBF_HToInv_M-125',  '/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-crab_VBF_HToInv_M-125_PU20bx25-bab29548c73f71aefc21197e14949f23/USER'))   #020/020 done
  tasks.append(('QCD_Pt-30to50',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-30to50_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))         #224/224 done
  tasks.append(('QCD_Pt-50to80',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-50to80_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))         #158/224 ????
  tasks.append(('QCD_Pt-80to120',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-80to120_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))       #262/262 done
  tasks.append(('QCD_Pt-120to170',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-120to170_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #280/280 done
  tasks.append(('QCD_Pt-170to300',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-170to300_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #089/174 
  tasks.append(('QCD_Pt-300to470',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-300to470_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #203/207
  tasks.append(('QCD_Pt-470to600',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-470to600_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #249/249 done
  tasks.append(('QCD_Pt-600to800',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-600to800_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #238/238 done
  tasks.append(('QCD_Pt-800to1000', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-800to1000_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))   #044/044 done
  tasks.append(('QCD_Pt-1000to1400','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-1000to1400_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER')) #045/045 done
  tasks.append(('QCD_Pt-1400to1800','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-1400to1800_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER')) #045/045 done
  tasks.append(('QCD_Pt-1800',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-1800_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))             #046/047

  submitTask(config,tasks)
  
elif args['puScenario']=='Phys14_PU20bx25' and args['hcalMethod']=='2':
  
  config.General.workArea    = 'HLTSimpleAnalyser/PU20bx25/HCALMethod2'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU20bx25/HCALMethod2/'

  tasks.append(('VBF_HToInv_M-125', '/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))  #020/020 done
  tasks.append(('QCD_Pt-30to50',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))     #224/224 done
  tasks.append(('QCD_Pt-50to80',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))     #224/224 done
  tasks.append(('QCD_Pt-80to120',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))    #262/262 done
  tasks.append(('QCD_Pt-120to170',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))   #280/280 done
  tasks.append(('QCD_Pt-170to300',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))   #089/174 
  tasks.append(('QCD_Pt-300to470',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))   #207/207 done
  tasks.append(('QCD_Pt-470to600',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))   #249/249 done
  tasks.append(('QCD_Pt-600to800',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))   #238/238 done
  tasks.append(('QCD_Pt-800to1000', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))  #044/044 done
  tasks.append(('QCD_Pt-1000to1400','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER')) #045/045 done
  tasks.append(('QCD_Pt-1400to1800','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER')) #045/045 done
  tasks.append(('QCD_Pt-1800',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod2-64414c57b778677c546dbdf0e6c14ed8/USER'))       #046/047
  
  submitTask(config,tasks)

elif args['puScenario']=='Phys14_PU20bx25' and args['hcalMethod']=='3':
  
  config.General.workArea    = 'HLTSimpleAnalyser/PU20bx25/HCALMethod3'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU20bx25/HCALMethod3/'
 
  tasks.append(('VBF_HToInv_M-125_PU20bx25',  '/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))  #19/20
  tasks.append(('QCD_Pt-30to50_AVE20BX25',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))     #168/224
  tasks.append(('QCD_Pt-50to80_AVE20BX25',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))     #162/224
  tasks.append(('QCD_Pt-80to120_AVE20BX25',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))    #261/262
  tasks.append(('QCD_Pt-120to170_AVE20BX25',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))   #280/280
  tasks.append(('QCD_Pt-170to300_AVE20BX25',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))   #89/174
  tasks.append(('QCD_Pt-300to470_AVE20BX25',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))   #172/207
  tasks.append(('QCD_Pt-470to600_AVE20BX25',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))   #249/249
  tasks.append(('QCD_Pt-600to800_AVE20BX25',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))   #222/238
  tasks.append(('QCD_Pt-800to1000_AVE20BX25', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))  #44/44
  tasks.append(('QCD_Pt-1000to1400_AVE20BX25','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #45/45
  tasks.append(('QCD_Pt-1400to1800_AVE20BX25','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #44/45
  tasks.append(('QCD_Pt-1800_AVE20BX25',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER'))       #46/47 <---

  submitTask(config,tasks)

elif args['puScenario']=='Phys14_PU40bx25' and args['hcalMethod']=='0':

  config.General.workArea    = 'HLTSimpleAnalyser/PU40bx25/HCALMethod0'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU40bx25/HCALMethod0/'

  tasks.append(('VBF_HToInv_M-125_PU40bx25','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-crab_VBF_HToInv_M-125_PU40bx25-bab29548c73f71aefc21197e14949f23/USER')) #6/6

  submitTask(config,tasks)

elif args['puScenario']=='Phys14_PU40bx25' and args['hcalMethod']=='3':

  # PU40bx25 HCALMethod3
  config.General.workArea    = 'HLTSimpleAnalyser/PU40bx25/HCALMethod3'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU40bx25/HCALMethod3/'

  tasks.append(('VBF_HToInv_M-125_PU40bx25','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU40bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #6/6
  
  submitTask(config,tasks)

elif args['puScenario']=='Phys14_PU30bx50' and args['hcalMethod']=='0':

  config.General.workArea    = 'HLTSimpleAnalyser/PU30bx50/HCALMethod0'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU30bx50/HCALMethod0/'

  tasks_PU30bx50_HCALMethod0.append(('VBF_HToInv_M-125_AVE30BX50','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-crab_VBF_HToInv_M-125_AVE30BX50-bab29548c73f71aefc21197e14949f23/USER')) #8/8
  
  submitTask(config,tasks)

elif args['puScenario']=='Phys14_PU30bx50' and args['hcalMethod']=='3':

  config.General.workArea    = 'HLTSimpleAnalyser/PU30bx50/HCALMethod3'
  config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU30bx50/HCALMethod3/'
  tasks_PU30bx50_HCALMethod3 = list()
  tasks_PU30bx50_HCALMethod3.append(('VBF_HToInv_M-125_AVE30BX50','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU30BX50_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #8/8
  
  submitTask(config,tasks)

else:
  
  print "Wrong PU Scenario"
