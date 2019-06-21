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
// $Id: G4TPCEventAction.cc 75604 2013-11-04 13:17:26Z gcosmo $
// 
/// \file G4TPCEventAction.cc
/// \brief Implementation of the G4TPCEventAction class

#include "G4TPCEventAction.hh"
#include "G4TPCRunAction.hh"
#include "G4TPCAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//------------------------------------------------------------------------------

G4TPCEventAction::G4TPCEventAction(EventContainer *pEventContainer, G4MCParticleUserAction *pG4MCParticleUserAction) :
    G4UserEventAction(),
    m_pEventContainer(pEventContainer),
    m_pG4MCParticleUserAction(pG4MCParticleUserAction)
{
}

//------------------------------------------------------------------------------

G4TPCEventAction::~G4TPCEventAction()
{
}

//------------------------------------------------------------------------------

void G4TPCEventAction::BeginOfEventAction(const G4Event *pG4Event)
{
    m_pG4MCParticleUserAction->BeginOfEventAction(pG4Event);
    m_pEventContainer->BeginOfEventAction();
}

//------------------------------------------------------------------------------

void G4TPCEventAction::EndOfEventAction(const G4Event *pG4Event)
{
    m_pG4MCParticleUserAction->EndOfEventAction(pG4Event);
    m_pEventContainer->EndOfEventAction();
}

