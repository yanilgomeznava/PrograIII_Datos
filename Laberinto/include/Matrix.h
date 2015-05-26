#ifndef MATRIX_H
#define MATRIX_H
#define DEF_FILAS 100
#define DEF_COLUMNAS 100


class Matrix
{

    private:
        int **matrix;
        int CantidadNodos;
        int filas;
        int columnas;

    public:
        Matrix(int pFilas= DEF_FILAS, int pColumnas= DEF_COLUMNAS);
        virtual ~Matrix();
        int** getMatrix(){return matrix;}

};

#endif // MATRIX_H
