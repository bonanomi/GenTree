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
  
  
  ggHUncertaintyNew uncertaintyHandler;
  
  // TFile* fileIn = TFile::Open(name_root_file_input.c_str(), "READ");
  // TTree* treeIn = (TTree*) fileIn -> Get ("ZZTree/candTree");
  
  // TFile* fileOut = TFile::Open(name_root_file_output.c_str(), "RECREATE");
  // fileOut->mkdir("ZZTree/");
  // fileOut->cd("ZZTree/");
  // TTree *treeOut = treeIn->CloneTree(0);
  
  // std::vector<float> allUnc;  
  // treeOut->Branch("allUnc", &allUnc);


  // Long64_t EventNumber;
  // Int_t htxsNJets;
  // Int_t htxs_stage1_cat;
  // float xsec;
  // float genxsec;

  // float htxsHPt;

  // float LHEweight_QCDscale_muR1_muF1;
  // float LHEweight_QCDscale_muR0p5_muF1;
  // float LHEweight_QCDscale_muR0p5_muF2;
  // float LHEweight_QCDscale_muR1_muF0p5;
  // float LHEweight_QCDscale_muR1_muF2;
  // float LHEweight_QCDscale_muR2_muF0p5;
  // float LHEweight_QCDscale_muR2_muF1;

  // treeIn->SetBranchAddress("EventNumber", &EventNumber);
  // treeIn->SetBranchAddress("htxsNJets",     &htxsNJets);
  // treeIn->SetBranchAddress("htxs_stage1_cat", &htxs_stage1_cat);
  // treeIn->SetBranchAddress("htxsHPt",   &htxsHPt);
  // treeIn->SetBranchAddress("xsec", &xsec);
  // treeIn->SetBranchAddress("genxsec", &genxsec);
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR1_muF1", &LHEweight_QCDscale_muR1_muF1);  
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR0p5_muF1", &LHEweight_QCDscale_muR0p5_muF1);  
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR0p5_muF2", &LHEweight_QCDscale_muR0p5_muF2);  
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR1_muF0p5", &LHEweight_QCDscale_muR1_muF0p5);  
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR1_muF2", &LHEweight_QCDscale_muR1_muF2);  
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR2_muF0p5", &LHEweight_QCDscale_muR2_muF0p5);  
  // treeIn->SetBranchAddress("LHEweight_QCDscale_muR2_muF1", &LHEweight_QCDscale_muR2_muF1);  

  // std::cout << " treeIn->GetEntries() = " << treeIn->GetEntries() << std::endl;

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
    allUnc = uncertaintyHandler.qcd_ggF_uncertSF_2017_New (jets30, higgs_pt, stage1_cat_pTjet30GeV);//htxsNJets, htxsHPt, htxs_stage1_cat);
    //allUnc = uncertaintyHandler.qcd_ggF_uncert_2017_New (jets30, higgs_pt, stage1_cat_pTjet30GeV);
    treeOut->Fill();

  }
  
    
  fileOut->Close();
  
  
  
}
