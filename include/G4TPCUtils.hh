#ifndef G4TPCUtils_HH
#define G4TPCUtils_HH

#include <string>
#include <vector>

namespace utils{

  static std::vector<std::string> TokeniseLine(const std::string &line, const std::string &sep){
  
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
    }
  
    return tokens;
  }

}

#endif

