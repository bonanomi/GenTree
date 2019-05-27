// 
// Stage 1.0  - 1.1
//    STXS
// 
// 

#include <iostream>
#include <fstream>

void CalculateScaleVariation() {

  std::vector< std::string > weights;
  weights.push_back("LHEweight_QCDscale_muR1_muF1"); //0
  weights.push_back("LHEweight_QCDscale_muR1_muF2"); //1
  weights.push_back("LHEweight_QCDscale_muR1_muF0p5"); //2
  weights.push_back("LHEweight_QCDscale_muR2_muF1"); //3
  weights.push_back("LHEweight_QCDscale_muR2_muF2"); //4
  weights.push_back("LHEweight_QCDscale_muR2_muF0p5"); //5
  weights.push_back("LHEweight_QCDscale_muR0p5_muF1"); //6
  weights.push_back("LHEweight_QCDscale_muR0p5_muF2"); //7
  weights.push_back("LHEweight_QCDscale_muR0p5_muF0p5"); //8

  // Apparently this was needed because of a problem with minlo NNLOPS
  // It should be checked whether now weights are fine or still >>1 in some cases.
  TString toWeightGlobal;
  toWeightGlobal = Form ("(LHEweight_QCDscale_muR1_muF1) * ( ( LHEweight_QCDscale_muR0p5_muF0p5 * (abs(LHEweight_QCDscale_muR0p5_muF0p5/LHEweight_QCDscale_muR1_muF1)<100)) + 0 * (abs(LHEweight_QCDscale_muR0p5_muF0p5/LHEweight_QCDscale_muR1_muF1)>100)  )");
  
  
  std::map< int , std::vector< float> > list_variation;
  
  std::map< int , float > max_up;
  std::map< int , float > max_do;
  
  std::map< int , float > nominal;
  
  
  TTree* tree1 = (TTree*) _file0->Get("ZZTree/candTree");  
  
  
  TH1F* histo_support = new TH1F ("histo_support", "", 1, 0, 2);  
  TString toWeight;
  TString toCut;
  
  float global_integral;
  tree1->Draw("1 >> histo_support", toWeightGlobal.Data() , "goff" );   
  global_integral = histo_support->Integral(0,histo_support->GetNbinsX()+1);
  
  /************************************************************************************************************************
   ********************************************  STXS STAGE 1.1 BINS  *****************************************************
  
      GG2H_FWDH = 100,
      GG2H_VBFTOPO_JET3VETO = 101, GG2H_VBFTOPO_JET3 = 102,
      GG2H_0J   = 103,
      GG2H_1J_PTH_0_60 = 104,      GG2H_1J_PTH_60_120 = 105, GG2H_1J_PTH_120_200 = 106,   GG2H_1J_PTH_GT200 = 107,
      GG2H_GE2J_PTH_0_60 = 108,      GG2H_GE2J_PTH_60_120 = 109, GG2H_GE2J_PTH_120_200 = 110,   GG2H_GE2J_PTH_GT200 = 111,

   ************************************************************************************************************************
  *************************************************************************************************************************/
  std::vector< std::string > stxs1p1_cuts;
  stxs1p1_cuts.push_back("100");
  stxs1p1_cuts.push_back("101");
  stxs1p1_cuts.push_back("102");
  stxs1p1_cuts.push_back("103");
  stxs1p1_cuts.push_back("104");
  stxs1p1_cuts.push_back("105");
  stxs1p1_cuts.push_back("106");
  stxs1p1_cuts.push_back("107");
  stxs1p1_cuts.push_back("108");
  stxs1p1_cuts.push_back("109");
  stxs1p1_cuts.push_back("110");
  stxs1p1_cuts.push_back("111");

  for (iCut = 0; iCut < stxs1p1_cuts.size() + 1; iCut++) {
    toCut = Form ("%s", toWeightGlobal.Data());
    toCut = Form ("%s * (htxs_stage1_cat==%s) ", toCut.Data(), stxs1p1_cuts.at(iCut).c_str() );
    std::cout << " STXS1p1 cat " << stxs1p1_cuts.at(iCut).c_str() << " -->  cut = " << toCut.Data() << std::endl;

    tree1->Draw("1 >> histo_support", toCut.Data() , "goff" );   
    nominal[std::stoi(stxs1p1_cuts.at(iCut))] = histo_support->Integral(0,histo_support->GetNbinsX()+1);
    
    max_up[std::stoi(stxs1p1_cuts.at(iCut))] = nominal[std::stoi(stxs1p1_cuts.at(iCut))];
    max_do[std::stoi(stxs1p1_cuts.at(iCut))] = nominal[std::stoi(stxs1p1_cuts.at(iCut))];

    std::vector <float> many_values;
    for (int i=1; i<9; i++) {
      if (i != 5 && i != 7) {
        toWeight = Form ("%s * (%s)/(LHEweight_QCDscale_muR1_muF1)", toCut.Data(), weights.at(i).c_str());  
        tree1->Draw("1 >> histo_support", toWeight.Data() , "goff" );   
        float value = histo_support->Integral(0,histo_support->GetNbinsX()+1);
//           if (value > max_up[std::pair<int, int> (i_pt_H, i_njet)]) max_up[std::pair<int, int> (i_pt_H, i_njet)] = value;
//           if (value < max_do[std::pair<int, int> (i_pt_H, i_njet)]) max_do[std::pair<int, int> (i_pt_H, i_njet)] = value;         
        many_values.push_back(value);
      }      
    }
    list_variation[std::stoi(stxs1p1_cuts.at(iCut))] = many_values;
  }    

  
  
  ofstream myfile;
  myfile.open ("scale_variations.txt");

  for (iCut = 0; iCut < stxs1p1_cuts.size() + 1; iCut++) {
    myfile << stxs1p1_cuts.at(iCut).c_str() << "  ";
    myfile << nominal[std::stoi(stxs1p1_cuts.at(iCut))] << "   ";   
    for (int i=0; i<6; i++) {
      myfile << list_variation[std::stoi(stxs1p1_cuts.at(iCut))][i] << "   ";
    }
    myfile << std::endl;
  }
    
  myfile.close(); 
 
  
}