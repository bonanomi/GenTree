void Draw_HiggsPt_1j( std::string var = "higgs_pt", int nbin = 50, float min = 0, float max = 200, std::string nameHR = "Higgs pT"){
  //0 jet bin, STXS 1.1 cat = 111, 112, 113
  TCanvas* cc_1j = new TCanvas("cc_1j","", 800, 600);
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TTree* tree3 = (TTree*) _file1->Get("GenTree/gentree");  

  TH1F* h1_1j = new TH1F ("h1_1j", "Higgs pT comparison, 1 jet bin", nbin, min, max);  
  TString toDraw = Form ("%s >> h1_1j", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 111) || (stage1_cat_pTjet30GeV == 112) || (stage1_cat_pTjet30GeV == 113))");

  
  TH1F* h3_1j = new TH1F ("h3_1j", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3_1j", var.c_str());
  tree3->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 111) || (stage1_cat_pTjet30GeV == 112) || (stage1_cat_pTjet30GeV == 113))");
  
  
  h1_1j->SetLineColor(kBlue);
  h1_1j->SetLineStyle(1);
  h1_1j->SetLineWidth(2);

  h3_1j->SetLineColor(kViolet);
  h3_1j->SetLineStyle(3);
  h3_1j->SetLineWidth(4);
  
  h1_1j->Scale (1. / h1_1j->Integral(0,h1_1j->GetNbinsX()+1));
  h3_1j->Scale (1. / h3_1j->Integral(0,h1_1j->GetNbinsX()+1));
  
  //---- add back overflow bin
  h1_1j->SetBinContent(h1_1j->GetNbinsX(), h1_1j->GetBinContent(h1_1j->GetNbinsX()) + h1_1j->GetBinContent(h1_1j->GetNbinsX()+1) );
  h3_1j->SetBinContent(h3_1j->GetNbinsX(), h3_1j->GetBinContent(h3_1j->GetNbinsX()) + h3_1j->GetBinContent(h3_1j->GetNbinsX()+1) );

  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1_1j->Scale (xsecInclusive);
  h3_1j->Scale (xsecInclusive);    
  
  gStyle->SetOptStat(0000);
       
  h1_1j->Draw();
  h1_1j->GetXaxis()->SetTitle(nameHR.c_str());
  h1_1j->GetYaxis()->SetTitle("pb");
  h3_1j->Draw("SAME");
  //                  
  TLegend* leg_1j = new TLegend(0.7,0.7,0.9,0.9);
  leg_1j->AddEntry(h1_1j,"powheg nnlops","l");
  leg_1j->AddEntry(h3_1j,"aMC@NLO","l");
  //                          
  leg_1j->Draw();
  //                              
  //                                
  cc_1j->SetGrid();
  //                                    
  //                                      

  TCanvas* ccRatio_1j = new TCanvas("ccRatio_1j","", 800, 600);
  
  TGraphErrors* gr_1j = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_1j->SetPoint      (ibin, h1_1j->GetBinCenter (ibin+1),  h1_1j->GetBinContent (ibin+1) / h3_1j->GetBinContent (ibin+1) );
    float err1 =  h1_1j->GetBinError (ibin+1);
    float err2 =  h3_1j->GetBinError (ibin+1);
    float val1 =  h1_1j->GetBinContent (ibin+1);
    float val2 =  h3_1j->GetBinContent (ibin+1);
    gr_1j->SetPointError (ibin, 0.5 * h1_1j->GetBinWidth (ibin+1),  sqrt(err1/val2*err1/val2 + err2*val1/val2/val2*err2*val1/val2/val2) );
  }
  
  gr_1j->SetMarkerStyle(20);
  gr_1j->SetMarkerSize(1);
  gr_1j->SetMarkerColor(kRed);
  
  gr_1j->Draw("APL");
  gr_1j->GetYaxis()->SetTitle("powheg nnlops / aMC@NLO");
  gr_1j->GetXaxis()->SetTitle("Higgs pT");

  ccRatio_1j->SetGrid();
}