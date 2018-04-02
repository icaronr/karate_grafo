/**
 * Autor: Icaro Nery Rezende - 150037023
 * Universidade de Brasilia
 * Teoria e Aplicacao de Grafos - Turma A - 2018/1
 * Trabalho 1
 * Cabecalho que contem a declaracao das classes e metodos de processamento dos dados do projeto
 */
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
    //Construtor da classe
    DataProcessing();
    //Recebe uma entrada para o menu
    int getInput();
    //Abre o arquivo e monsta o grafo com base nos dados do arquivo
    int analisarGrafo(string nomeArquivo);
    //Cria uma copia dos nos para ordenar
    VERTEX* organizaNos();
    //Ordena a copia em ordem crescente de grau
    VERTEX* organizaGrau(VERTEX *listaDeNos);
    //Getter
    NETWORK getNetwork(){
        return network;
    }
    //Setter
    void setNetwork(NETWORK network){
        this->network = network;
    }
    //Implementacao do algoritmo de Bron Kerbosch sem pivotamento
    void bronKerbosch(vector <VERTEX> R, vector <VERTEX> P, vector <VERTEX> X);
    //Inicializa o processo para iniciar o Bron Kerbosch e trata a saida do algoritmo
    vector <vector <VERTEX> > bronProcess();
    //Encontra os vizinhos de um vertice
    vector <VERTEX> neighbours(VERTEX v1);
    //Faz a uniao entre um vetor de vertices a um vertice
    vector <VERTEX> uniteVector(vector <VERTEX> v1,VERTEX v2);
    //Faz a intersecao entre 2 vetores de vertices
    vector <VERTEX> intersectVector(vector <VERTEX> v1, vector <VERTEX> v2);
    //Remove um elemento de um vetor de vertice
    vector <VERTEX> removeItem(vector <VERTEX> v1,VERTEX v2);
};

//Classe com as definicoes para o menu principal
class MenuOptions
{
private:
    int opcao;
    bool VALIDO;
public:
    //Construtor de classe
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
