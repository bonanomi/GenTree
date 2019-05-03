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
#include "GeneratorInterface/GenTree/interface/ggHUncertaintyNew.h"

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
  TTree* treeIn = (TTree*) fileIn -> Get ("GenTree/gentree");
  
  TFile* fileOut = new TFile (name_root_file_output.c_str(), "RECREATE");
  fileOut->mkdir("GenTree/");
  fileOut->cd("GenTree/");
  TTree *treeOut = treeIn->CloneTree(0);
  
  std::vector<float> allUnc;  
  treeOut->Branch("allUnc", &allUnc);

  UInt_t jets30;
  UInt_t stage0_cat;
  UInt_t stage1_cat_pTjet30GeV;
  float weight;
  
  float higgs_pt;
  float higgs_eta;
  
  float jet1_pt;
  float jet1_eta;
  
  
  treeIn->SetBranchAddress("jets30",     &jets30);
  treeIn->SetBranchAddress("stage0_cat", &stage0_cat);
  treeIn->SetBranchAddress("stage1_cat_pTjet30GeV", &stage1_cat_pTjet30GeV);
  treeIn->SetBranchAddress("weight",     &weight);
  treeIn->SetBranchAddress("higgs_pt",   &higgs_pt);
  treeIn->SetBranchAddress("higgs_eta",  &higgs_eta);
  treeIn->SetBranchAddress("jet1_pt",    &jet1_pt);
  treeIn->SetBranchAddress("jet1_eta",   &jet1_eta);
  
  std::cout << " treeIn->GetEntries() = " << treeIn->GetEntries() << std::endl;
  
  for (Long64_t iEntry = 0; iEntry<treeIn->GetEntries(); iEntry++) {
    
    if (!(iEntry%20000)) std::cout << " [" << iEntry << "]" << std::endl;
    
    treeIn->GetEntry(iEntry);
    
    allUnc.clear();    
    allUnc = uncertaintyHandler.qcd_ggF_uncertSF_2017 (jets30, higgs_pt, stage1_cat_pTjet30GeV);
    
    treeOut->Fill();

  }
  
    
  fileOut->Close();
  
  
  
}