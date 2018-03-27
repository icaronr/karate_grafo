#include <iostream>
#include <string>
extern "C"{
#include "dataprocessing.h"
#include "readgml.h"   
}


using namespace std;

DataProcessing::DataProcessing()
{
entrada = 0;
}

int DataProcessing::getInput()
{
    
    cin >> entrada;
    getchar();
    return entrada;
}

void DataProcessing::analisarGrafo(string nomeArquivo)
{
    int errorFlag;
    //Faz o cast da string para um ponteiro de char.
    //Necessario para o 'fopen', pois ele nao aceita o tipo 'string'.
    const char *cstr = nomeArquivo.c_str();
    FILE *fp;
    fp = fopen(cstr, "r");
    if (fp == NULL)
    {
        cout << endl << "O arquivo nao existe!" <<  endl;
        getchar();
        return;
    }
    cout << endl << "Before karate" << endl;
    NETWORK *karate;
cout << endl << "Calling shit!(Read Network)" << endl;
    errorFlag = read_network(karate, fp);
cout << endl << "Good Job!" << endl;

    
}

MenuOptions::MenuOptions()
{
    opcao = 0;
    VALIDO = false;
}
void MenuOptions::validaOpcao(int opcao)
{
    if(opcao>0 & opcao <4){
        setValido(true);
    }else{
        setValido(false);
    }
}
