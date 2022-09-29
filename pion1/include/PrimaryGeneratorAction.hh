#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include <cstdlib>
#include <ctime>

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries( G4Event* anEvent ) override;
    void SetGunPosition() const; 
    
  private:
    G4ParticleGun* fParticleGun;
};

#endif
