#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ParseGENIETrackerFile.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"

// A couple of helper functions
namespace helpers{
  inline float atof(const std::string& s) {
    return std::atof(s.c_str());
  }
  inline int atoi(const std::string& s) {
    return std::atoi(s.c_str());
  }
}

ParseGENIETrackerFile::ParseGENIETrackerFile() : ParseTrackerFile(){
  fParticleSource = nullptr;
}

ParseGENIETrackerFile::ParseGENIETrackerFile(G4ParticleGun *gps) : ParseTrackerFile(gps){
  fParticleSource = gps;
} 

ParseGENIETrackerFile::~ParseGENIETrackerFile(){

}

void ParseGENIETrackerFile::ReadFile(const std::string &inputFile){

  std::cout << "Attempting to open " << inputFile << std::endl;

  // Open the input file
  std::fstream input(inputFile,std::fstream::in);
 
  // File has the following format, repeated n_event times
  // $ begin
  // $ nuance <nuance_code>
  // $ vertex <x> <y> <z> <t>
  // $ track <pdg> <energy> <dir_x> <dir_y> <dir_z> <tracking_status>
  // $ track ... (repeat as necessary)
  // $ end

  if(input.is_open()){

    std::string line;
    std::vector<std::string> tokens;

    // We need a way to track if we are building an event
    // Values for eventStatus:
    // 0 = nothing
    // 1 = Got begin line
    // 2 = Got nuance line
    // 3 = Got vertex line
    // 4 = Got neutrino line
    unsigned int eventStatus = 0;
    TrackerNeutrinoEvent currentEvent;

    while(std::getline(input,line)){

      tokens = TokeniseLine(line," $");
  
      if(eventStatus == 0 && tokens[0] == "begin"){
        currentEvent.Reset();
        eventStatus = 1;
      }
      else if(eventStatus == 1 && tokens[0] == "nuance"){
        currentEvent.fInteraction = helpers::atoi(tokens[1]);
        eventStatus = 2;
      }
      else if(eventStatus == 2 && tokens[0] == "vertex"){
        currentEvent.fVertex = G4ThreeVector(helpers::atof(tokens[1]),
                                 helpers::atof(tokens[2]),helpers::atof(tokens[3]));
        currentEvent.fTime = helpers::atof(tokens[4]);
        eventStatus = 3;
      }
      else if(eventStatus == 3 && tokens[0] == "track"){
        TrackerParticle neutrino = ProcessTrackLine(tokens);
        currentEvent.fNeutrino = neutrino;
        eventStatus = 4;
      }
      else if(eventStatus == 4 && tokens[0] == "track"){
        // If the final token is not equal to zero then we don't want to consider this particle
        if(tokens[6] == "0"){
          TrackerParticle particle = ProcessTrackLine(tokens);
          currentEvent.fParticles.push_back(particle);
        }
      }
      else if(eventStatus == 4 && tokens[0] == "end"){
        // We have reached the end of this event, so save the event and move on
        fNeutrinoEvents.push_back(currentEvent);
        eventStatus = 0;
      }
      else if(eventStatus == 4 && tokens[0] == "stop"){
        std::cout << "Finished reading input file " << inputFile << std::endl;
      }
      else{
        std::cerr << "Something has gone wrong in the file. Event status = " << eventStatus << " but line token = " << tokens[0] << std::endl;
      }

    }

  }
  else{
    std::cerr << "Could not open input file" << std::endl;
    assert(0);
  }

  std::cout << "Read in " << fNeutrinoEvents.size() << " events." << std::endl;
  return;

} 

void ParseGENIETrackerFile::GenerateEvent(G4Event &event){

  // Annoyingly this is an int and we want an unsigned int
  const unsigned int eventNumber = static_cast<unsigned int>(event.GetEventID());

  G4ParticleTable *pTable = G4ParticleTable::GetParticleTable();

  if(eventNumber <= fNeutrinoEvents.size()){

    // To fire all of the particles from the same point we need to use the neutrino 
    // vertex position and time.
    const TrackerNeutrinoEvent & nu = fNeutrinoEvents[eventNumber];

    fParticleSource->SetParticlePosition(nu.fVertex);
    fParticleSource->SetParticleTime(nu.fTime);

    std::cout << "Generating event " << eventNumber << " with " << nu.GetNPrimaries() << " primaries" << std::endl; 
    
    // Now we fire all of our particles individually because there is no better way
    // to do this.
    for(const TrackerParticle &p : fNeutrinoEvents[eventNumber].fParticles){
      std::cout << "Firing particle with PDG = " << p.fPDG << std::endl; 
      fParticleSource->SetParticleDefinition(pTable->FindParticle(p.fPDG)); 
      double kineticEnergy = p.fEnergy - fParticleSource->GetParticleDefinition()->GetPDGMass();
      fParticleSource->SetParticleEnergy(kineticEnergy);
      fParticleSource->SetParticleMomentumDirection(p.fDirection);

      fParticleSource->GeneratePrimaryVertex(&event);
    }

  }

  return;
}

ParseGENIETrackerFile::TrackerParticle ParseGENIETrackerFile::ProcessTrackLine(const std::vector<std::string> &tokens) const{

  TrackerParticle particle;

  particle.fPDG = helpers::atoi(tokens[1]);
  particle.fEnergy = helpers::atof(tokens[2]);
  particle.fDirection = G4ThreeVector(helpers::atof(tokens[3]),
                                helpers::atof(tokens[4]),helpers::atof(tokens[5]));

//  std::cout << "Made particle of type " << particle.fPDG << std::endl;

  return particle;

}

void ParseGENIETrackerFile::SetEventVertexAndTime(const unsigned int &event, const G4ThreeVector &vtx, const double &time){

  if(event < fNeutrinoEvents.size()){
    fNeutrinoEvents[event].fVertex = vtx;
    fNeutrinoEvents[event].fTime = time;
  }
  else{
    std::cerr << "Event index out of range, doing nothing." << std::endl;
  }
}

std::vector<std::string> ParseGENIETrackerFile::TokeniseLine(const std::string &line, const std::string &sep) const{

  std::size_t startToken = 0, endToken = 0;
  
  std::vector<std::string> tokens;

  if(sep.size() == 0 || line.size() == 0) return tokens;

  while(startToken < line.size()){
    // Find the first character that isn't a separator
    startToken = line.find_first_not_of(sep,startToken);
    if(startToken == line.npos){
      endToken = line.size();
    }
    else{
      //Find end of token
      endToken = line.find_first_of(sep, startToken);
      if (endToken == line.npos){
          // If there was no end of token, assign it to the end of string
          endToken = line.size();
      }
      // Add this token to our vector
      tokens.push_back(line.substr(startToken,endToken-startToken));
      
      // We want to start looking from the end of this substring next iteration
      startToken = endToken;
    }
    
//    std::cout << "Token " << tokens.size() - 1 << ": " << tokens[tokens.size()-1] << std::endl;
    
  }
  

  return tokens;
}




