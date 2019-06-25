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
// $Id: G4TPCActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file G4TPCActionInitialization.cc
/// \brief Implementation of the G4TPCActionInitialization class

#include "EventContainer.hh"
#include "G4MCParticleUserAction.hh"
#include "G4TPCActionInitialization.hh"
#include "G4TPCPrimaryGeneratorAction.hh"
#include "G4TPCRunAction.hh"
#include "G4TPCEventAction.hh"
#include "G4TPCSteppingAction.hh"
#include "G4TPCDetectorConstruction.hh"

//------------------------------------------------------------------------------

G4TPCActionInitialization::G4TPCActionInitialization(G4TPCDetectorConstruction *pG4TPCDetectorConstruction, const InputParameters &parameters) :
    G4VUserActionInitialization(),
    m_pG4TPCDetectorConstruction(pG4TPCDetectorConstruction),
    m_parameters(parameters)
{
}

//------------------------------------------------------------------------------

G4TPCActionInitialization::~G4TPCActionInitialization()
{
}

//------------------------------------------------------------------------------

void G4TPCActionInitialization::BuildForMaster() const
{
}

//------------------------------------------------------------------------------

void G4TPCActionInitialization::Build() const
{
    // Set user defined actions
    EventContainer *pEventContainer = new EventContainer(m_parameters);
    G4MCParticleUserAction *pG4MCParticleUserAction = new G4MCParticleUserAction(pEventContainer);

    SetUserAction(new G4TPCPrimaryGeneratorAction(m_parameters));
    SetUserAction(new G4TPCRunAction(pEventContainer, pG4MCParticleUserAction));
    SetUserAction(new G4TPCEventAction(pEventContainer, pG4MCParticleUserAction));
    G4UserTrackingAction *trackingAction = (G4UserTrackingAction*) pG4MCParticleUserAction;
    SetUserAction(trackingAction);
    SetUserAction(new G4TPCSteppingAction(m_pG4TPCDetectorConstruction, pEventContainer, pG4MCParticleUserAction));
}

