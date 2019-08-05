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

#include "G4Step.hh"

//------------------------------------------------------------------------------

G4ThreadLocal G4GlobalMagFieldMessenger* G4TPCDetectorConstruction::fMagFieldMessenger(nullptr);

//------------------------------------------------------------------------------

G4TPCDetectorConstruction::G4TPCDetectorConstruction() : G4VUserDetectorConstruction(),
    m_xCenter(0*mm),
    m_yCenter(0*mm),
    m_zCenter(0*mm),
    m_xWidth(1000*mm),
    m_yWidth(1000*mm),
    m_zWidth(1000*mm),
    m_nLayers(1000),
    m_pG4LogicalVolumeLAr(nullptr),
    fCheckOverlaps(true)
{
    m_xLow = m_xCenter - 0.5f * m_xWidth;
    m_yLow = m_yCenter - 0.5f * m_yWidth;
    m_zLow = m_zCenter - 0.5f * m_zWidth;
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
    const G4double worldScale(1.05);
    G4ThreeVector worldCenter(m_xCenter, m_yCenter, m_zCenter);

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
    G4VSolid* worldS = new G4Box("World", m_xWidth * worldScale / 2.f, m_yWidth * worldScale / 2.f, m_zWidth * worldScale / 2.f);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, defaultMaterial, "World");
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, worldCenter, worldLV, "World", 0, false, 0, fCheckOverlaps);

    // Calorimeter
    G4VSolid* calorimeterS = new G4Box("Calorimeter", m_xWidth/2, m_yWidth/2, m_zWidth/2);
    G4LogicalVolume* calorLV = new G4LogicalVolume(calorimeterS, defaultMaterial, "Calorimeter");
    new G4PVPlacement(0, worldCenter, calorLV, "Calorimeter", worldLV, false, 0, fCheckOverlaps);

    // Layers
    const G4double layerThickness(m_zWidth/m_nLayers);
    G4VSolid* layerS = new G4Box("Layer", m_xWidth/2, m_yWidth/2, layerThickness/2);
    G4LogicalVolume* layerLV = new G4LogicalVolume(layerS, defaultMaterial, "Layer");
    new G4PVReplica("Layer", layerLV, calorLV, kZAxis, m_nLayers, layerThickness);

    // Absorber
    G4VSolid* absorberS = new G4Box("Abso", m_xWidth/2, m_yWidth/2, layerThickness/2);
    G4LogicalVolume* absorberLV = new G4LogicalVolume(absorberS, pG4Material_LAr, "Abso");
    m_pG4LogicalVolumeLAr = new G4PVPlacement(0, worldCenter, absorberLV, "Abso", layerLV, false, 0, fCheckOverlaps);

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
        << "---> The calorimeter is " << m_nLayers << " layers of: [ "
        << layerThickness/mm << "mm of " << pG4Material_LAr->GetName()
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

Cell G4TPCDetectorConstruction::GetCell(const G4Step *pG4Step) const
{
    // ATTN: Cell index is zero at lowest x,y,z coordinate, then builds up along x then y then z
    const int xIndex = m_nLayers * (pG4Step->GetPreStepPoint()->GetPosition().x() - m_xLow) / (m_xWidth);
    const int yIndex = m_nLayers * (pG4Step->GetPreStepPoint()->GetPosition().y() - m_yLow) / (m_yWidth);
    const int zIndex = m_nLayers * (pG4Step->GetPreStepPoint()->GetPosition().z() - m_zLow) / (m_zWidth);
    const int index(xIndex + yIndex * m_nLayers + zIndex * m_nLayers * m_nLayers);

    const float deltaX(m_xWidth / m_nLayers);
    const int xBin(std::floor((pG4Step->GetPreStepPoint()->GetPosition().x() + 0.5f * deltaX)/deltaX));
    const float xCell(xBin * deltaX);

    const float deltaY(m_yWidth / m_nLayers);
    const int yBin(std::floor((pG4Step->GetPreStepPoint()->GetPosition().y() + 0.5f * deltaY)/deltaY));
    const float yCell(yBin * deltaY);

    const float deltaZ(m_zWidth / m_nLayers);
    const int zBin(std::floor((pG4Step->GetPreStepPoint()->GetPosition().z() + 0.5f * deltaZ)/deltaZ));
    const float zCell(zBin * deltaZ);

    return Cell(xCell, yCell, zCell, index);
}

//------------------------------------------------------------------------------
