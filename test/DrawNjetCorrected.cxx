void DrawNjetCorrected( std::string var = "jets30", int nbin = 5, float min = 0, float max = 5, std::string nameHR = "n jet 30 GeV") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;
  
//           powheg              amc@nlo
//   
//   [0] => 0.861954     ----    0.92636
//   [1] => 1.19465     ----    1.09542
//   [2] => 1.33651     ----    1.12998
//   [3] => 1.37506     ----    1.10286
//   [4] => 1.41484     ----    1.16395
//   
//   
//   
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "powheg", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data(), "(0.861954*(jets30==0) + 1.19465*(jets30==1) + 1.33651*(jets30==2) + 1.37506*(jets30==3) + 1.41484*(jets30>=4))");
  
  TTree* tree2 = (TTree*) _file1->Get("GenTree/gentree");  
  TH1F* h2 = new TH1F ("h2", "powheg nnlops", nbin, min, max);  
  toDraw = Form ("%s >> h2", var.c_str());
  tree2->Draw(toDraw.Data(), "weight" );
  
  TTree* tree3 = (TTree*) _file2->Get("GenTree/gentree");  
  TH1F* h3 = new TH1F ("h3", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3", var.c_str());
  tree3->Draw(toDraw.Data(), "weight * (0.92636*(jets30==0) + 1.09542*(jets30==1) + 1.12998*(jets30==2) + 1.10286*(jets30==3) + 1.16395*(jets30>=4))");
  
  
  h1->SetLineColor(kBlue);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);
  
  h2->SetLineColor(kRed);
  h2->SetLineStyle(2);
  h2->SetLineWidth(3);

  h3->SetLineColor(kViolet);
  h3->SetLineStyle(3);
  h3->SetLineWidth(4);
  
  h1->Scale (1. / h1->Integral(0,h1->GetNbinsX()+1));
  h2->Scale (1. / h2->Integral(0,h1->GetNbinsX()+1));
  h3->Scale (1. / h3->Integral(0,h1->GetNbinsX()+1));
  
  h1->Draw();
  h1->GetXaxis()->SetTitle(nameHR.c_str());
  h1->GetYaxis()->SetTitle("normalized");
  h2->Draw("SAME");
  h3->Draw("SAME");
  
  TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(h1,"powheg","l");
  leg->AddEntry(h2,"powheg nnlops","l");
  leg->AddEntry(h3,"aMC@NLO","l");
  
  leg->Draw();
  
  
  cc->SetGrid();
  
  
}