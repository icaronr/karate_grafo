/**
 * Autor: Icaro Nery Rezende - 150037023
 * Universidade de Brasilia
 * Teoria e Aplicacao de Grafos - Turma A - 2018/1
 * Trabalho 1
 * Arquivo que contem a implementacao das classes e metodos de processamento dos dados do projeto
 */
#include <iostream>
#include <string>
#include <algorithm>
#include "dataprocessing.h"
extern "C"{
#include "readgml.h"   
}


using namespace std;
//Contrutor da classe
DataProcessing::DataProcessing()
{
entrada = 0;
network = { 0,      //nvertices
            0,      // directed
            NULL    //*vertex
};

myCliques = {};


}
//Recebe uma entrada para o menu
int DataProcessing::getInput()
{
    
    cin >> entrada;
    getchar();
    return entrada;
}
//Abre o arquivo e monsta o grafo com base nos dados do arquivo
int DataProcessing::analisarGrafo(string nomeArquivo)
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
        return 1;
    }
    NETWORK *karate;
    
    errorFlag = read_network(karate, fp);
    //free_network(&network);
    cout << endl << "Arquivo analisado com sucesso!" << endl;

    getchar();
    setNetwork(*karate);
    return 0;
}
//Cria uma copia dos nos para ordenar
VERTEX* DataProcessing::organizaNos(){
    int i, vertexCount;
    VERTEX* listaDeNos;
    vertexCount = network.nvertices;
    listaDeNos = (VERTEX*)calloc(vertexCount,sizeof(VERTEX));
    //laco para copiar os dados do grafo para o vetor('listaDeNos')
    for(i=0; i< network.nvertices; i++){
        listaDeNos[i] = network.vertex[i];
    } 
    //Chamada do metodo para ordenacao dos nos
    organizaGrau(listaDeNos);
    return listaDeNos;
}
//Ordena a copia em ordem crescente de grau
VERTEX* DataProcessing::organizaGrau(VERTEX *listaDeNos){
    int i,imax, flag;
    VERTEX tempVertex;
    imax = network.nvertices;
    //ordenacao em ordem crescente de grau
    do{
        flag = 0;
        for(i=0;i<imax-1;i++){
            if(listaDeNos[i].degree > listaDeNos[i+1].degree){
                tempVertex = listaDeNos[i];
                listaDeNos[i] = listaDeNos[i+1];
                listaDeNos[i+1] = tempVertex;
                flag = 1;
            }
                
        }
    }while(flag == 1);



    return listaDeNos;
}
//Inicializa o processo para iniciar o Bron Kerbosch e trata a saida do algoritmo
vector <vector <VERTEX> > DataProcessing::bronProcess(){
    vector <VERTEX> R, P, X;
    vector < vector <VERTEX> > clique;
    int i, imax, grau;
    imax = network.nvertices;
    //Faz a copia de todos os vertices para o vetor 'P'
    for(i=0; i<imax-1;i++){
        P.push_back(network.vertex[i]);
    }
    
    
    bronKerbosch(R, P, X);
    //Valor minimo do grau dos cliques a serem mostrados
    grau = 5;
    for(vector <VERTEX> cliq : myCliques){
            if(cliq.size()>=grau){
                clique.push_back(cliq);
            }
    }
    //retorna um vetor que contem os cliques de grau maior ou igual ao especificado
    return clique;
}
//Implementacao do algoritmo de Bron Kerbosch sem pivotamento
void DataProcessing::bronKerbosch(vector <VERTEX> R, vector <VERTEX> P, vector <VERTEX> X)
{
    int i,imax;
   
    vector <VERTEX> R1;
    vector <VERTEX> P1;
    vector <VERTEX> X1;
    vector < vector <VERTEX> > clique;
    
    if(P.empty() && X.empty()){
        
        myCliques.push_back(R);
        

    }else{
       
        imax = P.size();
    
        for(VERTEX v: P){
   
            R1 = uniteVector(R, v);
     
            P1 = intersectVector(P, neighbours(v));
    
            X1 = intersectVector(X, neighbours(v));
 
            bronKerbosch(R1, P1, X1);
           
            P = removeItem(P, v);
            
            X.push_back(v);
            
        }
       
        
    }
    
}


vector <VERTEX> DataProcessing::neighbours(VERTEX v1)
{
    vector <VERTEX> vizinhos;
    int i=0, j=0, grau = 0;
    int nodeId;

    for(i=0; i<network.nvertices; i++){
        for(j=0; j< network.vertex[i].degree; j++){
            if(i+1 == v1.id){//i vai de 0 a 33 e ID de 1 a 34, logo id==i+1
                nodeId = network.vertex[i].edge[j].target;
                vizinhos.push_back(network.vertex[nodeId]);
                grau++;
            }
        }
    }

    return vizinhos;
}

vector <VERTEX> DataProcessing::removeItem(vector <VERTEX> v1,VERTEX v2)
{
    int i, achou;
    achou =0;
    for(i=0; i<v1.size(); i++){
        if(v1[i].id == v2.id){
            achou = 1;
            break;
        }
    }
    if(achou){
        v1.erase(v1.begin()+i);
        for(i; i<v1.size(); i++){
            v1[i] = v1[i+1];
        }
       v1.pop_back();
    }
    return v1;
}

vector <VERTEX> DataProcessing::uniteVector(vector <VERTEX> v1,VERTEX v2)
{

    int i, elementoIgual;
    elementoIgual = 0;
    for(i=0; i!=v1.size(); i++){
        if(v1[i].id == v2.id){
            elementoIgual = 1;
        }               
    }  
    if(!elementoIgual){
        v1.push_back(v2);
    }
    
    return v1;
}


vector <VERTEX> DataProcessing::intersectVector(vector <VERTEX> v1, vector <VERTEX> v2)
{
    vector <VERTEX> intersectDone;
    int i, j;
    for(i=0; i!=v1.size(); i++){
        for(j=0; j!=v2.size(); j++){
            if(v1[i].id == v2[j].id){
               intersectDone.push_back(v1[i]); 
            }

        }
    }

    return intersectDone;
}

MenuOptions::MenuOptions()
{
    opcao = 0;
    VALIDO = false;
}
void MenuOptions::validaOpcao(int opcao)
{
    if(opcao>0 & opcao <5){
        setValido(true);
    }else{
        setValido(false);
    }
}
