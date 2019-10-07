#include "G4TPCRunMessenger.hh"
#include "G4TPCRunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4ios.hh"

G4TPCRunMessenger::G4TPCRunMessenger(G4TPCRunAction* pointerToAction) :
    fAction(pointerToAction) {

  std::cout << "Constructing PG messenger" << std::endl;

  // Define the directory we are looking for in the mac file
  fGenDir = new G4UIdirectory("/output/");
  fGenDir->SetGuidance("Control of the output file(s)");

  fOutputFileType = new G4UIcmdWithAString("/output/filetype",this);
  fOutputFileType->SetGuidance("Output file type: xml or text");
  fOutputFileType->SetParameterName("filetype",true);
  fOutputFileType->SetDefaultValue("xml");

}

G4TPCRunMessenger::~G4TPCRunMessenger() {
  if(fGenDir != nullptr) delete fGenDir;
  if(fOutputFileType != nullptr) delete fOutputFileType;
}

void G4TPCRunMessenger::SetNewValue(G4UIcommand * command, G4String newValue) {

  std::cout << "Setting option with new value = " << newValue << std::endl;

  if(command == fOutputFileType){
    fAction->SetOutputFileType(newValue);
  }

}

