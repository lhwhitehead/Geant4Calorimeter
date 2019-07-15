/**
 *  @file   src/InputParameters.cc
 *
 *  @brief  Implementation of the InputParameters class.
 *
 *  $Log: $
 */

#include "InputParameters.hh"

InputParameters::InputParameters() :
    m_species(""),
    m_outputFileName(""),
    m_energy(-1.),
    m_nEvents(1),
    m_nParticlesPerEvent(1),
    m_keepEMShowerDaughters(false),
    m_energyCut(0.001)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

InputParameters::~InputParameters()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

bool InputParameters::Valid()
{
    if (m_energy < 0.)
    {
        std::cout << "Energy not specified" << std::endl;
        return false;
    }

    if (m_species.empty())
    {
        std::cout << "Particles species not specified" << std::endl;
        return false;
    }

    if (m_outputFileName.empty())
    {
        std::cout << "Missing output file name" << std::endl;
        return false;
    }

    if (m_energyCut < 0.)
    {
        std::cout << "Invalid energy cut specified" << std::endl;
        return false;
    }

    return true;
}
