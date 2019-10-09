#include "G4TPCRunMessenger.hh"
#include "G4TPCRunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4ios.hh"

G4TPCRunMessenger::G4TPCRunMessenger(G4TPCRunAction* pointerToAction) :
    fAction(pointerToAction) {

  std::cout << "Constructing PG messenger" << std::endl;

  // Define the directory we are looking for in the mac file
  fGenDir = new G4UIdirectory("/output/");
  fGenDir->SetGuidance("Control of the output file(s)");

//  fOutputFileType = new G4UIcmdWithAString("/output/filetype",this);
//  fOutputFileType->SetGuidance("Output file type: xml or text");
//  fOutputFileType->SetParameterName("filetype",true);
//  fOutputFileType->SetDefaultValue("xml");

  fSaveXml = new G4UIcmdWithABool("/output/savexml",this);
  fSaveXml->SetGuidance("Save the xml output file");
  fSaveXml->SetParameterName("savexml",true);
  fSaveXml->SetDefaultValue(true);

  fSaveText = new G4UIcmdWithABool("/output/savetext",this);
  fSaveText->SetGuidance("Save the text output files");
  fSaveText->SetParameterName("savetext",true);
  fSaveText->SetDefaultValue(false);

  fSaveImages = new G4UIcmdWithABool("/output/saveimages",this);
  fSaveImages->SetGuidance("Save the image output files");
  fSaveImages->SetParameterName("saveimages",true);
  fSaveImages->SetDefaultValue(false);
}

G4TPCRunMessenger::~G4TPCRunMessenger() {
  if(fGenDir != nullptr) delete fGenDir;
//  if(fOutputFileType != nullptr) delete fOutputFileType;
  if(fSaveXml != nullptr) delete fSaveXml;
  if(fSaveText != nullptr) delete fSaveText;
  if(fSaveImages != nullptr) delete fSaveImages;
}

void G4TPCRunMessenger::SetNewValue(G4UIcommand * command, G4String newValue) {

  std::cout << "Setting option with new value = " << newValue << std::endl;

  if(command == fSaveXml){
    bool isTrue = (newValue == "true");
    fAction->SetSaveXml(isTrue);
  }
  if(command == fSaveText){
    bool isTrue = (newValue == "true");
    fAction->SetSaveText(isTrue);
  }
  if(command == fSaveImages){
    bool isTrue = (newValue == "true");
    fAction->SetSaveImages(isTrue);
  }
//  if(command == fOutputFileType){
//    fAction->SetOutputFileType(newValue);
//  }

}

