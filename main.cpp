#include <iostream>
#include "userinterface.h"
#include "dataprocessing.h"
extern "C"{
#include "readgml.h"   
}

using namespace std;

int main()
{
  //inicializacao das classes
  UserInterface *userInterface;
  DataProcessing *dataProcessing;
  MenuOptions *menuOptions;

  userInterface = new UserInterface();

  dataProcessing = new DataProcessing();

  menuOptions = new MenuOptions();

  int stopFlag = 0;
  
  while(!stopFlag){
    stopFlag = userInterface->menuPrincipal(menuOptions, dataProcessing);
  }
 
  
  delete userInterface;
  delete dataProcessing;
  delete menuOptions;
  
  return 0;
}
