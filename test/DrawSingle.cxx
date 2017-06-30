void DrawSingle( std::string var = "jets30", int nbin = 5, float min = 0, float max = 5, std::string nameHR = "n jet 30 GeV") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;
  
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "nnlops", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )" );
//   tree1->Draw(toDraw.Data(), "( weights_LHE[9] )" );
  
   
  h1->SetLineColor(kBlue);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);
   
  h1->Scale (1. / h1->Integral(0,h1->GetNbinsX()+1));

  //---- add back overflow bin
  h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX()) + h1->GetBinContent(h1->GetNbinsX()+1) );


  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1->Scale (xsecInclusive);
  

  
  h1->Draw();
  h1->GetXaxis()->SetTitle(nameHR.c_str());
  h1->GetYaxis()->SetTitle("pb");
  
  cc->SetGrid();
  
  float new_integral = 0;
  std::cout << std::endl;
  for (int ibin = 0; ibin < nbin; ibin++) {
    std::cout << "  " << h1->GetBinContent (ibin+1) << std::endl;
    new_integral += h1->GetBinContent (ibin+1);
  }
  std::cout << std::endl;
  
  std::cout << " integral = " << new_integral << std::endl;
  
  
  
  std::cout << std::endl;
  for (int ibin = 0; ibin < nbin; ibin++) {
    std::cout << "  " << h1->GetBinError (ibin+1) / h1->GetBinContent (ibin+1) << std::endl;
  }
  std::cout << std::endl;
  
}