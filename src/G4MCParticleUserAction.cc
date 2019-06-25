/**
 *  @file   src/G4MCParticleUserAction.cc
 *
 *  @brief  Implementation of the geant4 MCParticle user action class.
 *
 *  $Log: $
 */

#include "G4Event.hh"
#include "G4VProcess.hh"
#include "G4Run.hh"
#include "G4Step.hh"
#include "G4MCParticleUserAction.hh"

G4MCParticleUserAction::G4MCParticleUserAction(EventContainer *pEventContainer, const double energyCut) :
    m_pEventContainer(pEventContainer),
    m_keepEMShowerDaughters(false),
    m_energyCut(energyCut * CLHEP::GeV),
    m_currentPdgCode(0),
    m_currentTrackId(std::numeric_limits<int>::max()),
    m_trackIdOffset(0)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

G4MCParticleUserAction::~G4MCParticleUserAction()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::BeginOfRunAction(const G4Run * /*pG4Run*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::EndOfRunAction(const G4Run * /*pG4Run*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::BeginOfEventAction(const G4Event * /*pG4Event*/)
{
    m_currentMCParticleInfo.Clear();
    m_mcParticleList.Clear();
    m_currentTrackId = std::numeric_limits<int>::max();
    m_parentIdMap.clear();
    m_currentPdgCode = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::EndOfEventAction(const G4Event * /*pG4Event*/)
{
    for (auto iter : m_mcParticleList.m_mcParticles)
    {
        const int trackId(iter.first);
        MCParticle *pMCParticle(iter.second);

        const int parentTrackId(pMCParticle->GetParent());
        if (parentTrackId <= 0 || parentTrackId == std::numeric_limits<int>::max())
            continue;

        IntMCParticleMap::iterator parentIter(m_mcParticleList.m_mcParticles.find(parentTrackId));
        if (parentIter != m_mcParticleList.m_mcParticles.end())
        {
             MCParticle *pParentParticle((*parentIter).second);
             pParentParticle->AddDaughter(trackId);
        }
    }

    m_mcParticleList.m_parentIdMap = m_parentIdMap;
    m_pEventContainer->SetCurrentMCParticleList(m_mcParticleList);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

int G4MCParticleUserAction::GetParent(const int trackId) const
{
    int parentId(std::numeric_limits<int>::max());

    IntIntMap::const_iterator iter = m_parentIdMap.find(trackId);

    while (iter != m_parentIdMap.end())
    {
        parentId = (*iter).second;
        iter = m_parentIdMap.find(parentId);
    }

     return parentId;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

bool G4MCParticleUserAction::KnownParticle(const int trackId) const
{
    return m_mcParticleList.KnownParticle(trackId);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::PreUserTrackingAction(const G4Track *pG4Track)
{
    G4ParticleDefinition *pG4ParticleDefinition = pG4Track->GetDefinition();
    int pdgCode(pG4ParticleDefinition->GetPDGEncoding());
    int trackID(pG4Track->GetTrackID() + m_trackIdOffset);
    int parentTrackId(pG4Track->GetParentID() + m_trackIdOffset);

    m_currentPdgCode = pdgCode;

    const G4DynamicParticle *pG4DynamicParticle(pG4Track->GetDynamicParticle());
    const G4PrimaryParticle *pG4PrimaryParticle(pG4DynamicParticle->GetPrimaryParticle());

    std::string processName("");

    if (pG4PrimaryParticle)
    {
        processName = "primary";
        parentTrackId = 0;
    }
    else
    {
        processName = pG4Track->GetCreatorProcess()->GetProcessName();
        // ATTN : Scrap EM shower daughters
        if (!m_keepEMShowerDaughters
                && (processName.find("conv")           != std::string::npos
                || processName.find("LowEnConversion") != std::string::npos
                || processName.find("Pair")            != std::string::npos
                || processName.find("compt")           != std::string::npos
                || processName.find("Compt")           != std::string::npos
                || processName.find("Brem")            != std::string::npos
                || processName.find("phot")            != std::string::npos
                || processName.find("Photo")           != std::string::npos
                || processName.find("Ion")             != std::string::npos
                || processName.find("annihil")         != std::string::npos))
        {
            m_currentMCParticleInfo.Clear();
            m_parentIdMap[trackID] = parentTrackId;
            return;
        }

        // ATTN : Energy Cut
        double energy(pG4Track->GetKineticEnergy());
        if (energy < m_energyCut)
        {
            m_currentMCParticleInfo.Clear();
            m_parentIdMap[trackID] = parentTrackId;
        }

        if (!this->KnownParticle(parentTrackId))
        {
            m_parentIdMap[trackID] = parentTrackId;
            int pid(this->GetParent(parentTrackId));

            if (!this->KnownParticle(pid))
            {
                std::cout << "Unknown parent" << std::endl;
            }
            else
            {
                parentTrackId = pid;
            }
        }
    }

    double mass(pG4DynamicParticle->GetMass()/CLHEP::GeV);
    m_currentMCParticleInfo.Clear();
    m_currentMCParticleInfo.m_pMCParticle = new MCParticle(trackID, pdgCode, parentTrackId, mass);
    m_currentMCParticleInfo.m_generatedParticleIndex = 0;
    m_currentMCParticleInfo.m_keep = true;

    m_mcParticleList.Add(m_currentMCParticleInfo.m_pMCParticle, pG4Track->GetTrackID());
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::PostUserTrackingAction(const G4Track * /*pG4Track*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4MCParticleUserAction::UserSteppingAction(const G4Step *pG4Step)
{
    if (!m_currentMCParticleInfo.m_pMCParticle)
        return;

    const G4StepPoint *pPreStepPoint(pG4Step->GetPreStepPoint());

    const G4ThreeVector position(pPreStepPoint->GetPosition());
    const double time(pPreStepPoint->GetGlobalTime());
    const TLorentzVector fourPos(position.x() / CLHEP::mm, position.y() / CLHEP::mm, position.z() / CLHEP::mm, time / CLHEP::ns);

    const G4ThreeVector momentum(pPreStepPoint->GetMomentum());
    const double energy(pPreStepPoint->GetTotalEnergy());
    const TLorentzVector fourMom(momentum.x() / CLHEP::GeV, momentum.y() / CLHEP::GeV, momentum.z() / CLHEP::GeV, energy / CLHEP::GeV);

    m_currentMCParticleInfo.m_pMCParticle->AddTrajectoryPoint(fourPos, fourMom);
}

