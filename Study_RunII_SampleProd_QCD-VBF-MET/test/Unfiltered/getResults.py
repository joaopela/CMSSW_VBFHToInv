#!/usr/bin/python

from optparse import OptionParser

parser = OptionParser()
parser.add_option('-c','--cfg', dest='cfgFile', help='')
(options, args) = parser.parse_args()

if options.cfgFile:
  print "Configuration file:",options.cfgFile
  
  from HEPFWCommon.LatexCore.tabulate import tabulate
  from importlib import import_module
  import re
  
  mod     = import_module(options.cfgFile)
  results = getattr(mod, 'results')
  myOrder = getattr(mod, 'myOrder')
  
  header = []
  header.append('Sample')
  header.append('Job Number')
  header.append('CPU Model')
  header.append('#CPU')
  header.append('RAM')
  header.append('Job Start')
  
  data = []
  
  for key in myOrder:
    
    jobStartTime = ''
    jobNumber    = 0
    cpuNumber    = 0
    cpuName      = str('')
    mem          = 0
    totalXSec    = ''

    print "========================="
    print 'key=',key,' val=',results[key]
    print
    
    with open(results[key]+"/STDOUT",'r') as fIn:
      
      for line in fIn:
        
        if line.find('CERN job starter') != -1:
          strSplit = line.rsplit(': ',1)[1]
          jobStartTime = strSplit.split(' $',1)[0]
          
        if line.find('Working directory is') != -1:
          strSplit  = line.rsplit('/',1)[1]
          jobNumber = strSplit.split('>',1)[0]
           
        if line.find('processor') != -1 and line.find(':') != -1:
          cpuNumber=cpuNumber+1
          
        if cpuName=='' and line.find('model name') != -1 and line.find(':') != -1:
          strSplit = re.split(': |\n',line)
          cpuName  = strSplit[1]
          
        if line.find('MemTotal') != -1:
          strSplit = filter(None, re.split('[:\s\n]',line))
          mem = strSplit[1]
        
        if line.find('Before Filtrer: total cross section') != -1:
          totalXSec = line.rsplit('= ',1)[1]
     
    print "jobStartTime =",jobStartTime
    print "jobNumber    =",jobNumber
    print "cpuNumber    =",cpuNumber
    print "cpuName      =",cpuName
    print "RAM total    =",mem
    print "totalXSec    =",totalXSec
    
    iData = []
    iData.append(key)
    iData.append(jobNumber)
    iData.append(cpuName)
    iData.append(cpuNumber)
    iData.append(mem)
    iData.append(jobStartTime)
    data.append(iData)
  
  print tabulate(data,header)
  
