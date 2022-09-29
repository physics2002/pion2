#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"



PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(),
                                                   fParticleGun( nullptr ) {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun( n_particle );
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
//


//
  fParticleGun->SetParticleDefinition( particleTable->FindParticle( "kaon-" ) ); 

  SetGunPosition();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
  delete fParticleGun;
}

void PrimaryGeneratorAction::SetGunPosition() const {
  // Shoot the particle from the origin
  fParticleGun->SetParticlePosition( G4ThreeVector( 0.0, 0.0, 0.0*m ) );  //***LOOKHERE***
}

void PrimaryGeneratorAction::GeneratePrimaries( G4Event* anEvent ) {
  G4ThreeVector v( 0.0, 0.0, 1.0 );  //***LOOKHERE*** default shoot along the x-axis
  fParticleGun->SetParticleMomentumDirection( v );
  G4double ENERGY = (10. +  5.*G4UniformRand())*GeV; 
  fParticleGun->SetParticleEnergy(ENERGY);
  fParticleGun->GeneratePrimaryVertex( anEvent );
}
