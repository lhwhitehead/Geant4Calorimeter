#ifndef PARSETRACKERFILE_HH
#define PARSETRACKERFILE_HH

#include <string>
#include <vector>

/*
 * Class to parse a .mac file that controls g4TPC
 *
 * Author: Leigh Whitehead
 * Email: leigh.howard.whitehead@cern.ch
 *
*/

class ReadMacFile{

public:

  ReadMacFile();

  ~ReadMacFile();

  void ReadFile(const std::string macfile);

  std::vector<std::string> GetRunG4Commands() const {return fRunG4Commands;};
  std::vector<std::string> GetPrimaryGeneratorCommands() const {return fPrimaryGeneratorCommands;};
  std::vector<std::string> GetRunActionCommands() const {return fRunActionCommands;};

private:

  std::vector<std::string> fRunG4Commands;
  std::vector<std::string> fPrimaryGeneratorCommands;
  std::vector<std::string> fRunActionCommands;
};

#endif
