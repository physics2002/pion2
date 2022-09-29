#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"

DetectorMessenger::DetectorMessenger( DetectorConstruction* myDet ) : G4UImessenger(),
                                                                      fDetector( myDet ) {
  fDetectorDir = new G4UIdirectory( "/mydet/" );
  fDetectorDir->SetGuidance( "Detector control." );

  fFieldCommand = new G4UIcmdWithADoubleAndUnit( "/mydet/setField", this );  
  fFieldCommand->SetGuidance( "Define uniform magnetic field along Y." );
  fFieldCommand->SetGuidance( " -> in unit of  [Tesla]" );
  fFieldCommand->SetParameterName( "By", false );
  fFieldCommand->SetDefaultValue( 0.0 );
  fFieldCommand->SetUnitCategory( "Magnetic flux density" );
  fFieldCommand->AvailableForStates( G4State_PreInit, G4State_Idle );  

  fTargetMaterial = new G4UIcmdWithAString( "/mydet/targetMaterial", this );
  fTargetMaterial->SetGuidance( "Choice of the target material:" );
  fTargetMaterial->SetGuidance( "   a Geant4 NIST material, e.g. G4_Be " );
  fTargetMaterial->SetParameterName( "choiceTargetMaterial", true );
  fTargetMaterial->SetDefaultValue( "G4_Galactic" );
  fTargetMaterial->AvailableForStates( G4State_PreInit, G4State_Idle );

  fTargetInnerRadius = new G4UIcmdWithADoubleAndUnit( "/mydet/targetInnerRadius", this );
  fTargetInnerRadius->SetParameterName( "choiceTargetInnerRadius", true );
  fTargetInnerRadius->SetGuidance( "Target inner radius" );
  fTargetInnerRadius->SetDefaultValue( 9.0 );
  fTargetInnerRadius->AvailableForStates( G4State_PreInit, G4State_Idle );

  fTargetOuterRadius = new G4UIcmdWithADoubleAndUnit( "/mydet/targetOuterRadius", this );
  fTargetOuterRadius->SetParameterName( "choiceTargetOuterRadius", true );
  fTargetOuterRadius->SetGuidance( "Target outer radius" );
  fTargetOuterRadius->SetDefaultValue( 11.0 );
  fTargetOuterRadius->AvailableForStates( G4State_PreInit, G4State_Idle );

  fUpdateCommand = new G4UIcmdWithoutParameter( "/mydet/update", this);
  fUpdateCommand->SetGuidance( "Update calorimeter geometry." );
  fUpdateCommand->SetGuidance( "This command MUST be applied before \"beamOn\" " );
  fUpdateCommand->SetGuidance( "if you changed geometrical value(s)." );
  fUpdateCommand->AvailableForStates( G4State_Idle ); 
}

DetectorMessenger::~DetectorMessenger() {
  delete fDetectorDir;
  delete fFieldCommand;
  delete fTargetMaterial;
  delete fTargetInnerRadius;
  delete fTargetOuterRadius;
  delete fUpdateCommand;
}

void DetectorMessenger::SetNewValue( G4UIcommand* command, G4String newValue ) {
  if ( command == fFieldCommand ) { 
    fDetector->SetMagField( fFieldCommand->GetNewDoubleValue( newValue ) );
  }
  if ( command == fTargetMaterial ) { 
    fDetector->SetTargetMaterial( newValue );
  }
  if ( command == fTargetInnerRadius ) { 
    fDetector->SetTargetInnerRadius( fTargetInnerRadius->GetNewDoubleValue( newValue ) );
  }
  if ( command == fTargetOuterRadius ) { 
    fDetector->SetTargetOuterRadius( fTargetOuterRadius->GetNewDoubleValue( newValue ) );
  }
  if ( command == fUpdateCommand ) {
    fDetector->UpdateGeometry();
  }
}







