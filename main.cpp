/**
 * Universidade De Brasilia
 * Departamento de Ciencia da Computacao -CIC
 * Teoria e Aplicacao de Grafos - Turma A - 2018/1
 * Trabalho 1
 * Icaro Nery Rezende - 15/0037023
 * 
 * Este programa analisa um arquivo .gml e dele extrai um grafo.
 * A partir desse grafo, temos a opcao de mostrar os nos ordenados por grau.
 * Tambem temos a opcao de mostrar os cliques maximais e maximos.
 * 
 * Para compilar o arquivo, utilize o comando 'make' na pasta do projeto
 * Para executar o programa utilize o comando './karate_grafo' na pasta do projeto
 */

#include <iostream>
#include "userinterface.h"
#include "dataprocessing.h"
extern "C"{
#include "readgml.h"   
}

using namespace std;
//Metodo main, que instancia os objetos necessarios para a execucao do projeto
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
