// -*- C++ -*-
//
// Package:    GeneratorInterface/GenTree
// Class:      GenTree
// 
/**\class GenTree GenTree.cc GeneratorInterface/GenTree/plugins/GenTree.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrea Massironi
//         Created:  Tue, 31 Jan 2017 13:45:54 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"



#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


#include "TTree.h"



#include "SimDataFormats/HTXS/interface/HiggsTemplateCrossSections.h"


//---- to get weights
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"



//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class GenTree : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit GenTree(const edm::ParameterSet&);
      ~GenTree();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      
      
      TTree *outTree;
      int _jets30;
      int _stage0_cat;
      int _stage1_cat_pTjet30GeV;
      float _weight;
      
      float _higgs_pt;
      float _higgs_eta;
      
      float _jet1_pt;
      float _jet1_eta;
      
      std::vector<float> _weights_LHE;
      
      edm::EDGetTokenT<HTXS::HiggsClassification> htxsSrc_;
      edm::EDGetTokenT<GenEventInfoProduct> GenInfoT_ ;
      edm::EDGetTokenT<LHEEventProduct> LHEInfoT_ ;
      
      const LHEEventProduct* LHEInfoHandle_;    
      
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GenTree::GenTree(const edm::ParameterSet& iConfig)
{
  
  htxsSrc_ = consumes<HTXS::HiggsClassification>(edm::InputTag("rivetProducerHTXS","HiggsClassification"));
  
  GenInfoT_ = consumes<GenEventInfoProduct>(edm::InputTag("generator"));

//   LHEInfoT_ = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"));
  LHEInfoT_ = consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("LHERunInfo"));
  
   
  
  
  //now do what ever initialization is needed
  usesResource("TFileService");
  
  edm::Service<TFileService> fs;
  
  outTree = fs->make<TTree>("gentree","gentree");
  outTree->Branch("jets30",         &_jets30,      "jets30/i");
  outTree->Branch("stage0_cat",                &_stage0_cat,             "stage0_cat/i");
  outTree->Branch("stage1_cat_pTjet30GeV",     &_stage1_cat_pTjet30GeV,  "stage1_cat_pTjet30GeV/i");
  outTree->Branch("weight",         &_weight,      "weight/F");
  
  outTree->Branch("higgs_pt",          &_higgs_pt,      "higgs_pt/F");
  outTree->Branch("higgs_eta",         &_higgs_eta,     "higgs_eta/F");
  
  outTree->Branch("jet1_pt",          &_jet1_pt,      "jet1_pt/F");
  outTree->Branch("jet1_eta",         &_jet1_eta,     "jet1_eta/F");
  
  outTree->Branch("weights_LHE",         &_weights_LHE  );
  
  
  
  
}


GenTree::~GenTree()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   _jets30 = 0;
   
   edm::Handle<HTXS::HiggsClassification> htxs;
   iEvent.getByToken(htxsSrc_,htxs);
   _stage0_cat = htxs->stage0_cat;
   _stage1_cat_pTjet30GeV = htxs->stage1_cat_pTjet30GeV;
   _jets30     = (htxs->jets30).size();
   
   edm::Handle<GenEventInfoProduct> genEvtInfo;
   iEvent.getByToken(GenInfoT_, genEvtInfo);
   _weight = genEvtInfo->weight();
  
   
   edm::Handle<LHEEventProduct>   productLHEHandle;
   iEvent.getByToken(LHEInfoT_, productLHEHandle);
   
   LHEInfoHandle_ = (productLHEHandle.product());
   
   _weights_LHE.clear();
   int num_whichWeight = LHEInfoHandle_->weights().size();
   for (int i=0; i<num_whichWeight; i++) {
     _weights_LHE.push_back(LHEInfoHandle_->weights()[i].wgt);
   }
   
   
   
   _higgs_pt  = htxs->higgs.pt();
   _higgs_eta = htxs->higgs.eta();

   if ((htxs->jets25).size() >= 1) {
     _jet1_pt  = (htxs->jets25).at(0).pt();
     _jet1_eta = (htxs->jets25).at(0).eta();
   }
   else {     
     _jet1_pt  = -99;
     _jet1_eta = -99;
   }
   
   outTree->Fill();
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
GenTree::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenTree::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenTree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenTree);
