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
// $Id: G4TPCSteppingAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file G4TPCSteppingAction.cc
/// \brief Implementation of the G4TPCSteppingAction class

#include "G4TPCSteppingAction.hh"
#include "EventContainer.hh"
#include "G4TPCDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

//------------------------------------------------------------------------------

G4TPCSteppingAction::G4TPCSteppingAction(const G4TPCDetectorConstruction *pG4TPCDetectorConstruction, EventContainer *pEventContainer,
    G4MCParticleUserAction *pG4MCParticleUserAction) :
    G4UserSteppingAction(),
    m_pG4TPCDetectorConstruction(pG4TPCDetectorConstruction),
    m_pEventContainer(pEventContainer),
    m_pG4MCParticleUserAction(pG4MCParticleUserAction)
{
}

//------------------------------------------------------------------------------

G4TPCSteppingAction::~G4TPCSteppingAction()
{
}

//------------------------------------------------------------------------------

void G4TPCSteppingAction::UserSteppingAction(const G4Step *pG4Step)
{
//std::cout << "G4TPCSteppingAction::UserSteppingAction Start" << std::endl;
    m_pG4MCParticleUserAction->UserSteppingAction(pG4Step);

    // Collect energy and track length step by step
    G4VPhysicalVolume* pG4VPhysicalVolume = pG4Step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    if (pG4Step->GetTrack()->GetDefinition()->GetPDGCharge() == 0.)
        return;

    Cell cell(m_pG4TPCDetectorConstruction->GetCell(pG4Step));
    cell.AddEnergy(pG4Step->GetTotalEnergyDeposit());

    if (pG4VPhysicalVolume == m_pG4TPCDetectorConstruction->GetLArPV())
        m_pEventContainer->GetCurrentCellList().AddEnergyDeposition(&cell);
}
