/**
 *  @file   src/EventContainer.cc
 *
 *  @brief  Implementation of the EventContainer class.
 *
 *  $Log: $
 */

#include "tinyxml.hh"
#include "EventContainer.hh"

EventContainer::EventContainer() :
    m_eventNumber(0)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

EventContainer::~EventContainer()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::BeginOfEventAction()
{
    m_mcParticles.push_back(MCParticleList());
    m_cells.push_back(CellList());
    m_eventNumber++;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::SaveXml()
{
    TiXmlDocument tiXmlDocument;

    TiXmlElement *pHeadTiXmlElement = new TiXmlElement("Run");
    tiXmlDocument.LinkEndChild(pHeadTiXmlElement);

    for (unsigned int eventNumber = 0; eventNumber < m_mcParticles.size(); eventNumber++)
    {
        // Cells
std::cout << "Here" << std::endl;
        const CellList &cellList(m_cells.at(eventNumber));
std::cout << "Here2" << std::endl;
        for (const auto iter : cellList.m_idCellMap)
        {
            const Cell *pCell(iter.second);

            TiXmlElement *pTiXmlElement = new TiXmlElement("Cell");
            pTiXmlElement->SetAttribute("CellId", pCell->GetIdx());
            pTiXmlElement->SetDoubleAttribute("X", pCell->GetX());
            pTiXmlElement->SetDoubleAttribute("Y", pCell->GetY());
            pTiXmlElement->SetDoubleAttribute("Z", pCell->GetZ());
            pTiXmlElement->SetDoubleAttribute("Energy", pCell->GetEnergy());
            pHeadTiXmlElement->LinkEndChild(pTiXmlElement);
        }
    }

    tiXmlDocument.SaveFile("Events.xml");
    tiXmlDocument.Clear();
}

