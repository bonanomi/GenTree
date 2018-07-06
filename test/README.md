Instructions
====

See
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsTemplateCrossSection
    

Run

    cmsRun GenTree_cfg.py
    
    
    cmsRun GenTree_powheg_cfg.py
    cmsRun GenTree_powheg_nnlops_cfg.py
    cmsRun GenTree_amcatnlo_cfg.py

    cmsRun GenTree_powheg_nnlops_ATLAS_cfg.py
    cmsRun GenTree_powheg_nnlops_CMS_cfg.py
    cmsRun GenTree_powheg_nnlops_CMS_private_cfg.py

    
    r99t  gentree.root
    tree = (TTree*) _file0->Get("GenTree/gentree")
    tree->Draw("jets30")
    
    
Add uncertainties to the tree:

    cmsRun GenTree_powheg_nnlops_CMS_cfg.py

    addUncertainty  gentree_powheg_nnlops_cms_tune.root   gentree_powheg_nnlops_cms_tune_uncertainty.root     
    
    r99t gentree_powheg_nnlops_cms_tune_uncertainty.root Table.cxx

    
    r99t gentree_powheg_nnlops_cms_tune_uncertainty.root 
    tree = (TTree*) _file0->Get("GenTree/gentree")
    tree->Draw("stage1_cat_pTjet30GeV")
    
    
    
    
    
    
Draw

    r99t  gentree_powheg_nnlops_cms_tune.root  gentree_powheg_nnlops_cms_tune_private.root DrawComparison.cxx\(\"higgs_pt\",81,0,405,\"Higgs\ p_\{T\}\ \[GeV\]\"\)



    r99t  gentree_powheg_nnlops_cms_tune.root   DrawSingle.cxx\(\"higgs_pt\",40,0,200,\"Higgs\ p_\{T\}\ \[GeV\]\"\)
    
    r99t  gentree_powheg_nnlops_cms_tune.root   DrawSingle.cxx\(\"higgs_pt\",81,0,405,\"Higgs\ p_\{T\}\ \[GeV\]\"\)
    r99t  gentree_powheg_nnlops_atlas_tune.root DrawSingle.cxx\(\"higgs_pt\",81,0,405,\"Higgs\ p_\{T\}\ \[GeV\]\"\)

    r99t  gentree_powheg_nnlops_cms_tune.root  gentree_powheg_nnlops_atlas_tune.root DrawComparison.cxx\(\"higgs_pt\",81,0,405,\"Higgs\ p_\{T\}\ \[GeV\]\"\)

    
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx
    
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx\(\"jets30\",5,0,5,\"n\ jet\ 30\ GeV\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx\(\"higgs_pt\",20,0,200,\"Higgs\ p_\{T\}\ \[GeV\]\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx\(\"higgs_eta\",20,-6,6,\"Higgs\ #eta\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx\(\"jet1_pt\",20,0,200,\"jet1\ p_\{T\}\ \[GeV\]\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx\(\"higgs_pt\",26,0,260,\"Higgs\ p_\{T\}\ \[GeV\]\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx\(\"jets30\",5,0,5,\"n\ jet\ 30\ GeV\"\)
    

    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawNjetCorrected.cxx\(\"higgs_pt\",20,0,200,\"Higgs\ p_\{T\}\ \[GeV\]\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawNjetCorrected.cxx\(\"jets30\",5,0,5,\"n\ jet\ 30\ GeV\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawNjetCorrected.cxx\(\"higgs_eta\",20,-6,6,\"Higgs\ #eta\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawNjetCorrected.cxx\(\"jet1_pt\",20,0,200,\"jet1\ p_\{T\}\ \[GeV\]\"\)


    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawHpTCorrected.cxx\(\"higgs_pt\",20,0,200,\"Higgs\ p_\{T\}\ \[GeV\]\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawHpTCorrected.cxx\(\"jets30\",5,0,5,\"n\ jet\ 30\ GeV\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawHpTCorrected.cxx\(\"higgs_eta\",20,-6,6,\"Higgs\ #eta\"\)
    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    DrawHpTCorrected.cxx\(\"jet1_pt\",20,0,200,\"jet1\ p_\{T\}\ \[GeV\]\"\)
    
    
    
