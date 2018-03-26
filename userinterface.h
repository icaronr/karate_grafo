#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "dataprocessing.h"

using namespace std;

class UserInterface
{
private:
    bool RETORNO;
    int OPCAO;
public:
    UserInterface();

    int menuPrincipal(MenuOptions* menuOptions, DataProcessing* dataProcessing);
    void encontraGrafo(DataProcessing* dataProcessing);
};

#endif // USERINTERFACE_H
