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
        
        #https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=file+dataset%3D%2FGluGluHToGG_M125_13TeV_amcatnloFXFX_pythia*%2FRunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1%2FMINIAODSIM
        #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_CUETP8M1Up/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/4E294805-A8E6-E611-8081-001E67792736.root',
        #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_CUETP8M1Up/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/5CEA9B05-A8E6-E611-9B3B-001E677926F8.root',
        #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_CUETP8M1Up/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/CC1F7D4B-C7E6-E611-B1BC-001E67792658.root',
        #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_CUETP8M1Up/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/ECBCF232-B2E6-E611-B6AB-002590A371AC.root',

# https://cmsweb.cern.ch/das/request?view=list&limit=150&instance=prod%2Fglobal&input=file+dataset%3D%2FGluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8%2FRunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1%2FMINIAODSIM
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/04FEC0D8-A1C0-E611-8D40-0CC47A546E5E.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/085207D1-88C0-E611-BB51-001E67E6F7D3.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/3897472F-84C0-E611-AF4D-0090FAA579F0.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/5E7399E0-A1C0-E611-9127-008CFA197DF8.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/9CCD31B7-81C0-E611-BDEE-001E67396AC2.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/9E80D0D4-A1C0-E611-9202-A0000420FE80.root',
        '/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/120000/A4675190-A0C0-E611-946C-02163E011F16.root',
         
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


