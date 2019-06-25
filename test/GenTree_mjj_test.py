import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( 
      input = cms.untracked.int32(-1) 
      )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(

  '/store/mc/RunIISummer16MiniAODv3/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/04E5D347-2B3F-E911-B5F9-0CC47A7C345E.root',
    )
)


process.GenTree = cms.EDAnalyzer('GenTree',
  LHERunInfo = cms.InputTag('externalLHEProducer'),  
)




process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.rivetProducerHTXS = cms.EDProducer('HTXSRivetProducer',
  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
  LHERunInfo = cms.InputTag('externalLHEProducer'), 
  ProductionMode = cms.string('GGF'),
)

## MINIAOD
process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
    inputPruned = cms.InputTag("prunedGenParticles"),
    inputPacked = cms.InputTag("packedGenParticles"),
)

process.myGenerator = cms.EDProducer("GenParticles2HepMCConverter",
    genParticles = cms.InputTag("mergedGenParticles"),
    genEventInfo = cms.InputTag("generator"),
    signalParticlePdgIds = cms.vint32(25), ## for the Higgs analysis
)
process.p = cms.Path(process.mergedGenParticles * process.myGenerator * process.rivetProducerHTXS * process.GenTree)

process.TFileService = cms.Service("TFileService", 
                                   fileName = cms.string("/eos/user/m/mbonanom/gentree_mjj_test.root"), 
                                   closeFileFast = cms.untracked.bool(True),
                                   )


