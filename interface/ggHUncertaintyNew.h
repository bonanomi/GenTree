#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

class ggHUncertaintyNew {
public:
  //! constructor
  ggHUncertaintyNew();
  
  virtual ~ggHUncertaintyNew() {}
  
  //---- Fractional uncertainty amplitudes of the "WG1 scheme", the "STXS scheme" and the merged "2017 scheme"
  //---- The six first numbers are the same from each method below, namely the uncertainty amplitude of the jet bins:
  //---- mu, res, mig01, mig12, vbf2j, vbf3j
  //---- The last numbers are pT dependent uncertainies
  std::vector<float> qcd_ggF_uncert_wg1  (int Njets30, float pTH, int STXS);  // 7 nuisances, 5 x jetbin, pTH, qm_t
  std::vector<float> qcd_ggF_uncert_stxs (int Njets30, float pTH, int STXS);  // 8 nuisances, 5 x jetbin, D60, D120, D200
  std::vector<float> qcd_ggF_uncert_2017 (int Njets30, float pTH, int STXS);  // 8 nuisances, 5 x jetbin, pT60, pT120, qm_t
  std::vector<float> qcd_ggF_uncert_jve  (int Njets30, float pTH, int STXS);  // 7 nuisances, 4 x jetbin, pT60, pT120, qm_t
  
  //
  //---- Scale factors defined as "1+uncert", where uncert is the fractional uncertainty amplitude
  //---- This can be treated as an event weight to propagate the uncertainty to any observable/distribution.
  std::vector<float> qcd_ggF_uncertSF_wg1  (int Njets30, float pTH, int STXS_Stage1, float Nsigma=1.0);
  std::vector<float> qcd_ggF_uncertSF_stxs (int Njets30, float pTH, int STXS_Stage1, float Nsigma=1.0);
  std::vector<float> qcd_ggF_uncertSF_2017 (int Njets30, float pTH, int STXS_Stage1, float Nsigma=1.0);
  std::vector<float> qcd_ggF_uncertSF_jve  (int Njets30, float pTH, int STXS_Stage1, float Nsigma=1.0);
  
  
  
  // Cross sections of ggF with =0, =1, and >=2 jets
  // Obtained from Powheg NNLOPS. Scaled to sigma(N3LO) @125.09 = 48.52 pb
  // set as global variables (sorry!) since used both by BLPTW and JVE
  float g_sig0;
  float g_sig1;
  float g_sig_ge2;
  float g_sig_ge1;
  float g_sig_tot;
  float g_sig_vbfTopo;
  float g_sig_ge2noVBF;
  float g_sig_ge1noVBF;
  
  
  
  std::vector<float> blptw(int Njets30);
  float vbf_2j(int STXS);
  float vbf_3j(int STXS);
  float interpol(float x, float x1, float y1, float x2, float y2);
  
  float qm_t(float pT) ;
  float pT200(float pT, int Njets30) ;
  float pT120(float pT, int Njets30) ;
  float pT60(float pT, int Njets30) ;
  float pT10(float pT, int Njets30) ;
  std::vector<float> jetBinUnc(int Njets30, int STXS) ;
  
  
  // Gaussian uncertainty propagation
  // event weihgt = 1.0 + 1-stdDev-fractional-uncertainty-amplitudie * NumberOfStdDev
  std::vector<float> unc2sf(const std::vector<float> &unc, float Nsigma);
  
};


