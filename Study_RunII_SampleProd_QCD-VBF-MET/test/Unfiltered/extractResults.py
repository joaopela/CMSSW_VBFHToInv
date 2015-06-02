#!/usr/bin/python

import sys
import time
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
  
  firstJob  = True

  headerJob = []
  headerJob.append('Sample')
  headerJob.append('Job Number')
  headerJob.append('CPU Model')
  headerJob.append('nCPU')
  headerJob.append('RAM')
  headerJob.append('XSec [pb]')
  
  headerTiming = []
  headerTiming.append('Sample')
  headerTiming.append('Job Start')
  headerTiming.append('Job End')
  headerTiming.append('KSI2K')
  headerTiming.append('KHS06')
  
  headerStep1 = []
  headerStep1.append('Sample')
  
  headerStep2 = []
  headerStep2.append('Sample')
  
  dataJob     = []
  dataTimming = []
  dataStep1   = []
  dataStep2   = []
    
  for key in myOrder:
    
    jobNumber    = 0
    
    jobStartTime = ''
    jobEndTime   = ''
    
    timeKSI2K    = 0
    timeKHS06    = 0
        
    cpuNumber    = 0
    cpuName      = str('')
    mem          = 0
    totalXSec    = ''

    countStep = 0
    timeScan  = False
    
    iDataStep1 = []
    iDataStep1.append(key)

    iDataStep2 = []
    iDataStep2.append(key)

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
     
        if line.find('Job finished at') != -1:
          strSplit   = line.rsplit('Job finished at ',1)[1]
          jobEndTime = strSplit.split(' CEST ',1)[0]
          
        if line.find('KSI2K seconds') != -1:
          strSplit  = line.rsplit(' (',1)[1]
          timeKSI2K = strSplit.split(' KSI2K seconds',1)[0]
     
        if line.find('HS06  seconds') != -1:
          strSplit  = line.rsplit(' (',1)[1]
          timeKHS06 = strSplit.split(' HS06  seconds',1)[0]
     
        if line.find(' Time Summary:') != -1 or timeScan:
          if line !='\n':
            timeScan = True
          else:
            timeScan  = False
            countStep = countStep+1
            
          if timeScan and countStep==0 and line.find(' - ')!=-1:
            sys.stdout.write(line)
            
            strSplit  = line.rsplit(':',1)
            if firstJob:
              headerStep1.append(strSplit[0].replace(" - ",""))
            
            iDataStep1.append(strSplit[1].strip())
           
           
          if timeScan and countStep==1 and line.find(' - ')!=-1:
            sys.stdout.write(line)
           
            strSplit  = line.rsplit(':',1)
            if firstJob:
              headerStep2.append(strSplit[0].replace(" - ",""))
            
            iDataStep2.append(strSplit[1].strip())
    
    print "jobNumber    =",jobNumber
    print "cpuNumber    =",cpuNumber
    print "cpuName      =",cpuName
    print "RAM total    =",mem
    
    
    print "jobStartTime =",jobStartTime
    print "jobEndTime   =",jobEndTime
    print "timeKSI2K    =",timeKSI2K
    print "timeKHS06    =",timeKHS06
    print "totalXSec    =",totalXSec
    
    iData = []
    iData.append(key)
    iData.append(jobNumber)
    iData.append(cpuName)
    iData.append(cpuNumber)
    iData.append(mem)
    iData.append(totalXSec)
    
    #2010/06/23 14:22:16 & Mon May 18 16:34:34
    sTime = time.strptime(jobStartTime,'%Y/%m/%d %H:%M:%S')
    eTime = time.strptime(jobEndTime,  '%a %b %d %H:%M:%S')
    
    print sTime[0],sTime[1],sTime[2]," ",sTime[3],sTime[4],sTime[5]
    print eTime[0],eTime[1],eTime[2]," ",eTime[3],eTime[4],eTime[5]
    
    iDataTimming = []
    iDataTimming.append(key)
    iDataTimming.append(jobStartTime)
    iDataTimming.append(jobEndTime)
    iDataTimming.append(timeKSI2K)
    iDataTimming.append(timeKHS06)
    
    dataJob    .append(iData)
    dataTimming.append(iDataTimming)
    dataStep1  .append(iDataStep1)
    dataStep2  .append(iDataStep2)
        
    firstJob  = False
  
  print tabulate(dataJob,headerJob,tablefmt="latex")
  print
  print tabulate(dataTimming,headerJob,tablefmt="latex")
  print
  print tabulate(dataStep1,headerStep1,tablefmt="latex")
  print
  print tabulate(dataStep2,headerStep2,tablefmt="latex")
  