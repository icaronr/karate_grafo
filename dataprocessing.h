#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <string>
#include <vector>
extern "C"{
#include "readgml.h"   
}

using namespace std;

class DataProcessing
{
private:
    int entrada;
    NETWORK network;

   vector < vector <VERTEX> > myCliques;
public:
    DataProcessing();
    int getInput();
    int analisarGrafo(string nomeArquivo);
    VERTEX* organizaNos();
    VERTEX* organizaGrau(VERTEX *listaDeNos);
    
    NETWORK getNetwork(){
        return network;
    }
    void setNetwork(NETWORK network){
        this->network = network;
    }
    void bronKerbosch(vector <VERTEX> R, vector <VERTEX> P, vector <VERTEX> X);
    vector <vector <VERTEX> > bronProcess();
    vector <VERTEX> neighbours(VERTEX v1);

    vector <VERTEX> uniteVector(vector <VERTEX> v1,VERTEX v2);

    vector <VERTEX> intersectVector(vector <VERTEX> v1, vector <VERTEX> v2);

    vector <VERTEX> removeItem(vector <VERTEX> v1,VERTEX v2);
};

class MenuOptions
{
private:
    int opcao;
    bool VALIDO;
public:
    MenuOptions();
    int getOpcao(){
        return opcao;
    };
    void setOpcao(int opcao){
        this->opcao = opcao;
        validaOpcao(opcao);
    }
    void validaOpcao(int opcao);

    void setValido(bool VALIDO){
        this->VALIDO = VALIDO;
    }
    bool getValido(){
        return VALIDO;
    }
};

#endif // DATAPROCESSING_H
