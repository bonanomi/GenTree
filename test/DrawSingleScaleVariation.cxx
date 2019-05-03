void DrawSingleScaleVariation( std::string var = "jets30", int nbin = 5, float min = 0, float max = 5, std::string nameHR = "n jet 30 GeV") {
  
  
  std::cout << " var =    " << var    << std::endl;
  std::cout << " nbin =   " << nbin   << std::endl;
  std::cout << " min =    " << min    << std::endl;
  std::cout << " max =    " << max    << std::endl;
  std::cout << " nameHR = " << nameHR << std::endl;
  
  
  TCanvas* cc = new TCanvas("cc","", 800, 600);
  int n = 0;
  
  //---- scale to N3LO
  float xsecInclusive = 48.58;
  
  
  TString toCutGlobal;
  
  toCutGlobal = Form ("(weights_LHE[0]) * ( ( weights_LHE[9] * (abs(weights_LHE[9]/weights_LHE[0])<100)) + 0 * (abs(weights_LHE[9]/weights_LHE[0])>100)  )");
  
  
  TString toCut;
  TString toDraw;
  
  TTree* tree1 = (TTree*) _file0->Get("GenTree/gentree");  
  TH1F* hNominal = new TH1F ("hNominal", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hNominal", var.c_str());
  toCut = Form ("%s * (1)", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  hNominal->SetLineColor(kBlue);
  hNominal->SetLineStyle(1);
  hNominal->SetLineWidth(2);
  hNominal->Scale (1. / hNominal->Integral(0,hNominal->GetNbinsX()+1));

  //---- add back overflow bin
  hNominal->SetBinContent(hNominal->GetNbinsX(), hNominal->GetBinContent(hNominal->GetNbinsX()) + hNominal->GetBinContent(hNominal->GetNbinsX()+1) );

  //---- scale to N3LO
  hNominal->Scale (xsecInclusive);
  
  hNominal->Draw();
  hNominal->GetXaxis()->SetTitle(nameHR.c_str());
  hNominal->GetYaxis()->SetTitle("pb");
  
  
  
  // ---- 1001 = weights_LHE[0] ---> nominal
  //                                                         https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf
  //      [ 0 ] = 1001                                       <weight id="1001"> muR=0.10000E+01 muF=0.10000E+01 </weight>             Nominal
  //      [ 1 ] = 1002                                       <weight id="1002"> muR=0.10000E+01 muF=0.20000E+01 </weight>             NU
  //      [ 2 ] = 1003                                       <weight id="1003"> muR=0.10000E+01 muF=0.50000E+00 </weight>             ND
  //      [ 3 ] = 1004                                       <weight id="1004"> muR=0.20000E+01 muF=0.10000E+01 </weight>             UN
  //      [ 4 ] = 1005                                       <weight id="1005"> muR=0.20000E+01 muF=0.20000E+01 </weight>             UU
  //      [ 5 ] = 1006                                       <weight id="1006"> muR=0.20000E+01 muF=0.50000E+00 </weight>             UD   -> not used
  //      [ 6 ] = 1007                                       <weight id="1007"> muR=0.50000E+00 muF=0.10000E+01 </weight>             DN
  //      [ 7 ] = 1008                                       <weight id="1008"> muR=0.50000E+00 muF=0.20000E+01 </weight>             DU   -> not used
  //      [ 8 ] = 1009                                       <weight id="1009"> muR=0.50000E+00 muF=0.50000E+00 </weight>             DD
  //      [ 9 ] = nnlops-11-1
  //      
  
  //---- UU
  TH1F* hH_UU = new TH1F ("hH_UU", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hH_UU", var.c_str());
  toCut = Form ("%s * (weights_LHE[4])/(weights_LHE[0])", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  
  hH_UU->SetLineColor(kRed+1);
  hH_UU->SetLineStyle(1);
  hH_UU->SetLineWidth(2);
  hH_UU->Scale (1. / hH_UU->Integral(0,hH_UU->GetNbinsX()+1));
  
  //---- add back overflow bin
  hH_UU->SetBinContent(hH_UU->GetNbinsX(), hH_UU->GetBinContent(hH_UU->GetNbinsX()) + hH_UU->GetBinContent(hH_UU->GetNbinsX()+1) );
  
  //---- scale to N3LO
  hH_UU->Scale (xsecInclusive);
  
  hH_UU->Draw("same");
  







  //---- UN
  TH1F* hH_UN = new TH1F ("hH_UN", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hH_UN", var.c_str());
  toCut = Form ("%s * (weights_LHE[3])/(weights_LHE[0])", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  
  hH_UN->SetLineColor(kRed+2);
  hH_UN->SetLineStyle(1);
  hH_UN->SetLineWidth(2);
  hH_UN->Scale (1. / hH_UN->Integral(0,hH_UN->GetNbinsX()+1));
  
  //---- add back overflow bin
  hH_UN->SetBinContent(hH_UN->GetNbinsX(), hH_UN->GetBinContent(hH_UN->GetNbinsX()) + hH_UN->GetBinContent(hH_UN->GetNbinsX()+1) );
  
  //---- scale to N3LO
  hH_UN->Scale (xsecInclusive);
  
  hH_UN->Draw("same");
  

  
  
  
  //---- NU
  TH1F* hH_NU = new TH1F ("hH_NU", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hH_NU", var.c_str());
  toCut = Form ("%s * (weights_LHE[1])/(weights_LHE[0])", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  
  hH_NU->SetLineColor(kRed+3);
  hH_NU->SetLineStyle(1);
  hH_NU->SetLineWidth(2);
  hH_NU->Scale (1. / hH_NU->Integral(0,hH_NU->GetNbinsX()+1));
  
  //---- add back overflow bin
  hH_NU->SetBinContent(hH_NU->GetNbinsX(), hH_NU->GetBinContent(hH_NU->GetNbinsX()) + hH_NU->GetBinContent(hH_NU->GetNbinsX()+1) );
  
  //---- scale to N3LO
  hH_NU->Scale (xsecInclusive);
  
  hH_NU->Draw("same");
  
  
  
  
  
  
  //---- ND
  TH1F* hH_ND = new TH1F ("hH_ND", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hH_ND", var.c_str());
  toCut = Form ("%s * (weights_LHE[2])/(weights_LHE[0])", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  
  hH_ND->SetLineColor(kRed+4);
  hH_ND->SetLineStyle(1);
  hH_ND->SetLineWidth(2);
  hH_ND->Scale (1. / hH_ND->Integral(0,hH_ND->GetNbinsX()+1));
  
  //---- add back overflow bin
  hH_ND->SetBinContent(hH_ND->GetNbinsX(), hH_ND->GetBinContent(hH_ND->GetNbinsX()) + hH_ND->GetBinContent(hH_ND->GetNbinsX()+1) );
  
  //---- scale to N3LO
  hH_ND->Scale (xsecInclusive);
  
  hH_ND->Draw("same");
  
  
  
  
  
  //---- DN
  TH1F* hH_DN = new TH1F ("hH_DN", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hH_DN", var.c_str());
  toCut = Form ("%s * (weights_LHE[6])/(weights_LHE[0])", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  
  hH_DN->SetLineColor(kRed+5);
  hH_DN->SetLineStyle(1);
  hH_DN->SetLineWidth(2);
  hH_DN->Scale (1. / hH_DN->Integral(0,hH_DN->GetNbinsX()+1));
  
  //---- add back overflow bin
  hH_DN->SetBinContent(hH_DN->GetNbinsX(), hH_DN->GetBinContent(hH_DN->GetNbinsX()) + hH_DN->GetBinContent(hH_DN->GetNbinsX()+1) );
  
  //---- scale to N3LO
  hH_DN->Scale (xsecInclusive);
  
  hH_DN->Draw("same");
 
  
  
  
  
  //---- DD
  TH1F* hH_DD = new TH1F ("hH_DD", "nnlops", nbin, min, max);  
  toDraw = Form ("%s >> hH_DD", var.c_str());
  toCut = Form ("%s * (weights_LHE[8])/(weights_LHE[0])", toCutGlobal.Data());
  tree1->Draw(toDraw.Data(), toCut.Data() );
  
  
  hH_DD->SetLineColor(kRed+6);
  hH_DD->SetLineStyle(1);
  hH_DD->SetLineWidth(2);
  hH_DD->Scale (1. / hH_DD->Integral(0,hH_DD->GetNbinsX()+1));
  
  //---- add back overflow bin
  hH_DD->SetBinContent(hH_DD->GetNbinsX(), hH_DD->GetBinContent(hH_DD->GetNbinsX()) + hH_DD->GetBinContent(hH_DD->GetNbinsX()+1) );
  
  //---- scale to N3LO
  hH_DD->Scale (xsecInclusive);
  
  hH_DD->Draw("same");
  
}