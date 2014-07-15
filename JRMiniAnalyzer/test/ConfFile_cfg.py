import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
   #    'file:patTuple_mini_singlemu.root'
       'file:TT_Tune4C_13TeV-pythia8-tauola_PU_S14_PAT.root'

    )
)

process.demo = cms.EDAnalyzer('JRMiniAnalyzer',
                              CollectionTag = cms.InputTag('slimmedMuons')
)


process.p = cms.Path(process.demo)


