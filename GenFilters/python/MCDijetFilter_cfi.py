import FWCore.ParameterSet.Config as cms

mcDijetFilter_Pt20_Eta5p0_DEta3p2_Mjj700 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(20.0),
  MaxEta = cms.untracked.double(5.0),
  MinEta = cms.untracked.double(-5.0),
  MinDeltaEta = cms.untracked.double(3.2),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(6.30),
  MinInvMass = cms.untracked.double(700.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# Tight cuts
mcDijetFilter_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj1000 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(50.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(1.50),
  MinInvMass = cms.untracked.double(1000.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# Same as 'Tight' but with DPhi cut relaxed to 2.0
mcDijetFilter_Pt50_Eta4p8_DEta3p5_Dphi2p0_Mjj1000 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(50.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(2.00),
  MinInvMass = cms.untracked.double(1000.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# Same as 'Tight' but with DPhi cut relaxed to 2.5
mcDijetFilter_Pt50_Eta4p8_DEta3p5_Dphi2p5_Mjj1000 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(50.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(2.50),
  MinInvMass = cms.untracked.double(1000.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# Same as 'Tight' but with no DPhi cuts
mcDijetFilter_Pt50_Eta4p8_DEta3p5_Mjj1000 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(50.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(6.30),
  MinInvMass = cms.untracked.double(1000.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# Tight cuts but with Pt cut relaxed to 40
mcDijetFilter_Pt40_Eta4p8_DEta3p5_Dphi1p5_Mjj1000 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(40.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(1.50),
  MinInvMass = cms.untracked.double(1000.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

#####################################
# HLT jet cuts
#####################################
mcDijetFilter_Pt40_Eta4p8_DEta3p5_Mjj600 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(40.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(6.30),
  MinInvMass = cms.untracked.double(600.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# HLT jet cuts + Tight DPhi cuts
mcDijetFilter_Pt40_Eta4p8_DEta3p5_Dphi1p5_Mjj600 = cms.EDFilter("MCDijetFilter",
  MinPt = cms.untracked.double(40.0),
  MaxEta = cms.untracked.double(4.8),
  MinEta = cms.untracked.double(-4.8),
  MinDeltaEta = cms.untracked.double(3.5),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(1.50),
  MinInvMass = cms.untracked.double(600.0),
  MaxInvMass = cms.untracked.double(50000.0),
  outFile = cms.untracked.string('mcDijetFilter.root')
)

# Working Point B
mcDijetFilter_Pt50_Eta4p8_DEta3p0_Dphi2p0_Mjj1000 = cms.EDFilter("MCDijetFilter",
  MinPt       = cms.untracked.double(40.0),
  MaxEta      = cms.untracked.double(4.75),
  MinEta      = cms.untracked.double(-4.75),
  MinDeltaEta = cms.untracked.double(3.0),
  MaxDeltaEta = cms.untracked.double(10.0),
  MinDeltaPhi = cms.untracked.double(0),
  MaxDeltaPhi = cms.untracked.double(2.0),
  MinInvMass  = cms.untracked.double(1000.0),
  MaxInvMass  = cms.untracked.double(50000.0),
  outFile     = cms.untracked.string('mcDijetFilter.root')
)



# Alias
mcDijetFilter_RunI      = mcDijetFilter_Pt20_Eta5p0_DEta3p2_Mjj700
mcDijetFilter_RunII_WPA = mcDijetFilter_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj1000
mcDijetFilter_RunII_WPB = mcDijetFilter_Pt50_Eta4p8_DEta3p0_Dphi2p0_Mjj1000

