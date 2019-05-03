// 
// Stage 1.0  - 1.1
//    STXS
// 
// 

#include <iostream>
#include <fstream>

void CalculateScaleVariation() {
  
  float c_pt_H_boundaries[] = {10, 60, 120, 200};
  std::vector<float> pt_H_boundaries (c_pt_H_boundaries, c_pt_H_boundaries + sizeof(c_pt_H_boundaries) / sizeof(float) );
  
  float c_njet_boundaries[] = {1, 2, 3};
  std::vector<float> njet_boundaries (c_njet_boundaries, c_njet_boundaries + sizeof(c_njet_boundaries) / sizeof(float) );
  
  TString toWeightGlobal;
  toWeightGlobal = Form ("(weights_LHE[0]) * ( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )");
  
  
  std::map< std::pair<int, int> , std::vector< float> > list_variation;
  
  std::map< std::pair<int, int> , float > max_up;
  std::map< std::pair<int, int> , float > max_do;
  
  std::map< std::pair<int, int> , float > nominal;
  
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  
  
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
        toCut = Form ("%s * (higgs_pt<%f) ", toCut.Data(), pt_H_boundaries.at(i_pt_H) );
      }
      
      //---- overflow njet
      if (i_njet != njet_boundaries.size()) {      
        toCut = Form ("%s * (jets30<%f)", toCut.Data(), njet_boundaries.at(i_njet) );
      }
      
      if (i_pt_H != 0) {
        toCut = Form ("%s * (higgs_pt>=%f)", toCut.Data(), pt_H_boundaries.at(i_pt_H-1));
      }
      if (i_njet != 0) {
        toCut = Form ("%s * (jets30>=%f)", toCut.Data(), njet_boundaries.at(i_njet-1));
      }
      
      std::cout << " i_pt_H:i_njet " << i_pt_H << " , " << i_njet << " -->  cut = " << toCut.Data() << std::endl;
      
      tree1->Draw("1 >> histo_support", toCut.Data() , "goff" );   
      nominal[std::pair<int, int> (i_pt_H, i_njet)] = histo_support->Integral(0,histo_support->GetNbinsX()+1);
      
      max_up[std::pair<int, int> (i_pt_H, i_njet)] = nominal[std::pair<int, int> (i_pt_H, i_njet)];
      max_do[std::pair<int, int> (i_pt_H, i_njet)] = nominal[std::pair<int, int> (i_pt_H, i_njet)];
      

      std::vector <float> many_values;
      for (int i=1; i<9; i++) {
        if (i != 5 && i != 7) {
          toWeight = Form ("%s * (weights_LHE[%d])/(weights_LHE[0])", toCut.Data(), i);  
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
  myfile.open ("values.txt");
  
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
  
  
  
  
  
  /*
  //---- now print
  
//   std::cout << " ===================== " << std::endl;
//   std::cout << " ===================== " << std::endl;
//   std::cout << " ===================== " << std::endl;
//   
//   for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
//     
//     for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
//       
//       //       std::cout << " pt:njet (<, <) = " << nominal[std::pair<int, int> (i_pt_H, i_njet)] << std::endl;
//       float value = nominal[std::pair<int, int> (i_pt_H, i_njet)];
//       if (value != 0) {
//         std::cout << " pt:njet (<, <) : " << value / global_integral << " ===> " << (max_do[std::pair<int, int> (i_pt_H, i_njet)]-value) / value * 100. << " :: " << (max_up[std::pair<int, int> (i_pt_H, i_njet)]-value) / value * 100. << std::endl;
//       }
//       else {
//         std::cout << " pt:njet (<, <) : " << value / global_integral << std::endl;
//       }
//       
//     }
//   }
  
  
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  
  
  //---- setup the max/min variation, after normalizing per jet bin 
  //---- for every variation considered
  
  for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
    
    float total_i_njet = 0;
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
      total_i_njet += nominal[std::pair<int, int> (i_pt_H, i_njet)];
    }
    
    for (int i=0; i<6; i++) {
      
      float total_var_i_njet = 0;
      for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
        total_var_i_njet += list_variation[std::pair<int, int> (i_pt_H, i_njet)] [i];
      }
      
      for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
        list_variation[std::pair<int, int> (i_pt_H, i_njet)] [i]  *=  (total_i_njet/total_var_i_njet);
      }
      
    }
    
  }
  
  
  for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
    
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
      for (int i=0; i<6; i++) {
        
        float value = list_variation[std::pair<int, int> (i_pt_H, i_njet)] [i];
        
        // max_up/do have been initialized to nominal at the beginning
        if (value > max_up[std::pair<int, int> (i_pt_H, i_njet)]) max_up[std::pair<int, int> (i_pt_H, i_njet)] = value;
        if (value < max_do[std::pair<int, int> (i_pt_H, i_njet)]) max_do[std::pair<int, int> (i_pt_H, i_njet)] = value;
        
      }
    }
  }
  
  
    
  //---- now really print
  
  for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
    
    float total_i_njet = 0;
    float total_up_i_njet = 0;
    float total_do_i_njet = 0;
    
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
      total_i_njet += nominal[std::pair<int, int> (i_pt_H, i_njet)];
      total_up_i_njet += max_up[std::pair<int, int> (i_pt_H, i_njet)];
      total_do_i_njet += max_do[std::pair<int, int> (i_pt_H, i_njet)];
    }
    
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size()+1; i_pt_H++) {
      
      //       std::cout << " pt:njet (<, <) = " << nominal[std::pair<int, int> (i_pt_H, i_njet)] << std::endl;
      
      float value = nominal[std::pair<int, int> (i_pt_H, i_njet)] / total_i_njet;

      if (value != 0) {
        std::cout << " pt:njet (<, <) : " << value / global_integral * total_i_njet << " ===> " ;
        std::cout << (max_do[std::pair<int, int> (i_pt_H, i_njet)]/total_do_i_njet-value) / value * 100. << " :: " ;
        std::cout << (max_up[std::pair<int, int> (i_pt_H, i_njet)]/total_up_i_njet-value) / value * 100. << std::endl;
      }
      else {
        std::cout << " pt:njet (<, <) : " << value / global_integral * total_i_njet << std::endl;
      }
      
    }
  }
  */
  
  
  
  // ---- 1001 = weights_LHE[0] ---> nominal
  //                                                         https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf
  //      [ 0 ] = 1001                                       <weight id="1001"> muR=0.10000E+01 muF=0.10000E+01 </weight>             Nominal
  //      [ 1 ] = 1002                                       <weight id="1002"> muR=0.10000E+01 muF=0.20000E+01 </weight>             NU
  //      [ 2 ] = 1003                                       <weight id="1003"> muR=0.10000E+01 muF=0.50000E+00 </weight>             ND
  //      [ 3 ] = 1004                                       <weight id="1004"> muR=0.20000E+01 muF=0.10000E+01 </weight>             UN
  //      [ 4 ] = 1005                                       <weight id="1005"> muR=0.20000E+01 muF=0.20000E+01 </weight>             UU
  //      [ 5 ] = 1006                                       <weight id="1006"> muR=0.20000E+01 muF=0.50000E+00 </weight>             UD   -> not used
  //      [ 6 ] = 1007                                       <weight id="1007"> muR=0.50000E+00 muF=0.10000E+01 </weight>             DN
  //      [ 7 ] = 1008                                       <weight id="1008"> muR=0.50000E+00 muF=0.20000E+01 </weight>             DU   -> not used
  //      [ 8 ] = 1009                                       <weight id="1009"> muR=0.50000E+00 muF=0.50000E+00 </weight>             DD
  //      [ 9 ] = nnlops-11-1
  //      
  
  
//   TLegend* legend = new TLegend(0.50,0.50,0.90,0.90);
//   legend->AddEntry(hNominal,"#mu_{R} = 1.0, #mu_{F} = 1.0","f");
//   
// 
//   
//   //---- UU
//   TH1F* hH_UU = new TH1F ("hH_UU", "nnlops", nbin, min, max);  
//   toDraw = Form ("%s >> hH_UU", var.c_str());
//   toWeight = Form ("%s * (weights_LHE[4])/(weights_LHE[0])", toWeightGlobal.Data());
//   tree1->Draw(toDraw.Data(), toWeight.Data() , "goff" );
//   
//   
//   hH_UU->SetLineColor(kRed+1);
//   hH_UU->SetLineStyle(1);
//   hH_UU->SetLineWidth(1);
//   hH_UU->Scale (1. / hH_UU->Integral(0,hH_UU->GetNbinsX()+1));
//   
//   //---- add back overflow bin
//   hH_UU->SetBinContent(hH_UU->GetNbinsX(), hH_UU->GetBinContent(hH_UU->GetNbinsX()) + hH_UU->GetBinContent(hH_UU->GetNbinsX()+1) );
//   
//   //---- scale to N3LO
//   hH_UU->Scale (xsecInclusive);
//   
//   hH_UU->Draw("same histo");
//   legend->AddEntry(hH_UU,"#mu_{R} = 2.0, #mu_{F} = 2.0","f");
//   
// 
// 
// 
// 
// 
// 
// 
//   //---- UN
//   TH1F* hH_UN = new TH1F ("hH_UN", "nnlops", nbin, min, max);  
//   toDraw = Form ("%s >> hH_UN", var.c_str());
//   toWeight = Form ("%s * (weights_LHE[3])/(weights_LHE[0])", toWeightGlobal.Data());
//   tree1->Draw(toDraw.Data(), toWeight.Data() , "goff" );
//   
//   
//   hH_UN->SetLineColor(kRed+2);
//   hH_UN->SetLineStyle(1);
//   hH_UN->SetLineWidth(1);
//   hH_UN->Scale (1. / hH_UN->Integral(0,hH_UN->GetNbinsX()+1));
//   
//   //---- add back overflow bin
//   hH_UN->SetBinContent(hH_UN->GetNbinsX(), hH_UN->GetBinContent(hH_UN->GetNbinsX()) + hH_UN->GetBinContent(hH_UN->GetNbinsX()+1) );
//   
//   //---- scale to N3LO
//   hH_UN->Scale (xsecInclusive);
//   
//   hH_UN->Draw("same histo");
//   legend->AddEntry(hH_UN,"#mu_{R} = 2.0, #mu_{F} = 1.0","f");
//   
// 
//   
//   
//   
//   //---- NU
//   TH1F* hH_NU = new TH1F ("hH_NU", "nnlops", nbin, min, max);  
//   toDraw = Form ("%s >> hH_NU", var.c_str());
//   toWeight = Form ("%s * (weights_LHE[1])/(weights_LHE[0])", toWeightGlobal.Data());
//   tree1->Draw(toDraw.Data(), toWeight.Data() , "goff" );
//   
//   
//   hH_NU->SetLineColor(kRed+3);
//   hH_NU->SetLineStyle(1);
//   hH_NU->SetLineWidth(1);
//   hH_NU->Scale (1. / hH_NU->Integral(0,hH_NU->GetNbinsX()+1));
//   
//   //---- add back overflow bin
//   hH_NU->SetBinContent(hH_NU->GetNbinsX(), hH_NU->GetBinContent(hH_NU->GetNbinsX()) + hH_NU->GetBinContent(hH_NU->GetNbinsX()+1) );
//   
//   //---- scale to N3LO
//   hH_NU->Scale (xsecInclusive);
//   
//   hH_NU->Draw("same histo");
//   legend->AddEntry(hH_NU,"#mu_{R} = 1.0, #mu_{F} = 2.0","f");
//   
//   
//   
//   
//   
//   
//   //---- ND
//   TH1F* hH_ND = new TH1F ("hH_ND", "nnlops", nbin, min, max);  
//   toDraw = Form ("%s >> hH_ND", var.c_str());
//   toWeight = Form ("%s * (weights_LHE[2])/(weights_LHE[0])", toWeightGlobal.Data());
//   tree1->Draw(toDraw.Data(), toWeight.Data() , "goff" );
//   
//   
//   hH_ND->SetLineColor(kRed-1);
//   hH_ND->SetLineStyle(1);
//   hH_ND->SetLineWidth(1);
//   hH_ND->Scale (1. / hH_ND->Integral(0,hH_ND->GetNbinsX()+1));
//   
//   //---- add back overflow bin
//   hH_ND->SetBinContent(hH_ND->GetNbinsX(), hH_ND->GetBinContent(hH_ND->GetNbinsX()) + hH_ND->GetBinContent(hH_ND->GetNbinsX()+1) );
//   
//   //---- scale to N3LO
//   hH_ND->Scale (xsecInclusive);
//   
//   hH_ND->Draw("same histo");
//   legend->AddEntry(hH_ND,"#mu_{R} = 1.0, #mu_{F} = 0.5","f");
//   
//   
//   
//   
//   
//   //---- DN
//   TH1F* hH_DN = new TH1F ("hH_DN", "nnlops", nbin, min, max);  
//   toDraw = Form ("%s >> hH_DN", var.c_str());
//   toWeight = Form ("%s * (weights_LHE[6])/(weights_LHE[0])", toWeightGlobal.Data());
//   tree1->Draw(toDraw.Data(), toWeight.Data() , "goff" );
//   
//   
//   hH_DN->SetLineColor(kRed-2);
//   hH_DN->SetLineStyle(1);
//   hH_DN->SetLineWidth(1);
//   hH_DN->Scale (1. / hH_DN->Integral(0,hH_DN->GetNbinsX()+1));
//   
//   //---- add back overflow bin
//   hH_DN->SetBinContent(hH_DN->GetNbinsX(), hH_DN->GetBinContent(hH_DN->GetNbinsX()) + hH_DN->GetBinContent(hH_DN->GetNbinsX()+1) );
//   
//   //---- scale to N3LO
//   hH_DN->Scale (xsecInclusive);
//   
//   hH_DN->Draw("same histo");
//   legend->AddEntry(hH_DN,"#mu_{R} = 0.5, #mu_{F} = 1.0","f");
//   
//   
//   
//   
//   
//   //---- DD
//   TH1F* hH_DD = new TH1F ("hH_DD", "nnlops", nbin, min, max);  
//   toDraw = Form ("%s >> hH_DD", var.c_str());
//   toWeight = Form ("%s * (weights_LHE[8])/(weights_LHE[0])", toWeightGlobal.Data());
//   tree1->Draw(toDraw.Data(), toWeight.Data() , "goff" );
//   
//   
//   hH_DD->SetLineColor(kRed-3);
//   hH_DD->SetLineStyle(1);
//   hH_DD->SetLineWidth(1);
//   hH_DD->Scale (1. / hH_DD->Integral(0,hH_DD->GetNbinsX()+1));
//   
//   //---- add back overflow bin
//   hH_DD->SetBinContent(hH_DD->GetNbinsX(), hH_DD->GetBinContent(hH_DD->GetNbinsX()) + hH_DD->GetBinContent(hH_DD->GetNbinsX()+1) );
//   
//   //---- scale to N3LO
//   hH_DD->Scale (xsecInclusive);
//   
//   hH_DD->Draw("same histo");
//   legend->AddEntry(hH_DD,"#mu_{R} = 0.5, #mu_{F} = 0.5","f");
//   
//   
//   
//   legend->Draw();
  
  
}