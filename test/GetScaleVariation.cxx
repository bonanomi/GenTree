// 
// Stage 1.0  - 1.1
//    STXS
// 
// 

#include <iostream>
#include <fstream>
#include <sstream>

void GetScaleVariation() {
  
  float c_pt_H_boundaries[] = {10, 60, 120, 200};
  std::vector<float> pt_H_boundaries (c_pt_H_boundaries, c_pt_H_boundaries + sizeof(c_pt_H_boundaries) / sizeof(float) );
  
  float c_njet_boundaries[] = {1, 2, 3};
  std::vector<float> njet_boundaries (c_njet_boundaries, c_njet_boundaries + sizeof(c_njet_boundaries) / sizeof(float) );
  
  std::map< std::pair<int, int> , std::vector<float> > list_variation;
  std::map< std::pair<int, int> , float > nominal;
  
  std::map< std::pair<int, int> , float > max_Delta;
  std::map< std::pair<int, int> , float > Relative_Delta_Smaller;
  std::map< std::pair<int, int> , float > Relative_Delta_Greater;
  
  
  std::ifstream file ("values.txt"); 
  
  std::string buffer;
  int num_i_njet;
  int num_i_pt_H;
  float value;
  
  if(!file.is_open()) {
    std::cerr << "** ERROR: Can't open values.txt for input" << std::endl;
  }
  
  while(!file.eof()) {
    getline(file,buffer);
    std::cout << " buffer = " << buffer << std::endl;
    if (buffer != ""){ ///---> save from empty line at the end!
      std::stringstream line( buffer );      
      line >> num_i_njet; 
      line >> num_i_pt_H; 

      line >> value; 
      nominal[std::pair<int, int> (num_i_pt_H, num_i_njet)] = value;
      
      std::vector <float> vector_values;
      for (int i=0; i<6; i++) {
        line >> value; 
        vector_values.push_back(value);        
      }
      list_variation[std::pair<int, int> (num_i_pt_H, num_i_njet)] = vector_values;
      
      
    } 
  }
  
  
  

  //---- now print
  //
  //---- merge bins according to the edges
  //
  
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  
  for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
    
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size(); i_pt_H++) {
      
      float smaller_nominal = 0;
      float greater_nominal = 0;
      
      for (int j_pt_H = 0; j_pt_H < pt_H_boundaries.size()+1; j_pt_H++) {
        if (j_pt_H<=i_pt_H) {
          smaller_nominal += nominal[std::pair<int, int> (j_pt_H, i_njet)];
        }
        else {
          greater_nominal += nominal[std::pair<int, int> (j_pt_H, i_njet)];
        }
      }
      
      float nominal = smaller_nominal + greater_nominal;
      
      std::cout << " i_njet = " << i_njet << " i_pt_H = " << i_pt_H << " nominal = " << nominal << std::endl;
      
      float Delta_max = 0;
      
      //
      // smaller + greater = constant
      // (smaller+Delta) + (greater-Delta) = constant
      // --> find maximum Delta
      //
      
      for (int i=0; i<6; i++) {
        float smaller_nominal_variation = 0;
        float greater_nominal_variation = 0;
        for (int j_pt_H = 0; j_pt_H < pt_H_boundaries.size()+1; j_pt_H++) {
          if (j_pt_H<=i_pt_H) {
            smaller_nominal_variation += list_variation[std::pair<int, int> (j_pt_H, i_njet)][i];
          }
          else {
            greater_nominal_variation += list_variation[std::pair<int, int> (j_pt_H, i_njet)][i];
          }
        }
        
        float normalization = smaller_nominal_variation + greater_nominal_variation;
        if (normalization!=0) {
          normalization = nominal/normalization;
        }
        else {
          normalization = 1.;
        }
        
//         std::cout << "        normalization = " << normalization << std::endl;
        
        smaller_nominal_variation *= normalization;
        greater_nominal_variation *= normalization;
        
        float Delta = fabs(smaller_nominal_variation - smaller_nominal);
        
//         std::cout << " small/great = " << (smaller_nominal_variation - smaller_nominal) << " / " << (greater_nominal_variation - greater_nominal);
//         std::cout << " --> " << (smaller_nominal-Delta_max)/smaller_nominal;
//         std::cout << " = (" << smaller_nominal << " - " << Delta_max << " ) / "  << smaller_nominal << std::endl;
        
        if (Delta_max < Delta) Delta_max = Delta;
        
      }
      
      max_Delta[std::pair<int, int> (i_pt_H, i_njet)] = Delta_max;
      Relative_Delta_Smaller[std::pair<int, int> (i_pt_H, i_njet)] = (-Delta_max)/smaller_nominal;
      Relative_Delta_Greater[std::pair<int, int> (i_pt_H, i_njet)] = ( Delta_max)/greater_nominal;
      
    }
  }
  
  
  
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  std::cout << " ===================== " << std::endl;
  
  
  //---- now print
  
  for (int i_njet = 0; i_njet < njet_boundaries.size()+1; i_njet++) {
    for (int i_pt_H = 0; i_pt_H < pt_H_boundaries.size(); i_pt_H++) {
      std::cout << " njet:pt_H " << i_njet << " : " << i_pt_H ;
      std::cout << "    smaller +/- " << Relative_Delta_Smaller[std::pair<int, int> (i_pt_H, i_njet)] *100 << " % " ;
      std::cout << "    greater +/- " << Relative_Delta_Greater[std::pair<int, int> (i_pt_H, i_njet)] *100 << " % " ;
//       std::cout << "          Delta = " << max_Delta[std::pair<int, int> (i_pt_H, i_njet)];
      std::cout << std::endl;
      
    }
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