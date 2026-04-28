#include <iostream>

using namespace std;

struct nodo_columna {
    nodo_fila* columna = NULL;
    nodo_columna* link = NULL;
}typedef ncolumna;

struct nodo_fila{
    nodo_fila* link;
    int dato;

}typedef nfila;

int main(){
    ncolumna matriz;
    int dato;
    int cant_filas;
    int cant_columnas;
    cout << "ingrese la cantidad de filas que quiere que tenga su matriz\n";
    cin >> cant_filas;
    cout << "ingrese la cantidad de columnas que quiere que tenga su matriz\n";
    cin >> cant_columnas;


    return 0;
}

void CreadorMatrizcolumnas(ncolumna*  &matriz,int columna){
    ncolumna* nnodo = new ncolumna() ;
    ncolumna* aux;
    if (matriz == NULL){
        matriz = nnodo;
        return;
    }
    while (aux->link != NULL){
        aux->link = aux->link->link;
    }
    aux->link = nnodo;
}

void CreadorMatrizfilas (ncolumna* matriz, int filas){
    ncolumna* auxc;
    nfila* auxf;
    auxc = matriz;
    if (matriz == NULL){
        return;
    }
    for (int i = 0; i<filas;i++){
        nfila* nnodo = new nfila();
        if (auxc->columna==NULL){
            auxc->columna = nnodo;
        }
        while ( ){


        }


    }

}


