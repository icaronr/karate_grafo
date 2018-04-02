#include <iostream>
#include <string>
#include <algorithm>
#include "dataprocessing.h"
extern "C"{
#include "readgml.h"   
}


using namespace std;

DataProcessing::DataProcessing()
{
entrada = 0;
network = { 0,      //nvertices
            0,      // directed
            NULL    //*vertex
};

myCliques = {};


}

int DataProcessing::getInput()
{
    
    cin >> entrada;
    getchar();
    return entrada;
}

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
    free_network(&network);
cout << endl << "Arquivo analisado com sucesso!" << endl;

getchar();
    setNetwork(*karate);
    return 0;
}

VERTEX* DataProcessing::organizaNos(){
    int i, vertexCount;
    VERTEX* listaDeNos;
    vertexCount = network.nvertices;
    listaDeNos = (VERTEX*)calloc(vertexCount,sizeof(VERTEX));

    for(i=0; i< network.nvertices; i++){
        listaDeNos[i] = network.vertex[i];
    } 
    organizaGrau(listaDeNos);
    return listaDeNos;
}

VERTEX* DataProcessing::organizaGrau(VERTEX *listaDeNos){
    int i,imax, flag;
    VERTEX tempVertex;
    imax = network.nvertices;
    
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

vector <vector <VERTEX> > DataProcessing::bronProcess(){
    vector <VERTEX> R, P, X;
    vector < vector <VERTEX> > clique;
    int i, imax;
    imax = network.nvertices;
    for(i=0; i<imax-1;i++){
        P.push_back(network.vertex[i]);
    }
    
    
    bronKerbosch(R, P, X);
    for(vector <VERTEX> cliq : myCliques){
            if(cliq.size()>4){
                clique.push_back(cliq);
            }
    }
    return clique;
}

void DataProcessing::bronKerbosch(vector <VERTEX> R, vector <VERTEX> P, vector <VERTEX> X)
{
    int i,imax;
   
    vector <VERTEX> R1;
    vector <VERTEX> P1;
    vector <VERTEX> X1;
    vector < vector <VERTEX> > clique;
   // cout << endl << "TAMANHO  -+- " << P.size() << endl;
    
    if(P.empty() && X.empty()){
        
        myCliques.push_back(R);
        

    }else{
       
        imax = P.size();
        //cout << endl << P.size() << " tamanho nessa iteracao" << endl;
        //for(i=0; i<imax; i++){
        for(VERTEX v: P){
            //cout << endl << "i=  " << i << "   P[i].id =  " << P[i].id << endl;
            //cout << endl << "TAMANHO  -- " << P.size() << endl;
            
            //R1 = uniteVector(R,P[i]);
            R1 = uniteVector(R, v);
            //for(int pao =0; pao < R1.size(); pao++){
            //    cout << endl << "R1(" << pao << ") - " << R1[pao].id << endl;
            //}
            // getchar();
            //P1 = intersectVector(P,neighbours(P[i]));
            P1 = intersectVector(P, neighbours(v));
            //for(int pao =0; pao < P1.size(); pao++){
            //    cout << endl << "P1(" << pao << ") - " << P1[pao].id << endl;
            //}
            // getchar();
            //X1 = intersectVector(X, neighbours(P[i]));
            X1 = intersectVector(X, neighbours(v));
            //for(int pao =0; pao < R1.size(); pao++){
            //    cout << endl << "X1(" << pao << ") - " << X1[pao]->id << endl;
            //}
            // getchar();
            //cout << endl << "-----------------PROXIMA CHAMADA----------------------------" << endl;
            bronKerbosch(R1, P1, X1);
            //cout << endl << "ASJDHFLJAH" << endl;
            //cout << endl << "P[i](" << i << ") - " << P[i].id << endl;
           //for(int pao =0; pao < P.size(); pao++){
            //    cout << endl << "P(" << pao << ")(pao) - " << P[pao].id << endl;
            //}
            //cout << endl << "a ser removido = " << v.id << endl;
           // P = removeItem(P,P[i]);
            P = removeItem(P, v);
            //cout << endl << "REMOVED" << endl;
           // for(int pao =0; pao < P.size(); pao++){
            //    cout << endl << "P(" << pao << ") - " << P[pao].id << endl;
          //  }
            
            //X.push_back(P[i]);
            X.push_back(v);
            
        }
       
        
    }
     //cout << endl << "IOOOP" << endl;
     //getchar();
    
}


vector <VERTEX> DataProcessing::neighbours(VERTEX v1)
{
    vector <VERTEX> vizinhos;
    //cout << endl << "NO TESTE  -- " << v1->id << endl;
    int i=0, j=0, grau = 0;
    int nodeId;

    for(i=0; i<network.nvertices; i++){
        for(j=0; j< network.vertex[i].degree; j++){
            if(i+1 == v1.id){//i vai de 0 a 33 e ID de 1 a 34, logo id==i+1
                nodeId = network.vertex[i].edge[j].target;
                vizinhos.push_back(network.vertex[nodeId]);//nodeID vai de 1 a 34, o index do vertex começa em 0
                //cout << endl << network.vertex[nodeId].id << " - " << v1.id << endl;
                grau++;
            }/*else{
                if(network.vertex[i].edge[j].target == v1->id){
                    vizinhos.push_back(&network.vertex[i]);
                    grau++;
                }
            }*/
        }
    }
   /* cout << endl << grau << "    -   " << v1->degree << endl;
    getchar();
    if(grau == v1->degree){
        cout << endl << "GRAU OK! -  " << grau << endl;
        getchar();
        getchar();
    }*/

    return vizinhos;
}

vector <VERTEX> DataProcessing::removeItem(vector <VERTEX> v1,VERTEX v2)
{
    //cout << endl << "remove(start)" << endl;
    int i, achou;
    achou =0;
    for(i=0; i<v1.size(); i++){
        if(v1[i].id == v2.id){
            achou = 1;
            break;
        }
    }
    //cout << endl << "middle" << endl;
    if(achou){
        v1.erase(v1.begin()+i);
        for(i; i<v1.size(); i++){
            v1[i] = v1[i+1];
        }
      //  cout << endl << "opa" << endl;
       v1.pop_back();
       //cout << endl << "pas" << endl;
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
