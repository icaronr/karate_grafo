#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "dataprocessing.h"
extern "C"{
#include "readgml.h"   
}

using namespace std;

class UserInterface
{
private:
    bool RETORNO;
    int OPCAO;
    bool ARQUIVOLIDO;
public:
    UserInterface();

    int menuPrincipal(MenuOptions* menuOptions, DataProcessing* dataProcessing);
    void encontraGrafo(DataProcessing* dataProcessing);
    void mostraNos(VERTEX *listaDeNos, DataProcessing* dataProcessing);
    void setArquivoLido(bool ARQUIVOLIDO){
        this->ARQUIVOLIDO = ARQUIVOLIDO;
    }
    void mostraCliques(vector < vector <VERTEX> > myCliques, DataProcessing* dataProcessing);
};

#endif // USERINTERFACE_H
