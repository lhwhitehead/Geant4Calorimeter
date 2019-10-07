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
// $Id: G4TPCRunAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file G4TPCRunAction.cc
/// \brief Implementation of the G4TPCRunAction class

#include <sstream>

#include "G4TPCRunAction.hh"
#include "G4TPCRunMessenger.hh"
#include "G4TPCAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//------------------------------------------------------------------------------

G4TPCRunAction::G4TPCRunAction(EventContainer *pEventContainer, G4MCParticleUserAction *pG4MCParticleUserAction) :
    G4UserRunAction(),
    m_pEventContainer(pEventContainer),
    m_pG4MCParticleUserAction(pG4MCParticleUserAction)
{
    G4RunManager::GetRunManager()->SetPrintProgress(1);
    fMessenger = new G4TPCRunMessenger(this);
}

//------------------------------------------------------------------------------

G4TPCRunAction::~G4TPCRunAction()
{
    delete G4AnalysisManager::Instance();
}

//------------------------------------------------------------------------------

void G4TPCRunAction::BeginOfRunAction(const G4Run *pG4Run)
{
    m_pG4MCParticleUserAction->BeginOfRunAction(pG4Run);

    //inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

    /*
     * Added autoseed functionality to resolve issue with specifying seeds greater than LONG_MAX
     */
    G4cout << "*******************" << G4endl;
    G4cout << "*** AUTOSEED ON ***" << G4endl;
    G4cout << "*******************" << G4endl;
    long seeds[2];
    time_t systime = time(NULL);
    seeds[0] = (long) systime;
    seeds[1] = (long) (systime*G4UniformRand());
    G4Random::setTheSeeds(seeds);
    G4Random::showEngineStatus();

    m_pG4MCParticleUserAction->BeginOfRunAction(pG4Run);
}

//------------------------------------------------------------------------------

void G4TPCRunAction::EndOfRunAction(const G4Run *pG4Run)
{
    m_pG4MCParticleUserAction->EndOfRunAction(pG4Run);
//    m_pEventContainer->SaveXml();
    if(fOutputFileType == "xml"){
      m_pEventContainer->SaveXml();
    }
    else{
      m_pEventContainer->SaveText();
    }
}

