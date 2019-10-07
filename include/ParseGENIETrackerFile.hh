#ifndef PARSEGENIETRACKERFILE_HH
#define PARSEGENIETRACKERFILE_HH

#include <fstream>
#include <vector>
#include "ParseTrackerFile.hh"
#include "G4ThreeVector.hh"

// Forward class definitions
class G4ParticleGun;
class G4Event;

/*
 * Class to parse the text file format from GENIE
 *
 * Author: Leigh Whitehead
 * Email: leigh.howard.whitehead@cern.ch
 *
*/

class ParseGENIETrackerFile : public ParseTrackerFile{

public:
//  // Struct to store each track from the file
//  struct TrackerParticle{
//  
//    TrackerParticle(){};
//    ~TrackerParticle(){};
//  
//    int fPDG;
//    double fEnergy;
//    G4ThreeVector fDirection;
//  };
//  
//  // Struct to store each event from the file
//  struct TrackerNeutrinoEvent{
//  
//    TrackerNeutrinoEvent(){};
//    ~TrackerNeutrinoEvent(){};
//  
//    // Interaction properties 
//    G4ThreeVector fVertex;
//    double fTime;
//    int fInteraction;
//    TrackerParticle fNeutrino;
//    std::vector<TrackerParticle> fParticles;
//  
//    // Reset the vector
//    void Reset(){
//      fParticles.clear();
//    }
//  };

  ParseGENIETrackerFile();
  ParseGENIETrackerFile(G4ParticleGun *gps); 

  ~ParseGENIETrackerFile();

  void ReadFile(const std::string &inputFile);
  void GenerateEvent(G4Event &event);

//  bool GetNumberOfEvents() {return fNeutrinoEvents.size();};

  void SetEventVertexAndTime(const unsigned int &event, const G4ThreeVector &vtx, const double &time);

private:
  TrackerParticle ProcessTrackLine(const std::vector<std::string> &tokens) const;
  std::vector<std::string> TokeniseLine(const std::string &line, const std::string &sep) const;

};

#endif
