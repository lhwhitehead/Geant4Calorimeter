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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4TPCSteppingAction::G4TPCSteppingAction(
                      const G4TPCDetectorConstruction* detectorConstruction,
                      G4TPCEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4TPCSteppingAction::~G4TPCSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4TPCSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

  // get volume of the current step
  G4VPhysicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  
  // step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }

//  std::cout << "Step Length / mm     : " << stepLength << std::endl;

//  std::cout << "Step Z position : " << step->GetPreStepPoint()->GetPosition().z() << std::endl;
//  std::cout << "Step Energy     : " << edep << std::endl;

  G4double z = step->GetPreStepPoint()->GetPosition().z();
  G4int layer = this->getLayerNumber(z,volume);

  fEventAction->AddEZ(edep, z, layer);

  if ( volume == fDetConstruction->GetAbsorberPV() ) {
    fEventAction->AddAbsE(edep,layer);
  }

//  std::cout << "Z : " << z << std::endl;
//  std::cout << "Layer number : " << this->getLayerNumber(z,volume) << std::endl;

  if ( volume == fDetConstruction->GetAbsorberPV() ) {
    fEventAction->AddAbs(edep,stepLength);
    //std::cout << "Step Length / mm     : " << stepLength/mm << std::endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int G4TPCSteppingAction::getLayerNumber(float z, G4VPhysicalVolume* volume)
{
    const G4double calorThickness = fDetConstruction->getCalorThickness();
    const G4double layerThickness = fDetConstruction->getLayerThickness();
//    const G4int nofLayers = fDetConstruction->getNumberOfLayers();
    G4int layer(-2);

    if (volume == fDetConstruction->GetAbsorberPV())
    {
        layer = floor((z + calorThickness/2) / layerThickness);
    }

    return layer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
