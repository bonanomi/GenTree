void Draw_HiggsPt( std::string var = "higgs_pt", int nbin = 100, float min = 0, float max = 400, std::string nameHR = "Higgs pT") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;

  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "MC generators comparison", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )");
  
  TTree* tree2 = (TTree*) _file1->Get("GenTree/gentree");  
  TH1F* h2 = new TH1F ("h2", "powheg nnlops", nbin, min, max);  
  toDraw = Form ("%s >> h2", var.c_str());
  tree2->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )" );  
  
  TTree* tree3 = (TTree*) _file2->Get("GenTree/gentree");  
  TH1F* h3 = new TH1F ("h3", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3", var.c_str());
  tree3->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )"); //"weight");
  
  TTree* tree4 = (TTree*) _file3->Get("GenTree/gentree");  
  TH1F* h4 = new TH1F ("h4", "minloHJJ", nbin, min, max);  
  toDraw = Form ("%s >> h4", var.c_str());
  tree4->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )"); //"weight");

  h1->SetLineColor(kBlue);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);
  
  h2->SetLineColor(kRed);
  h2->SetLineStyle(2);
  h2->SetLineWidth(3);

  h3->SetLineColor(kViolet);
  h3->SetLineStyle(3);
  h3->SetLineWidth(4);

  h4->SetLineColor(kMagenta);
  h4->SetLineStyle(4);
  h4->SetLineWidth(5);
  
  h1->Scale (1. / h1->Integral(0,h1->GetNbinsX()+1));
  h2->Scale (1. / h2->Integral(0,h2->GetNbinsX()+1));
  h3->Scale (1. / h3->Integral(0,h3->GetNbinsX()+1));
  h4->Scale (1. / h4->Integral(0,h4->GetNbinsX()+1));

  //---- add back overflow bin
  h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX()) + h1->GetBinContent(h1->GetNbinsX()+1) );
  h2->SetBinContent(h2->GetNbinsX(), h2->GetBinContent(h2->GetNbinsX()) + h2->GetBinContent(h2->GetNbinsX()+1) );
  h3->SetBinContent(h3->GetNbinsX(), h3->GetBinContent(h3->GetNbinsX()) + h3->GetBinContent(h3->GetNbinsX()+1) );
  h4->SetBinContent(h4->GetNbinsX(), h4->GetBinContent(h3->GetNbinsX()) + h4->GetBinContent(h3->GetNbinsX()+1) );

  //---- Scale to N3LO xsec
  float xsecInclusive = 48.52;
  if (var == "higgs_pt") {
    h1->Scale(xsecInclusive);
    h2->Scale(xsecInclusive);
    h3->Scale(xsecInclusive);
    h4->Scale(xsecInclusive);
  }
  gStyle->SetOptStat(0000);
       
  h1->Draw();
  h1->GetXaxis()->SetTitle(nameHR.c_str());
  h1->GetYaxis()->SetTitle("pb");
  h2->Draw("SAME");
  h3->Draw("SAME");
  h4->Draw("SAME");

  //                  
  TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(h1,"powheg","l");
  leg->AddEntry(h2,"powheg nnlops","l");
  leg->AddEntry(h3,"aMC@NLO","l");
  leg->AddEntry(h4, "minloHJJ", "l");
  //                          
  leg->Draw();
  //                              
  //                                
  cc->SetGrid();
  //                                    
  //                                      

  TCanvas* ccRatio = new TCanvas("ccRatio","", 800, 600);

  TGraphErrors* gr_pow = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_pow->SetPoint      (ibin, h1->GetBinCenter (ibin+1),  h2->GetBinContent (ibin+1) / h1->GetBinContent (ibin+1) );
    float err1 =  h2->GetBinError (ibin+1);
    float err2 =  h1->GetBinError (ibin+1);
    float val1 =  h2->GetBinContent (ibin+1);
    float val2 =  h1->GetBinContent (ibin+1);
  }

  TGraphErrors* gr_HJJ = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_pow->SetPoint      (ibin, h2->GetBinCenter (ibin+1),  h2->GetBinContent (ibin+1) / h4->GetBinContent (ibin+1) );
    float err1 =  h2->GetBinError (ibin+1);
    float err2 =  h4->GetBinError (ibin+1);
    float val1 =  h2->GetBinContent (ibin+1);
    float val2 =  h4->GetBinContent (ibin+1);
  }
  
  TGraphErrors* gr_aMC = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr_aMC->SetPoint      (ibin, h2->GetBinCenter (ibin+1),  h2->GetBinContent (ibin+1) / h3->GetBinContent (ibin+1) );
    float err1 =  h2->GetBinError (ibin+1);
    float err2 =  h3->GetBinError (ibin+1);
    float val1 =  h2->GetBinContent (ibin+1);
    float val2 =  h3->GetBinContent (ibin+1);
  }
  
  gr_aMC->SetLineColor(kViolet);
  gr_pow->SetLineColor(kBlue);
  gr_HJJ->SetLineColor(kRed);

  gr_aMC->Draw("AL");
  gr_pow->Draw("L");
  gr_HJJ->Draw("L");

  gr_aMC->SetTitle("Ratio w.r.t. nnlops");
  gr_aMC->GetYaxis()->SetTitle("powheg nnlops / aMC@NLO");
  gr_aMC->GetXaxis()->SetTitle("Higgs pT");

  TLegend* leg_ratio = new TLegend(0.7,0.7,0.9,0.9);
  leg_ratio->AddEntry(gr_aMC,"nnlops/aMC@NLO","l");
  leg_ratio->AddEntry(gr_pow,"nnlops/powheg","l");
  leg_ratio->AddEntry(gr_HJJ,"nnlops/minloHJJ","l");
  //                          
  leg_ratio->Draw();
  ccRatio->SetGrid();
}