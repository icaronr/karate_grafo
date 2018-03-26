#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <string>

using namespace std;

class DataProcessing
{
private:
    int entrada;
public:
    DataProcessing();
    int getInput();
    void analisarGrafo(string nomeArquivo);
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
