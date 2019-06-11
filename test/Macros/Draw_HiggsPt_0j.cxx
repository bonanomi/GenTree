void Draw_HiggsPt_0j( std::string var = "higgs_pt", int nbin = 50, float min = 0, float max = 200, std::string nameHR = "Higgs pT"){
  //0 jet bin, STXS 1.1 cat = 102, 103
  TCanvas* cc_0j = new TCanvas("cc_0j","", 800, 600);
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TTree* tree3 = (TTree*) _file1->Get("GenTree/gentree");  

  TH1F* h1_0j = new TH1F ("h1_0j", "Higgs pT comparison, 0 jet bin", nbin, min, max);  
  TString toDraw = Form ("%s >> h1_0j", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 102) || (stage1_cat_pTjet30GeV == 103))");

  
  TH1F* h3_0j = new TH1F ("h3_0j", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3_0j", var.c_str());
  tree3->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  ) && ((stage1_cat_pTjet30GeV == 102) || (stage1_cat_pTjet30GeV == 103))");
  
  
  h1_0j->SetLineColor(kBlue);
  h1_0j->SetLineStyle(1);
  h1_0j->SetLineWidth(2);

  h3_0j->SetLineColor(kViolet);
  h3_0j->SetLineStyle(3);
  h3_0j->SetLineWidth(4);
  
  h1_0j->Scale (1. / h1_0j->Integral(0,h1_0j->GetNbinsX()+1));
  h3_0j->Scale (1. / h3_0j->Integral(0,h1_0j->GetNbinsX()+1));
  
  //---- add back overflow bin
  h1_0j->SetBinContent(h1_0j->GetNbinsX(), h1_0j->GetBinContent(h1_0j->GetNbinsX()) + h1_0j->GetBinContent(h1_0j->GetNbinsX()+1) );
  h3_0j->SetBinContent(h3_0j->GetNbinsX(), h3_0j->GetBinContent(h3_0j->GetNbinsX()) + h3_0j->GetBinContent(h3_0j->GetNbinsX()+1) );

  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1_0j->Scale (xsecInclusive);
  h3_0j->Scale (xsecInclusive);    
  
  gStyle->SetOptStat(0000);
       
  h1_0j->Draw();
  h1_0j->GetXaxis()->SetTitle(nameHR.c_str());
  h1_0j->GetYaxis()->SetTitle("pb");
  h3_0j->Draw("SAME");
  //                  
  TLegend* leg_0j = new TLegend(0.7,0.7,0.9,0.9);
  leg_0j->AddEntry(h1_0j,"powheg nnlops","l");
  leg_0j->AddEntry(h3_0j,"aMC@NLO","l");
  //                          
  leg_0j->Draw();
  //                              
  //                                
  cc_0j->SetGrid();
  //                                    
  //                                      

  TCanvas* ccRatio_0j = new TCanvas("ccRatio_0j","", 800, 600);
  
  TGraphErrors* gr_0j = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_0j->SetPoint      (ibin, h1_0j->GetBinCenter (ibin+1),  h1_0j->GetBinContent (ibin+1) / h3_0j->GetBinContent (ibin+1) );
    float err1 =  h1_0j->GetBinError (ibin+1);
    float err2 =  h3_0j->GetBinError (ibin+1);
    float val1 =  h1_0j->GetBinContent (ibin+1);
    float val2 =  h3_0j->GetBinContent (ibin+1);
    gr_0j->SetPointError (ibin, 0.5 * h1_0j->GetBinWidth (ibin+1),  sqrt(err1/val2*err1/val2 + err2*val1/val2/val2*err2*val1/val2/val2) );
  }
  
  gr_0j->SetMarkerStyle(20);
  gr_0j->SetMarkerSize(1);
  gr_0j->SetMarkerColor(kRed);
  
  gr_0j->Draw("APL");
  gr_0j->GetYaxis()->SetTitle("powheg nnlops / aMC@NLO");
  gr_0j->GetXaxis()->SetTitle("Higgs pT");

  ccRatio_0j->SetGrid();
}