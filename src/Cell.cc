/**
 *  @file   src/Cell.cc
 *
 *  @brief  Implementation of the Cell class.
 *
 *  $Log: $
 */

#include <algorithm>

#include "Cell.hh"

Cell::Cell(const float x, const float y, const float z, const int idx) :
    m_idx(idx),
    m_x(x),
    m_y(y),
    m_z(z),
    m_energy(0.f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

Cell::~Cell()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

CellList::CellList()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

CellList::~CellList()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void CellList::AddEnergyDeposition(Cell *pCell, const int geantTrackId)
{
    if (m_idCellMap.find(pCell->GetIdx()) == m_idCellMap.end())
    {
        m_idCellMap.insert(IntCellMap::value_type(pCell->GetIdx(), pCell));

        IntFloatVector mcToEnergyVector;
        mcToEnergyVector.push_back(IntFloatPair(geantTrackId, pCell->GetEnergy()));
        m_mcComponents.insert(MCComponents::value_type(pCell->GetIdx(), mcToEnergyVector));
    }
    else
    {
        m_idCellMap.at(pCell->GetIdx())->AddEnergy(pCell->GetEnergy());

        IntFloatVector mcToEnergyVector(m_mcComponents.at(pCell->GetIdx()));
        auto it = std::find_if(mcToEnergyVector.begin(), mcToEnergyVector.end(), [&geantTrackId](IntFloatPair& iter){ return iter.first == geantTrackId;} );

        if (it == mcToEnergyVector.end())
        {
            mcToEnergyVector.push_back(IntFloatPair(geantTrackId, pCell->GetEnergy()));
        }
        else
        {
            (*it).second += pCell->GetEnergy();
        }

        delete pCell;
    }
}

