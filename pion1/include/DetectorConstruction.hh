#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"       

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4FieldManager;
class G4UniformMagField;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction {
  public:
    DetectorConstruction();
    ~DetectorConstruction(); 
    G4VPhysicalVolume* Construct() override;
  
    void SetTargetMaterial( const G4String name );
    inline G4Material* GetTargetMaterial() const;
    inline void SetTargetInnerRadius( const G4double value );
    inline G4double GetTargetInnerRadius() const;
    inline void SetTargetOuterRadius( const G4double value );
    inline G4double GetTargetOuterRadius() const;
    void SetMagField( const G4double fieldValue );
    void UpdateGeometry();
  
  private:
    // To be invoked each time the geometry needs to be updated
    G4VPhysicalVolume* ConstructLayer();
  
    void PrintParameters();
    G4Material* fTargetMaterial;
    G4LogicalVolume* fLogicExperimentalHall;
    G4VPhysicalVolume* fPhysExperimentalHall;
    G4LogicalVolume*  fLogicTargetLayer;
    G4VPhysicalVolume* fPhysTargetLayer;
    G4LogicalVolume*  fLogicTargetLayer1;
    G4VPhysicalVolume* fPhysTargetLayer1;
    G4LogicalVolume*  fLogicTargetLayer2;
    G4VPhysicalVolume* fPhysTargetLayer2;
    
    G4FieldManager* fFieldMgr;
    G4UniformMagField* fUniformMagField; 
    DetectorMessenger* fDetectorMessenger;
    G4double fTargetInnerRadius;
    G4double fTargetOuterRadius;
};

inline G4Material* DetectorConstruction::GetTargetMaterial() const {
  return fTargetMaterial;
}

inline void DetectorConstruction::SetTargetInnerRadius( const G4double value ) {
  fTargetInnerRadius = value;
}

inline G4double DetectorConstruction::GetTargetInnerRadius() const {
  return fTargetInnerRadius;
}

inline void DetectorConstruction::SetTargetOuterRadius( const G4double value ) {
  fTargetOuterRadius = value;
}

inline G4double DetectorConstruction::GetTargetOuterRadius() const {
  return fTargetOuterRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
