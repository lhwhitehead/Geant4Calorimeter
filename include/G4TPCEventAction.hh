//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: G4TPCEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file G4TPCEventAction.hh
/// \brief Definition of the G4TPCEventAction class

#ifndef G4TPCEventAction_h
#define G4TPCEventAction_h 1

#include "EventContainer.hh"
#include "G4MCParticleUserAction.hh"
#include "G4UserEventAction.hh"

#include "globals.hh"

#include <map>
#include <vector>

/// Event action class

class G4TPCEventAction : public G4UserEventAction
{
public:
    G4TPCEventAction(EventContainer *pEventContainer, G4MCParticleUserAction *pG4MCParticleUserAction);
    virtual ~G4TPCEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

private:
    EventContainer         *m_pEventContainer;
    G4MCParticleUserAction *m_pG4MCParticleUserAction;
};

#endif
