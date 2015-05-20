#include <iostream>
#include <winbgim.h>
#include "DLinkedList.h"

using namespace std;

int main()
{
    int X_INICIAL = 50;
    int Y_INICIAL = 25;

    DLinkedList<int> *grafo;

    int i=0;
    int contador = 1;

    int columnasActual = 0;
    int filasActual = 0;
    int columnas = 0;
    int filas = 0;

    while(i == 0)
    {
        columnasActual = X_INICIAL * contador;
        filasActual = Y_INICIAL * contador;

        grafo = new DLinkedList<int>[columnasActual * filasActual];

        initwindow(columnasActual, filasActual);
        columnas = columnasActual / X_INICIAL;
        filas = filasActual / Y_INICIAL;
        cout << columnas << " - " << filas << endl;

        circle(columnasActual / 2, filasActual / 2, 1);


        delete [] grafo;
        cin >> i;
        contador ++;
        closegraph();
    }

    return 0;
}
