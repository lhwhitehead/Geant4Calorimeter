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

#include <chrono>
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

G4TPCPrimaryGeneratorAction::G4TPCPrimaryGeneratorAction(const InputParameters &parameters) :
    G4VUserPrimaryGeneratorAction(),
    m_pG4ParticleGun(0),
    m_parameters(parameters)
{
    G4int numberOfParticleInstances = 1;
    m_pG4ParticleGun = new G4ParticleGun(numberOfParticleInstances);

    // default particle kinematic
    G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(m_parameters.m_species.c_str());
    m_pG4ParticleGun->SetParticleDefinition(particleDefinition);
    m_pG4ParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    m_pG4ParticleGun->SetParticleEnergy(m_parameters.m_energy*GeV);
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

    G4LogicalVolume *worlLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    G4LogicalVolume *tpcLV = G4LogicalVolumeStore::GetInstance()->GetVolume("Calorimeter");
    G4Box *worldBox = nullptr;
    G4Box *tpcBox = nullptr;

    if (worlLV)
        worldBox = dynamic_cast<G4Box*>(worlLV->GetSolid());

    if (tpcLV)
        tpcBox = dynamic_cast<G4Box*>(tpcLV->GetSolid());

    if (!worldBox || !tpcBox)
    {
        G4ExceptionDescription msg;
        msg << "Unable to cast G4LogicalVolume to G4Box for world and TPC volumes." << G4endl;
        G4Exception("G4TPCPrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002", EventMustBeAborted, msg);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    CLHEP::HepRandom::setTheSeed(seed);

    // Set gun position
    for (int particle = 0; particle < m_parameters.m_nParticlesPerEvent; particle++)
    {
        G4ThreeVector startPoint(tpcBox->GetPointOnSurface());
        G4ThreeVector endPoint(tpcBox->GetPointOnSurface());

        while (std::fabs(startPoint.x() - endPoint.x()) < std::numeric_limits<double>::epsilon() ||
               std::fabs(startPoint.y() - endPoint.y()) < std::numeric_limits<double>::epsilon() ||
               std::fabs(startPoint.z() - endPoint.z()) < std::numeric_limits<double>::epsilon())
        {
            endPoint = tpcBox->GetPointOnSurface();
        }

        G4ThreeVector direction(endPoint - startPoint);

        G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(m_parameters.m_species.c_str());
        m_pG4ParticleGun->SetParticleDefinition(particleDefinition);
        m_pG4ParticleGun->SetParticlePosition(startPoint);
        m_pG4ParticleGun->SetParticleMomentumDirection(direction);
        m_pG4ParticleGun->SetParticleEnergy(m_parameters.m_energy*GeV);
        m_pG4ParticleGun->GeneratePrimaryVertex(anEvent);
    }
}

