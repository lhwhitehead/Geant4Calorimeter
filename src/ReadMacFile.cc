#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "ReadMacFile.hh"

ReadMacFile::ReadMacFile(){

}

ReadMacFile::~ReadMacFile(){

}

void ReadMacFile::ReadFile(const std::string macfile){

  // Open the input file
  std::fstream input(macfile,std::fstream::in);

  // .mac files contain commands like this:
  // /<folder>/<command> <value>
  // <folder> defines which messenger it refers to
  // <command> is the property we want to control
  // <value> is the value we want to assign to the property

  if(input.is_open()){

    std::string line;

    while(std::getline(input,line)){

      // Remove empty lines
      if(line.length() == 0) continue;

      if(line.find("/run/") != line.npos){
        // These commands control GEANT - to start running etc
        fRunG4Commands.push_back(line);
      }
      else if(line.find("/output/") != line.npos){
        // These commands control the output format
        fRunActionCommands.push_back(line);
      }
      else if(line.find("/mygps/") != line.npos){
        // These commands contol the primary generator
        fPrimaryGeneratorCommands.push_back(line);
      }
      else{
        std::cout << "Did not recognise command " << line << std::endl;
      }
    }
  }

  std::cout << "Read " << fRunG4Commands.size() << " " << fRunActionCommands.size() << " " << fPrimaryGeneratorCommands.size() << std::endl;

}

