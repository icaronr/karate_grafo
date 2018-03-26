#include <iostream>
#include <cstdlib>
#include <string>
#include "userinterface.h"
#include "dataprocessing.h"

using namespace std;


UserInterface::UserInterface()
{

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
        cout << "3 - Sair do programa " << endl;

        menuOptions->setOpcao(dataProcessing->getInput());
        
        if(!menuOptions->getValido()){
            
            cout << endl <<"Opcao invalida! Pressione ENTER para continuar!" << endl;
                       
            getchar();
        }else{
            int num = menuOptions->getOpcao();
            switch(num){
                case 1: encontraGrafo(dataProcessing);
                        break;
                case 2:break;
                case 3: stopFlag = 1;
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
            dataProcessing->analisarGrafo(nomeGrafo);
            break;
        }else if((confirma == 'N')||(confirma == 'n')){
            cout << endl << "Entre com o nome do arquivo .gml desejado: (ex.:nome.gml)" << endl;
            cin >> nomeGrafo;
            getchar();
        }
    }   
}
