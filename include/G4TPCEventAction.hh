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
// $Id: G4TPCEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file G4TPCEventAction.hh
/// \brief Definition of the G4TPCEventAction class

#ifndef G4TPCEventAction_h
#define G4TPCEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

/// Event action class
///
/// It defines data members to hold the m_Energy deposit and track lengths
/// of charged particles in Absober and Gap m_Layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class G4TPCEventAction : public G4UserEventAction
{
  public:
    G4TPCEventAction();
    virtual ~G4TPCEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    void AddAbs(G4double de, G4double dl);
    void AddAbs2(G4double de, G4double dl);
    void AddGap(G4double de, G4double dl);
    void AddGap2(G4double de, G4double dl);
    void AddEZ(G4double de, G4double z, G4int layer);
    void AddAbsE(G4double de, G4int layer);
    void AddGapE(G4double de, G4int layer);

  private:
    G4double  fEnergyAbs;
    G4double  fEnergyGap;
    G4double  fTrackLAbs;
    G4double  fTrackLGap;
    std::vector<float> m_Z;
    std::vector<float> m_Energy;
    std::vector<int> m_Layer;
    std::vector<float> m_AbsEnergy;
    std::vector<float> m_GapEnergy;
};

// inline functions

inline void G4TPCEventAction::AddAbs(G4double de, G4double dl) {
  fEnergyAbs += de;
  fTrackLAbs += dl;
}

inline void G4TPCEventAction::AddAbs2(G4double de, G4double dl) {
  fEnergyAbs += de;
  fTrackLAbs += dl;
}

inline void G4TPCEventAction::AddGap(G4double de, G4double dl) {
  fEnergyGap += de;
  fTrackLGap += dl;
}

inline void G4TPCEventAction::AddGap2(G4double de, G4double dl) {
  fEnergyGap += de;
  fTrackLGap += dl;
}

inline void G4TPCEventAction::AddEZ(G4double de, G4double z, G4int layer){
  m_Energy.push_back(de);
  m_Z.push_back(z);
  m_Layer.push_back(layer);
}

inline void G4TPCEventAction::AddAbsE(G4double de, G4int layer){
  if (layer >= 0 and layer < 30)
    m_AbsEnergy.at(layer) += de;
}

inline void G4TPCEventAction::AddGapE(G4double de, G4int layer){
  if (layer >= 0 and layer < 30)
    m_GapEnergy.at(layer) += de;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

