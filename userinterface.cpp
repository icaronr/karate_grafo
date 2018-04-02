/**
 * Autor: Icaro Nery Rezende - 150037023
 * Universidade de Brasilia
 * Teoria e Aplicacao de Grafos - Turma A - 2018/1
 * Trabalho 1
 * Arquivo que contem a implementacao das classes e metodos responsaveis pela entrada e saida de dados.
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include "userinterface.h"
#include "dataprocessing.h"

using namespace std;


UserInterface::UserInterface()
{
ARQUIVOLIDO = false;
}

int UserInterface::menuPrincipal(MenuOptions* menuOptions, DataProcessing* dataProcessing){
    int stopFlag = 0;
    menuOptions->setValido(false);
    //loopa o menu ate entrar um valor válido
    while(!menuOptions->getValido()){
        system("clear");
        cout << "-> Menu Principal " << endl;
        cout << endl << endl;
        cout << "Escolha uma das opcoes abaixo: " << endl;
        cout << "1 - Analisar o grafo" << endl;
        cout << "2 - Mostrar os nos em decrescente" << endl;
        cout << "3 - Mostrar cliques maximos/maximais com pelo menos 5 elementos" << endl;
        cout << "4 - Sair do programa " << endl;

        menuOptions->setOpcao(dataProcessing->getInput());
        
        if(!menuOptions->getValido()){
            
            cout << endl <<"Opcao invalida! Pressione ENTER para continuar!" << endl;
                       
            getchar();
        }else{
            int num = menuOptions->getOpcao();
            switch(num){
                case 1: encontraGrafo(dataProcessing);
                        break;
                case 2: if(!ARQUIVOLIDO){
                            cout << endl << "Voce precisa analisar um aquivo para carregar um grafo na memoria" << endl;
                            getchar();
                            break;
                        }
                        mostraNos(dataProcessing->organizaNos(),dataProcessing); 
                        break;
                case 3: if(!ARQUIVOLIDO){
                            cout << endl << "Voce precisa analisar um aquivo para carregar um grafo na memoria" << endl;
                            getchar();
                            break;
                        }
                        mostraCliques(dataProcessing->bronProcess(), dataProcessing);
                        
                        
                        break;
                case 4: stopFlag = 1;
                        break;
                default: break;
            }   
        }
    }
    return stopFlag;
}

void UserInterface::encontraGrafo(DataProcessing* dataProcessing)
{
    string nomeGrafo = "karate.gml";
    while(1){
        
        system("clear");
        cout << "Antes de analisar o grafo, confirme o nome do arquivo. " << endl;
        cout << "O arquivo analisado sera: " << "'" << nomeGrafo << "'" << endl;
        cout << "Prosseguir(s) ou procurar outro arquivo(n)?" << endl;
        
        char confirma;
        cin >> confirma;
        getchar();
        if((confirma == 'S')||(confirma == 's')){
            int i;
            bool flag = true;
            i = dataProcessing->analisarGrafo(nomeGrafo);
            
            if(i==0){
                setArquivoLido(flag);
            }
            break;
        }else if((confirma == 'N')||(confirma == 'n')){
            cout << endl << "Entre com o nome do arquivo .gml desejado: (ex.:nome.gml)" << endl;
            cin >> nomeGrafo;
            getchar();
        }
    }   
}

void UserInterface::mostraNos(VERTEX *listaDeNos, DataProcessing* dataProcessing)
{
    int i=0;
while(listaDeNos[i].id>0){
    cout << endl<< "ID do Vertice: " << listaDeNos[i].id << "  \n->Grau do Vertice "<< listaDeNos[i].id << ": " << listaDeNos[i].degree << endl;
    i++;
}
getchar();
}

void UserInterface::mostraCliques(vector < vector <VERTEX> > myClique, DataProcessing* dataProcessing){
    for(vector <VERTEX> cliq: myClique){
        cout << endl << "------CLIQUE------" << endl;
        for(VERTEX vertex: cliq){
            cout << vertex.id << " ";
        }
        cout << endl << "--FIM DO CLIQUE---";
    }
    getchar();
    getchar();
}