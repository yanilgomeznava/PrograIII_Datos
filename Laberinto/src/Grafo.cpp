#include "Grafo.h"
#include <Matrix.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#define MAX_SIZE 10000

Grafo::Grafo(int pFilas,int pColumnas)
{
    filas=pFilas;
    columnas=pColumnas;
    cantidadNodos= filas*columnas;
    nodoActual=0;
    Matrix *matrizGrafo= new Matrix(filas,columnas);
    grafo= matrizGrafo->getMatrix();
    visitados= new bool[cantidadNodos];
    Matrix *matrizArcos= new Matrix(cantidadNodos,4);
    arcos= matrizArcos->getMatrix();
    initGrafo();
    initArcos();

}

Grafo::~Grafo(){
    delete *grafo;
    delete *arcos;
}

void Grafo::initGrafo(){

    for (int i=0;i<cantidadNodos;i++){
        grafo[i/columnas][i%columnas]=i;
    }

}

void Grafo::initArcos(){

    for(int z = 0; z < cantidadNodos; z++){
            if((z) - columnas >= 0){
                arcos[z][0] = grafo[z/columnas-1][z%columnas];
            }else{
                arcos[z][0] = -2;
            }
            if(((z) % columnas) != 0){
                arcos[z][1] = grafo[z/columnas][z%columnas-1];
            }else{
                arcos[z][1] = -2;
            }
            if((((z) + 1) % columnas) != 0){
                arcos[z][2] = grafo[z/columnas][z%columnas+1];
            }else{
                arcos[z][2] = -2;
            }
            if(((z) + columnas) < (cantidadNodos)){
                arcos[z][3] = grafo[z/columnas+1][z%columnas];
            }else{
                arcos[z][3] = -2;
            }
        }


//    for(int w = 0; w < cantidadNodos; w++){
//        std::cout << "Nodo:" << w << "--->" << arcos[w][0] << "," << arcos[w][1] << "," << arcos[w][2] << "," << arcos[w][3] << std::endl;
//    }

}

void Grafo::limpiarVisitados(){
    for(int i=0;i<cantidadNodos;i++){
        visitados[i]=false;

    }
}


int** Grafo::generarArbolExpan(){

    int **ArbolExp;
    Matrix *matrizArbol= new Matrix(cantidadNodos,4);
    ArbolExp= matrizArbol->getMatrix();
    nodoActual=0;
    //Dejar conexiones nulas
    for (int i=0;i<cantidadNodos;i++){
        for (int j=0;j<4;j++){
            ArbolExp[i][j]=-2;
        }
    }

    limpiarVisitados();
    visitados[nodoActual]=true;
    generarArbolExpanAux(ArbolExp,nodoActual);

    return ArbolExp;
}

void Grafo::generarArbolExpanAux(int **pArbolExpansion,int pNodoActual){


    while (hasConexionesUnVisited(pNodoActual)){
            int arcoSig= rand() % 4+0;

            //Verifica que la conexion sea válida y que el nodo al que va no se encuentre visitado
            if (arcos[pNodoActual][arcoSig]!=-2 && !isVisited(arcos[pNodoActual][arcoSig])){

                //Marca el nodo visitado
                int nodoSig= arcos[pNodoActual][arcoSig];
                visitados[nodoSig]=true;

                //Da conexiones en el arbol de expansión hacia ambos lados
                //Para nodoActual
                pArbolExpansion[pNodoActual][arcoSig]= nodoSig;

                //Para nodoSiguiente
                int arcoAnt;

                if (arcoSig==0){
                    arcoAnt=3;
                }else if(arcoSig==1){
                    arcoAnt=2;
                }else if(arcoSig==2){
                    arcoAnt=1;
                }else{
                    arcoAnt=0;
                }
                pArbolExpansion[nodoSig][arcoAnt]=pNodoActual;

                generarArbolExpanAux(pArbolExpansion,nodoSig);
            }

    }

}



bool Grafo::hasConexionesUnVisited(int pNodo){
    for (int i=0;i<4;i++){
        if (arcos[pNodo][i]!=-2 && !isVisited(arcos[pNodo][i])){
            return true;
        }
    }
    return false;
}

int* Grafo::djkstra(int**pArbolExp,int pNodoActual){

    limpiarVisitados();
    int *pesos= new int[cantidadNodos];
    int *rutas= new int[cantidadNodos];
    nodoActual= pNodoActual;

    for(int i=0;i<cantidadNodos;i++){
        pesos[i]= MAX_SIZE;
        rutas[i]= -2;
    }
    visitados[nodoActual]=true;
    rutas[nodoActual]=nodoActual;
    pesos[nodoActual]=0;

    darPesosVecinosDjkstra(pesos,rutas,nodoActual,pArbolExp);

    djkstraAux(pArbolExp,nodoActual,rutas,pesos);

    return rutas;
}



void Grafo::djkstraAux(int **pArbolExp,int pNodoActual,int *pRutas, int *pPesos){


    if (!allVisited()){

        int menorPeso=MAX_SIZE;
        for(int i=0;i<cantidadNodos;i++){
            if  (pPesos[i]<menorPeso && !isVisited(i)){
                menorPeso= pPesos[i];
            }
        }

        int nodoSig;
        for (int i=0;i<cantidadNodos;i++){
            if (pPesos[i]==menorPeso && !isVisited(i)){
                nodoSig= i;
                visitados[nodoSig]=true;
                darPesosVecinosDjkstra(pPesos,pRutas,nodoSig,pArbolExp);
                djkstraAux(pArbolExp,nodoSig,pRutas,pPesos);
            }
        }
    }


}

void Grafo::darPesosVecinosDjkstra(int *pPesos,int *pRutas,int pNodoActual,int**pArbolExp){

    for (int i=0;i<4;i++){
        int vecino= pArbolExp[pNodoActual][i];
        if (vecino!= -2 && (pPesos[pNodoActual]+1<pPesos[vecino])){
            pPesos[vecino]=pPesos[pNodoActual]+1;
            pRutas[vecino]=pNodoActual;
        }
    }
}


bool Grafo::allVisited(){

    for (int i=0; i<cantidadNodos;i++){
        if (!visitados[i])
            return false;
    }
    return true;

}

void Grafo::imprimirRutas(int*pRutas){

    std::cout<<"Rutas"<<std::endl;
    for (int i=0;i<cantidadNodos;i++){
        std::cout<<"Nodo: "<<i<<" Ruta: "<<pRutas[i]<<std::endl;
    }


}



