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
    EventContainer();

    /**
     *  Destructor
     */
    ~EventContainer();

    /**
     *  Increment variables for next event
     */
    void BeginOfEventAction();

    /**
     *  Save events to xml
     */
    void SaveXml();

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
    typedef std::vector<MCParticleList> MCParticleListVector;
    typedef std::vector<CellList> CellListVector;

    int                  m_eventNumber;
    MCParticleListVector m_mcParticles;
    CellListVector       m_cells;
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline CellList &EventContainer::GetCurrentCellList()
{
    if ((m_cells.size() + 1) == m_eventNumber)
        m_cells.push_back(CellList());

    return m_cells.at(m_eventNumber);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline MCParticleList &EventContainer::GetCurrentMCParticleList()
{
//    if (m_mcParticles.size() < m_eventNumber)
//        m_mcParticles.push_back(MCParticleList());

    return m_mcParticles.at(m_eventNumber);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void EventContainer::SetCurrentMCParticleList(const MCParticleList &mcParticleList)
{
    m_mcParticles.at(m_eventNumber) = mcParticleList;
}

#endif // #ifndef EVENT_CONTAINER_H
