#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class Run;

class ActionInitialization : public G4VUserActionInitialization {
  public:
    ActionInitialization();
    virtual ~ActionInitialization();
    virtual void BuildForMaster() const override;
    virtual void Build() const override;
};

#endif
