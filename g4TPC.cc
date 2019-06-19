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
// $Id: exampleG4TPC.cc 86065 2014-11-07 08:51:15Z gcosmo $
//
/// \file exampleG4TPC.cc
/// \brief Main program of the G4TPC example

#include "G4TPCDetectorConstruction.hh"
#include "G4TPCActionInitialization.hh"
//#include "G4MCParticleUserAction.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4StepLimiterPhysics.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BERT.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//------------------------------------------------------------------------------

namespace
{

void PrintUsage()
{
    G4cerr << " Usage: " << G4endl;
    G4cerr << " exampleG4TPC [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode." << G4endl;
}

}

//------------------------------------------------------------------------------

int main(int argc,char** argv)
{
    // Evaluate arguments
    if ( argc > 7 )
    {
        PrintUsage();
        return 1;
    }

    G4String macro;
    G4String session;
#ifdef G4MULTITHREADED
    G4int nThreads = 0;
#endif

    for ( G4int i=1; i<argc; i=i+2 )
    {
        if ( G4String(argv[i]) == "-m" )
        {
            macro = argv[i+1];
        }
        else if ( G4String(argv[i]) == "-u" )
        {
            session = argv[i+1];
        }
#ifdef G4MULTITHREADED
        else if ( G4String(argv[i]) == "-t" )
        {
             nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
        }
#endif
        else
        {
            PrintUsage();
            return 1;
        }
    }

    // Detect interactive mode (if no macro provided) and define UI session
    G4UIExecutive* pG4UIExecutive = nullptr;

    if(!macro.size())
        pG4UIExecutive = new G4UIExecutive(argc, argv);

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    // Construct the default run manager
#ifdef G4MULTITHREADED
    G4MTRunManager *pG4RunManager = new G4MTRunManager;

    if(nThreads > 0)
        pG4RunManager->SetNumberOfThreads(nThreads);
#else
    G4RunManager *pG4RunManager = new G4RunManager;
#endif

    // Set mandatory and optional initialization classes
    G4TPCDetectorConstruction *pG4TPCDetectorConstruction = new G4TPCDetectorConstruction();
    pG4RunManager->SetUserInitialization(pG4TPCDetectorConstruction);

    G4VModularPhysicsList *pG4VModularPhysicsList = new QGSP_BERT;
    pG4VModularPhysicsList->RegisterPhysics(new G4StepLimiterPhysics()); // Has to be added to limit step size
    pG4RunManager->SetUserInitialization(pG4VModularPhysicsList);

    G4TPCActionInitialization *pG4TPCActionInitialization = new G4TPCActionInitialization(pG4TPCDetectorConstruction);
    pG4RunManager->SetUserInitialization(pG4TPCActionInitialization);
/*
    // Set user defined actions
    G4MCParticleUserAction *pG4MCParticleUserAction = new G4MCParticleUserAction();

    G4UserRunAction *runAction = (G4UserRunAction*) pG4MCParticleUserAction;
    G4UserEventAction *eventAction = (G4UserEventAction*) pG4MCParticleUserAction;
    G4UserTrackingAction *trackingAction = (G4UserTrackingAction*) pG4MCParticleUserAction;
    G4UserSteppingAction *steppingAction = (G4UserSteppingAction*) pG4MCParticleUserAction;

    pG4RunManager->SetUserAction(runAction);
    pG4RunManager->SetUserAction(eventAction);
    pG4RunManager->SetUserAction(trackingAction);
    pG4RunManager->SetUserAction(steppingAction);
*/
    // Initialize visualization
    G4VisManager* pG4VisManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* pG4VisManager = new G4VisExecutive("Quiet");
    pG4VisManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* pG4UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    if (macro.size())
    {
        // batch mode
        G4String command = "/control/execute ";
        pG4UImanager->ApplyCommand(command+macro);
    }
    else
    {
        // interactive mode : define UI session
        pG4UImanager->ApplyCommand("/control/execute init_vis.mac");

        if (pG4UIExecutive->IsGUI())
        {
            pG4UImanager->ApplyCommand("/control/execute gui.mac");
        }

        pG4UIExecutive->SessionStart();
        delete pG4UIExecutive;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !

    delete pG4VisManager;
    delete pG4RunManager;
}

//------------------------------------------------------------------------------
