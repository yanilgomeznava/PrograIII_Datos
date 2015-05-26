#ifndef GRAFO_H
#define GRAFO_H
#define DEF_FILAS 100
#define DEF_COLUMNAS 100

class Grafo
{

    private:

        int **grafo;
        int **arcos;
        int cantidadNodos;
        int filas;
        int columnas;
        int nodoActual;
        bool *visitados;

    public:

        Grafo(int pFilas= DEF_FILAS,int pColumnas= DEF_COLUMNAS);

        virtual ~Grafo();

        void initArcos();
        void initGrafo();
        int* djkstra(int**pArbolExp,int pNodoActual);
        void djkstraAux(int**pArbolExp,int pNodoActual,int*pRutas,int*pPesos);
        void darPesosVecinosDjkstra(int* pPesos,int*pRutas,int pNodoActual,int**pArbolExpansion);
        void generarArbolExpanAux(int**pArbolExp,int pNodoActual);
        void generarMultiCamino(int**pArbolExp);
        bool hasConexionesUnVisited(int pNodo);
        bool isVisited(int pNodo){return visitados[pNodo];}
        void limpiarVisitados();
        int** generarArbolExpan();
        void agregarArco(int numNodoOrig,int numNodoDest);
        void eliminarArco(int numNodoOrig,int numNodoDest);
        void imprimirGrafo();
        int** getGrafo(){return grafo;}
        int** getArcos(){return arcos;}
        bool allVisited();
        void imprimirRutas(int*pRutas);




};

#endif // GRAFO_H
