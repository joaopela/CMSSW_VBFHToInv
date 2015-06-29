from WMCore.Configuration import Configuration

config = Configuration()

config.section_('General')
config.section_('Data')
config.section_('JobType')
config.section_('User')
config.section_('Site')
config.General.transferOutputs = True
config.General.transferLogs    = True
config.General.workArea        = 'HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79/HCALMethod3'

config.JobType.psetName    = 'HLT_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3_cfg.py'
config.JobType.pluginName  = 'Analysis'
config.JobType.outputFiles = ['hltReRunResults.root',]

config.Data.outLFNDirBase   = '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod3/'
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

    tasks=list()
    #Signal 125 GeV
    tasks.append(('VBF_HToInv_M-125_PU20bx25', '/VBF_HToInv_M-125_13TeV_powheg-pythia6/Phys14DR-AVE30BX50_tsg_PHYS14_ST_V1-v2/GEN-SIM-RAW','PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('VBF_HToInv_M-125_PU40bx25', '/VBF_HToInv_M-125_13TeV_powheg-pythia6/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/GEN-SIM-RAW', 'PU40bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('VBF_HToInv_M-125_AVE30BX50','/VBF_HToInv_M-125_13TeV_powheg-pythia6/Phys14DR-PU40bx25_PHYS14_25_V1-v2/GEN-SIM-RAW',     'PU30BX50_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    
    tasks.append(('QCD_Pt-30to50_AVE20BX25',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v2/GEN-SIM-RAW',    'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-50to80_AVE20BX25',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',    'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-80to120_AVE20BX25',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',   'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-120to170_AVE20BX25',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',  'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-170to300_AVE20BX25',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',  'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-300to470_AVE20BX25',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',  'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-470to600_AVE20BX25',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',  'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-600to800_AVE20BX25',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',  'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-800to1000_AVE20BX25', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW', 'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-1000to1400_AVE20BX25','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW','PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-1400to1800_AVE20BX25','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW','PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))
    tasks.append(('QCD_Pt-1800_AVE20BX25',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/Phys14DR-AVE20BX25_tsg_castor_PHYS14_25_V3-v1/GEN-SIM-RAW',      'PU20bx25_HLT_PATTrigger_dev_CMSSW_7_4_0_GRun_V79_HCALMethod3'))

    #tasks.append(('QCD_Pt-30to50_AVE30BX50',    '/QCD_Pt-30to50_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v2/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-50to80_AVE30BX50',    '/QCD_Pt-50to80_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-80to120_AVE30BX50',   '/QCD_Pt-80to120_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-120to170_AVE30BX50',  '/QCD_Pt-120to170_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-170to300_AVE30BX50',  '/QCD_Pt-170to300_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-300to470_AVE30BX50',  '/QCD_Pt-300to470_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-470to600_AVE30BX50',  '/QCD_Pt-470to600_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-600to800_AVE30BX50',  '/QCD_Pt-600to800_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-800to1000_AVE30BX50', '/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-1000to1400_AVE30BX50','/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-1400to1800_AVE30BX50','/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))
    #tasks.append(('QCD_Pt-1800_AVE30BX50',      '/QCD_Pt-1800_Tune4C_13TeV_pythia8/Phys14DR-AVE30BX50_tsg_castor_PHYS14_ST_V1-v1/GEN-SIM-RAW'))

    for task in tasks:
        print task[0]
        config.General.requestName  = task[0]
        config.Data.inputDataset    = task[1]
        config.Data.publishDataName = task[2]
        submit(config)




