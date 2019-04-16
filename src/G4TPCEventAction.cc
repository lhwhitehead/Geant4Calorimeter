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
// $Id: G4TPCEventAction.cc 75604 2013-11-04 13:17:26Z gcosmo $
// 
/// \file G4TPCEventAction.cc
/// \brief Implementation of the G4TPCEventAction class

#include "G4TPCEventAction.hh"
#include "G4TPCRunAction.hh"
#include "G4TPCAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//------------------------------------------------------------------------------

G4TPCEventAction::G4TPCEventAction() : G4UserEventAction()
{
}

//------------------------------------------------------------------------------

G4TPCEventAction::~G4TPCEventAction()
{
}

//------------------------------------------------------------------------------

void G4TPCEventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    pointToEnergy.clear();
}

//------------------------------------------------------------------------------

void G4TPCEventAction::EndOfEventAction(const G4Event* /*event*/)
{
//    pointToEnergy convert to output root file
/*
    // get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // fill histograms
    analysisManager->FillH1(1, fEnergyAbs);
    analysisManager->FillH1(2, fEnergyGap);
    analysisManager->FillH1(3, fTrackLAbs);
    analysisManager->FillH1(4, fTrackLGap);

    for (unsigned int i = 0; i < m_Z.size(); i++)
    {
        analysisManager->FillH1(5, m_Z.at(i));
        analysisManager->FillH1(6, m_Layer.at(i));
        analysisManager->FillH1(7, m_Energy.at(i));
    }

    // fill ntuple
    analysisManager->FillNtupleDColumn(0, fEnergyAbs);
    analysisManager->FillNtupleDColumn(1, fEnergyGap);
    analysisManager->FillNtupleDColumn(2, fTrackLAbs);
    analysisManager->FillNtupleDColumn(3, fTrackLGap);

    for (unsigned int i = 0; i < 30; i++)
    {
        analysisManager->FillNtupleDColumn((2*i)+4, m_AbsEnergy.at(i));
        analysisManager->FillNtupleDColumn((2*i)+5, m_GapEnergy.at(i));
    }

    analysisManager->AddNtupleRow();
*/
}

//------------------------------------------------------------------------------

G4TPCEventAction::CartesianVector::CartesianVector(const float x, const float y, const float z) :
    m_x(x),
    m_y(y),
    m_z(z)
{
}
