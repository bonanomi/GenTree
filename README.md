# GenTree


Instructions
====

See
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsTemplateCrossSection
    
Install:

    cmsrel CMSSW_8_0_19
    cd CMSSW_8_0_19/src
    cmsenv
    // Retrieve the HTXS package and compile
    git cms-merge-topic -u perrozzi:HTXS_clean
    
    cd GeneratorInterface
    
    git clone git@github.com:amassiro/GenTree.git
    
    cd ..
    
    scramv1 b -j 10
    
    

