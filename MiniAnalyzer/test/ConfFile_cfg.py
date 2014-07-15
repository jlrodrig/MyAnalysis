import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
# This works              'root://cmsxrootd.fnal.gov//store/cmst3/user/gpetrucc/miniAOD/v1/TT_Tune4C_13TeV-pythia8-tauola_PU_S14_PAT.root'
# This doesn't work       '/store/cmst3/user/gpetrucc/miniAOD/v1/TT_Tune4C_13TeV-pythia8-tauola_PU_S14_PAT.root'
        'file:TT_Tune4C_13TeV-pythia8-tauola_PU_S14_PAT.root'
    )
)

process.demo = cms.EDAnalyzer('MiniAnalyzer',
                              vertices  = cms.InputTag('offlineSlimmedPrimaryVertices'),
                              muons     = cms.InputTag('slimmedMuons'),
                              electrons = cms.InputTag('slimmedElectrons'),
                              taus      = cms.InputTag('slimmedTaus'),
                              photons   = cms.InputTag('slimmedPhotons'),
                              jets      = cms.InputTag('slimmedJets'),
                              fatjets   = cms.InputTag('slimmedJetsAK8'),
                              mets      = cms.InputTag('slimmedMets'),
)

process.p = cms.Path(process.demo)


