#ifndef G4TPCPrimaryGeneratorMessenger_HH
#define G4TPCPrimaryGeneratorMessenger_HH

class G4TPCPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;

#include "G4UImessenger.hh"
#include "globals.hh"

class G4TPCPrimaryGeneratorMessenger: public G4UImessenger {
  public:
    G4TPCPrimaryGeneratorMessenger(G4TPCPrimaryGeneratorAction* mpga);
    ~G4TPCPrimaryGeneratorMessenger();

  public:
    void SetNewValue(G4UIcommand* command, G4String newValues);
//    G4String GetCurrentValue(G4UIcommand* command);

  private:
    G4TPCPrimaryGeneratorAction* fAction;

  private:
    //commands
    G4UIdirectory* fGenDir;
//    G4UIcmdWithAString* genCmd;
    G4UIcmdWithABool* fTrackerSwitch;
    G4UIcmdWithAString* fTrackerFile;
    // Need a second vec file for overlaid events
//    G4UIcmdWithAString* fOverlayNameCmd;
    // Option to enable random vertex positions
//    G4UIcmdWithABool* fRandomVertexCmd;
    // Define the size of the gap to the wall - default = 1m.
//    G4UIcmdWithADouble* fFiducialBorderCmd;
    // Toggle to swap X and Z for beam events generated along Z (ie with GENIE).
//    G4UIcmdWithABool* fSwapXZCmd;

};

#endif
