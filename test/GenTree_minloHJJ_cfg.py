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
          
    ## minloHJJ
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/C05CF28B-1A69-3C49-B637-A9775F6F5A29.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/20788841-E4F2-7B4E-920D-35F67881308A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/CF91D54C-BA0F-EC4A-B617-1F2FC4F6865D.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/F7FA0508-73AC-F644-98F3-0C0B75B9C8EB.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/A59C809B-1F71-CB42-9B0E-01172950A938.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/F82A1A26-EFC8-9548-866F-F76B21FEA0F9.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/07248673-7203-484F-91B3-C3D3385F5B72.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/150AE00D-BC79-7247-8505-9FECFDDA4E84.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/DB9C0D8D-E10E-BE42-87EF-376DE070DD2A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/3B0B0051-E8D7-3845-ADE1-E8C4BEFFE9C3.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/C6F2DBCB-2858-4C45-9BFC-9598452B84BE.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/D529D399-6E1F-3843-8F64-4BC42CBB3646.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/F87DCE7E-3257-AC48-ABBB-207B044BAE0E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/1AE71A89-0460-1C46-AA1D-BE5BA8EA72E8.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/E2563EF4-11C0-6D4B-9C26-F2C4E133F883.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/BE6553AB-5B97-314D-B908-19AC4E82FB8F.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/749DABBD-9618-7D49-877F-EA9B7B22887A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/613A9F19-3422-C140-852C-84677BC15FEF.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/989E94C9-D68B-9844-81A5-3B704145CF9E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/06247E90-EFB7-8F41-94A2-60BB811DB1D3.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/BA3A51F5-AF85-3E4B-B885-485C82159383.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/BCF68117-9F3A-7C47-97DC-F9D74CE1E960.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/CBD07616-75D5-7442-A2C0-9C9663207BCF.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/04429045-6E48-6E45-8D5C-B8E9C498A427.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/D4ED347C-901C-554F-9C32-32FB3086D995.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/94308A9C-188C-3641-8D03-1AE797500391.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/D8ABEE02-636C-3046-A29C-99C9623E1215.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/EE7BFD54-B4DC-EA4B-AF2A-FAA159DDC7D0.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/8609A7EE-BC32-EF4C-8DDD-19933FFC09BC.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/13249D62-BA0D-6741-9A9E-613A3D5592F1.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/351612B3-69C7-5C4A-B04D-55842DCDCD56.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/4B08EEE2-755C-B448-A48D-744A94953A19.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/2CC4C63D-07B4-2A48-8A6A-F0AA8CF8E2D2.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/8BDC7005-D70C-4644-AA24-7FD9A50045E5.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/6B099752-5E0C-564C-A32D-207A847A4EA4.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/43781D13-5793-F247-8978-B0A4BF97CF4E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/971F7A44-0281-AA42-A2F5-516106C38DF1.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/EFDF98C4-D180-BD4D-9A29-E0EE99AA9AC3.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/13341B82-11E4-7547-8F7B-2D6C1931E105.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/FDBF2AEC-DB88-2249-B9A4-E28A8D26773F.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/10EB9CEC-BF36-6A42-8853-7DE572DAC1EE.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/E0424821-F429-954D-819F-4A018665DB79.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/72451AF2-EA58-BE44-9B20-3282D4B721A0.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/675C615D-9650-534B-8A9E-A8BE0618F979.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/142AF13F-C2EB-D845-B5D5-FE45AE8E6A2E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/F67EB581-6B21-3846-B66C-517F0B261B4A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/EAB46EC2-2E83-534C-8A02-2151C51E6900.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/1C27DD35-2B12-864C-9639-4951B8C4D636.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/24C29A77-E916-B047-ABED-C0063DB283C4.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/9677D67F-E982-FC44-AC28-657E41AA6342.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/CDB34DC9-2DE6-4242-98A1-A9EBC9AAF475.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/C6D39670-77B9-DE40-9B94-8ED786EF4EED.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/A0F2ABED-1CAE-9249-8206-DA3959DECE61.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/6F1D7800-1A5E-DF42-AD72-45044A65981E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/F0B7A6F6-079C-CD4F-A91A-F40DD142A4D8.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/019ED9D9-6EAD-1B47-B75F-BB570CFD9245.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/24974263-7798-5043-A8A5-94D6DFB52CE3.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/703225D9-9A2A-5C45-ABA5-042B90D28813.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/A1621216-AC5A-5444-AFCF-7839BE61617A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/8D126010-B63B-7543-BCCE-05EC48FDC94D.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/EF68E9AD-7D69-754F-AF53-8BF6D9EDE779.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/B8869455-61FA-1142-AAAC-C2224729668D.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/6FB62816-3773-4347-8812-CED6A57B5B66.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/518325AE-065A-A747-8BC0-E0C7B191AF2A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/8F8D04C3-B5A9-8E4E-8AAA-3E3F75544587.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/244172CB-C64F-A640-9471-2E6FD9A1DA28.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/C039B824-A724-B441-B40E-D458D740DC9A.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/E16C3093-1BC0-1540-A70B-ADCE28A7C871.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/3207AD10-5E6A-FB4B-B3B4-7D222B8F4338.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/FC5AFA74-C99F-D647-B474-1B04AAA6DD63.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/CB24F1B0-553C-D042-ADE8-F549BCE2FC6E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/7EA4361A-B799-9841-B7CD-00D459534370.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/6F8FDA74-7B9A-BC40-8967-C54117BEC9C3.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/94D84750-8820-934E-A3DF-C1F9B14BE058.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/AAB9CA89-6DF1-4D47-B0EE-68CF7DAC42DC.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/694191AC-2C13-374A-B609-DF39631493FE.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/9C86C6CD-072D-214B-ABF7-9CF7140D857D.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/AEB64F99-EAD9-3F44-8561-57340608DF07.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/337E739A-AAC2-0D43-9B8F-271F0ACD1D7E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/875F86C2-7FDC-494D-9559-242AF4342E62.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/C3D308F4-7340-AF44-9E05-FDA70E14470B.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/359AD8DC-2A94-0146-A57F-EB5A5EA6E418.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/8EEFACC2-23CE-E245-9879-4B1E9017AD1E.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/645931E5-FD9E-D94E-AB2E-BB4741658C06.root',
        '/store/mc/RunIIAutumn18MiniAOD/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJJ_JHUGenV7011_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/88D0B8D4-149B-C845-9B55-CB6A28F65E60.root',
    )
)

# /GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_DownPS/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM


process.GenTree = cms.EDAnalyzer('GenTree',
    LHERunInfo = cms.InputTag('externalLHEProducer'),                                 
)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.rivetProducerHTXS = cms.EDProducer('HTXSRivetProducer',
  HepMCCollection = cms.InputTag('myGenerator','unsmeared'),
  LHERunInfo = cms.InputTag('externalLHEProducer'),
  ProductionMode = cms.string('GGF'),
  #ProductionMode = cms.string('AUTO'),
)

#MINIAOD
process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
    inputPruned = cms.InputTag("prunedGenParticles"),
    inputPacked = cms.InputTag("packedGenParticles"),
)
process.myGenerator = cms.EDProducer("GenParticles2HepMCConverter",
    genParticles = cms.InputTag("mergedGenParticles"),
    genEventInfo = cms.InputTag("generator"),
    signalParticlePdgIds = cms.vint32(25),
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
                                   fileName = cms.string("/eos/user/m/mbonanom/gentree_minloHJJ.root"), 
                                   closeFileFast = cms.untracked.bool(True),
                                   )


#process.o = cms.EndPath( process.out )


