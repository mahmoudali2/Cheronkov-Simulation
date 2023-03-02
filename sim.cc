/// Main program of the cherenkov-detector g4 simulation

#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "geometry.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{

// Construct the default run manager
    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new DetectorConstruction()); // Detector construction
    runManager->SetUserInitialization(new MyPhysicsList());  // Physics list
    runManager->SetUserInitialization(new MyActionInitialization());  // User action initialization

    runManager->Initialize();

// Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive();  // Initialize visualization
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();   // Get the pointer to the User Interface manager

//// interactive mode, these commands can be also be put in macro file and be intialized separately
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    ui->SessionStart();

    return 0;
}