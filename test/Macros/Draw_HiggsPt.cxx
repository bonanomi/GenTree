void Draw_HiggsPt( std::string var = "higgs_pt", int nbin = 50, float min = 0, float max = 200, std::string nameHR = "Higgs pT") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;
  
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "Higgs pT comparison", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )");

  
  TTree* tree3 = (TTree*) _file1->Get("GenTree/gentree");  
  TH1F* h3 = new TH1F ("h3", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3", var.c_str());
  tree3->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )");
  
  
  h1->SetLineColor(kBlue);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);

  h3->SetLineColor(kViolet);
  h3->SetLineStyle(3);
  h3->SetLineWidth(4);
  
  h1->Scale (1. / h1->Integral(0,h1->GetNbinsX()+1));
  h3->Scale (1. / h3->Integral(0,h1->GetNbinsX()+1));
  
  //---- add back overflow bin
  h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX()) + h1->GetBinContent(h1->GetNbinsX()+1) );
  h3->SetBinContent(h3->GetNbinsX(), h3->GetBinContent(h3->GetNbinsX()) + h3->GetBinContent(h3->GetNbinsX()+1) );

  //---- scale to N3LO
  float xsecInclusive = 48.58;
  h1->Scale (xsecInclusive);
  h3->Scale (xsecInclusive);    
  
  gStyle->SetOptStat(0000);
       
  h1->Draw();
  h1->GetXaxis()->SetTitle(nameHR.c_str());
  h1->GetYaxis()->SetTitle("pb");
  h3->Draw("SAME");
  //                  
  TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(h1,"powheg nnlops","l");
  leg->AddEntry(h3,"aMC@NLO","l");
  //                          
  leg->Draw();
  //                              
  //                                
  cc->SetGrid();
  //                                    
  //                                      

  TCanvas* ccRatio = new TCanvas("ccRatio","", 800, 600);
  
  TGraphErrors* gr = new TGraphErrors();
  for (int ibin = 0; ibin < nbin; ibin++) {
    gr->SetPoint      (ibin, h1->GetBinCenter (ibin+1),  h1->GetBinContent (ibin+1) / h3->GetBinContent (ibin+1) );
    float err1 =  h1->GetBinError (ibin+1);
    float err2 =  h3->GetBinError (ibin+1);
    float val1 =  h1->GetBinContent (ibin+1);
    float val2 =  h3->GetBinContent (ibin+1);
    gr->SetPointError (ibin, 0.5 * h1->GetBinWidth (ibin+1),  sqrt(err1/val2*err1/val2 + err2*val1/val2/val2*err2*val1/val2/val2) );
  }
  
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1);
  gr->SetMarkerColor(kRed);
  
  gr->Draw("APL");
  gr->GetYaxis()->SetTitle("powheg nnlops / aMC@NLO");
  gr_0j->GetXaxis()->SetTitle("Higgs pT");

  ccRatio->SetGrid();
}