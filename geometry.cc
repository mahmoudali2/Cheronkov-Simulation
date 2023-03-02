// Implementation of the Detector Construction class

#include "geometry.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
// Material definition    
    G4NistManager *nist = G4NistManager::Instance();
// silicon di-oxide definition by nist    
    G4Material *SiO2 = new G4Material("SiO2",    // Name of the material
     2.201*g/cm3,                                // its density
      2);                                        // Number of different elements used in material
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);   
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
    
// Water definition by nist   
    G4Material *H2O = new G4Material("H2O",      // Name of the material
     1.000*g/cm3,                                // its density
      2);                                        // Number of different elements used in material
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

// Carbon definition by nist     
    G4Element *C = nist->FindOrBuildElement("C");
    
// Aerogel definition by nist     
    G4Material *Aerogel = new G4Material("Aerogel",   // Name of the material
     0.200*g/cm3,                                     // its density
      3);                                             // Number of different elements used in material
    Aerogel->AddMaterial(SiO2, 62.5*perCent);         // contribution of silicon di-oxide to the Aerogel compound, and its percentage
    Aerogel->AddMaterial(H2O, 37.4*perCent);          // contribution of water to the Aerogel compound, and its percentage
    Aerogel->AddElement(C, 0.1*perCent);              // contribution of carbon to the Aerogel compound, and its percentage
    
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};   //define the energy of the incident particle
    G4double rindexAerogel[2] = {1.1, 1.1};  //define the refractive index of Aerogel
    G4double rindexWorld[2] = {1.0, 1.0};    //define the refractive index of surrounding world


// Adding together each material properties    
    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
    
    Aerogel->SetMaterialPropertiesTable(mptAerogel);
    
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    
    worldMat->SetMaterialPropertiesTable(mptWorld);

// creating the different volumes    
    G4Box *solidWorld = new G4Box("solidWorld",  // its name
    0.5*m, 0.5*m, 0.5*m);                        //its size, 0.5m in both directioms means 1m total in G4

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,  //its solid
    worldMat,                                                      //its material
    "logicWorld");                                                 //its name

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,            // no rotation
    G4ThreeVector(0., 0., 0.),                                     // origin (0, 0, 0)
    logicWorld,                                                    // its logical volume
    "physWorld",                                                   // its name
    0,                                                             // its mother volume
    false,                                                         // no boolean operations
    0,                                                             // copy number
    true);                                                         // checking overlaps
    
    G4Box *solidRadiator = new G4Box("solidRadiator",              // its name
     0.4*m, 0.4*m, 0.01*m);                                        // its size

    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator,  // its solid
    Aerogel,                                                             // its material
    "logicalRadiator");                                                  // its name

    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0,               // no rotation
    G4ThreeVector(0., 0., 0.25*m),                                       // origin (0, 0, 0.25)
    logicRadiator,                                                       // its logical volume
    "physRadiator",                                                      // its name
    logicWorld,                                                          // its mother volume
    false,                                                               // no boolean operations
    0,                                                                   // copy number
    true);                                                               // checking overlaps

    G4Box *solidDetector = new G4Box("solidDetector",                    //its name
    0.005*m, 0.005*m, 0.01*m);                                           //its size

    logicDetector = new G4LogicalVolume(solidDetector,                   // its solid
    worldMat,                                                            // its material
    "logicDetector");                                                    // its name


// creating the detector matrix of small sensors boxes 100*100
    for(G4int i = 0; i < 100; i++)
    {
        for(G4int j = 0; j < 100; j++)
        {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true);

        }

    }

    return physWorld;
}
void DetectorConstruction::ConstructSDandField()
{

// Sensitive detectors
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}