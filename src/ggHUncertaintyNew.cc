// 
// 
// 

#include "GeneratorInterface/GenTree/interface/ggHUncertaintyNew.h"

// 
// typedef std::vector<float> std::vector<float>;
//
// The input kinematics should be based on the truth quantites of
// defined according to:
// https://svnweb.cern.ch/cern/wsvn/lhchiggsxs/repository/TemplateXS/HiggsTemplateCrossSections.h
// namely Higgs boson pT (in GeV!), jet multiplicity with 30 GeV pT threshold
// of jets built ignoring all stable particles originating from the Higgs boson decay
// and the Stage1 STXS category
// In the code above, these quanties are part of the HiggsClassification struct and called:
//   higgs.Pt(), jets30.size(), stage1_cat_pTjet30GeV
//
// Note: the stage 1 STXS index is only used to determine if the current event fulfil the
//       VBF topology selection. I.e. only categories
//         GG2H_VBFTOPO_JET3VETO = 101, GG2H_VBFTOPO_JET3 = 102,
//       are checked
//
// Dag Gillberg, March 21, 2017
// 



ggHUncertaintyNew::ggHUncertaintyNew() {
  
//   
//   tot =  30.117 + 12.928 + 5.475  = 48.52
//   mH 125.09 @ N3LO accuracy
//   
  
  g_sig0 = 30.117;
  g_sig1 = 12.928;
  g_sig_ge2 = 5.475;
  g_sig_ge1 = g_sig1+g_sig_ge2;
  g_sig_tot = g_sig0+g_sig_ge1;
  g_sig_vbfTopo = 0.630;
  g_sig_ge2noVBF = g_sig_ge2-g_sig_vbfTopo;
  g_sig_ge1noVBF = g_sig_ge1-g_sig_vbfTopo;
  
}



//----
//---- Jet bin uncertainties 
std::vector<float> ggHUncertaintyNew::blptw(int Njets30) {
  
  static std::vector<float> sig({g_sig0,g_sig1,g_sig_ge2noVBF}); // NNLOPS subtracting VBF
  
  // BLPTW absolute uncertainties in pb
  static std::vector<float> yieldUnc({ 1.12, 0.66, 0.42});
  static std::vector<float> resUnc  ({ 0.03, 0.57, 0.42});
  static std::vector<float> cut01Unc({-1.22, 1.00, 0.21});
  static std::vector<float> cut12Unc({    0,-0.86, 0.86});
  
  // account for missing EW+quark mass effects by scaling BLPTW total cross section to sigma(N3LO)
  float sf = 48.52/47.4;
  int jetBin = (Njets30 > 1 ? 2 : Njets30);
  float normFact = sf/sig[jetBin];
  
  return { yieldUnc[jetBin]*normFact, 
    resUnc[jetBin]*normFact,
    cut01Unc[jetBin]*normFact,
    cut12Unc[jetBin]*normFact };
}

float ggHUncertaintyNew::vbf_2j(int STXS) {
  if (STXS==131 || STXS == 141) return 0.200; // 20.0%
  return 0.0; // Events with no VBF topology have no VBF uncertainty
}

float ggHUncertaintyNew::vbf_3j(int STXS) {
  if (STXS==132) return -0.320; // GG2H_VBFTOPO_JET3VETO, tot unc 38%
  if (STXS==142) return  0.235; // GG2H_VBFTOPO_JET3, tot unc 30.4%
  return 0.0; // Events with no VBF topology have no VBF uncertainty
}

float ggHUncertaintyNew::interpol(float x, float x1, float y1, float x2, float y2) {
  if (x<x1) return y1;
  if (x>x2) return y2;
  return y1+(y2-y1)*(x-x1)/(x2-x1);
}



// Difference between finite top mass dependence @NLO vs @LO evaluated using Powheg NNLOPS
// taken as uncertainty on the treamtment of top mass in ggF loop
float ggHUncertaintyNew::qm_t(float pT) {
  return interpol(pT,160,0.0,500,0.37);
}


// migration uncertaitny around the 200 GeV boundary
float ggHUncertaintyNew::pT200(float pT, int Njets30) {
  if      (Njets30==0) return 0;
  else if (Njets30==1) return interpol(pT, 190, -0.0012, 210, 0.074);
  else if (Njets30==2) return interpol(pT, 190, -0.0034, 210, 0.054);
  else                 return interpol(pT, 190, -0.0091, 210, 0.046);
//   if (Njets30>=3) return interpol(pT, 190, -0.0091, 210, 0.046);
}

// njet:pt_H 1 : 3    smaller +/- -0.126483 %     greater +/- 7.42588 % 
// njet:pt_H 2 : 3    smaller +/- -0.341676 %     greater +/- 5.44669 % 
// njet:pt_H 3 : 3    smaller +/- -0.905543 %     greater +/- 4.56983 % 


// migration uncertaitny around the 120 GeV boundary
float ggHUncertaintyNew::pT120(float pT, int Njets30) {
  if (Njets30==0) return 0;
  return interpol(pT,90,-0.016,160,0.14);
}

// migration uncertaitny around the 60 GeV boundary
float ggHUncertaintyNew::pT60(float pT, int Njets30) {
  if (Njets30==0) return 0;
  if (Njets30==1) return interpol(pT,20,-0.1,100,0.1);
  return interpol(pT,0,-0.1,180,0.10); // >=2 jets
}

// migration uncertaitny around the 10 GeV boundary (only for 0 jet bin)
float ggHUncertaintyNew::pT10(float pT, int Njets30) {
  if (Njets30!=0) return 0;
  return interpol(pT, 9, -0.25, 11, 0.09);
}



std::vector<float> ggHUncertaintyNew::jetBinUnc(int Njets30, int STXS) {
  std::vector<float> result = blptw(Njets30);
  result.push_back(vbf_2j(STXS));
  result.push_back(vbf_3j(STXS));
  // set jet bin uncertainties to zero if we are in the VBF phase-space
  if (result.back()!=0.0) result[0]=result[1]=result[2]=result[3]=0.0;
  return result;
}







std::vector<float> ggHUncertaintyNew::qcd_ggF_uncert_wg1(int Njets30, float pT, int STXS) {
  std::vector<float> result = jetBinUnc(Njets30,STXS);
  
  // High pT uncertainty 
  static float y1_1 = -0.12, y2_1 = 0.16, x2_1 = 150;
  static float y1_ge2 = -0.12, y2_ge2 = 0.16, x2_ge2 = 225;
  float pTH_unc = 0.0;
  if      (Njets30==1) pTH_unc = interpol(pT,0,y1_1,x2_1,y2_1);
  else if (Njets30>=2) pTH_unc = interpol(pT,0,y1_ge2,x2_ge2,y2_ge2);
  result.push_back(pTH_unc);
  
  // finite top mass uncertainty
  result.push_back(qm_t(pT));
  
  return result;
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncert_stxs(int Njets30, float pT, int STXS) {
  std::vector<float> result = jetBinUnc(Njets30,STXS);
  // Dsig60, Dsig120 and Dsig200 are extracted from Powheg NNLOPS
  // scale variations (envelope of 26 variations)
  //   sig(60,200)  = 9.095 +/- 1.445 pb, BLPTW 10.9%
  //   sig(120,200) = 1.961 +/- 0.401 pb, BLPTW 13.1%
  //   sig(200,inf) = 0.582 +/- 0.121 pb, BLPTW 15.1%
  static float sig0_60=8.719, sig60_200=9.095, sig120_200=1.961, 
  sig0_120=sig0_60+sig60_200-sig120_200, sig200_plus=0.582; // 0.121 (-) 0.151*0.582
  static float Dsig60_200=1.055, Dsig120_200=0.206, Dsig200_plus=0.0832; // with 2M evts, and subtraction
  float dsig60=0, dsig120=0, dsig200=0;
  if (Njets30>=1) {
    if      (pT<60)  dsig60=-Dsig60_200/sig0_60;  // -17.2%
    else if (pT<200) dsig60=Dsig60_200/sig60_200; // +16.0%
    
    if      (pT<120) dsig120 = -Dsig120_200/sig0_120;   //  -2.6%
    else if (pT<200) dsig120 =  Dsig120_200/sig120_200; // +20.8%
    
    if (pT>200) dsig200=Dsig200_plus/sig200_plus; // +14.3%
  }
  result.push_back(dsig60);
  result.push_back(dsig120);
  result.push_back(dsig200);
  return result;
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncert_2017(int Njets30, float pT, int STXS) {
  std::vector<float> result = jetBinUnc(Njets30,STXS);
  result.push_back(pT60(pT,Njets30));
  result.push_back(pT120(pT,Njets30));
  result.push_back(qm_t(pT));
  return result;
}


std::vector<float> ggHUncertaintyNew::qcd_ggF_uncert_2017_New(int Njets30, float pT, int STXS) {
  std::vector<float> result = jetBinUnc(Njets30,STXS);
  result.push_back(pT10(pT,Njets30));
  result.push_back(pT60(pT,Njets30));
  result.push_back(pT120(pT,Njets30));
  result.push_back(pT200(pT,Njets30));
  result.push_back(qm_t(pT));
  return result;
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncert_jve(int Njets30, float pT, int STXS) {
  std::vector<float> result;
  // Central values for eps0 and eps1 from Powheg NNLOPS
  //   eps0 = 0.617 +- 0.012 <= from Fabrizio and Pier
  //   eps1 = 0.681 +- 0.057 <= from Fabrizio and Pier
  // and setting inclusive uncertainty to 3.9% (YR4 for N3LO)
  static float D01=g_sig_tot*0.012, D12=g_sig_ge1*0.057;
  
  result.push_back(0.039); // YR4 inclusive cross section (Gaussian)
  
  // mig 0 -> 1 from eps0. Taking out VBF topology piece
  float d01 = Njets30==0 ? -D01/g_sig0 : D01/g_sig_ge1noVBF; 
  result.push_back(d01);
  
  float d12 = 0.0;
  if      (Njets30==1) d12 = -D12/g_sig1;
  else if (Njets30>=2) d12 =  D12/g_sig_ge2noVBF;
  result.push_back(d12);
  
  // VBF-topology
  result.push_back(vbf_2j(STXS));
  result.push_back(vbf_3j(STXS));
  // set jet bin uncertainties to zero if we are in the VBF phase-space
  if (result.back()!=0.0) result[0]=result[1]=result[2]=0.0;
  
  // pTH uncertainties from 2017 scheme
  result.push_back(pT60(pT,Njets30));
  result.push_back(pT120(pT,Njets30));
  result.push_back(qm_t(pT));
  return result;
}


// Gaussian uncertainty propagation
// event weihgt = 1.0 + 1-stdDev-fractional-uncertainty-amplitudie * NumberOfStdDev
std::vector<float> ggHUncertaintyNew::unc2sf(const std::vector<float> &unc, float Nsigma) {
  std::vector<float> sfs; 
  for (auto u:unc) sfs.push_back(1.0+Nsigma*u);
  return sfs;
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncertSF_wg1(int Njets30, float pT, int STXS_Stage1, float Nsigma) {
  return unc2sf(qcd_ggF_uncert_wg1(Njets30,pT,STXS_Stage1),Nsigma);
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncertSF_stxs(int Njets30, float pT, int STXS_Stage1, float Nsigma) {
  return unc2sf(qcd_ggF_uncert_stxs(Njets30,pT,STXS_Stage1),Nsigma);
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncertSF_2017(int Njets30, float pT, int STXS_Stage1, float Nsigma) {
  return unc2sf(qcd_ggF_uncert_2017(Njets30,pT,STXS_Stage1),Nsigma);
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncertSF_jve(int Njets30, float pT, int STXS_Stage1, float Nsigma) {
  return unc2sf(qcd_ggF_uncert_jve(Njets30,pT,STXS_Stage1),Nsigma);
}

std::vector<float> ggHUncertaintyNew::qcd_ggF_uncertSF_2017_New(int Njets30, float pT, int STXS_Stage1, float Nsigma) {
  return unc2sf(qcd_ggF_uncert_2017_New(Njets30,pT,STXS_Stage1),Nsigma);
}

