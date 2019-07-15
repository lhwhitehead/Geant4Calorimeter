/**
 *  @file   include/InputParameters.cc
 *
 *  @brief  Header file for the InputParameters class.
 *
 *  $Log: $
 */

#ifndef INPUT_PARAMETERS_H
#define INPUT_PARAMETERS_H 1

#include <iostream>

/**
 *  @brief InputParameters class
 */
class InputParameters
{
public:
    /**
     *  Constructor
     */
    InputParameters();

    /**
     *  Destructor
     */
    ~InputParameters();

    /**
     *  Check whether parameters are valid
     */
    bool Valid();

    std::string          m_species;
    std::string          m_outputFileName;
    double               m_energy;
    int                  m_nEvents;
    int                  m_nParticlesPerEvent;
    bool                 m_keepEMShowerDaughters;
    double               m_energyCut;
};

#endif // #ifndef INPUT_PARAMETERS_H
