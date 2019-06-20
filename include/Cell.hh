/**
 *  @file   include/Cell.cc
 *
 *  @brief  Header file for the Cell class.
 *
 *  $Log: $
 */

#ifndef CELL_H
#define CELL_H 1

#include <map>
#include <vector>

/**
 *  @brief Cell class
 */
class Cell
{
public:
    /**
     *  Default constructor
     */
    Cell(const float x, const float y, const float z, const int idx);

    /**
     *  Destructor
     */
    ~Cell();

    int GetIdx() const;
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetEnergy() const;

    void AddEnergy(const float energy);

private:
    int   m_idx;    ///< Index
    float m_x;      ///< X position
    float m_y;      ///< Y position
    float m_z;      ///< Z position
    float m_energy; ///< Enegry
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int Cell::GetIdx() const
{
    return m_idx;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetX() const
{
    return m_x;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetY() const
{
    return m_y;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetZ() const
{
    return m_z;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetEnergy() const
{
    return m_energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void Cell::AddEnergy(const float energy)
{
    m_energy += energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

typedef std::map<int, Cell*> IntCellMap;
typedef std::pair<int, float> IntFloatPair;
typedef std::vector<IntFloatPair> IntFloatVector;
typedef std::map<int, IntFloatVector> MCComponents;

/**
 *  @brief CellList class
 */
class CellList
{
public:
    /**
     *  Constructor
     */
    CellList();

    /**
     *  Destructor
     */
    ~CellList();

    /**
     *  Add energy deposition from given geant track
     */
    void AddEnergyDeposition(Cell *pCell, const int geantTrackId);

    IntCellMap     m_idCellMap;
    MCComponents   m_mcComponents;
};

#endif // #ifndef CELL_H
