#ifndef SteppingAction_H
#define SteppingAction_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class Run;

class SteppingAction : public G4UserSteppingAction {
  public:
    SteppingAction();
    virtual ~SteppingAction();

    virtual void UserSteppingAction( const G4Step* ) override;
  
    void Initialize();

    void SetRunPointer( Run* inputValue = nullptr ) { fRunPtr = inputValue; }

  private:

    G4bool IsPreassignedDecayEnabled() const { return fIsPreassignedDecayEnabled; }
    G4bool IsBoostToLabEnabled() const { return fIsBoostToLabEnabled; }
    G4double ToleranceEPviolations() const { return fToleranceEPviolations; }
    G4double ToleranceDeltaDecayRadius() const { return fToleranceDeltaDecayRadius; }

    const G4bool fIsPreassignedDecayEnabled = true;  //***LOOKHERE***
    const G4bool fIsBoostToLabEnabled = true;        //***LOOKHERE***

    G4double fToleranceEPviolations;

    const G4double fToleranceDeltaDecayRadius = 1.0*CLHEP::micrometer;

    Run* fRunPtr;

    G4int    fPrimaryParticleId;
    G4double fPrimaryParticleInitialKineticEnergy;
    G4double fPrimaryParticleInitialTotalEnergy;
    G4double fPrimaryParticleInitialMomentum;
    G4double fPrimaryParticleInitialBeta;     // Lorentz beta
    G4double fPrimaryParticleInitialGamma;    // Lorentz gamma
    G4ThreeVector fPrimaryParticleInitial3Momentum;
    G4ThreeVector fPrimaryParticleInitialPosition;

    G4double fMaxEkin_deltaMax;            
    G4double fMaxEtot_deltaMax;            
    G4double fMaxP_deltaMax;               
    G4double fMaxPdir_deltaMax;
    G4double fMaxMass_deltaMax1;           
    G4double fMaxMass_deltaMax2;           
    G4double fMaxMass_deltaMax3;           
    G4double fMeanMass_deltaMax3;          
    G4double fMaxBeta_deltaMax1;           
    G4double fMaxBeta_deltaMax2;           
    G4double fMaxGamma_deltaMax1;          
    G4double fMaxGamma_deltaMax2;          
    G4double fMaxGamma_deltaMax3;          
    G4double fMaxT_proper_deltaMax;        
    G4double fMaxT_lab_deltaMax ;          
    G4double fMaxMc_truth_rPos_deltaMax;   
    G4double fMeanMc_truth_rPos_deltaMax;

    G4double fMeanDeltaR_primaryDecay;   
    G4double fMinDeltaR_primaryDecay;    
    G4double fMaxDeltaR_primaryDecay;    
    G4double fMeanR_primaryDecay;        
    G4double fMinR_primaryDecay;         
    G4double fMaxR_primaryDecay;         
    G4double fMeanX_primaryDecay;        
    G4double fMinX_primaryDecay;         
    G4double fMaxX_primaryDecay;         
    G4double fMeanY_primaryDecay;        
    G4double fMinY_primaryDecay;         
    G4double fMaxY_primaryDecay;         
    G4double fMeanZ_primaryDecay;        
    G4double fMinZ_primaryDecay;         
    G4double fMaxZ_primaryDecay;
    G4double fMeanDeltaAngle_primaryDecay;
    G4double fMinDeltaAngle_primaryDecay;
    G4double fMaxDeltaAngle_primaryDecay;
    G4double fMeanDeltaEkin_primaryDecay;
    G4double fMinDeltaEkin_primaryDecay; 
    G4double fMaxDeltaEkin_primaryDecay; 
    G4double fMeanEkin_primaryDecay;     
    G4double fMinEkin_primaryDecay;      
    G4double fMaxEkin_primaryDecay;      
    G4double fMeanPx_primaryDecay;       
    G4double fMinPx_primaryDecay;        
    G4double fMaxPx_primaryDecay;        
    G4double fMeanPy_primaryDecay;       
    G4double fMinPy_primaryDecay;        
    G4double fMaxPy_primaryDecay;        
    G4double fMeanPz_primaryDecay;       
    G4double fMinPz_primaryDecay;        
    G4double fMaxPz_primaryDecay; 

    G4double fMinUnderestimated_mc_truth_rPos_delta;  
    G4double fMaxOverestimated_mc_truth_rPos_delta;   
    G4double fMeanUnderestimated_mc_truth_rPos_delta; 
    G4double fMeanOverestimated_mc_truth_rPos_delta;  
    G4double fMinUnderestimated_rDeltaPos;            
    G4double fMaxOverestimated_rDeltaPos;             
    G4double fMeanUnderestimated_rDeltaPos;           
    G4double fMeanOverestimated_rDeltaPos;            

    G4double fMaxFloat_rDeltaPos_deltaMax;

    G4double fMeanViolationE_primaryDecay; 
    G4double fMinViolationE_primaryDecay;  
    G4double fMaxViolationE_primaryDecay;  
    G4double fMeanViolationPx_primaryDecay;
    G4double fMinViolationPx_primaryDecay; 
    G4double fMaxViolationPx_primaryDecay; 
    G4double fMeanViolationPy_primaryDecay;
    G4double fMinViolationPy_primaryDecay; 
    G4double fMaxViolationPy_primaryDecay; 
    G4double fMeanViolationPz_primaryDecay;
    G4double fMinViolationPz_primaryDecay; 
    G4double fMaxViolationPz_primaryDecay; 
    G4double A;
};

#endif

