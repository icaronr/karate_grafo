/**
 * Autor: Icaro Nery Rezende - 150037023
 * Universidade de Brasilia
 * Teoria e Aplicacao de Grafos - Turma A - 2018/1
 * Trabalho 1
 * Cabecalho que contem a declaracao das classes e metodos responsaveis pela entrada e saida de dados.
 */
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "dataprocessing.h"
extern "C"{
#include "readgml.h"   
}

using namespace std;

//Classe com os metodos responsaveis pela entrada e saida de dados para o usuario
class UserInterface
{
private:
    bool RETORNO;
    int OPCAO;
    bool ARQUIVOLIDO;
public:
    //Construtor da classe
    UserInterface();
    //Metodo do menu principal
    int menuPrincipal(MenuOptions* menuOptions, DataProcessing* dataProcessing);
    //Metodo que inicia a leitura do arquivo .gml
    void encontraGrafo(DataProcessing* dataProcessing);
    //Metodo para mostrar os nos em ordem crescente de grau
    void mostraNos(VERTEX *listaDeNos, DataProcessing* dataProcessing);
    //Setter da flag ARQUIVOLIDO
    void setArquivoLido(bool ARQUIVOLIDO){
        this->ARQUIVOLIDO = ARQUIVOLIDO;
    }
    //Metodo que mostra os cliques maximais com grau maior que o especificado em DataProcessing::bronProcess;
    void mostraCliques(vector < vector <VERTEX> > myCliques, DataProcessing* dataProcessing);
};

#endif // USERINTERFACE_H
