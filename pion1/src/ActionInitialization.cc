#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
  SetUserAction( new RunAction );
}

void ActionInitialization::Build() const {
  // Called in the SEQ-mode and in the MT-mode for Worker threads only.
  SetUserAction( new PrimaryGeneratorAction );
  SteppingAction* steppingAction = new SteppingAction;
  SetUserAction( steppingAction );
  SetUserAction( new RunAction( steppingAction ) );
  SetUserAction( new StackingAction );
}
