Instructions
====

See
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsTemplateCrossSection
    

Run

    cmsRun GenTree_cfg.py
    
    
    r99t  gentree.root
    tree = (TTree*) _file0->Get("GenTree/gentree")
    tree->Draw("jets30")
    
    
Draw

    r99t   gentree_powheg.root  gentree_powheg_nnlops.root   gentree_amcatnlo.root    Draw.cxx
    
    