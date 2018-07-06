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

#
# Private files from David Sperka
#
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_1.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_2.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_3.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_4.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_5.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_6.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_7.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_8.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_9.root',
        #'/store/user/dsperka/Run2MC/NNLOPS_HJ_ZZ4L_nnloPdf_13TeV_GEN/HJ_NNLOPS_14TeV_GEN_10.root',       


#/GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_minloHJJ_JHUGenV702_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v5/MINIAODSIM
#/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM


         '/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/16B2B949-9380-E711-93E7-484D7E8DF114.root',
         '/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/2A9C6E5C-2880-E711-AEB0-001E6779244C.root',
         '/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/584A7AB8-177F-E711-8FB1-10983627C3CE.root',
         '/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/6C007993-DC7F-E711-9796-008CFAF558EE.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/768BB960-7B7F-E711-AC13-FA163E457330.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/7C7E3BF4-D57F-E711-B4C5-0026B94DBE31.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/807206C8-D57F-E711-9BEC-FA163E89B73C.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/882146D9-6380-E711-9FA8-0025901D4446.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/A0D91FDF-697F-E711-B89A-00266CFFCC54.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/AE3C9B48-C181-E711-874F-FA163E21693B.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/BEE742FE-C181-E711-B7CB-FA163E3C0AC5.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/C4429D29-0E81-E711-93A6-0025904B9B3E.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/E82C153E-F27F-E711-B20A-7CD30AD09316.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/EAFC7D28-6D80-E711-A974-FA163EDEB37D.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/FAF67187-987F-E711-B464-C45444922991.root',



#
# Official CMSSW files
#
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/1AB054CF-E060-E711-99B9-008CFA110AD0.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/B8E0046F-7B61-E711-9F93-A0369FC5B85C.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/C0B7F1B6-9461-E711-A55D-549F35AD8B6E.root',
         #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/C8C3D40A-B361-E711-B3A8-549F35AE4FFD.root',



         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/40E3BF3D-CD5F-E711-9B8C-0242AC110003.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/48FFCEDA-D95F-E711-AD1C-28924A33AFD2.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/4AB217E0-CC5F-E711-BD98-3417EBE47C5E.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/50830291-DC5F-E711-A113-0242AC110009.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/581CC618-D25F-E711-BED1-0242AC1C0501.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/58EAF332-CB5F-E711-B0D0-BC305B390A59.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/66E2A172-D75F-E711-898D-BC305B390A4C.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/6AD77008-D45F-E711-BA9B-BC305B390A32.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/70F49009-D65F-E711-944F-0242AC11000A.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/8005C79F-D95F-E711-ABC0-0242AC110003.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/849CCF91-DA5F-E711-8CE6-0242AC110003.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/84CEEE46-D95F-E711-820E-0242AC110006.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/864442F7-C65F-E711-84CC-0026B92785E9.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/864CBC30-CF5F-E711-AB2C-0026B9278692.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/88C8F657-D65F-E711-8746-28924A33BBAA.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/8C180CB0-CE5F-E711-B65B-0242AC110005.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/9467C342-CE5F-E711-9CDB-A0B3CCDFB624.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/98B3EC8E-D15F-E711-BEAF-28924A33AFD2.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/9C0EC458-E05F-E711-A04C-0242AC1C0500.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/A2E78519-D95F-E711-A3BE-0242AC110002.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/AC8E29F7-CE5F-E711-AA20-0242AC110005.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/ACF37CCA-E35F-E711-A923-0242AC110006.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/AE11C0E4-CF5F-E711-B5D2-0242AC11000A.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/BEFB1F41-E75F-E711-ADBA-0242AC1C0500.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/C49BE6BC-E55F-E711-A80F-0242AC110012.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/C8BB6633-D05F-E711-AC24-0242AC110002.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/CC102417-CC5F-E711-875D-BC305B390A59.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/CCF8422C-CE5F-E711-A1CA-0242AC110003.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/D0E0A986-D05F-E711-8B02-0242AC110009.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/D2B622B5-D35F-E711-AE19-0242AC110013.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/D853E69A-D25F-E711-9742-0242AC110005.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/DECD0CFF-D65F-E711-B28D-0242AC110012.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/E4A10DCA-D15F-E711-9432-0242AC1C0500.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/E4C883D3-DA5F-E711-8656-0242AC110004.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/E4DBB6C7-D25F-E711-AACE-0026B9278692.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/F46AD49A-CF5F-E711-8245-0242AC110005.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/F83022BB-D85F-E711-9E49-0242AC110004.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/FC4874E0-D65F-E711-9B61-28924A35056A.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/023628B5-E75F-E711-91B9-009C02AAB484.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/049E2B35-CD5F-E711-B533-28924A33B9FE.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/08488821-DB5F-E711-A3A5-0242AC110003.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/10453139-D95F-E711-A4CF-28924A33AFC2.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/121390E1-D45F-E711-B7C7-0242AC110002.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/16F26F0D-DC5F-E711-927E-0242AC110003.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/1E0861EA-C75F-E711-A332-0026B92785E9.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/2298F43B-DB5F-E711-9D00-28924A33AFF6.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/3036C8FA-D85F-E711-8B6D-BC305B390A4C.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/30BC14D1-D05F-E711-9E7F-0242AC1C0501.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/388EEC20-D45F-E711-B8C9-0242AC110002.root',
         #'/store/mc/RunIISummer15GS/GluGluHToGG_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/GEN-SIM/MCRUN2_71_V1-v1/50000/3A6B7089-D15F-E711-8812-0242AC110009.root',

    )
)

# /GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_DownPS/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM


process.GenTree = cms.EDAnalyzer('GenTree',
    LHERunInfo = cms.InputTag('source'),    # ---> for central production
  #LHERunInfo = cms.InputTag('externalLHEProducer'),   ---> for private production
)




process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.rivetProducerHTXS = cms.EDProducer('HTXSRivetProducer',
  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
  LHERunInfo = cms.InputTag('source'),    # ---> for central production
  #LHERunInfo = cms.InputTag('externalLHEProducer'),   ---> for private production
  ProductionMode = cms.string('GGF'), # --> otherwise it will not work for MINLO !!!
  #ProductionMode = cms.string('AUTO'),
)

## MINIAOD
process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
    inputPruned = cms.InputTag("prunedGenParticles"),
    inputPacked = cms.InputTag("packedGenParticles"),
)
process.myGenerator = cms.EDProducer("GenParticles2HepMCConverterHTXS",
    genParticles = cms.InputTag("mergedGenParticles"),
    genEventInfo = cms.InputTag("generator"),
)
process.p = cms.Path(process.mergedGenParticles * process.myGenerator * process.rivetProducerHTXS * process.GenTree)

## # AOD
#process.myGenerator = cms.EDProducer("GenParticles2HepMCConverterHTXS",
   #genParticles = cms.InputTag("genParticles"),
   #genEventInfo = cms.InputTag("generator"),
#)
#process.p = cms.Path(process.myGenerator * process.rivetProducerHTXS * process.GenTree)

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


