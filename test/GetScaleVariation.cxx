// 
// Stage 1.0  - 1.1
//    STXS
// 
// 

#include <iostream>
#include <fstream>
#include <sstream>

void GetScaleVariation() {
    
  std::map< int , std::vector<float> > list_variation;
  std::map< int, float > nominal;
  
  std::map< int , float > max_Delta;
  std::map< int , float > Relative_Delta_Smaller;
  std::map< int , float > Relative_Delta_Greater;
  
  /************************************************************************************************************************
   ********************************************  STXS STAGE 1.1 BINS  *****************************************************
  
                                                GG2H_FWDH = 100,
                                                GG2H_PTH_GE200 = 150,

                                                GG2H_PTH_0_200_0J_PTH_0_10 = 102,
                                                GG2H_PTH_0_200_0J_PTH_10_200 = 103,

                                                GG2H_PTH_0_200_1J_PTH_0_60 = 111,
                                                GG2H_PTH_0_200_1J_PTH_60_120 = 112,
                                                GG2H_PTH_0_200_1J_PTH_120_200 = 113,

                                                GG2H_PTH_0_200_GE2J_MJJ_0_350_PTH_0_60 = 121,
                                                GG2H_PTH_0_200_GE2J_MJJ_0_350_PTH_60_120 = 122,
                                                GG2H_PTH_0_200_GE2J_MJJ_0_350_PTH_120_200 = 123,

                                                GG2H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_0_25 = 131,
                                                GG2H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_GE25 = 132,

                                                GG2H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_0_25 = 141,
                                                GG2H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_GE25 = 142,

   ************************************************************************************************************************
  *************************************************************************************************************************/
  
  std::vector< std::string > stxs1p1_cuts;
  // stxs1p1_cuts.push_back("100");
  stxs1p1_cuts.push_back("102");
  stxs1p1_cuts.push_back("103");
  stxs1p1_cuts.push_back("111");
  stxs1p1_cuts.push_back("112");
  stxs1p1_cuts.push_back("113");
  stxs1p1_cuts.push_back("121");
  stxs1p1_cuts.push_back("122");
  stxs1p1_cuts.push_back("123");
  stxs1p1_cuts.push_back("131");
  stxs1p1_cuts.push_back("132");
  stxs1p1_cuts.push_back("141");
  stxs1p1_cuts.push_back("142");
  stxs1p1_cuts.push_back("150");

  std::ifstream file ("scale_variations.txt"); 
  
  std::string buffer;
//  int num_i_njet;
//  int num_i_pt_H;
  int stxs1p1_cut;
  float value;
  
  if(!file.is_open()) {
    std::cerr << "** ERROR: Can't open scale_variations.txt for input" << std::endl;
  }
  
  while(!file.eof()) {
    getline(file,buffer);
    std::cout << " buffer = " << buffer << std::endl;
    if (buffer != ""){ ///---> save from empty line at the end!
      std::stringstream line( buffer );      
      line >> stxs1p1_cut;//num_i_njet; 
      // line >> num_i_pt_H; 

      line >> value; 
      nominal[stxs1p1_cut] = value;
      
      std::vector <float> vector_values;
      for (int i=0; i<6; i++) {
        line >> value; 
        vector_values.push_back(value);        
      }
      list_variation[stxs1p1_cut] = vector_values;
      
      
    } 
  }

  
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;

  for (int iCut = 0; iCut < stxs1p1_cuts.size(); iCut++) {
    float smaller_nominal = 0;
    float greater_nominal = 0;
    int stxs1p1 = std::stoi(stxs1p1_cuts.at(iCut));

    if (stxs1p1 == 102) //10GeV
    {
      smaller_nominal += nominal[102];
      greater_nominal += nominal[103];
    }
    if (stxs1p1 == 103) //200GeV
    {
      smaller_nominal += nominal[102] + nominal[103];
      greater_nominal += 0.0;
    }
    if (stxs1p1 == 111) //60GeV
    {
      smaller_nominal += nominal[111];
      greater_nominal += nominal[112] + nominal[113];
    }
    if (stxs1p1 == 112) //120GeV
    {
      smaller_nominal += nominal[111] + nominal[112];
      greater_nominal += nominal[113];
    }
    if (stxs1p1 == 113) //200GeV
    {
      smaller_nominal += nominal[111] + nominal[112] + nominal[113];
      greater_nominal += 0.0;
    }
    if (stxs1p1 == 121) //60GeV
    {
      smaller_nominal += nominal[121];
      greater_nominal += nominal[122] + nominal[123];
    }
    if (stxs1p1 == 122) //120GeV
    {
      smaller_nominal += nominal[121] + nominal[122];
      greater_nominal += nominal[123];
    }
    if (stxs1p1 == 123) //200GeV
    {
      smaller_nominal += nominal[121] + nominal[122] + nominal[123];
      greater_nominal += 0.0;
    }
    if (stxs1p1 == 131) //200GeV, 2jets VBF
    {
      smaller_nominal += nominal[131];
      greater_nominal += nominal[132];
    }
    if (stxs1p1 == 132) //200GeV, 2jets VBF
    {
      smaller_nominal += nominal[131] + nominal[132];
      greater_nominal += 0.0;
    }
    if (stxs1p1 == 141) //200GeV, 2jets VBF
    {
      smaller_nominal += nominal[141];
      greater_nominal += nominal[142];
    }
    if (stxs1p1 == 142) //200GeV, 2jets VBF
    {
      smaller_nominal += nominal[141] + nominal[142];
      greater_nominal += 0.0;
    }
    if (stxs1p1 == 150)
    {
      smaller_nominal += nominal[150];
      greater_nominal += 0.;
    }

    float nominal = smaller_nominal + greater_nominal;

    std::cout << " STXS1.1 = " << stxs1p1 << " nominal = " << nominal << std::endl;

    float Delta_max = 0;
    for (int i=0; i<6; i++) {
      float smaller_nominal_variation = 0;
      float greater_nominal_variation = 0;   
      if (stxs1p1 == 102) //10GeV
      {
        smaller_nominal_variation += list_variation[102][i];
        greater_nominal_variation += list_variation[103][i];
      }
      if (stxs1p1 == 103) //200GeV
      {
        smaller_nominal_variation += list_variation[102][i] + list_variation[103][i];
        greater_nominal_variation += 0.0;
      }
      if (stxs1p1 == 111) //60GeV
      {
        smaller_nominal_variation += list_variation[111][i];
        greater_nominal_variation += list_variation[112][i] + list_variation[113][i];
      }
      if (stxs1p1 == 112) //120GeV
      {
        smaller_nominal_variation += list_variation[111][i] + list_variation[112][i];
        greater_nominal_variation += list_variation[113][i];
      }
      if (stxs1p1 == 113) //200GeV
      {
        smaller_nominal_variation += list_variation[111][i] + list_variation[112][i] + list_variation[113][i];
        greater_nominal_variation += 0.0;
      }
      if (stxs1p1 == 121) //60GeV
      {
        smaller_nominal_variation += list_variation[121][i];
        greater_nominal_variation += list_variation[122][i] + list_variation[123][i];
      }
      if (stxs1p1 == 122) //120GeV
      {
        smaller_nominal_variation += list_variation[121][i] + list_variation[122][i];
        greater_nominal_variation += list_variation[123][i];
      }
      if (stxs1p1 == 123) //200GeV
      {
        smaller_nominal_variation += list_variation[121][i] + list_variation[122][i] + list_variation[123][i];
        greater_nominal_variation += 0.0;
      }
      if (stxs1p1 == 131) //200GeV, 2jets VBF
      {
        smaller_nominal_variation += list_variation[131][i];
        greater_nominal_variation += list_variation[132][i];
      }
      if (stxs1p1 == 132) //200GeV, 2jets VBF
      {
        smaller_nominal_variation += list_variation[131][i] + list_variation[132][i];
        greater_nominal_variation += 0.0;
      }
      if (stxs1p1 == 141) //200GeV, 2jets VBF
      {
        smaller_nominal_variation += list_variation[141][i];
        greater_nominal_variation += list_variation[142][i];
      }
      if (stxs1p1 == 142) //200GeV, 2jets VBF
      {
        smaller_nominal_variation += list_variation[141][i] + list_variation[142][i];
        greater_nominal_variation += 0.0;
      }
      if (stxs1p1 == 150)
      {
        smaller_nominal_variation += list_variation[150][i];
        greater_nominal_variation += 0.;
      }     
    

    float normalization = smaller_nominal_variation + greater_nominal_variation;
    if (normalization!=0) {
      normalization = nominal/normalization;
    }
    else {
      normalization = 1.;
    }
            
    smaller_nominal_variation *= normalization;
    greater_nominal_variation *= normalization;
    
    float Delta = fabs(smaller_nominal_variation - smaller_nominal);
    
    if (Delta_max < Delta) Delta_max = Delta;
    }

    max_Delta[stxs1p1] = Delta_max;
    Relative_Delta_Smaller[stxs1p1] = (-Delta_max)/smaller_nominal;
    Relative_Delta_Greater[stxs1p1] = ( Delta_max)/greater_nominal;

  }

  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  
  
  //---- now print
  for (int iCut = 0; iCut < stxs1p1_cuts.size(); iCut++) {
    int stxs1p1 = std::stoi(stxs1p1_cuts.at(iCut));
    std::cout << "STXS1.1: " << stxs1p1 << " ";
    std::cout << "    smaller +/- " << Relative_Delta_Smaller[stxs1p1] *100 << " % " ;
    std::cout << "    greater +/- " << Relative_Delta_Greater[stxs1p1] *100 << " % " ;
    std::cout << std::endl;

  }  
  
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
  
  
}