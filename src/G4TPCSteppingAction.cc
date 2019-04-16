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
#include "G4TPCEventAction.hh"
#include "G4TPCDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

//------------------------------------------------------------------------------

G4TPCSteppingAction::G4TPCSteppingAction(const G4TPCDetectorConstruction *pG4TPCDetectorConstruction, G4TPCEventAction *pG4TPCEventAction) :
    G4UserSteppingAction(),
    m_pG4TPCDetectorConstruction(pG4TPCDetectorConstruction),
    m_pG4TPCEventAction(pG4TPCEventAction)
{
}

//------------------------------------------------------------------------------

G4TPCSteppingAction::~G4TPCSteppingAction()
{
}

//------------------------------------------------------------------------------

void G4TPCSteppingAction::UserSteppingAction(const G4Step *pG4Step)
{
    // Collect energy and track length step by step
    // get pG4VPhysicalVolume of the current step
    //G4VPhysicalVolume* pG4VPhysicalVolume = pG4Step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    // energy deposit
    //G4double energyDeposition = pG4Step->GetTotalEnergyDeposit();

    // step length
    //G4double stepLength = 0.;
    //if (pG4Step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    //{
    //    stepLength = pG4Step->GetStepLength();
    //}

    const G4int cell(m_pG4TPCDetectorConstruction->GetCell(pG4Step));
    std::cout << cell << std::endl;
/*
    if (pG4VPhysicalVolume == m_pG4TPCDetectorConstruction->GetAbsorberPV())
    {
        m_pG4TPCEventAction->AddAbsE(energyDeposition,layer);
    }
*/
}
