/**
 *  @file   src/Cell.cc
 *
 *  @brief  Implementation of the Cell class.
 *
 *  $Log: $
 */

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

void CellList::AddEnergyDeposition(Cell *pCell)
{
    if (m_idCellMap.find(pCell->GetIdx()) == m_idCellMap.end())
    {
        m_idCellMap.insert(IntCellMap::value_type(pCell->GetIdx(), pCell));
    }
    else
    {
        m_idCellMap.at(pCell->GetIdx())->AddEnergy(pCell->GetEnergy());
    }
}

