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
// $Id: G4TPCDetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
// 
/// \file G4TPCDetectorConstruction.cc
/// \brief Implementation of the G4TPCDetectorConstruction class

#include "G4TPCDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserLimits.hh"

//------------------------------------------------------------------------------

G4ThreadLocal
G4GlobalMagFieldMessenger* G4TPCDetectorConstruction::fMagFieldMessenger = 0;

//------------------------------------------------------------------------------

G4TPCDetectorConstruction::G4TPCDetectorConstruction() : G4VUserDetectorConstruction(),
    m_nofLayers(100),
    m_layerThickness(2.5*mm),
    m_gapThickness(2.5*mm),
    m_calorThickness(m_nofLayers * m_layerThickness),
    m_calorSizeXY(100.*cm),
    fAbsorberPV(0),
    fCheckOverlaps(true)
{
}

//------------------------------------------------------------------------------

G4TPCDetectorConstruction::~G4TPCDetectorConstruction()
{
}

//------------------------------------------------------------------------------

G4VPhysicalVolume* G4TPCDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//------------------------------------------------------------------------------

void G4TPCDetectorConstruction::DefineMaterials()
{
    // Lead material defined using NIST Manager
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_Pb");

    // Liquid argon material
    G4double a;  // mass of a mole;
    G4double z;  // z=mean number of protons;
    G4double density;
    new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density = 1.390*g/cm3); // The argon by NIST Manager is a gas with a different density

    // Vacuum
    new G4Material("Galactic", z=1., a=1.01*g/mole,density = universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//------------------------------------------------------------------------------

G4VPhysicalVolume* G4TPCDetectorConstruction::DefineVolumes()
{
    // Geometry parameters
    G4double worldSizeXY = 12;
    G4double worldSizeZ  = 12;

    G4double caloOffset = 0;

    // Get materials
    G4Material* defaultMaterial = G4Material::GetMaterial("Galactic");
    G4Material *pG4Material_LAr = G4Material::GetMaterial("liquidArgon");

    if (!pG4Material_LAr)
    {
        G4ExceptionDescription msg;
        msg << "Cannot retrieve materials already defined.";
        G4Exception("G4TPCDetectorConstruction::DefineVolumes()", "MyCode0001", FatalException, msg);
    }

    // World
    G4VSolid* worldS = new G4Box("World", worldSizeXY/2, worldSizeXY/2, worldSizeZ/2);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, defaultMaterial, "World");
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlaps);

    // Calorimeter
    G4VSolid* calorimeterS = new G4Box("Calorimeter", m_calorSizeXY/2, m_calorSizeXY/2, m_calorThickness/2);
    G4LogicalVolume* calorLV = new G4LogicalVolume(calorimeterS, defaultMaterial, "Calorimeter");
    new G4PVPlacement(0, G4ThreeVector(), calorLV, "Calorimeter", worldLV, false, 0, fCheckOverlaps);

    // Layers
    G4VSolid* layerS = new G4Box("Layer", m_calorSizeXY/2, m_calorSizeXY/2, m_layerThickness/2);
    G4LogicalVolume* layerLV = new G4LogicalVolume(layerS, defaultMaterial, "Layer");
    new G4PVReplica("Layer", layerLV, calorLV, kZAxis, m_nofLayers, m_layerThickness);

    // Absorber
    G4VSolid* absorberS = new G4Box("Abso", m_calorSizeXY/2, m_calorSizeXY/2, m_layerThickness/2);
    G4LogicalVolume* absorberLV = new G4LogicalVolume(absorberS, pG4Material_LAr, "Abso");
    fAbsorberPV = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), absorberLV, "Abso", layerLV, false, 0, fCheckOverlaps);

    // Example of User Limits
    //
    // Below is an example of how to set tracking constraints in a given
    // logical volume
    //
    // Sets a max step length in the tracker region, with G4StepLimiter

    G4double maxStep = 0.001*mm;
    G4UserLimits* fStepLimit = new G4UserLimits(maxStep);
    worldLV->SetUserLimits(fStepLimit);
    calorLV->SetUserLimits(fStepLimit);
    layerLV->SetUserLimits(fStepLimit);
    absorberLV->SetUserLimits(fStepLimit);

    // Set additional contraints on the track, with G4UserSpecialCuts
    //
    // G4double maxLength = 2*trackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
    // trackerLV->SetUserLimits(new G4UserLimits(maxStep,
    //                                           maxLength,
    //                                           maxTime,
    //                                           minEkin));

    // print parameters
    G4cout << G4endl
        << "------------------------------------------------------------" << G4endl
        << "---> The calorimeter is " << m_nofLayers << " layers of: [ "
        << m_layerThickness/mm << "mm of " << pG4Material_LAr->GetName() 
        << "------------------------------------------------------------" << G4endl;

    // Visualization attributes
    worldLV->SetVisAttributes (G4VisAttributes::Invisible);

    G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    simpleBoxVisAtt->SetVisibility(true);
    calorLV->SetVisAttributes(simpleBoxVisAtt);

    // Always return the physical World
    return worldPV;
}

//------------------------------------------------------------------------------

void G4TPCDetectorConstruction::ConstructSDandField()
{
    // Create global magnetic field messenger.
    // Uniform magnetic field is then created automatically if
    // the field value is not zero.
    G4ThreeVector fieldValue = G4ThreeVector();
    fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);

    // Register the field messenger for deleting
    G4AutoDelete::Register(fMagFieldMessenger);
}

//------------------------------------------------------------------------------
