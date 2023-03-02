// Implementation of the PhysicsList class

#include "physics.hh"


MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());    //insertion of the optical physics is important for scintilation detectors
}
MyPhysicsList::~MyPhysicsList()
{}