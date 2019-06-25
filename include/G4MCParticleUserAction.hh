/**
 *  @file   include/G4MCParticleUserAction.hh
 *
 *  @brief  Header file for the geant4 MCParticle user action class.
 *
 *  $Log: $
 */

#ifndef GEANT4_MCPARTICLE_USER_ACTION_H
#define GEANT4_MCPARTICLE_USER_ACTION_H 1

#include <map>

#include "globals.hh"

#include "EventContainer.hh"
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
    G4MCParticleUserAction(EventContainer *pEventContainer, const double energyCut = 0.001);

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

    int GetParent(const int trackId) const;
    bool KnownParticle(const int trackId) const;

    /**
     *  Functions expected from a G4UserTrackingAction
     */
    void PreUserTrackingAction(const G4Track *pG4Track);
    void PostUserTrackingAction(const G4Track *pG4Track);

    /**
     *  Functions expected from a G4UserSteppingAction
     */
    void UserSteppingAction(const G4Step *pG4Step);

private:
    typedef std::map<int, int> IntIntMap;

    EventContainer  *m_pEventContainer;
    bool             m_keepEMShowerDaughters;
    double           m_energyCut;
    MCParticleInfo   m_currentMCParticleInfo;
    MCParticleList   m_mcParticleList;
    IntIntMap        m_parentIdMap;
    int              m_currentPdgCode;
    int              m_currentTrackId;
    int              m_trackIdOffset;
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

#endif // #ifndef GEANT4_MCPARTICLE_USER_ACTION_H
