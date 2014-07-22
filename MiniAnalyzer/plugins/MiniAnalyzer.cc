// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

// TFile Service and root
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"

//
// The class MiniAnalyzer is declered here. It inherts from edm::EDAnalyzer.  
//

class MiniAnalyzer : public edm::EDAnalyzer { // class declaration MiniAnalyzer derives from edm::EDAnalyzer
public:
  explicit MiniAnalyzer(const edm::ParameterSet&); // delcare the constructor
  ~MiniAnalyzer(); // delcare the destructor

private:
  // ---------declare the member functions (aka methods) ------------------
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override; 
  void beginJob();
  void BookTuples(); 

  // ----------declare the member data ---------------------------
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::TauCollection> tauToken_;
  edm::EDGetTokenT<pat::PhotonCollection> photonToken_;
  edm::EDGetTokenT<pat::JetCollection> jetToken_;
  edm::EDGetTokenT<pat::JetCollection> fatjetToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_;

  // ----------declare the FileService needed to write out a root file
  edm::Service<TFileService> fs; 

  // ----------declare pointer to TTree object (ntuple is an instantiation of the TTree class)
  TTree* ntuple; //I know its not really an ntuple but... 

  // ----------declare the ntuple variables
  double t_Pt, t_Eta, t_Phi;
  unsigned int nleadjet;
};

//
// -------------Now define the constructor/destructor and member functions
//
MiniAnalyzer::MiniAnalyzer(const edm::ParameterSet& iConfig): // define the constructor
 
  // Not sure what any of this does but its needed when using getByToken to get at data
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  tauToken_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("taus"))),
  photonToken_(consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("photons"))),
  jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"))),
  fatjetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("fatjets"))),
  metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("mets")))
{
}

MiniAnalyzer::~MiniAnalyzer() 
{
}

void MiniAnalyzer::beginJob() { 
  BookTuples(); // Book the tuples

}

void MiniAnalyzer::BookTuples() {

  // Create two ntuples (Trees) one to collect events 
  ntuple = fs->make<TTree>("ntuple","CSA14tuple");

  // This just saves the ntuple to disk 
  ntuple->SetAutoSave(10000);
 
  ntuple->Branch("t_cutPt",  &t_Pt,  "t_Pt/D");
  ntuple->Branch("t_cutEta", &t_Eta, "t_Eta/D");
  ntuple->Branch("t_cutPhi", &t_Phi, "t_Phi/D");
  ntuple->Branch("nleadjet", &nleadjet, "nleadjet/I");

}

void MiniAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) //Called once for every event
{
  // So you don't have to type std:: for every member
  using namespace std;
  using namespace edm;

  // Grab the data objects via the getByToken method in edm::Event object passed by reference in argumet above
  Handle<pat::JetCollection> jets; 
  iEvent.getByToken(jetToken_, jets);

  nleadjet = 0; // make sure the nleadjet is zeroed before the event loop
  cout << "This event has "<< jets->size()<<" jets"<<endl; // sanity check

  for (vector<pat::Jet>::const_iterator it=jets->begin(); it!=jets->end(); it++) {// iterator method of looping
    t_Pt  = it->pt();
    t_Eta = it->eta();
    t_Phi = it->phi();

    if ( t_Pt <= 50.0 && fabs(t_Eta)< 2.4 ) nleadjet++; //If condition satisfied augment counter
    ntuple->Fill();
  }
  cout<<"    But only "<<nleadjet<<" of these jets have a pt>50 && |eta|<2.4"<<endl;

}
//define this as a plug-in
DEFINE_FWK_MODULE(MiniAnalyzer);
