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

  float c_pt_H_boundaries[] = {10, 60, 120, 200};
  std::vector<float> pt_H_boundaries (c_pt_H_boundaries, c_pt_H_boundaries + sizeof(c_pt_H_boundaries) / sizeof(float) );
  
  float c_njet_boundaries[] = {1, 2, 3};
  std::vector<float> njet_boundaries (c_njet_boundaries, c_njet_boundaries + sizeof(c_njet_boundaries) / sizeof(float) );
  
  TString toWeightGlobal;
  toWeightGlobal = Form ("(LHEweight_QCDscale_muR1_muF1) * ( ( LHEweight_QCDscale_muR0p5_muF0p5 * (abs(LHEweight_QCDscale_muR0p5_muF0p5/LHEweight_QCDscale_muR1_muF1)<100)) + 0 * (abs(LHEweight_QCDscale_muR0p5_muF0p5/LHEweight_QCDscale_muR1_muF1)>100)  )");
  
  
  std::map< std::pair<int, int> , std::vector< float> > list_variation;
  
  std::map< std::pair<int, int> , float > max_up;
  std::map< std::pair<int, int> , float > max_do;
  
  std::map< std::pair<int, int> , float > nominal;
  
  
  TTree* tree1 = (TTree*) _file0->Get("ZZTree/candTree");  
  
  
  TH1F* histo_support = new TH1F ("histo_support", "", 1, 0, 2);  
  TString toWeight;
  TString toCut;
  
  float global_integral;
  tree1->Draw("1 >> histo_support", toWeightGlobal.Data() , "goff" );   
  global_integral = histo_support->Integral(0,histo_support->GetNbinsX()+1);
  
  
  for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
    for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
      
      toCut = Form ("%s", toWeightGlobal.Data());
      
      //---- overflow pt_H
      if (i_pt_H != pt_H_boundaries.size()) {      
        toCut = Form ("%s * (htxsHPt<%f) ", toCut.Data(), pt_H_boundaries.at(i_pt_H) );
      }
      
      //---- overflow njet
      if (i_njet != njet_boundaries.size()) {      
        toCut = Form ("%s * (htxsNJets<%f)", toCut.Data(), njet_boundaries.at(i_njet) );
      }
      
      if (i_pt_H != 0) {
        toCut = Form ("%s * (htxsHPt>=%f)", toCut.Data(), pt_H_boundaries.at(i_pt_H-1));
      }
      if (i_njet != 0) {
        toCut = Form ("%s * (htxsNJets>=%f)", toCut.Data(), njet_boundaries.at(i_njet-1));
      }
      
      std::cout << " i_pt_H:i_njet " << i_pt_H << " , " << i_njet << " -->  cut = " << toCut.Data() << std::endl;
      
      tree1->Draw("1 >> histo_support", toCut.Data() , "goff" );   
      nominal[std::pair<int, int> (i_pt_H, i_njet)] = histo_support->Integral(0,histo_support->GetNbinsX()+1);
      
      max_up[std::pair<int, int> (i_pt_H, i_njet)] = nominal[std::pair<int, int> (i_pt_H, i_njet)];
      max_do[std::pair<int, int> (i_pt_H, i_njet)] = nominal[std::pair<int, int> (i_pt_H, i_njet)];
      

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
      list_variation[std::pair<int, int> (i_pt_H, i_njet)] = many_values;
      
    }
  }
  
  
  ofstream myfile;
  myfile.open ("scale_variations.txt");
  
  for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
      myfile << i_njet << "  " << i_pt_H << "  ";
      myfile << nominal[std::pair<int, int> (i_pt_H, i_njet)] << "   ";   
      for (int i=0; i<6; i++) {
        myfile << list_variation[std::pair<int, int> (i_pt_H, i_njet)][i] << "   ";
      }
      myfile << std::endl;
    }
  }
    
  myfile.close(); 
 
  
}