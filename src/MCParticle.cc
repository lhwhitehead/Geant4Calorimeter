/**
 *  @file   src/MCParticle.cc
 *
 *  @brief  Implementation of the MCParticle class.
 *
 *  $Log: $
 */

#include <iterator>

#include "MCParticle.hh"

MCParticle::MCParticle() :
    m_status(std::numeric_limits<int>::max()),
    m_trackId(std::numeric_limits<int>::max()),
    m_pdgCode(std::numeric_limits<int>::max()),
    m_parent(std::numeric_limits<int>::max()),
    m_trajectory(Trajectory()),
    m_mass(std::numeric_limits<double>::max())
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

MCParticle::MCParticle(const int trackId, const int pdg, const int parent, const double mass, const int status) :
    m_status(status),
    m_trackId(trackId),
    m_pdgCode(pdg),
    m_parent(parent),
    m_trajectory(Trajectory()),
    m_mass(mass)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

MCParticle::~MCParticle()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

MCParticle::Trajectory::Trajectory()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

MCParticle::Trajectory::Trajectory(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV)
{
    m_trajectoryPointVector.push_back(std::make_pair(vtxTLV, momentumTLV));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

const TLorentzVector &MCParticle::Trajectory::GetPosition(const int i) const
{
    TrajectoryPointVector::const_iterator iter = m_trajectoryPointVector.begin();
    std::advance(iter, i);
    return (*iter).first;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

const TLorentzVector &MCParticle::Trajectory::GetMomentum(const int i) const
{
    TrajectoryPointVector::const_iterator iter = m_trajectoryPointVector.begin();
    std::advance(iter, i);
    return (*iter).second;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void MCParticle::Trajectory::AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV)
{
    m_trajectoryPointVector.push_back(std::make_pair(vtxTLV, momentumTLV));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

MCParticleInfo::MCParticleInfo() :
    m_pMCParticle(nullptr),
    m_keep(false),
    m_generatedParticleIndex(std::numeric_limits<int>::max())
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

MCParticleList::MCParticleList()
{
}

