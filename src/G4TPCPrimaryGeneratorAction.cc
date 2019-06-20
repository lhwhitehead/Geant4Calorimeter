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
// $Id: G4TPCPrimaryGeneratorAction.cc 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file G4TPCPrimaryGeneratorAction.cc
/// \brief Implementation of the G4TPCPrimaryGeneratorAction class

#include <random>

#include "G4TPCPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//------------------------------------------------------------------------------

G4TPCPrimaryGeneratorAction::G4TPCPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(),
    m_pG4ParticleGun(0)
{
    G4int numberOfParticleInstances = 1;
    m_pG4ParticleGun = new G4ParticleGun(numberOfParticleInstances);

    // default particle kinematic
    G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
    m_pG4ParticleGun->SetParticleDefinition(particleDefinition);
    m_pG4ParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    m_pG4ParticleGun->SetParticleEnergy(50.*MeV);
}

//------------------------------------------------------------------------------

G4TPCPrimaryGeneratorAction::~G4TPCPrimaryGeneratorAction()
{
    delete m_pG4ParticleGun;
}

//------------------------------------------------------------------------------

void G4TPCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // This function is called at the begining of event

    // In order to avoid dependence of PrimaryGeneratorAction
    // on DetectorConstruction class we get world volume
    // from G4LogicalVolumeStore

    G4double worldZHalfLength = 0;
    G4LogicalVolume *worlLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    G4Box* worldBox = 0;

    if ( worlLV)
        worldBox = dynamic_cast< G4Box*>(worlLV->GetSolid());

    if ( worldBox )
    {
        worldZHalfLength = worldBox->GetZHalfLength();
    }
    else
    {
        G4ExceptionDescription msg;
        msg << "World volume of box not found." << G4endl;
        msg << "Perhaps you have changed geometry." << G4endl;
        msg << "The gun will be place in the center.";
        G4Exception("G4TPCPrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002", JustWarning, msg);
    }

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.,50.0);
    std::normal_distribution<double> distribution2(0.,0.05);
    std::normal_distribution<double> distribution3(1.,0.01);

    // Set gun position
    for (int particle = 0; particle < 2; particle++)
    {
        G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
        m_pG4ParticleGun->SetParticleDefinition(particleDefinition);
        m_pG4ParticleGun->SetParticlePosition(G4ThreeVector(distribution(generator), distribution(generator), -worldZHalfLength));
        m_pG4ParticleGun->SetParticleMomentumDirection(G4ThreeVector(distribution2(generator), distribution2(generator), distribution3(generator)));
        m_pG4ParticleGun->SetParticleEnergy(1.*GeV);
        m_pG4ParticleGun->GeneratePrimaryVertex(anEvent);
    }
}

