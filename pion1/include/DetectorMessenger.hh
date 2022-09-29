#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger {
  public:
    DetectorMessenger( DetectorConstruction* );
    ~DetectorMessenger();
    void SetNewValue( G4UIcommand* , G4String ) override;
  private:
    DetectorConstruction*      fDetector;
    G4UIdirectory*             fDetectorDir;
    G4UIcmdWithADoubleAndUnit* fFieldCommand;
    G4UIcmdWithAString*        fTargetMaterial;
    G4UIcmdWithADoubleAndUnit* fTargetInnerRadius;
    G4UIcmdWithADoubleAndUnit* fTargetOuterRadius;
    G4UIcmdWithoutParameter*   fUpdateCommand;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
