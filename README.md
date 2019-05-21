# GenTree
## Fork from A. Massironi's repo [GenTree](https://github.com/amassiro/GenTree).

Instructions
====

See
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsTemplateCrossSection
    
Install:

    cmsrel CMSSW_10_3_1
    cd CMSSW_10_3_1/src
    cmsenv
    
    // To work with the CJLST framework, follow:
    // [this link](https://github.com/CJLST/ZZAnalysis#zzanalysis) to install it.
    

    // Retrieve the HTXS package and compile
    // Already implemented in CMSSW > 8.X
    // Merge not necessary, everything should work
    // git cms-merge-topic -u perrozzi:HTXS_clean
    
    cd GeneratorInterface
    
    git clone https://github.com/bonanomi/GenTree.git
    
    cd ..
    
    scramv1 b -j 10 
    
