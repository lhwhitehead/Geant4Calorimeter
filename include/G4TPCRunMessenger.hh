#ifndef G4TPCRunMessenger_HH
#define G4TPCRunMessenger_HH

class G4TPCRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

#include "G4UImessenger.hh"
#include "globals.hh"

class G4TPCRunMessenger: public G4UImessenger {
  public:
    G4TPCRunMessenger(G4TPCRunAction* mpga);
    ~G4TPCRunMessenger();

  public:
    void SetNewValue(G4UIcommand* command, G4String newValues);
//    G4String GetCurrentValue(G4UIcommand* command);

  private:
    G4TPCRunAction* fAction;

  private:
    //commands
    G4UIdirectory* fGenDir;
//    G4UIcmdWithAString* genCmd;
//    G4UIcmdWithAString* fOutputFileType;
    // Need a second vec file for overlaid events
    G4UIcmdWithABool* fSaveXml;
    G4UIcmdWithABool* fSaveText;
    G4UIcmdWithABool* fSaveImages;
//    G4UIcmdWithAString* fOverlayNameCmd;
    // Option to enable random vertex positions
//    G4UIcmdWithABool* fRandomVertexCmd;
    // Define the size of the gap to the wall - default = 1m.
//    G4UIcmdWithADouble* fFiducialBorderCmd;
    // Toggle to swap X and Z for beam events generated along Z (ie with GENIE).
//    G4UIcmdWithABool* fSwapXZCmd;

};

#endif
