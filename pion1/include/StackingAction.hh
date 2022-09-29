#ifndef StackingAction_H
#define StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include <fstream>

class G4Track;

class StackingAction : public G4UserStackingAction {
  public:
    StackingAction();
    virtual ~StackingAction();
    virtual G4ClassificationOfNewTrack ClassifyNewTrack( const G4Track* aTrack ) override;
    virtual void PrepareNewEvent() override;
};

#endif

