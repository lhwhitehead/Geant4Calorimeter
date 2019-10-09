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
// $Id: G4TPCRunAction.hh 74265 2013-10-02 14:41:20Z gcosmo $
// 
/// \file G4TPCRunAction.hh
/// \brief Definition of the G4TPCRunAction class

#ifndef G4TPCRunAction_h
#define G4TPCRunAction_h 1

#include "G4MCParticleUserAction.hh"
#include "G4UserRunAction.hh"

#include "globals.hh"

class G4Run;
class G4TPCRunMessenger;

/// Run action class
///
/// It accumulates statistic and computes dispersion of the energy deposit 
/// and track lengths of charged particles with use of analysis tools:
/// H1D histograms are created in BeginOfRunAction() for the following 
/// physics quantities:
/// - Edep in absorber
/// - Edep in gap
/// - Track length in absorber
/// - Track length in gap
/// The same values are also saved in the ntuple.
/// The histograms and ntuple are saved in the output file in a format
/// accoring to a selected technology in G4TPCAnalysis.hh.
///
/// In EndOfRunAction(), the accumulated statistic and computed 
/// dispersion is printed.
///

class G4TPCRunAction : public G4UserRunAction
{
public:
    G4TPCRunAction(EventContainer *pEventContainer, G4MCParticleUserAction *pG4MCParticleUserAction);
    virtual ~G4TPCRunAction();

    virtual void BeginOfRunAction(const G4Run *pG4Run);
    virtual void EndOfRunAction(const G4Run *pG4Run);

//    void SetOutputFileType(G4String name){fOutputFileType=name;};
    void SetSaveXml(bool val){fSaveXml = val;};  
    void SetSaveText(bool val){fSaveText = val;};  
    void SetSaveImages(bool val){fSaveImages = val;};  

private:
    EventContainer         *m_pEventContainer;
    G4MCParticleUserAction *m_pG4MCParticleUserAction;
    G4TPCRunMessenger *fMessenger;

//    std::string fOutputFileType;
    bool fSaveXml;
    bool fSaveText;
    bool fSaveImages;
};

#endif
