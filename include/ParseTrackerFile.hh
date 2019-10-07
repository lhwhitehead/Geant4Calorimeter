#ifndef PARSETRACKERFILE_HH
#define PARSETRACKERFILE_HH

#include <fstream>
#include <vector>

#include "G4ThreeVector.hh"
#include "G4ParticleGun.hh"

// Forward class definitions
//class G4ParticleGun;
class G4Event;

/*
 * Class to parse the text file format from GENIE
 *
 * Author: Leigh Whitehead
 * Email: leigh.howard.whitehead@cern.ch
 *
*/

class ParseTrackerFile{

public:
  // Struct to store each track from the file
  struct TrackerParticle{
  
    TrackerParticle(){};
    ~TrackerParticle(){};
  
    int fPDG;
    double fEnergy;
    G4ThreeVector fDirection;
  };
  
  // Struct to store each event from the file
  struct TrackerNeutrinoEvent{
  
    TrackerNeutrinoEvent(){};
    ~TrackerNeutrinoEvent(){};
 
    unsigned int GetNPrimaries() const{return fParticles.size();};
 
    // Interaction properties 
    G4ThreeVector fVertex;
    double fTime;
    int fInteraction;
    TrackerParticle fNeutrino;
    std::vector<TrackerParticle> fParticles;
  
    // Reset the vector
    void Reset(){
      fParticles.clear();
    }
  };

  ParseTrackerFile(){fParticleSource=nullptr;};
  ParseTrackerFile(G4ParticleGun *gps){fParticleSource = gps;}; 

  virtual ~ParseTrackerFile();

  // Abstract base class
  virtual void ReadFile(const std::string& ){};
  virtual void GenerateEvent(G4Event& ){};

  virtual unsigned int GetNumberOfEvents() {return fNeutrinoEvents.size();};

  virtual void SetEventVertexAndTime(const unsigned int&, const G4ThreeVector&, const double&){};

protected:
  //virtual void ProcessTrackLine(const std::vector<std::string> &tokens, TrackerParticle &particle) const;
  //virtual void TokeniseLine(const std::string &line, const std::string &sep, std::vector<std::string> &tokens) const;

  std::fstream fInputFile;

  // The particle source to which we add the final state particles
  G4ParticleGun *fParticleSource;
  
  // Vector of neutrino events read from the file
  std::vector<TrackerNeutrinoEvent> fNeutrinoEvents;
};

#endif
