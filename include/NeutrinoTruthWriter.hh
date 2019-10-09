#ifndef NEUTRINOTRUTHWRITER_HH
#define NEUTRINOTRUTHWRITER_HH

#include <string>
#include <vector>

#include "ParseTrackerFile.hh"

/*
 * This class writes the .info files needed for the deep learning
 * methods to define the training targets
 *
 * Author: Leigh Whitehead
 * Email: leigh.howard.whitehead@cern.ch
 *
*/

class NeutrinoTruthWriter{

public:

  struct TruthInfo{
    TruthInfo(){};
    ~TruthInfo(){};

    int fPDG;
    unsigned int fInteraction;
    unsigned int fNProtons;
    unsigned int fNPions;
    unsigned int fNPizeros;
    unsigned int fNNeutrons;
  }

  NeutrinoTruthWriter(const TrackerNeutrinoEvent &nu){};

  ~NeutrinoTruthWriter(){};

  // Function tries to define which final state particles will be visible
  void FilterParticles(){};

private:

  

};

#endif
