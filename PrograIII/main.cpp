#include <iostream>
#include <winbgim.h>
#include "DLinkedList.h"

using namespace std;

int main()
{
    int X_INICIAL = 50;
    int Y_INICIAL = 50;

    DLinkedList<int> *grafo;

    int i=0;
    int contador = 1;

    int xActual = 0;
    int yActual = 0;
    int columnas = 0;
    int filas = 0;

    while(i == 0)
    {
        xActual = X_INICIAL * contador;
        yActual = Y_INICIAL * contador;
        grafo = new DLinkedList<int>[yActual]();

        for(int i = 0; i < xActual; i++)
        {
            for(int j = 0; j < yActual; j++)
            {
                grafo[i].insert(j);
            }
        }

        initwindow(xActual, yActual);
        columnas = xActual / X_INICIAL;
        filas = yActual / Y_INICIAL;

        cout << columnas << " - " << filas << endl;

        int FONDO = COLOR(255, 255, 255);
        setcolor(FONDO);
        for(int i = 0; i < filas; i++)
        {
            for(int j = 0; j < columnas; j++)
            {
                circle(i, j , 5);
            }
        }



        cin >> i;
        contador ++;
        cleardevice();
        closegraph();
    }

    return 0;
}
