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

#include <map>
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

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

private:
    class CartesianVector
    {
    public:
        CartesianVector(const float x, const float y, const float z);
        float GetX() const;
        float GetY() const;
        float GetZ() const;
        void SetX(const float x);
        void SetY(const float y);
        void SetZ(const float z);

    private:
        float m_x;
        float m_y;
        float m_z;
    };

    std::map<CartesianVector, float> pointToEnergy;
};

//------------------------------------------------------------------------------

inline float G4TPCEventAction::CartesianVector::GetX() const
{
    return m_x;
}

//------------------------------------------------------------------------------

inline void G4TPCEventAction::CartesianVector::SetX(const float x)
{
    m_x = x;
}

//------------------------------------------------------------------------------

inline float G4TPCEventAction::CartesianVector::GetY() const
{
    return m_y;
}

//------------------------------------------------------------------------------

inline void G4TPCEventAction::CartesianVector::SetY(const float y)
{
    m_y = y;
}

//------------------------------------------------------------------------------

inline float G4TPCEventAction::CartesianVector::GetZ() const
{
    return m_z;
}

//------------------------------------------------------------------------------

inline void G4TPCEventAction::CartesianVector::SetZ(const float z)
{
    m_z = z;
}

#endif
