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
// $Id: G4TPCSteppingAction.hh 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file G4TPCSteppingAction.hh
/// \brief Definition of the G4TPCSteppingAction class

#ifndef G4TPCSteppingAction_h
#define G4TPCSteppingAction_h 1

#include "G4MCParticleUserAction.hh"
#include "G4UserSteppingAction.hh"

#include "globals.hh"

class G4TPCDetectorConstruction;
class G4TPCEventAction;
class G4VPhysicalVolume;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track
/// lengths of charged particles in Absober and Gap layers and
/// updated in G4TPCEventAction.

class G4TPCSteppingAction : public G4UserSteppingAction
{
public:
    G4TPCSteppingAction(const G4TPCDetectorConstruction *pG4TPCDetectorConstruction, EventContainer *pEventContainer,
        G4MCParticleUserAction *pG4MCParticleUserAction);

    virtual ~G4TPCSteppingAction();

    virtual void UserSteppingAction(const G4Step *pG4Step);

private:
    const G4TPCDetectorConstruction *m_pG4TPCDetectorConstruction; ///< Detector construction class
    EventContainer                  *m_pEventContainer;            ///< Event action class
    G4MCParticleUserAction          *m_pG4MCParticleUserAction;    ///< MCParticle user action class
};

#endif
