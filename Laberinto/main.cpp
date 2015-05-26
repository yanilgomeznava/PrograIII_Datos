#include <iostream>
#include <Grafo.h>
#include <iostream>
#include <winbgim.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>


#define NODE_SIZE 10
#define MARGIN_SIZE NODE_SIZE
#define DEF_DELAY 3

using namespace std;



//Variables
int **arcos;
int filasLaberinto;
int columnasLaberinto;
int cantidadNodos;
int windowWidth;
int windowHeight;
int*rutas;
bool djkstraActivated=false;
int hintAttemps=3;

//Funciones
void outintxy(int x, int y, int value);
int get_int(int min, std::string prompt);
bool validarMov(int pPosActual,int pDireccion);
void pintarNodos();
void pintarArbolExpansion();
void pintarDjkstra(int pNodoActual,int*pRutas);
void imprimirRutas(int*pRutas);

int main()
{



    filasLaberinto = get_int(1,"Ingrese la cantidad de filas deseadas:");
    columnasLaberinto = get_int(1,"Ingrese la cantidad de columnas deseadas:");
    cantidadNodos = filasLaberinto * columnasLaberinto;
    windowWidth = (MARGIN_SIZE*2)+((columnasLaberinto*NODE_SIZE)*2);
    windowHeight = (MARGIN_SIZE*2)+((filasLaberinto*NODE_SIZE)*2);


    srand(time(0));
    Grafo *g1= new Grafo(filasLaberinto,columnasLaberinto);



    while (true){

    initwindow (windowWidth,windowHeight);

    //Margenes
    setfillstyle(SOLID_FILL, 1);
    bar(0,0,windowWidth-NODE_SIZE,MARGIN_SIZE); //Arriba
    bar(0,0,MARGIN_SIZE,windowHeight-NODE_SIZE); //Izquierda
    bar(windowWidth-MARGIN_SIZE*2,0,windowWidth,windowHeight); //Derecha
    bar(0,windowHeight-MARGIN_SIZE*2,windowWidth,windowHeight); //Abajo

    //Impresion de nodos
    pintarNodos();

    //Conexion de nodos
    arcos= g1->generarArbolExpan();
    pintarArbolExpansion();

    char c;

    int filaJugador = 0;
    int columnaJugador = 0;
    int nodoActual= 0;

    setfillstyle(SOLID_FILL,4);
    bar((MARGIN_SIZE*(1+(columnaJugador*2)))+3,(MARGIN_SIZE*(1+(filaJugador*2)))+3,(MARGIN_SIZE*(2+(columnaJugador*2)))-3,(MARGIN_SIZE*(2+(filaJugador*2)))-3);

    do{

        c = (char) getch();


        if(djkstraActivated){

            pintarNodos();
            pintarArbolExpansion();
            djkstraActivated=false;
            setfillstyle(SOLID_FILL,4);
            bar((MARGIN_SIZE*(1+(columnaJugador*2)))+2,(MARGIN_SIZE*(1+(filaJugador*2)))+2,(MARGIN_SIZE*(2+(columnaJugador*2)))-2,(MARGIN_SIZE*(2+(filaJugador*2)))-2);

        }

        if(c != 0 && c!='h'){
            cout << "Please use the arrow keys." << endl;

        }else if(c=='h'){
            //cout<<"h Key"<<endl;
            if (hintAttemps>0){
                cout<<"Hints left: "<<--hintAttemps<<endl;
                rutas= g1->djkstra(arcos,nodoActual);
                //cout<<"djkstra good"<<endl;
                djkstraActivated=true;
                pintarDjkstra(nodoActual,rutas);
            }else{
                cout<<"No more hints left"<<endl;
            }
        }else{

            c = (char) getch();

            switch (c){

                case KEY_UP:

                    if(filaJugador > 0 && validarMov(nodoActual,0)){
                        setfillstyle(SOLID_FILL,15);
                        bar(MARGIN_SIZE*(1+(columnaJugador*2)),MARGIN_SIZE*(1+(filaJugador*2)),MARGIN_SIZE*(2+(columnaJugador*2)),MARGIN_SIZE*(2+(filaJugador*2)));
                        setfillstyle(SOLID_FILL,4);
                        filaJugador--;
                        nodoActual-=columnasLaberinto;
                        bar((MARGIN_SIZE*(1+(columnaJugador*2)))+2,(MARGIN_SIZE*(1+(filaJugador*2)))+2,(MARGIN_SIZE*(2+(columnaJugador*2)))-2,(MARGIN_SIZE*(2+(filaJugador*2)))-2);
                        //cout << "Up key."     << endl;
                    }
                    break;

                case KEY_LEFT:

                    if(columnaJugador > 0 && validarMov(nodoActual,1)){
                        setfillstyle(SOLID_FILL,15);
                        bar(MARGIN_SIZE*(1+(columnaJugador*2)),MARGIN_SIZE*(1+(filaJugador*2)),MARGIN_SIZE*(2+(columnaJugador*2)),MARGIN_SIZE*(2+(filaJugador*2)));
                        setfillstyle(SOLID_FILL,4);
                        columnaJugador--;
                        nodoActual--;
                        bar((MARGIN_SIZE*(1+(columnaJugador*2)))+2,(MARGIN_SIZE*(1+(filaJugador*2)))+2,(MARGIN_SIZE*(2+(columnaJugador*2)))-2,(MARGIN_SIZE*(2+(filaJugador*2)))-2);
                        //cout << "Left key."   << endl;
                    }
                    break;

                case KEY_RIGHT:

                    if(columnaJugador < columnasLaberinto-1 && validarMov(nodoActual,2)){
                        setfillstyle(SOLID_FILL,15);
                        bar(MARGIN_SIZE*(1+(columnaJugador*2)),MARGIN_SIZE*(1+(filaJugador*2)),MARGIN_SIZE*(2+(columnaJugador*2)),MARGIN_SIZE*(2+(filaJugador*2)));
                        setfillstyle(SOLID_FILL,4);
                        columnaJugador++;
                        nodoActual++;
                        bar((MARGIN_SIZE*(1+(columnaJugador*2)))+2,(MARGIN_SIZE*(1+(filaJugador*2)))+2,(MARGIN_SIZE*(2+(columnaJugador*2)))-2,(MARGIN_SIZE*(2+(filaJugador*2)))-2);
                        //cout << "Right key."  << endl;
                    }
                    break;

                case KEY_DOWN:

                    if(filaJugador < filasLaberinto-1 && validarMov(nodoActual,3)){
                        setfillstyle(SOLID_FILL,15);
                        bar(MARGIN_SIZE*(1+(columnaJugador*2)),MARGIN_SIZE*(1+(filaJugador*2)),MARGIN_SIZE*(2+(columnaJugador*2)),MARGIN_SIZE*(2+(filaJugador*2)));
                        setfillstyle(SOLID_FILL,4);
                        filaJugador++;
                        nodoActual+=columnasLaberinto;
                        bar((MARGIN_SIZE*(1+(columnaJugador*2)))+2,(MARGIN_SIZE*(1+(filaJugador*2)))+2,(MARGIN_SIZE*(2+(columnaJugador*2)))-2,(MARGIN_SIZE*(2+(filaJugador*2)))-2);
                        //cout << "Down key."   << endl;
                    }
                    break;


                default:
                    cout << "Unknown extended key.\n" << endl;
            }
            if((columnaJugador == columnasLaberinto-1) && (filaJugador == filasLaberinto-1)){
                    cout << "Congratulations! You won!\n";
                    break;
            }
        }

    } while ((c != 'x') && (c != 'X'));
    hintAttemps=3;



    closegraph();
    }
    return 0;
}




void lecturaDeTecla(){
    char c;

    do{
        c = (char) getch();

        if(c != 0){
            cout << "Please use the arrow keys." << endl;
        }else{

            c = (char) getch();

            switch (c){

                case KEY_UP:
                    cout << "Up key."     << endl; break;
                    setfillstyle(SOLID_FILL,4);
                    bar(20,20,100,100);

                case KEY_LEFT:
                    cout << "Left key."   << endl; break;

                case KEY_RIGHT:
                    cout << "Right key."  << endl; break;

                case KEY_DOWN:
                    cout << "Down key."   << endl; break;

                case 'h':
                    cout<<"h key"<<endl;break;

                default:
                    cout << "Unknown extended key." << endl;
            }

        }
    } while ((c != 'x') && (c != 'X'));
}


void outintxy(int x, int y, int value)
{

   char digit_string[20];

   sprintf(digit_string, "%d", value);

   outtextxy(x, y, digit_string);

}

int get_int(int min, std::string prompt){
	int ret_integer;
	std::string str_number;

	while(true) {

		std::cout << prompt;
		std::getline(std::cin, str_number); //get string input
		std::stringstream convert(str_number); //turns the string into a stream

		//checks for complete conversion to integer and checks for minimum value
		if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= min) {
            return ret_integer;
		}

		std::cin.clear(); //just in case an error occurs with cin (eof(), etc)
		std::cerr << "La cantidad ingresada debe ser mayor a " << min << ". Por favor intente de nuevo..\n";
	}
}

bool validarMov(int pPosActual,int pDireccion ){ //pDireccion 0 es arriba, 1 es izquierda, 2 es derecha, 3 es abajo
    if (arcos[pPosActual][pDireccion]!=-2){
        return true;
    }
    return false;
}

void pintarArbolExpansion(){

    setfillstyle(SOLID_FILL,15);
    for (int NumNodo=0;NumNodo<cantidadNodos;NumNodo++){
        if (arcos[NumNodo][0]!=-2){
            bar(MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto)-NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto)+NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto));
        }
        if (arcos[NumNodo][1]!=-2){
            bar(MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto)-NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto)+NODE_SIZE);
        }
        if (arcos[NumNodo][2]!=-2){
            bar(MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto)+NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto)+NODE_SIZE*2,MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto)+NODE_SIZE);

        }
        if (arcos[NumNodo][3]!=-2){
            bar(MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto)+NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(NumNodo%columnasLaberinto)+NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(NumNodo/columnasLaberinto)+NODE_SIZE*2);

        }
    }

}

void pintarDjkstra(int pNodoInicio,int*pRutas){


    setfillstyle(SOLID_FILL,2);
    int nodoActual= cantidadNodos-1;
    int nodoCamino;
    while(nodoActual!=pNodoInicio){

        nodoCamino= pRutas[nodoActual];
        if (nodoActual>nodoCamino){
            bar(MARGIN_SIZE+NODE_SIZE*2*(nodoCamino%columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(nodoCamino/columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(nodoActual%columnasLaberinto)+NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(nodoActual/columnasLaberinto)+NODE_SIZE);
        }else{
            bar(MARGIN_SIZE+NODE_SIZE*2*(nodoActual%columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(nodoActual/columnasLaberinto),MARGIN_SIZE+NODE_SIZE*2*(nodoCamino%columnasLaberinto)+NODE_SIZE,MARGIN_SIZE+NODE_SIZE*2*(nodoCamino/columnasLaberinto)+NODE_SIZE);

        }
        nodoActual=nodoCamino;
    }



}

void pintarNodos(){
    setfillstyle(SOLID_FILL,15);
    for(int x = -1; x < columnasLaberinto-1; x++){
        for(int y = -1; y < filasLaberinto-1; y++){
                bar(MARGIN_SIZE*(3+(x*2)),MARGIN_SIZE*(3+(y*2)),MARGIN_SIZE*(4+(x*2)),MARGIN_SIZE*(4+(y*2)));
        }
    }

}

void imprimirRutas(int*pRutas){

    cout<<"Rutas"<<endl;
    cout<<pRutas[0]<<endl;
    for (int i=0;i<cantidadNodos;i++){
        cout<<"Nodo: "<<i<<"Ruta: "<<pRutas[i]<<endl;
    }


}

