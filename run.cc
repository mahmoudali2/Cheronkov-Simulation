// Implementation of the RunAction class
#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
// Generating root file
    man->OpenFile("output.root");
    

// Create ntuples.
// Ntuples ids are generated automatically starting from 0.    
// Create 1st(and the only for our case) ntuple (id = 0) 
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");  // column Id = 0
    man->CreateNtupleDColumn("fY");  // column Id = 1
    man->CreateNtupleDColumn("fZ");  // column Id = 2
    man->FinishNtuple(0);


}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}