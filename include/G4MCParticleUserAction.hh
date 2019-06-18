/**
 *  @file   include/G4MCParticleUserAction.hh
 *
 *  @brief  Header file for the geant4 MCParticle user action class.
 *
 *  $Log: $
 */

#ifndef GEANT4_MCPARTICLE_USER_ACTION_H
#define GEANT4_MCPARTICLE_USER_ACTION_H 1

#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"

#include "MCParticle.hh"

/**
 *  @brief G4MCParticleUserAction class
 */
class G4MCParticleUserAction: public G4UserRunAction, public G4UserEventAction, public G4UserTrackingAction, public G4UserSteppingAction
{
public:
    /**
     *  Default constructor
     */
    G4MCParticleUserAction();

    /**
     *  Destructor
     */
    ~G4MCParticleUserAction();

    /**
     *  Functions expected from a G4UserRunAction
     */
    void BeginOfRunAction(const G4Run *pG4Run);
    void EndOfRunAction(const G4Run *pG4Run);

    /**
     *  Functions expected from a G4UserEventAction
     */
    void BeginOfEventAction(const G4Event *pG4Event);
    void EndOfEventAction(const G4Event *pG4Event);

    /**
     *  Functions expected from a G4UserTrackingAction
     */
    void PreTrackingAction(const G4Track *pG4Track);
    void PostTrackingAction(const G4Track *pG4Track);

    /**
     *  Functions expected from a G4UserSteppingAction
     */
    void SteppingAction(const G4Step *pG4Step);

private:
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

#endif // #ifndef GEANT4_MCPARTICLE_USER_ACTION_H
