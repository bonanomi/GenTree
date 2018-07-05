//---- std include ----
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream> 


#include "GeneratorInterface/GenTree/interface/ggHUncertainty.h"

#include "TFile.h"
#include "TTree.h"


int main(int argc, char** argv) {
  
  std::cout << "Add uncertainty to tree " << std::endl;
  
  std::string name_root_file_input  = (argv[1]) ; 
  std::string name_root_file_output = (argv[2]) ; 
  
  std::cout << " input  = " << name_root_file_input  << std::endl;
  std::cout << " output = " << name_root_file_output << std::endl;
  
  
  ggHUncertainty uncertaintyHandler;
  
  TFile* fileIn = new TFile (name_root_file_input.c_str(), "READ");
  TTree* treeIn = (TTree*) fileIn -> Get ("Tree");
  
  TFile* fileOut = new TFile (name_root_file_output.c_str(), "RECREATE");
  TTree *treeOut = treeIn->CloneTree(0);
  
  std::vector<float> allUnc;
  
  treeOut->Branch("allUnc", &allUnc);
  
  
  for (Long64_t iEntry = 0; iEntry<treeIn->GetEntries(); iEntry++) {
    
    treeIn->GetEntry(iEntry);
    
    int Njets30 = 2;
    float HTXS_ptHiggs = 30.;
    float HTXS_stage1_pTjet30GeV = 3;
    
    allUnc.clear();    
    allUnc = uncertaintyHandler.qcd_ggF_uncertSF_2017 (int(Njets30), HTXS_ptHiggs, int(HTXS_stage1_pTjet30GeV));
    treeIn->GetEntry(iEntry);
    
    treeOut->Fill();

    //   for (unsigned int i=0; i<allUnc.size(); i++) {
    //     
    //     std::cout << " [" << i << "] = " << allUnc.at(i) << std::endl;
    //     
    //   }
    //   
    
  }
  
  
  
  /*
  //  cond::CondDBDumper<EcalPulseShapes> PulseShapeGeneration("EcalPulseShapes_hlt");
  //  PulseShapeGeneration.run(argc, argv);
  
  
  //  cond::CondDBDumper<EcalPulseShapes> PulseShapeFit("EcalPulseShapes_hlt");
  //  PulseShapeFit.run(argc, argv);
  
  
  std::string name_tag = (argv[1]) ; //---- EcalPulseShapes_Legacy2016_v2
  
  int simulate     (atoi(argv[2])) ;
  int fit          (atoi(argv[3])) ;
  
  
  
  //                                                                                                          simulate    fit
  //  cond::CondDBDumper<EcalPulseShapes> PulseShapeGenerationAndFit("EcalPulseShapes_hlt", "EcalPulseShapes_hlt",  1      ,    2);
  //  cond::CondDBDumper<EcalPulseShapes> PulseShapeGenerationAndFit("EcalPulseShapes_hlt", "EcalPulseShapes_hlt",  simulate      ,    fit);
  
  //  cond::CondDBDumper<EcalPulseShapes> PulseShapeGenerationAndFit("EcalPulseShapes_October2017_rereco_v3", "EcalPulseShapes_October2017_rereco_v3",  simulate      ,    fit);
  cond::CondDBDumper<EcalPulseShapes> PulseShapeGenerationAndFit(name_tag.c_str(), name_tag.c_str(),  simulate      ,    fit);
  
  
  int argc2 = argc-3;
  char** argv2 = argv; 
  PulseShapeGenerationAndFit.run(argc2, argv2);
  
  std::cout << " done " << std::endl;
  
  //---- generate according to PulseShapeGeneration and fit using PulseShapeFit
  
  //---- generate
  
  
  //---- fit */
  
  
  
  
  
}