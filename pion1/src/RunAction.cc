#include "RunAction.hh"
#include "globals.hh"
#include "G4Run.hh"
#include "Run.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"

RunAction::RunAction( SteppingAction* steppingAction ) : G4UserRunAction(),
                                                         fSteppingAction( steppingAction ) {

    G4AnalysisManager *A_mu = G4AnalysisManager::Instance();
    A_mu->CreateNtuple("nu angle", "nu angle");
    A_mu->CreateNtupleDColumn("Anti_nu_mu_15GeV_det");
    A_mu->FinishNtuple();
/*
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->CreateNtuple("Z coordinate", "Z coordinate");
    man->CreateNtupleDColumn("Coordinate_for_10GeV");    
    man->FinishNtuple(0);
*/
/*
    G4AnalysisManager *A_nu = G4AnalysisManager::Instance();
    A_nu->CreateNtuple("nu angle", "nu angle");
    A_nu->CreateNtupleDColumn("Angle_10GeV_nu");
    A_nu->FinishNtuple(0);
*/
}

RunAction::~RunAction() {}

G4Run* RunAction::GenerateRun() {
  return new Run;
}

void RunAction::BeginOfRunAction( const G4Run* aRun ) {
  G4cout << "### Run " << aRun->GetRunID() << " starts." << G4endl;
  if ( fSteppingAction ) {
    fSteppingAction->Initialize();
    Run* run = const_cast< Run* >( static_cast< const Run* >( aRun ) );
    if ( run != nullptr ) fSteppingAction->SetRunPointer( run );
  }

    G4AnalysisManager *A_mu = G4AnalysisManager::Instance();
    A_mu->OpenFile("angleMU.root");

/*
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->OpenFile("coor.root");
*/
/*    G4AnalysisManager *A_nu = G4AnalysisManager::Instance();
    A_nu->OpenFile("angleNU.root");
*/
}

void RunAction::EndOfRunAction( const G4Run* aRun ) {
  const Run* run = static_cast< const Run* >( aRun );
  if ( run == nullptr  ||  run->GetNumberOfEvent() == 0 ) return;
  if ( IsMaster() ) run->PrintInfo();

    G4AnalysisManager *A_mu = G4AnalysisManager::Instance();
    A_mu->Write();
    A_mu->CloseFile();

/*
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
*/
/*    G4AnalysisManager *A_nu = G4AnalysisManager::Instance();
    A_nu->Write();
    A_nu->CloseFile();
*/}


