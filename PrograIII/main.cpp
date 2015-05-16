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

    while(i == 0)
    {
        xActual = X_INICIAL * contador;
        yActual = Y_INICIAL * contador;
        initwindow(xActual, yActual);
        grafo = new DLinkedList<int>[yActual]();
        for(int i = 0; i < xActual; i++)
        {
            for(int j = 0; j < yActual; j++)
            {
                grafo[i].insert(j);
            }
        }

        cin >> i;
        contador ++;
    }

    return 0;
}
