#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(),  
                                               fTargetMaterial( nullptr ),
  fLogicExperimentalHall( nullptr ), fPhysExperimentalHall( nullptr ),
  fLogicTargetLayer( nullptr ), fPhysTargetLayer( nullptr ),
  fDetectorMessenger( nullptr )
{
  fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial( "G4_Galactic" );
  fDetectorMessenger = new DetectorMessenger( this );
}

DetectorConstruction::~DetectorConstruction() {
  delete fDetectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  return ConstructLayer();
}

G4VPhysicalVolume* DetectorConstruction::ConstructLayer() {
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

    G4bool checkOverlaps = true;


  const G4double halfLength = 152.0*m;
  const G4double expHall_x = 1.0*halfLength;  // half dimension along x
  const G4double expHall_y = 1.0*halfLength;  // half dimension along y
  const G4double expHall_z = 1.0*halfLength;  // half dimension along z

  G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial( "G4_Galactic" );
  G4Box* experimentalHallBox = new G4Box( "expHallBox", expHall_x, expHall_y, expHall_z );
  fLogicExperimentalHall = new G4LogicalVolume( experimentalHallBox,  // solid
                                                vacuum,               // material
                                                "logicExpHall",       // name
                                                0,                    // field manager
                                                0,                    // sensitive detector
                                                0 );                  // user limits
  fPhysExperimentalHall = new G4PVPlacement( 0,                       // rotation
                                             G4ThreeVector(),         // translation
                                             "expHall",               // name
                                             fLogicExperimentalHall,  // logical volume
                                             0,                       // mother physical volume
                                             false,                   // boolean operation
                                             0 );                     // copy number
  G4Tubs* solidTargetLayer = new G4Tubs( "solidTargetLayer",
                                         1.*m,          // inner radius
                                         1.01*m,          // outer radius
                                         50.*m,                  // half cylinder length in z
                                         0.0,                         // starting phi angle in rad
                                         2.0*pi );                    // final phi angle in rad
  fLogicTargetLayer = new G4LogicalVolume( solidTargetLayer,          // solid
                                           fTargetMaterial,           // material
                                           "logicTargetLayer",        // name
                                           0,                         // field manager
                                           0,                         // sensitive detector
                                           0 );                       // user limits
fPhysTargetLayer = new G4PVPlacement( 0,                            // rotation
                                        G4ThreeVector(0,0,50*m),              // translation
                                        "physTargetLayer",            // name
                                        fLogicTargetLayer,            // logical volume
                                        fPhysExperimentalHall,        // mother physical volume
                                        false,                        // boolean operation
                                        0,
                                        checkOverlaps);                          // copy number
    G4Material *tubeMatFe = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  G4Tubs* solidTargetLayer1 = new G4Tubs( "solidTargetLayer1",
                                         0.*m,          // inner radius
                                         1.*m,          // outer radius
                                         25.*m,                  // half cylinder length in z
                                         0.0,                         // starting phi angle in rad
                                         2.0*pi );                    // final phi angle in rad
  fLogicTargetLayer1 = new G4LogicalVolume( solidTargetLayer1,          // solid
                                           tubeMatFe,           // material
                                           "fLogicTargetLayer1",        // name
                                           0,                         // field manager
                                           0,                         // sensitive detector
                                           0 );                       // user limits
fPhysTargetLayer1 = new G4PVPlacement( 0,                            // rotation
                                        G4ThreeVector(0,0,125*m),              // translation
                                        "physTargetLayer1",            // name
                                        fLogicTargetLayer1,            // logical volume
                                        fPhysExperimentalHall,        // mother physical volume
                                        false,                        // boolean operation
                                        0,
                                        checkOverlaps);                          // copy number    

    G4Material *det_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  G4Tubs* solidTargetLayer2 = new G4Tubs( "solidTargetLayer2",
                                         0.*m,          // inner radius
                                         1.*m,          // outer radius
                                         1.*m,                  // half cylinder length in z
                                         0.0,                         // starting phi angle in rad
                                         2.0*pi );                    // final phi angle in rad
  fLogicTargetLayer2 = new G4LogicalVolume( solidTargetLayer2,          // solid
                                           det_mat,           // material
                                           "logicTargetLayer2",        // name
                                           0,                         // field manager
                                           0,                         // sensitive detector
                                           0 );                       // user limits
fPhysTargetLayer2 = new G4PVPlacement( 0,                            // rotation
                                        G4ThreeVector(0,0,151*m),              // translation
                                        "physTargetLayer2",            // name
                                        fLogicTargetLayer2,            // logical volume
                                        fPhysExperimentalHall,        // mother physical volume
                                        false,                        // boolean operation
                                        0,
                                        checkOverlaps);                          // copy number    



  PrintParameters();
  G4cout << G4endl
         << "DetectorConstruction::ConstructLayer() : " << G4endl
         << "\t World (box) size: " << G4endl
         << "\t \t x : -/+ " << expHall_x << " m ;"
         << "\t y : -/+ "    << expHall_y << " m ;"
         << "\t z : -/+ "    << expHall_z << " m ;" << G4endl
         << "\t Layer (cylinder) size : " << G4endl
         << "\t \t radii : " << fTargetInnerRadius << " , " << fTargetOuterRadius << " m ;"
         << "\t \t length (along z) : " << 2.0*halfLength << " m ;" << G4endl
         << G4endl << G4endl;
  return fPhysExperimentalHall;
}


void DetectorConstruction::SetTargetMaterial( const G4String name ) {
  fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial( name ); 
  if ( ! fTargetMaterial ) {
    G4cout << G4endl << G4endl
           << "WARNING: the name of the material has not been recognized!" << G4endl
           << "     ===> the default  * G4_Galactic *  will be used." << G4endl << G4endl;
    fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial( "G4_Galactic" );
  }
  if ( fLogicTargetLayer ) fLogicTargetLayer->SetMaterial( fTargetMaterial );
}

void DetectorConstruction::UpdateGeometry() {
  G4RunManager::GetRunManager()->ReinitializeGeometry();
  PrintParameters();
  const PrimaryGeneratorAction* pPrimaryAction = dynamic_cast< const PrimaryGeneratorAction* >
    ( G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction() );
  if ( pPrimaryAction ) pPrimaryAction->SetGunPosition();
}

void DetectorConstruction::PrintParameters() {
  G4cout << G4endl << G4endl
         << " ------  DetectorConstruction::PrintParameters() ------ " << G4endl
         << " Material            = " << fTargetMaterial->GetName() << G4endl
         << " Target Inner Radius = " << fTargetInnerRadius  << " mm" << G4endl
         << " Target Outer Radius = " << fTargetOuterRadius  << " mm" << G4endl
         << " B [T]               = "
         << ( fUniformMagField ? fUniformMagField->GetConstantFieldValue()/CLHEP::tesla :
              G4ThreeVector(0.0, 0.0, 0.0) ) << G4endl
         << " ------------------------------------------------------ " << G4endl << G4endl;
}

void DetectorConstruction::SetMagField( const G4double fieldValue ) {
  if ( fUniformMagField ) delete fUniformMagField;
  if ( std::abs( fieldValue ) > 0.0 ) {
    // Apply a global uniform magnetic field along the Z axis
    fUniformMagField = new G4UniformMagField( G4ThreeVector( 0.0, 0.0, fieldValue ) );
    fFieldMgr->SetDetectorField( fUniformMagField );
    fFieldMgr->CreateChordFinder( fUniformMagField );
  } 
}







