import FWCore.ParameterSet.Config as cms

from CMSSW_VBFHToInv.GenFilters.VBFGenJetFilter_cfi import *
from RecoJets.Configuration.GenJetParticles_cff import *
from RecoJets.Configuration.RecoGenJets_cff import *

vbfGenJetFilterSeq = cms.Sequence(
  genParticlesForJetsNoNu*
  ak4GenJetsNoNu*
  vbfGenJetFilter
)