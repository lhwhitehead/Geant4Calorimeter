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
// $Id: G4TPCDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file G4TPCDetectorConstruction.hh
/// \brief Definition of the G4TPCDetectorConstruction class

#ifndef G4TPCDetectorConstruction_h
#define G4TPCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "Cell.hh"

#include "globals.hh"
#include <math.h>

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;
class G4UserLimits;
class G4Step;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class G4TPCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    G4TPCDetectorConstruction();
    virtual ~G4TPCDetectorConstruction();
    virtual G4VPhysicalVolume *Construct();
    virtual void ConstructSDandField();

    const G4VPhysicalVolume *GetLArPV() const;

    /**
     *  @brief  Get the index of the cell for the given position
     *
     *  @return the cell index
     */
    Cell GetCell(const G4Step *pG4Step) const;

private:
    void DefineMaterials();
    G4VPhysicalVolume *DefineVolumes();

    // data members
    static G4ThreadLocal G4GlobalMagFieldMessenger *fMagFieldMessenger;

    G4double             m_xCenter;              ///<
    G4double             m_yCenter;              ///<
    G4double             m_zCenter;              ///<
    G4double             m_xWidth;               ///<
    G4double             m_yWidth;               ///<
    G4double             m_zWidth;               ///<
    G4double             m_xLow;
    G4double             m_yLow;
    G4double             m_zLow;
    G4int                m_nLayers;

    G4VPhysicalVolume*   m_pG4LogicalVolumeLAr;  ///< the absorber physical volume
    G4bool               fCheckOverlaps;         ///< option to activate checking of volumes overlaps
};

//------------------------------------------------------------------------------

inline const G4VPhysicalVolume *G4TPCDetectorConstruction::GetLArPV() const
{
    return m_pG4LogicalVolumeLAr;
}

#endif

