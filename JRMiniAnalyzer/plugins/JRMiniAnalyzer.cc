// -*- C++ -*-
//
// Package:    Test/JRMiniAnalyzer
// Class:      JRMiniAnalyzer
// 
/**\class JRMiniAnalyzer JRMiniAnalyzer.cc Test/JRMiniAnalyzer/plugins/JRMiniAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jorge Rodriguez
//         Created:  Mon, 07 Jul 2014 14:12:51 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
//Stuff Jorge added: From miniAOD workbook example .cc file
//
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"


// Stuff Jorge added
#define THIS_IS_AN_EVENT_EXAMPLE
//#include "DataFormats/PatCandidates/interface/Muon.h"


//
// class declaration
//

class JRMiniAnalyzer : public edm::EDAnalyzer {
   public:
      explicit JRMiniAnalyzer(const edm::ParameterSet&);
      ~JRMiniAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
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
JRMiniAnalyzer::JRMiniAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


JRMiniAnalyzer::~JRMiniAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JRMiniAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace std;
  using namespace edm;

#ifdef THIS_IS_AN_EVENT_EXAMPLE
  // Check slimmed Muons
   Handle< std::vector<pat::Muon> > muons;
   iEvent.getByLabel("slimmedMuons",muons);
   cout << "Number-O-Muons "<< muons->size()<<endl;

  // Check slimmed Electrons
   Handle< std::vector<pat::Electron> > electrons;
   iEvent.getByLabel("slimmedElectrons",electrons);
   cout << "Number-O-Electrons "<< electrons->size()<<endl;

  // Check slimmed Taus
   Handle< std::vector<pat::Tau> > taus;
   iEvent.getByLabel("slimmedTaus",taus);
   cout << "Number-O-Taus "<< taus->size()<<endl;

  // Check slimmed Photons
   Handle< std::vector<pat::Photon> > photons;
   iEvent.getByLabel("slimmedPhotons",photons);
   cout << "Number-O-Photons "<< photons->size()<<endl;

  // Check slimmed Jets
   Handle< std::vector<pat::Jet> > jets;
   iEvent.getByLabel("slimmedJets",jets);
   cout << "Number-O-Jets "<< jets->size()<<endl;

   /*  // Check slimmed JetsAK8
   Handle< std::vector<pat::Jet> > jetsAK8;
   iEvent.getByLabel("slimmedJetsAK8",jetsAK8);
   cout << "Number-O-JetsAK8 "<< jetsAK8->size()<<endl;
   */

  // Check slimmed METs
   Handle< std::vector<pat::MET> > METs;
   iEvent.getByLabel("slimmedMETs",METs);
   cout << "Number-O-METs "<< METs->size()<<endl; 


#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
JRMiniAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JRMiniAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
JRMiniAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
JRMiniAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
JRMiniAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
JRMiniAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JRMiniAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JRMiniAnalyzer);
