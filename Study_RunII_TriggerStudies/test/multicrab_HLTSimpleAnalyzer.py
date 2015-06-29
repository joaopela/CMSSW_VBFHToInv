from WMCore.Configuration import Configuration

config = Configuration()

config.section_('General')
config.section_('Data')
config.section_('JobType')
config.section_('User')
config.section_('Site')
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

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    # PU20bx25 HCALMethod0
    config.General.workArea    = 'HLTSimpleAnalyser/PU20bx25/HCALMethod0'
    config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU20bx25/HCALMethod0/'
    tasks_PU20bx25_HCALMethod0 = list()
    tasks_PU20bx25_HCALMethod0.append(('VBF_HToInv_M-125_PU20bx25',  '/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-crab_VBF_HToInv_M-125_PU20bx25-bab29548c73f71aefc21197e14949f23/USER'))    #020/020 done
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-30to50_AVE20BX25',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-30to50_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))         #220/224
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-50to80_AVE20BX25',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-50to80_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))         #158/224
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-80to120_AVE20BX25',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-80to120_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))       #262/262 done
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-120to170_AVE20BX25',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-120to170_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #280/280 done
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-170to300_AVE20BX25',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-170to300_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #089/174 
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-300to470_AVE20BX25',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-300to470_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #175/300
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-470to600_AVE20BX25',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-470to600_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #249/249
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-600to800_AVE20BX25',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-600to800_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))     #233/238
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-800to1000_AVE20BX25', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-800to1000_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))   #044/044
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-1000to1400_AVE20BX25','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-1000to1400_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER')) #045/045
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-1400to1800_AVE20BX25','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-1400to1800_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER')) #045/045
    tasks_PU20bx25_HCALMethod0.append(('QCD_Pt-1800_AVE20BX25',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/pela-crab_QCD_Pt-1800_AVE20BX25-bab29548c73f71aefc21197e14949f23/USER'))             #046/047
    
    for task in tasks_PU20bx25_HCALMethod0:
      print task[0]
      config.General.requestName  = task[0]
      config.Data.inputDataset    = task[1]
      submit(config)
    
    # PU20bx25 HCALMethod3
    config.General.workArea    = 'HLTSimpleAnalyser/PU20bx25/HCALMethod3'
    config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU20bx25/HCALMethod3/'
    tasks_PU20bx25_HCALMethod3 = list()
    tasks_PU20bx25_HCALMethod3.append(('VBF_HToInv_M-125_PU20bx25',  '/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #19/20
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-30to50_AVE20BX25',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #168/224
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-50to80_AVE20BX25',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #162/224
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-80to120_AVE20BX25',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #261/262
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-120to170_AVE20BX25',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #280/280
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-170to300_AVE20BX25',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #89/174
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-300to470_AVE20BX25',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #172/207
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-470to600_AVE20BX25',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #249/249
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-600to800_AVE20BX25',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #222/238
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-800to1000_AVE20BX25', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #44/44
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-1000to1400_AVE20BX25','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #45/45
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-1400to1800_AVE20BX25','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #44/45
    tasks_PU20bx25_HCALMethod3.append(('QCD_Pt-1800_AVE20BX25',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/pela-PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #46/47 <---
    
    for task in tasks_PU20bx25_HCALMethod3:
      print task[0]
      config.General.requestName  = task[0]
      config.Data.inputDataset    = task[1]
      submit(config)
    
    # PU40bx25 HCALMethod0
    config.General.workArea    = 'HLTSimpleAnalyser/PU40bx25/HCALMethod0'
    config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU40bx25/HCALMethod0/'
    tasks_PU40bx25_HCALMethod0=list()
    tasks_PU40bx25_HCALMethod0.append(('VBF_HToInv_M-125_PU40bx25','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-crab_VBF_HToInv_M-125_PU40bx25-bab29548c73f71aefc21197e14949f23/USER')) #6/6
    
    for task in tasks_PU40bx25_HCALMethod0:
      print task[0]
      config.General.requestName  = task[0]
      config.Data.inputDataset    = task[1]
      submit(config)
    
    # PU40bx25 HCALMethod3
    config.General.workArea    = 'HLTSimpleAnalyser/PU40bx25/HCALMethod3'
    config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU40bx25/HCALMethod3/'
    tasks_PU40bx25_HCALMethod3=list()
    tasks_PU40bx25_HCALMethod3.append(('VBF_HToInv_M-125_PU40bx25','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU40bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #6/6
    
    for task in tasks_PU40bx25_HCALMethod3:
      print task[0]
      config.General.requestName  = task[0]
      config.Data.inputDataset    = task[1]
      submit(config)
    
    # PU30bx50 HCALMethod0
    config.General.workArea    = 'HLTSimpleAnalyser/PU30bx50/HCALMethod0'
    config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU30bx50/HCALMethod0/'
    tasks_PU30bx50_HCALMethod0=list()
    tasks_PU30bx50_HCALMethod0.append(('VBF_HToInv_M-125_AVE30BX50','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-crab_VBF_HToInv_M-125_AVE30BX50-bab29548c73f71aefc21197e14949f23/USER')) #8/8
    
    for task in tasks_PU30bx50_HCALMethod0:
      print task[0]
      config.General.requestName  = task[0]
      config.Data.inputDataset    = task[1]
      submit(config)
    
    # PU30bx50 HCALMethod3
    config.General.workArea    = 'HLTSimpleAnalyser/PU30bx50/HCALMethod3'
    config.Data.outLFNDirBase  = '/store/user/pela/2015/HLTSimpleAnalyser/PU30bx50/HCALMethod3/'
    tasks_PU30bx50_HCALMethod3 = list()
    tasks_PU30bx50_HCALMethod3.append(('VBF_HToInv_M-125_AVE30BX50','/VBF_HToInv_M-125_13TeV_powheg-pythia6/pela-PU30BX50_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3-44a9dda7380fda8c10ac873eb1cb389d/USER')) #8/8
    
    for task in tasks_PU30bx50_HCALMethod3:
      print task[0]
      config.General.requestName  = task[0]
      config.Data.inputDataset    = task[1]
      submit(config)




