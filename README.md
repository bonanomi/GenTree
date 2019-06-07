# GenTree
## Fork from A. Massironi's repo [GenTree](https://github.com/amassiro/GenTree).

Instructions
====

See
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsTemplateCrossSection
    
Install:

    cmsrel CMSSW_10_3_1
    cd CMSSW_10_3_1/src
    cmsenv
    
    // To work with the CJLST framework, follow:
    // [this link](https://github.com/CJLST/ZZAnalysis#zzanalysis) to install it.
    
 **NOTE:** Set up CMSSW_10_3_1 with the CJLST framework, as described above, to work with STXS Stage 1.1 bins. Otherwise the [GenTree](https://github.com/bonanomi/GenTree/blob/CJLST/plugins/GenTree.cc#L176) plugin will not work.

    // Retrieve the HTXS package and compile
    // Already implemented in CMSSW > 8.X
    // Merge not necessary, everything should work
    // git cms-merge-topic -u perrozzi:HTXS_clean
    
    cd GeneratorInterface
    
    git clone https://github.com/bonanomi/GenTree.git
    
    cd ..
    
    scramv1 b -j 10 
    
## Uncertainties for STXS Stage 1.1 
The following code allows to compute the theoretical uncertainties associated to each STXS Stage 1.1 bin.
The code follows the *ad interim scheme 2017* presented in [these slides](https://indico.cern.ch/event/628660/contributions/2593406/attachments/1459912/2255407/May-16-HIG_Massironi.pdf).

The `TTrees`  used for the study are constructed starting from MINIAOD files, using the `GenTree_*_cfg.py` scripts present in [`/test`](https://github.com/bonanomi/GenTree/tree/CJLST/test).
In the `/test` folder there are several `GenTree_*_cfg.py` scripts, which allow to create the `TTrees` for different MC generators. 
 * Use the MC generator believed to have adequate modelling of the kinematics:
   * For low pT bins, minlo NNLOPS is reccomanded;
   * For VBF phase space aMC@NLO and HJJ are reccomanded;
Note that the uncertainties are not expected to depend on the generator. However, some generators are better than others to describe specific phase space regions.

### How to compute uncertainties
In the *ad interim scheme 2017* we have 10 nuisance parameters, namely: 5 jet bins, the fluctuations around each pT value (pT10, pT60, pT120, pT200) and the uncertainty realted to the
quark mass approximation (i.e. uncertainty source from finite top mass @LO vs @NLO, qm_t). 
The jetbins uncertainties are derived from the YR4 recipe, and are calculated with the [`BLPTW` method](https://github.com/bonanomi/GenTree/blob/CJLST/src/ggHUncertaintyNew.cc#L51).
The remaining uncertainty sources are pT dependent and are calculated using scale variations.

### pT related uncertainties
All the pT uncertainties are calculated in the `ggHUncertaintyNew` class with [specific methods](https://github.com/bonanomi/GenTree/blob/CJLST/src/ggHUncertaintyNew.cc#L99). 
More precisely, the workflow used is the following:
 * Compute the xsec value applying different QCD scale variations and compare it to the nominal one. The QCD scales are the renormalization and factorisation ones, contained in the `weight_LHE` branch of the `TTree` created as described above. This step can be done with the [CalculateScaleVariations.cxx](https://github.com/bonanomi/GenTree/blob/CJLST/test/CalculateScaleVariation.cxx#L12) macro. The output is a [`.txt` file](https://github.com/bonanomi/GenTree/blob/CJLST/test/CalculateScaleVariation.cxx#L119) containing the number of entries for each rescaled xsec. One can have a qualitative display of the rescaling effect using the [`Draw*` ] macros, as described in the [/test/README](https://github.com/bonanomi/GenTree/tree/CJLST/test#instructions).

 * Having produced the `.txt` file with all the scaled xsec values, we are now interested in the largest and smallest variations w.r.t. the nominal one. These two values are needed for the calculation of the uncertainties (and are **MC generator dependent!**), hence this step is crucial. To get them one can use the [`GetScaleVariations.cxx`](https://github.com/bonanomi/GenTree/blob/CJLST/test/GetScaleVariation.cxx) macro. The output of this macro gives us the fractional % variations (for each STXS Stage 1.1 bin), which correspond to the "uncertainty band" in which the theoretical xsec lies. We need to feed these two values into the [`interpol()`](https://github.com/bonanomi/GenTree/blob/CJLST/src/ggHUncertaintyNew.cc#L83) function defined in `ggHUncertaintyNew.cc`. More precisely, we have to set the `y1` and `y2` parameters, while `x1` and `x2` define the pT values where we expect the transition to happen. This function implements a smooth transition between the smallest and the largest fractional xsecs around a given pT boundary. It is still not clear (to me) why *this* function, hence take it as a given recipe.

 * Once the `interpol()` functions are set up with the correct values of `y1` and `y2` for the MC generator used, we can add the uncertainties to the `TTree`. To do so, we use the [`addUncertainty`](https://github.com/bonanomi/GenTree/blob/CJLST/bin/addUncertainty.cpp#L120) command, which is set up to create a new `TTree` with the same branches as the original one, plus an additional branch per event containing the uncertainties of the 10 nuisance parameters.  **NOTE:** The `addUncertainty` method actually adds weights to the `TTree` and *not uncertainties* (well, as soon as sigma = 1.0, these weights are simply the uncertainties shifted up by 1.0) ! These weights correspond to the 1 sigma std dev of the fractional uncertainty amplitude and are computed with the [`unc2df` method](https://github.com/bonanomi/GenTree/blob/master/src/ggHUncertaintyNew.cc#L245). The list of assigned uncertainties is defined as follow:

        ggH_mu     = allUnc[0]
        ggH_res    = allUnc[1]
        ggH_mig01  = allUnc[2]
        ggH_mig12  = allUnc[3]
        ggH_VBF2j  = allUnc[4]
        ggH_VBF3j  = allUnc[5]
        ggH_pT10   = allUnc[6]
        ggH_pT60   = allUnc[7]
        ggH_pT120  = allUnc[8]
        ggH_pT200  = allUnc[9]
        ggH_qmtop  = allUnc[10]


## Produce uncertainties for nuisances in STXS Stage 1.1
The `TTree` with the uncertainties can be used to evaluate the fractional uncertainty amplitudes associated to each STXS Stage 1.1 bin per each nuisance parameters. This is done using the [`Table.cxx`](https://github.com/bonanomi/GenTree/blob/CJLST/test/Table.cxx) macro. This macro takes the xsec in the STXS 1.1 bins and evaluates the fractional cross section w.r.t. the nominal one associated to each uncertainty source (nuisance parameters) defined above. This information is stored in the [`matrix_uncertainties_up`](https://github.com/bonanomi/GenTree/blob/CJLST/test/Table.cxx#L121) object. The final output of the macro is a table containing the fractional uncertainty amplitudes (i.e. the weights associated to each nusiance), defined as the % difference between the fractional cross section in that bin and the fractional cross section for each uncertainty source. The total uncertainty in each STXS Stage 1.1 bin is then computed as the sqrt of the squared sum of all the fractional uncertainties.

