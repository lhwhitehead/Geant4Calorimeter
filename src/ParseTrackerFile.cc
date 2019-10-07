#include "ParseTrackerFile.hh"

ParseTrackerFile::~ParseTrackerFile(){
  if(fParticleSource != nullptr){
    delete fParticleSource;
    fParticleSource = nullptr;
  }
}
