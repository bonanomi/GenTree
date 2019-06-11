void Draw_HiggsPt_ge2j( std::string var = "higgs_pt", int nbin = 50, float min = 0, float max = 200, std::string nameHR = "Higgs pT"){
  //0 jet bin, STXS 1.1 cat = 131, 132, 141, 142
  TCanvas* cc_ge2j = new TCanvas("cc_ge2j","", 800, 600);
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TTree* tree3 = (TTree*) _file1->Get("GenTree/gentree");  

  TH1F* h1_ge2j = new TH1F ("h1_ge2j", "Higgs pT comparison, 2 jet bin, mJJ > 350 GeV", nbin, min, max);  
  TString toDraw = Form ("%s >> h1_ge2j", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 131) || (stage1_cat_pTjet30GeV == 132) || (stage1_cat_pTjet30GeV == 141)) || (stage1_cat_pTjet30GeV == 142))");

  
  TH1F* h3_ge2j = new TH1F ("h3_ge2j", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3_ge2j", var.c_str());
  tree3->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 131) || (stage1_cat_pTjet30GeV == 141) || (stage1_cat_pTjet30GeV == 142))");
  
  
  h1_ge2j->SetLineColor(kBlue);
  h1_ge2j->SetLineStyle(1);
  h1_ge2j->SetLineWidth(2);

  h3_ge2j->SetLineColor(kViolet);
  h3_ge2j->SetLineStyle(3);
  h3_ge2j->SetLineWidth(4);
  
  h1_ge2j->Scale (1. / h1_ge2j->Integral(0,h1_ge2j->GetNbinsX()+1));
  h3_ge2j->Scale (1. / h3_ge2j->Integral(0,h1_ge2j->GetNbinsX()+1));
  
  //---- add back overflow bin
  h1_ge2j->SetBinContent(h1_ge2j->GetNbinsX(), h1_ge2j->GetBinContent(h1_ge2j->GetNbinsX()) + h1_ge2j->GetBinContent(h1_ge2j->GetNbinsX()+1) );
  h3_ge2j->SetBinContent(h3_ge2j->GetNbinsX(), h3_ge2j->GetBinContent(h3_ge2j->GetNbinsX()) + h3_ge2j->GetBinContent(h3_ge2j->GetNbinsX()+1) );

  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1_ge2j->Scale (xsecInclusive);
  h3_ge2j->Scale (xsecInclusive);    
  
  gStyle->SetOptStat(0000);
       
  h1_ge2j->Draw();
  h1_ge2j->GetXaxis()->SetTitle(nameHR.c_str());
  h1_ge2j->GetYaxis()->SetTitle("pb");
  h3_ge2j->Draw("SAME");
  //                  
  TLegend* leg_ge2j = new TLegend(0.7,0.7,0.9,0.9);
  leg_ge2j->AddEntry(h1_ge2j,"powheg nnlops","l");
  leg_ge2j->AddEntry(h3_ge2j,"aMC@NLO","l");
  //                          
  leg_ge2j->Draw();
  //                              
  //                                
  cc_ge2j->SetGrid();
  //                                    
  //                                      

  TCanvas* ccRatio_ge2j = new TCanvas("ccRatio_ge2j","", 800, 600);
  
  TGraphErrors* gr_ge2j = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_ge2j->SetPoint      (ibin, h1_ge2j->GetBinCenter (ibin+1),  h1_ge2j->GetBinContent (ibin+1) / h3_ge2j->GetBinContent (ibin+1) );
    float err1 =  h1_ge2j->GetBinError (ibin+1);
    float err2 =  h3_ge2j->GetBinError (ibin+1);
    float val1 =  h1_ge2j->GetBinContent (ibin+1);
    float val2 =  h3_ge2j->GetBinContent (ibin+1);
    gr_ge2j->SetPointError (ibin, 0.5 * h1_ge2j->GetBinWidth (ibin+1),  sqrt(err1/val2*err1/val2 + err2*val1/val2/val2*err2*val1/val2/val2) );
  }
  
  gr_ge2j->SetMarkerStyle(20);
  gr_ge2j->SetMarkerSize(1);
  gr_ge2j->SetMarkerColor(kRed);
  
  gr_ge2j->Draw("APL");
  gr_ge2j->GetYaxis()->SetTitle("powheg nnlops / aMC@NLO");
  gr_ge2j->GetXaxis()->SetTitle("Higgs pT");

  ccRatio_ge2j->SetGrid();
}