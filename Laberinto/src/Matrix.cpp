#include "Matrix.h"

Matrix::Matrix(int pFilas,int pColumnas)
{

    filas= pFilas;
    columnas= pColumnas;
    CantidadNodos= pFilas*pColumnas;
    matrix= new int*[filas];


    for (int i=0;i<filas;i++){
        matrix[i]= new int[columnas];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < CantidadNodos; ++i)
        delete [] matrix[i];
  delete [] matrix;
}
