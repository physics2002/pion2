#ifndef RunAction_h
#define RunAction_h

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"

class G4Run;
class SteppingAction;

class RunAction: public G4UserRunAction {
  public:
    RunAction( SteppingAction* steppingAction = nullptr );
    virtual ~RunAction();
    virtual void BeginOfRunAction( const G4Run* aRun ) override;
    virtual void EndOfRunAction(   const G4Run* aRun ) override;
    virtual G4Run* GenerateRun() override;
  private:
    SteppingAction* fSteppingAction;
};

#endif
