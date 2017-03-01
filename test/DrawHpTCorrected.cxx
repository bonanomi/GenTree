void DrawHpTCorrected( std::string var = "jets30", int nbin = 5, float min = 0, float max = 5, std::string nameHR = "n jet 30 GeV") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;
  
//         
//  from Dag, only for powheg
//  
//  if (H_pT<20) return 1.11;
//  if (H_pT<45) return 1.11 - (H_pT-20)/25*0.2; // -> 0.91
//  if (H_pT<135) return 0.91 - (H_pT-45)/90*0.36; // -> 0.55
//  
  
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* h1 = new TH1F ("h1", "powheg", nbin, min, max);  
  TString toDraw = Form ("%s >> h1", var.c_str());
  tree1->Draw(toDraw.Data(), "(1.11*(higgs_pt<20) + (1.11 - (higgs_pt-20)/25*0.2 ) *(higgs_pt>=20 && higgs_pt < 45) + (0.91 - (higgs_pt-45)/90*0.36 ) *(higgs_pt>=45 && higgs_pt < 135)  + 0.55 * (higgs_pt>=135) )");
  
  TTree* tree2 = (TTree*) _file1->Get("GenTree/gentree");  
  TH1F* h2 = new TH1F ("h2", "powheg nnlops", nbin, min, max);  
  toDraw = Form ("%s >> h2", var.c_str());
  tree2->Draw(toDraw.Data(), "( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )" );
  
  TTree* tree3 = (TTree*) _file2->Get("GenTree/gentree");  
  TH1F* h3 = new TH1F ("h3", "aMC@nlo", nbin, min, max);  
  toDraw = Form ("%s >> h3", var.c_str());
  tree3->Draw(toDraw.Data(), "weight * 1.00");
  
  
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