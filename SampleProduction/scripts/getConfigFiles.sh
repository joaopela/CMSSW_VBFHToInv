#!/bin/bash

cd $CMSSW_BASE/src/

# Getting files
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00042 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00042-fragment.py 
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00043 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00043-fragment.py 
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00044 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00044-fragment.py
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00045 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00045-fragment.py 
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00046 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00046-fragment.py
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00047 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00047-fragment.py
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00048 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00048-fragment.py
curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BTV-Fall13-00049 --retry 2 --create-dirs -o Configuration/GenProduction/python/BTV-Fall13-00049-fragment.py

cd -
