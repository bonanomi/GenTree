void Draw( std::string var = "jets30", int nbin = 5, float min = 0, float max = 5) {
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;
  
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "powheg", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data());
  
  TTree* tree2 = (TTree*) _file1->Get("GenTree/gentree");  
  TH1F* h2 = new TH1F ("h2", "powheg nnlops", nbin, min, max);  
  toDraw = Form ("%s >> h2", var.c_str());
  tree2->Draw(toDraw.Data(), "weight" );
  
  TTree* tree3 = (TTree*) _file2->Get("GenTree/gentree");  
  TH1F* h3 = new TH1F ("h3", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3", var.c_str());
  tree3->Draw(toDraw.Data(), "weight");
  
  
  h1->SetLineColor(kBlue);
  h1->SetLineStyle(1);
  h1->SetLineWidth(2);
  
  h2->SetLineColor(kRed);
  h2->SetLineStyle(2);
  h2->SetLineWidth(3);

  h3->SetLineColor(kViolet);
  h3->SetLineStyle(3);
  h3->SetLineWidth(4);
  
  h1->Scale (1. / h1->Integral());
  h2->Scale (1. / h2->Integral());
  h3->Scale (1. / h3->Integral());
  
  h1->Draw();
  h1->GetXaxis()->SetTitle("n jet 30 GeV");
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