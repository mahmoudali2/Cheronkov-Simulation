// Implementation of the PrimaryGeneratorAction class

#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
// particle definition
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="Proton";
    G4ParticleDefinition *particle =particleTable->FindParticle("proton");

    G4ThreeVector pos(0., 0., 0.);   // position direction
    G4ThreeVector mom(0., 0., 1.);   // momentum direction
    
// default particle kinematic
   fParticleGun->SetParticlePosition(pos);               // position
   fParticleGun->SetParticleMomentumDirection(mom);      // momentum direction
   fParticleGun->SetParticleMomentum(100 *GeV);          // momentum
   fParticleGun->SetParticleDefinition(particle);        

   fParticleGun->GeneratePrimaryVertex(anEvent);
}