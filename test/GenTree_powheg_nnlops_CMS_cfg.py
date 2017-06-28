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
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_1.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_2.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_3.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_4.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_5.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_6.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_7.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_8.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_9.root',
        '/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_10.root',       
    )
)

# /GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_DownPS/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM


process.GenTree = cms.EDAnalyzer('GenTree'
)




process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.rivetProducerHTXS = cms.EDProducer('HTXSRivetProducer',
  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
  LHERunInfo = cms.InputTag('externalLHEProducer'),
  #ProductionMode = cms.string('GGF'),
  ProductionMode = cms.string('AUTO'),
)

## MINIAOD
#process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
    #inputPruned = cms.InputTag("prunedGenParticles"),
    #inputPacked = cms.InputTag("packedGenParticles"),
#)
#process.myGenerator = cms.EDProducer("GenParticles2HepMCConverterHTXS",
    #genParticles = cms.InputTag("mergedGenParticles"),
    #genEventInfo = cms.InputTag("generator"),
#)
#process.p = cms.Path(process.mergedGenParticles * process.myGenerator * process.rivetProducerHTXS * process.GenTree)

# # AOD
process.myGenerator = cms.EDProducer("GenParticles2HepMCConverterHTXS",
   genParticles = cms.InputTag("genParticles"),
   genEventInfo = cms.InputTag("generator"),
)
process.p = cms.Path(process.myGenerator * process.rivetProducerHTXS * process.GenTree)

#process.out = cms.OutputModule("PoolOutputModule",
    #outputCommands = cms.untracked.vstring('drop *','keep *_*_*_runRivetAnalysis','keep *_generator_*_*','keep *_externalLHEProducer_*_*'),
    #fileName = cms.untracked.string('testHTXSRivet_ggH4l_MINIAOD_100k.root')
#)

process.TFileService = cms.Service("TFileService", 
                                   #fileName = cms.string("gentree_powheg.root"), 
                                   fileName = cms.string("gentree_powheg_nnlops_cms_tune.root"), 
                                   #fileName = cms.string("gentree_amcatnlo.root"), 
                                   closeFileFast = cms.untracked.bool(True),
                                   )


#process.o = cms.EndPath( process.out )


