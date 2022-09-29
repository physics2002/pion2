#include "StackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4TouchableHistory.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include <iostream>
#include <string>
#include <cmath>
#include "G4SystemOfUnits.hh"

StackingAction::StackingAction() : G4UserStackingAction() {}

StackingAction::~StackingAction() {}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack( const G4Track* aTrack ) {
  G4ClassificationOfNewTrack result( fUrgent );
  //if ( aTrack->GetParentID() != 0 ) result = fKill;  // Kill all secondaries
  return result;
}



void StackingAction::PrepareNewEvent() {}
