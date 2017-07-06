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
      #https://cmsweb.cern.ch/das/request?view=list&instance=prod%2Fglobal&input=file+dataset%3D%2FGluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8%2FRunIISummer16MiniAOD*%2FMINIAODSIM
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/00C2BA0D-54C0-E611-A7E9-001E67E6F7D3.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/02946258-56C0-E611-BAFD-848F69FD2484.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/08C42F39-63C0-E611-96D7-00259073E3FC.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/327DEBF1-7EC0-E611-ACF2-0CC47A5FBE25.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/30540FAC-85C0-E611-8347-00269E95B128.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/B82B2ECE-9EC0-E611-991E-008CFAFC043A.root',
    )
)

# /GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_DownPS/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM


process.GenTree = cms.EDAnalyzer('GenTree'
    LHERunInfo = cms.InputTag('externalLHEProducer'),                                 
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
                                   fileName = cms.string("gentree_powheg.root"), 
                                   #fileName = cms.string("gentree_powheg_nnlops.root"), 
                                   #fileName = cms.string("gentree_amcatnlo.root"), 
                                   closeFileFast = cms.untracked.bool(True),
                                   )


#process.o = cms.EndPath( process.out )


