#include "G4TPCPrimaryGeneratorMessenger.hh"
#include "G4TPCPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4ios.hh"

G4TPCPrimaryGeneratorMessenger::G4TPCPrimaryGeneratorMessenger(G4TPCPrimaryGeneratorAction* pointerToAction) :
    fAction(pointerToAction) {

  std::cout << "Constructing PG messenger" << std::endl;

  // Define the directory we are looking for in the mac file
  fGenDir = new G4UIdirectory("/mygps/");
  fGenDir->SetGuidance("Control of the tracker file input");

  fTrackerSwitch = new G4UIcmdWithABool("/mygps/usetracker",this);
  fTrackerSwitch->SetGuidance("Set to true to use tracker file input");
  fTrackerSwitch->SetParameterName("usetracker",true);
  fTrackerSwitch->SetDefaultValue(false);

  fTrackerFile = new G4UIcmdWithAString("/mygps/trackerfile",this);
  fTrackerFile->SetGuidance("Tracker format input file");
  fTrackerFile->SetParameterName("trackerfile",true);
  fTrackerFile->SetDefaultValue("");

}

G4TPCPrimaryGeneratorMessenger::~G4TPCPrimaryGeneratorMessenger() {
  if(fGenDir != nullptr) delete fGenDir;
  if(fTrackerSwitch != nullptr) delete fTrackerSwitch;
  if(fTrackerFile != nullptr) delete fTrackerFile;
}

void G4TPCPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command, G4String newValue) {

  std::cout << "Setting option with new value = " << newValue << std::endl;

  if(command == fTrackerSwitch){
    if(newValue == "true") fAction->UseTrackerFile(true);
    else fAction->UseTrackerFile(false);
  }
  else if(command == fTrackerFile){
    fAction->SetTrackerFile(newValue);
  }

}

