
#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}
MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

// defining the track or the particle hits in the detector 
// prestep for the initial hit 
// poststep for the final hit
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

//    G4cout << "Photon position" << posPhoton << G4endl;
// this get the precise position for the photon, but that not applicable in real experiments

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

//    G4cout << "Copy Number:" << copyNo << G4endl;
// this get you the detector number like "4913"

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout << "Detector position: " << posDetector << G4endl;
// this print the position of the detector which had been hitted.   

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
// calling the ntuple 
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector(0)); // column Id = 0
    man->FillNtupleDColumn(2, posDetector(1)); // column Id = 0
    man->FillNtupleDColumn(3, posDetector(2)); // column Id = 0
    man->AddNtupleRow(0);

}
