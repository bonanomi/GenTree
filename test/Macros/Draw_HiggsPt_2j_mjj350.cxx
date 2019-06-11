void Draw_HiggsPt_2j_mjj350( std::string var = "higgs_pt", int nbin = 50, float min = 0, float max = 200, std::string nameHR = "Higgs pT"){
  //0 jet bin, STXS 1.1 cat = 121, 122, 123
  TCanvas* cc_2j_mjj350 = new TCanvas("cc_2j_mjj350","", 800, 600);
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TTree* tree3 = (TTree*) _file1->Get("GenTree/gentree");  

  TH1F* h1_2j_mjj350 = new TH1F ("h1_2j_mjj350", "Higgs pT comparison, 2 jet bin, mJJ < 350 GeV", nbin, min, max);  
  TString toDraw = Form ("%s >> h1_2j_mjj350", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 121) || (stage1_cat_pTjet30GeV == 122) || (stage1_cat_pTjet30GeV == 123))");

  
  TH1F* h3_2j_mjj350 = new TH1F ("h3_2j_mjj350", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3_2j_mjj350", var.c_str());
  tree3->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 121) || (stage1_cat_pTjet30GeV == 122) || (stage1_cat_pTjet30GeV == 123))");
  
  
  h1_2j_mjj350->SetLineColor(kBlue);
  h1_2j_mjj350->SetLineStyle(1);
  h1_2j_mjj350->SetLineWidth(2);

  h3_2j_mjj350->SetLineColor(kViolet);
  h3_2j_mjj350->SetLineStyle(3);
  h3_2j_mjj350->SetLineWidth(4);
  
  h1_2j_mjj350->Scale (1. / h1_2j_mjj350->Integral(0,h1_2j_mjj350->GetNbinsX()+1));
  h3_2j_mjj350->Scale (1. / h3_2j_mjj350->Integral(0,h1_2j_mjj350->GetNbinsX()+1));
  
  //---- add back overflow bin
  h1_2j_mjj350->SetBinContent(h1_2j_mjj350->GetNbinsX(), h1_2j_mjj350->GetBinContent(h1_2j_mjj350->GetNbinsX()) + h1_2j_mjj350->GetBinContent(h1_2j_mjj350->GetNbinsX()+1) );
  h3_2j_mjj350->SetBinContent(h3_2j_mjj350->GetNbinsX(), h3_2j_mjj350->GetBinContent(h3_2j_mjj350->GetNbinsX()) + h3_2j_mjj350->GetBinContent(h3_2j_mjj350->GetNbinsX()+1) );

  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1_2j_mjj350->Scale (xsecInclusive);
  h3_2j_mjj350->Scale (xsecInclusive);    
  
  gStyle->SetOptStat(0000);
       
  h1_2j_mjj350->Draw();
  h1_2j_mjj350->GetXaxis()->SetTitle(nameHR.c_str());
  h1_2j_mjj350->GetYaxis()->SetTitle("pb");
  h3_2j_mjj350->Draw("SAME");
  //                  
  TLegend* leg_2j_mjj350 = new TLegend(0.7,0.7,0.9,0.9);
  leg_2j_mjj350->AddEntry(h1_2j_mjj350,"powheg nnlops","l");
  leg_2j_mjj350->AddEntry(h3_2j_mjj350,"aMC@NLO","l");
  //                          
  leg_2j_mjj350->Draw();
  //                              
  //                                
  cc_2j_mjj350->SetGrid();
  //                                    
  //                                      

  TCanvas* ccRatio_2j_mjj350 = new TCanvas("ccRatio_2j_mjj350","", 800, 600);
  
  TGraphErrors* gr_2j_mjj350 = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_2j_mjj350->SetPoint      (ibin, h1_2j_mjj350->GetBinCenter (ibin+1),  h1_2j_mjj350->GetBinContent (ibin+1) / h3_2j_mjj350->GetBinContent (ibin+1) );
    float err1 =  h1_2j_mjj350->GetBinError (ibin+1);
    float err2 =  h3_2j_mjj350->GetBinError (ibin+1);
    float val1 =  h1_2j_mjj350->GetBinContent (ibin+1);
    float val2 =  h3_2j_mjj350->GetBinContent (ibin+1);
    gr_2j_mjj350->SetPointError (ibin, 0.5 * h1_2j_mjj350->GetBinWidth (ibin+1),  sqrt(err1/val2*err1/val2 + err2*val1/val2/val2*err2*val1/val2/val2) );
  }
  
  gr_2j_mjj350->SetMarkerStyle(20);
  gr_2j_mjj350->SetMarkerSize(1);
  gr_2j_mjj350->SetMarkerColor(kRed);
  
  gr_2j_mjj350->Draw("APL");
  gr_2j_mjj350->GetYaxis()->SetTitle("powheg nnlops / aMC@NLO");
  gr_2j_mjj350->GetXaxis()->SetTitle("Higgs pT");

  ccRatio_2j_mjj350->SetGrid();
}