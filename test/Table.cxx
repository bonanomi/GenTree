void Table() {
  /***
   Cross  section (%)     mu+     mu-     res+    res-    mig01+  mig01-  VBF2J+  VBF2j-  PT10   PT60  PT120  PT120  m_top
  
  
  
   Uncertainties matrix: NxM matrix, where N is the bins size (i.e. `list_cuts` defined below) and M is the size of 
   nuisance parameters/bins migrations. 
  
  In the STXS stage 1.1 we have more bins, in particular ptH migrations around 10GeV and 200GeV bins are taken into account.
  Hence, the new uncertainties (`ggHUncertaintyNew::qcd_ggF_uncertSF_2017_New()`) stored in the TTree are:
  ggH_mu    [0] = allUnc[0]
  ggH_res   [0] = allUnc[1]
  ggH_mig01 [0] = allUnc[2]
  ggH_mig12 [0] = allUnc[3]
  ggH_VBF2j [0] = allUnc[4]
  ggH_VBF3j [0] = allUnc[5]
  ggH_pT10  [0] = allUnc[6]
  ggH_pT60  [0] = allUnc[7]
  ggH_pT120 [0] = allUnc[8]
  ggH_pT200 [0] = allUnc[9]
  ggH_qmtop [0] = allUnc[10]
  ***/
  
  
  std::vector< std::string > list_cuts;
  std::vector <float> list_fraction_cross_section;
  std::vector< std::vector <float> > matrix_uncertainties_up;     //---- [ cut , uncertainties ]
  std::vector< std::vector <float> > matrix_uncertainties_down;   //---- [ cut , uncertainties ]
  
  std::vector< std::string > list_uncertainties;
  
  
  // list_cuts.push_back("(htxsHPt<10.000000) && (htxsNJets<1.000000)");
  // list_cuts.push_back("(htxsHPt<10.000000) && (htxsNJets<2.000000) && (htxsNJets>=1.000000)");
  // list_cuts.push_back("(htxsHPt<10.000000) && (htxsNJets<3.000000) && (htxsNJets>=2.000000)");
  // list_cuts.push_back("(htxsHPt<10.000000) && (htxsNJets>=3.000000)");
  // list_cuts.push_back("(htxsHPt<60.000000) && (htxsNJets<1.000000) && (htxsHPt>=10.000000)");
  // list_cuts.push_back("(htxsHPt<60.000000) && (htxsNJets<2.000000) && (htxsHPt>=10.000000) && (htxsNJets>=1.000000)");
  // list_cuts.push_back("(htxsHPt<60.000000) && (htxsNJets<3.000000) && (htxsHPt>=10.000000) && (htxsNJets>=2.000000)");
  // list_cuts.push_back("(htxsHPt<60.000000) && (htxsHPt>=10.000000) && (htxsNJets>=3.000000)");
  // list_cuts.push_back("(htxsHPt<120.000000) && (htxsNJets<1.000000) && (htxsHPt>=60.000000)");
  // list_cuts.push_back("(htxsHPt<120.000000) && (htxsNJets<2.000000) && (htxsHPt>=60.000000) && (htxsNJets>=1.000000)");
  // list_cuts.push_back("(htxsHPt<120.000000) && (htxsNJets<3.000000) && (htxsHPt>=60.000000) && (htxsNJets>=2.000000)");
  // list_cuts.push_back("(htxsHPt<120.000000) && (htxsHPt>=60.000000) && (htxsNJets>=3.000000)");
  // list_cuts.push_back("(htxsHPt<200.000000) && (htxsNJets<1.000000) && (htxsHPt>=120.000000)");
  // list_cuts.push_back("(htxsHPt<200.000000) && (htxsNJets<2.000000) && (htxsHPt>=120.000000) && (htxsNJets>=1.000000)");
  // list_cuts.push_back("(htxsHPt<200.000000) && (htxsNJets<3.000000) && (htxsHPt>=120.000000) && (htxsNJets>=2.000000)");
  // list_cuts.push_back("(htxsHPt<200.000000) && (htxsHPt>=120.000000) && (htxsNJets>=3.000000)");
  // list_cuts.push_back("(htxsNJets<1.000000) && (htxsHPt>=200.000000)");
  // list_cuts.push_back("(htxsNJets<2.000000) && (htxsHPt>=200.000000) && (htxsNJets>=1.000000)");
  // list_cuts.push_back("(htxsNJets<3.000000) && (htxsHPt>=200.000000) && (htxsNJets>=2.000000)");
  // list_cuts.push_back("(htxsHPt>=200.000000) && (htxsNJets>=3.000000)");

  list_cuts.push_back("102");
  list_cuts.push_back("103");
  list_cuts.push_back("111");
  list_cuts.push_back("112");
  list_cuts.push_back("113");
  list_cuts.push_back("121");
  list_cuts.push_back("122");
  list_cuts.push_back("123");
  list_cuts.push_back("131");
  list_cuts.push_back("132");
  list_cuts.push_back("141");
  list_cuts.push_back("142");
  list_cuts.push_back("150");
  
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
  list_uncertainties.push_back("allUnc[9]");
  list_uncertainties.push_back("allUnc[10]");
  
  
  TTree* tree = (TTree*) _file0->Get("ZZTree/candTree");  
  
  TH1F *htemp = new TH1F ("htemp", "", 1, 0, 2);
  float xsectot = tree->GetEntries();
  
  for (int iCut = 0; iCut<list_cuts.size(); iCut++) {
    float xsec = tree->GetEntries(list_cuts.at(iCut).c_str());
    list_fraction_cross_section.push_back(xsec/xsectot); 
    
    std::vector<float> uncertainties_up;
    std::vector<float> uncertainties_down;
    for (int iUnc = 0; iUnc<list_uncertainties.size(); iUnc++) {
      TString cut_up = Form ("(stage1_cat_pTjet30GeV==%s) * (%s)", list_cuts.at(iCut).c_str(), list_uncertainties.at(iUnc).c_str() );//("(htxs_stage1_cat==%s) * (%s)", list_cuts.at(iCut).c_str(), list_uncertainties.at(iUnc).c_str() );
      tree->Draw("1 >> htemp", cut_up.Data(), "goff");
      float xsec_up = htemp->Integral();
      uncertainties_up.push_back(xsec_up/xsectot); 

      TString cut_down = Form ("(stage1_cat_pTjet30GeV==%s) * (2 - %s)", list_cuts.at(iCut).c_str(), list_uncertainties.at(iUnc).c_str() );//("(htxs_stage1_cat==%s) * (2 - %s)", list_cuts.at(iCut).c_str(), list_uncertainties.at(iUnc).c_str() );
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