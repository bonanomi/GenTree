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
        #'/store/mc/RunIISpring16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/10000/2C7F3153-393B-E611-9323-0CC47AA98A3A.root',
        #'/store/mc/RunIISummer16MiniAODv2/HJ_MiNLO_NNLOPS_HToWWTo2L2Nu_M125_NNPDF30_13TeV_JHUGen702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/70000/148787A1-36DB-E611-88CC-0CC47A4D7630.root',  ===> HWW
        #'/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/100000/181CC30D-16DE-E611-93D8-FA163E5DBAC6.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_DownPS/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/100000/2817C1CE-CCE9-E611-BC09-0025904B2294.root',
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

#MINIAOD
process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
    inputPruned = cms.InputTag("prunedGenParticles"),
    inputPacked = cms.InputTag("packedGenParticles"),
)
process.myGenerator = cms.EDProducer("GenParticles2HepMCConverterHTXS",
    genParticles = cms.InputTag("mergedGenParticles"),
    genEventInfo = cms.InputTag("generator"),
)
process.p = cms.Path(process.mergedGenParticles * process.myGenerator * process.rivetProducerHTXS * process.GenTree)

# # AOD
#process.myGenerator = cms.EDProducer("GenParticles2HepMCConverterHTXS",
#    genParticles = cms.InputTag("genParticles"),
#    genEventInfo = cms.InputTag("generator"),
#)
#process.p = cms.Path(process.myGenerator*process.rivetProducerHTXS)

#process.out = cms.OutputModule("PoolOutputModule",
    #outputCommands = cms.untracked.vstring('drop *','keep *_*_*_runRivetAnalysis','keep *_generator_*_*','keep *_externalLHEProducer_*_*'),
    #fileName = cms.untracked.string('testHTXSRivet_ggH4l_MINIAOD_100k.root')
#)

process.TFileService = cms.Service("TFileService", 
                                   #fileName = cms.string("gentree_powheg.root"), 
                                   #fileName = cms.string("gentree_powheg_nnlops.root"), 
                                   fileName = cms.string("gentree_amcatnlo.root"), 
                                   closeFileFast = cms.untracked.bool(True),
                                   )


#process.o = cms.EndPath( process.out )


