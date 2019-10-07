/**
 *  @file   src/EventContainer.cc
 *
 *  @brief  Implementation of the EventContainer class.
 *
 *  $Log: $
 */

#include <fstream>

#include "tinyxml.hh"
#include "EventContainer.hh"

EventContainer::EventContainer(const InputParameters &parameters) :
    m_eventNumber(0),
    m_parameters(parameters)
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
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::EndOfEventAction()
{
    m_eventNumber++;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::SaveXml()
{
    TiXmlDocument tiXmlDocument;

    TiXmlElement *pRunTiXmlElement = new TiXmlElement("Run");
    tiXmlDocument.LinkEndChild(pRunTiXmlElement);

    for (unsigned int eventNumber = 0; eventNumber < m_eventNumber; eventNumber++)
    {
        TiXmlElement *pEventTiXmlElement = new TiXmlElement("Event");
        pRunTiXmlElement->LinkEndChild(pEventTiXmlElement);

        const CellList &cellList(m_cells.at(eventNumber));
        const MCParticleList &mcParticleList(m_mcParticles.at(eventNumber));

        // Cells
        for (const auto iter : cellList.m_idCellMap)
        {
            const Cell *pCell(iter.second);

            IntFloatVector trackIdToEnergy(cellList.m_mcComponents.at(pCell->GetIdx()));

            int mainVisibleMCTrackId = GetMainVisibleTrackID(mcParticleList,trackIdToEnergy);
            if(mainVisibleMCTrackId < 0) continue;

            TiXmlElement *pTiXmlElement = new TiXmlElement("Cell");
            pTiXmlElement->SetAttribute("Id", pCell->GetIdx());
            pTiXmlElement->SetAttribute("MCId", mainVisibleMCTrackId);
            pTiXmlElement->SetDoubleAttribute("X", pCell->GetX());
            pTiXmlElement->SetDoubleAttribute("Y", pCell->GetY());
            pTiXmlElement->SetDoubleAttribute("Z", pCell->GetZ());
            pTiXmlElement->SetDoubleAttribute("Energy", pCell->GetEnergy());
            pEventTiXmlElement->LinkEndChild(pTiXmlElement);
        }

        // MCParticles
        for (const auto iter : mcParticleList.m_mcParticles)
        {
            const MCParticle *pMCParticle(iter.second);

            TiXmlElement *pTiXmlElement = new TiXmlElement("MCParticle");
            pTiXmlElement->SetAttribute("Id", pMCParticle->GetTrackId());
            pTiXmlElement->SetAttribute("PDG", pMCParticle->GetPDGCode());
            pTiXmlElement->SetAttribute("ParentId", pMCParticle->GetParent());
            pTiXmlElement->SetDoubleAttribute("Mass", pMCParticle->GetMass());
            pTiXmlElement->SetDoubleAttribute("Energy", pMCParticle->GetEnergy());
            pTiXmlElement->SetDoubleAttribute("StartX", pMCParticle->GetPositionX());
            pTiXmlElement->SetDoubleAttribute("StartY", pMCParticle->GetPositionY());
            pTiXmlElement->SetDoubleAttribute("StartZ", pMCParticle->GetPositionZ());
            pTiXmlElement->SetDoubleAttribute("EndX", pMCParticle->GetEndPositionX());
            pTiXmlElement->SetDoubleAttribute("EndY", pMCParticle->GetEndPositionY());
            pTiXmlElement->SetDoubleAttribute("EndZ", pMCParticle->GetEndPositionZ());
            pTiXmlElement->SetDoubleAttribute("MomentumX", pMCParticle->GetMomentumX());
            pTiXmlElement->SetDoubleAttribute("MomentumY", pMCParticle->GetMomentumY());
            pTiXmlElement->SetDoubleAttribute("MomentumZ", pMCParticle->GetMomentumZ());
            pEventTiXmlElement->LinkEndChild(pTiXmlElement);
        }
    }

    tiXmlDocument.SaveFile(m_parameters.m_outputFileName.c_str());
    tiXmlDocument.Clear();
}

void EventContainer::SaveText() const{

  // We use the supplied name as the root
  


  for(unsigned int event = 0; event < m_eventNumber; ++event){
    std::string thisFile = m_parameters.m_outputFileName + "_" + std::to_string(event) + ".txt";
    std::ofstream output;
    output.open(thisFile);
    output << "id/I:trkid/I:x/F:y/F:z/F:energy/F\n";

    // Now we want to write out the positions and energy of each cell
    const CellList &cellList(m_cells.at(event));
    const MCParticleList &mcParticleList(m_mcParticles.at(event));

    // Cells
    for (const auto iter : cellList.m_idCellMap)
    {
      const Cell *pCell(iter.second);

      IntFloatVector trackIdToEnergy(cellList.m_mcComponents.at(pCell->GetIdx()));

      int mainVisibleMCTrackId = GetMainVisibleTrackID(mcParticleList,trackIdToEnergy);

      output << pCell->GetIdx() << " " << mainVisibleMCTrackId << " "
             << pCell->GetX() << " " << pCell->GetY() << " " << pCell->GetZ() << " "
             << pCell->GetEnergy() << "\n";

    }

    output.close();
  }
}

int EventContainer::GetMainVisibleTrackID(const MCParticleList &particles, const IntFloatVector &trkIDToEnergy) const{
  // ATTN : Doesn't account for track ID offset, but not using for now
  int mainMCTrackId(-1);
  float largestEnergyContribution(0.f);
  for (const auto contribution : trkIDToEnergy)
  {
    if (contribution.second > largestEnergyContribution)
    {
      largestEnergyContribution = contribution.second;
      mainMCTrackId = contribution.first;
    }
  }

  if (largestEnergyContribution < std::numeric_limits<float>::epsilon())
    return mainMCTrackId;

  int mainVisibleMCTrackId(mainMCTrackId);
  while (!particles.KnownParticle(mainVisibleMCTrackId))
  {
    if (particles.m_parentIdMap.find(mainVisibleMCTrackId) != particles.m_parentIdMap.end())
    {
      mainVisibleMCTrackId = particles.m_parentIdMap.at(mainVisibleMCTrackId);
    }
    else
    {
      mainVisibleMCTrackId = 0;
      break;
    }
  }

  return mainVisibleMCTrackId;
}


