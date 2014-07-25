#!/bin/bash

g++ getResultsTriggerStudy.cxx -o getResultsTriggerStudy.exe -g -pthread -m64 -I/home/pela/sw/root_v5.34.11/include -L/home/pela/sw/root_v5.34.11/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -I/home/pela/sw/ICTools/src -L/home/pela/sw/ICTools/lib  -lICAlgorithm -lICFWCore -lICHistograms -lICLatex -lICParameters -lICPlots
