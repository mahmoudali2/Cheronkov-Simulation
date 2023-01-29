#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction();

    virtual G4VPhysicalVolume *Construct();
};
#endif