/**
 *  @file   include/EventContainer.cc
 *
 *  @brief  Header file for the EventContainer class.
 *
 *  $Log: $
 */

#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H 1

#include <iostream>

#include "Cell.hh"
#include "InputParameters.hh"
#include "MCParticle.hh"

/**
 *  @brief EventContainer class
 */
class EventContainer
{
public:
    /**
     *  Default constructor
     */
    EventContainer(const InputParameters &parameters);

    /**
     *  Destructor
     */
    ~EventContainer();

    /**
     *  Increment variables for current event
     */
    void BeginOfEventAction();

    /**
     *  Increment variables for next event
     */
    void EndOfEventAction();

    /**
     *  Save events to xml
     */
    void SaveXml();

    /**
    * Save events to text file
    */
    void SaveText() const;

    /**
     *  Get the current cell list
     */
    CellList &GetCurrentCellList();

    /**
     *  Get the current MCParticle list
     */
    MCParticleList &GetCurrentMCParticleList();

    /**
     *  Set the current MCParticle list
     */
    void SetCurrentMCParticleList(const MCParticleList &mcParticleList);

private:

    int GetMainVisibleTrackID(const MCParticleList &particles, const IntFloatVector &trkIDToEnergy) const;

    typedef std::vector<MCParticleList> MCParticleListVector;
    typedef std::vector<CellList> CellListVector;

    unsigned int         m_eventNumber;
    MCParticleListVector m_mcParticles;
    CellListVector       m_cells;
    InputParameters      m_parameters;
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline CellList &EventContainer::GetCurrentCellList()
{
    return m_cells.at(m_eventNumber);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline MCParticleList &EventContainer::GetCurrentMCParticleList()
{
    return m_mcParticles.at(m_eventNumber);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void EventContainer::SetCurrentMCParticleList(const MCParticleList &mcParticleList)
{
    m_mcParticles.at(m_eventNumber) = mcParticleList;
}

#endif // #ifndef EVENT_CONTAINER_H
