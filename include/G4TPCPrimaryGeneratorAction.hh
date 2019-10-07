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
// $Id: G4TPCPrimaryGeneratorAction.hh 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file G4TPCPrimaryGeneratorAction.hh
/// \brief Definition of the G4TPCPrimaryGeneratorAction class

#ifndef G4TPCPrimaryGeneratorAction_h
#define G4TPCPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "InputParameters.hh"

class G4TPCPrimaryGeneratorMessenger;
class G4ParticleGun;
class G4Event;
class ParseGENIETrackerFile;

/// The primary generator action class with particle gum.
///
/// It defines a single particle which hits the calorimeter
/// perpendicular to the input face. The type of the particle
/// can be changed via the G4 build-in commands of G4ParticleGun class
/// (see the macros provided with this example).

class G4TPCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    G4TPCPrimaryGeneratorAction(const InputParameters &parameters);
    virtual ~G4TPCPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

    void SetRandomFlag(G4bool value);

    // Tracker file options used by the messenger class
    void UseTrackerFile(bool val){fUseTrackerFile = val;};
    void SetTrackerFile(G4String name); //{fTrackerFile = name;};

private:
    G4TPCPrimaryGeneratorMessenger *fMessenger;

    G4ParticleGun   *m_pG4ParticleGun; ///< G4 particle gun
    InputParameters  m_parameters;     ///< Input parameters

    ParseGENIETrackerFile *fParser;
    bool fUseTrackerFile;
    G4String fTrackerFile;
};

#endif


