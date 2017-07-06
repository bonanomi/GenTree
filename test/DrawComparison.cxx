void DrawComparison( std::string var = "jets30", int nbin = 5, float min = 0, float max = 5, std::string nameHR = "n jet 30 GeV") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "powheg", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )" );
  
  TTree* tree2 = (TTree*) _file1->Get("GenTree/gentree");  
  TH1F* h2 = new TH1F ("h2", "powheg nnlops", nbin, min, max);  
  toDraw = Form ("%s >> h2", var.c_str());
  tree2->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )" );
  
  
  h1->SetLineColor(kBlue);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);
  
  h2->SetLineColor(kRed);
  h2->SetLineStyle(2);
  h2->SetLineWidth(3);

  h1->Scale (1. / h1->Integral(0,h1->GetNbinsX()+1));
  h2->Scale (1. / h2->Integral(0,h1->GetNbinsX()+1));
  
  //---- add back overflow bin
  h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX()) + h1->GetBinContent(h1->GetNbinsX()+1) );
  h2->SetBinContent(h2->GetNbinsX(), h2->GetBinContent(h2->GetNbinsX()) + h2->GetBinContent(h2->GetNbinsX()+1) );
  
  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1->Scale (xsecInclusive);
  h2->Scale (xsecInclusive);
  
  
  h1->Draw();
  h1->GetXaxis()->SetTitle(nameHR.c_str());
  h1->GetYaxis()->SetTitle("pb");
  h2->Draw("SAME");
  
  TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(h1,"CMS tune","l");
  leg->AddEntry(h2,"ATLAS tune","l");

//   leg->AddEntry(h1,"CMS central","l");
//   leg->AddEntry(h2,"CMS private","l");
  
  leg->Draw();
  
  
  cc->SetGrid();
  
  
  
  
  TCanvas* ccRatio = new TCanvas("ccRatio","", 800, 600);
  
  TGraphErrors* gr = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr->SetPoint      (ibin, h1->GetBinCenter (ibin+1),  h1->GetBinContent (ibin+1) / h2->GetBinContent (ibin+1) );
    float err1 =  h1->GetBinError (ibin+1);
    float err2 =  h2->GetBinError (ibin+1);
    float val1 =  h1->GetBinContent (ibin+1);
    float val2 =  h2->GetBinContent (ibin+1);
    gr->SetPointError (ibin, 0.5 * h1->GetBinWidth (ibin+1),  sqrt(err1/val2*err1/val2 + err2*val1/val2/val2*err2*val1/val2/val2) );
  }
  
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1);
  gr->SetMarkerColor(kMagenta);
  
  gr->Draw("APL");
  gr->GetYaxis()->SetTitle("CMS / ATLAS");
//   gr->GetYaxis()->SetTitle("central / private");
  gr->GetXaxis()->SetTitle(nameHR.c_str());
  
  ccRatio->SetGrid();
  
  
}

