#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include "DLinkedList.h"

using namespace std;

int main()
{
    int X_INICIAL = 50;
    int Y_INICIAL = 25;

    DLinkedList<int> *grafo;

    int i=0;
    int contador = 1;
    int currentWindow;

    int columnasActual = 0;
    int filasActual = 0;
    int columnas = 0;
    int filas = 0;
    int tamanoGrafo = 0;

    while(i == 0)
    {
        columnasActual = X_INICIAL * contador;
        filasActual = Y_INICIAL * contador;
        tamanoGrafo = columnasActual * filasActual;

        grafo = new DLinkedList<int>[tamanoGrafo];

        for(int i = 0; i < tamanoGrafo; i++)
        {
            if(0 < i && i < columnasActual)
            {
                grafo[i].insert(i - 1);
                grafo[i].insert(i + 1);
                grafo[i].insert(i + columnasActual);
            }
            else if((tamanoGrafo - columnasActual) < i && i < tamanoGrafo)
            {
                grafo[i].insert(i - 1);
                grafo[i].insert(i + 1);
                grafo[i].insert(i - columnasActual);
            }
            else if(i % 4 == 0)
            {
                grafo[i].insert(i + 1);
                grafo[i].insert(i + columnasActual);
            }
            else if((i + 1) % 4 == 0)
            {
                grafo[i].insert(i - 1);
                grafo[i].insert(i + columnasActual);
            }
            else
            {
                grafo[i].insert(i + 1);
                grafo[i].insert(i - 1);
                grafo[i].insert(i + columnasActual);
                grafo[i].insert(i - columnasActual);
            }
        }

        initwindow(columnasActual, filasActual);

        circle(20, 20, 10);
        cout << getactivepage() << " - " << getvisualpage() << getcurrentwindow() << endl;


        delete [] grafo;
        cin >> i;
        contador ++;
        closegraph();
    }

    return 0;
}
