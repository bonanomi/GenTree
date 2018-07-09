void Table() {
 
  //                               Cross  section (%)     mu+     mu-     res+    res-    mig01+  mig01-  VBF2J+  VBF2j-  PT60    PT120   m_top
  //
  //
  //  0 jet
  //  1 jet                                                                                               ggH_mu    [0] = allUnc[0]
  //  1 jet & ptH [0-60]                                                                                  ggH_res   [0] = allUnc[1]
  //  1 jet & ptH [60-120]                                                                                ggH_mig01 [0] = allUnc[2]
  //  1 jet & ptH [120-200]                                                                               ggH_mig12 [0] = allUnc[3]
  //  1 jet & ptH [200-inf]                                                                               ggH_VBF2j [0] = allUnc[4]
  //  >=2 jet                                                                                             ggH_VBF3j [0] = allUnc[5]
  //  >=2 jet & ptH [0-60]                                                                                ggH_pT60  [0] = allUnc[6]
  //  >=2 jet & ptH [60-120]                                                                              ggH_pT120 [0] = allUnc[7]
  //  >=2 jet & ptH [120-200]                                                                             ggH_qmtop [0] = allUnc[8]
  //  >=2 jet & ptH [200-inf]
  //  >=1 jet
  //  VBF_3JV                                                 if (STXS==101) return -0.320; // GG2H_VBFTOPO_JET3VETO, tot unc 38%
  //  VBF_3J                                                  if (STXS==102) return  0.235; // GG2H_VBFTOPO_JET3, tot unc 30.4%
  // 
  // 
  
  
  
  std::vector< std::string > list_cuts;
  std::vector <float> list_fraction_cross_section;
  std::vector< std::vector <float> > matrix_uncertainties_up;     //---- [ cut , uncertainties ]
  std::vector< std::vector <float> > matrix_uncertainties_down;   //---- [ cut , uncertainties ]
  
  std::vector< std::string > list_uncertainties;
  
  
  list_cuts.push_back("jets30==0");
  list_cuts.push_back("jets30==1");
  list_cuts.push_back("(jets30==1 && (higgs_pt<60))");
  list_cuts.push_back("(jets30==1 && (higgs_pt>60)  && (higgs_pt<120))");
  list_cuts.push_back("(jets30==1 && (higgs_pt>120) && (higgs_pt<200))");
  list_cuts.push_back("(jets30==1 && (higgs_pt>200))");
  list_cuts.push_back("jets30>=2");
  list_cuts.push_back("(jets30>=2 && (higgs_pt<60))");
  list_cuts.push_back("(jets30>=2 && (higgs_pt>60)  && (higgs_pt<120))");
  list_cuts.push_back("(jets30>=2 && (higgs_pt>120) && (higgs_pt<200))");
  list_cuts.push_back("(jets30>=2 && (higgs_pt>200))");
  list_cuts.push_back("jets30>=1");
  list_cuts.push_back("stage1_cat_pTjet30GeV==101");
  list_cuts.push_back("stage1_cat_pTjet30GeV==102");
  
  list_cuts.push_back("1"); //---- inclusive
  
  
  list_uncertainties.push_back("allUnc[0]");
  list_uncertainties.push_back("allUnc[1]");
  list_uncertainties.push_back("allUnc[2]");
  list_uncertainties.push_back("allUnc[3]");
  list_uncertainties.push_back("allUnc[4]");
  list_uncertainties.push_back("allUnc[5]");
  list_uncertainties.push_back("allUnc[6]");
  list_uncertainties.push_back("allUnc[7]");
  list_uncertainties.push_back("allUnc[8]");
  
  
  TTree* tree = (TTree*) _file0->Get("GenTree/gentree");  
  
  TH1F *htemp = new TH1F ("htemp", "", 1, 0, 2);
  float xsectot = tree->GetEntries();
  
  for (int iCut = 0; iCut<list_cuts.size(); iCut++) {
    float xsec = tree->GetEntries(list_cuts.at(iCut).c_str());
    list_fraction_cross_section.push_back(xsec/xsectot); 
    
    std::vector<float> uncertainties_up;
    std::vector<float> uncertainties_down;
    for (int iUnc = 0; iUnc<list_uncertainties.size(); iUnc++) {
      TString cut_up = Form ("(%s) * (%s)", list_cuts.at(iCut).c_str(), list_uncertainties.at(iUnc).c_str() );
      tree->Draw("1 >> htemp", cut_up.Data(), "goff");
      float xsec_up = htemp->Integral();
      uncertainties_up.push_back(xsec_up/xsectot); 

      TString cut_down = Form ("(%s) * (2 - %s)", list_cuts.at(iCut).c_str(), list_uncertainties.at(iUnc).c_str() );
      tree->Draw("1 >> htemp", cut_down.Data(), "goff");
      float xsec_down = htemp->Integral();
      uncertainties_down.push_back(xsec_down/xsectot);
      
//       
//      'ggH_mu', '1+(1.-ggH_mu)'
//       
    }
    matrix_uncertainties_up.push_back(uncertainties_up);
    matrix_uncertainties_down.push_back(uncertainties_down);  
  }
  
  //---- now draw 
  
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  for (int iCut = 0; iCut<list_cuts.size(); iCut++) {
    std::cout << " [" << iCut << "] = " << std::setw(6) << std::setprecision(3) << list_fraction_cross_section.at(iCut) << std::endl;
  }
  
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  for (int iCut = 0; iCut<list_cuts.size(); iCut++) {
    std::cout << std::setw(6) << std::setprecision(3) << list_fraction_cross_section.at(iCut) << std::endl;
  }
  
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  for (int iCut = 0; iCut<list_cuts.size(); iCut++) {
    for (int iUnc = 0; iUnc<list_uncertainties.size(); iUnc++) {
      std::cout << " ["  << std::setw(4) << std::setprecision(2) << ((matrix_uncertainties_down.at(iCut)).at(iUnc) - list_fraction_cross_section.at(iCut))*100 
                << " / " << std::setw(4) << std::setprecision(2) << ((matrix_uncertainties_up.at(iCut)).at(iUnc)   - list_fraction_cross_section.at(iCut))*100 << " ] ";
    }
    std::cout << std::endl;
  }
  
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;


  for (int iCut = 0; iCut<list_cuts.size(); iCut++) {
    for (int iUnc = 0; iUnc<list_uncertainties.size(); iUnc++) {
      std::cout << " " << std::setw(6) << std::setprecision(3) << ((matrix_uncertainties_up.at(iCut)).at(iUnc)   - list_fraction_cross_section.at(iCut))*100 << " ";
    }
    std::cout << std::endl;
  }
  
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  std::cout << " ---- " << std::endl;
  
  









  
  
}