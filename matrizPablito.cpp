// multilista

#include<iostream>
using namespace std;

struct Lista_sec{
    int dato;
    Lista_sec* siguiente;
};

struct Lista_prim{
    Lista_sec* cabecera;
    Lista_prim* siguiente;
};

void agregar(Lista_prim*&);
void agregar(Lista_sec*&);
void construir_matriz(Lista_prim*&, int, int);
void rellenar_matriz(Lista_prim*&, int, int);
void ver_matriz(Lista_prim*, int, int);

int main(){
    int filas, col;
    Lista_prim* principal = NULL;

    cout << "Ingrese la cantidad de filas de la matriz: ";
    cin >> filas;
    cout << "Ingrese la cantidad de columnas de la matriz: ";
    cin >> col;

    construir_matriz(principal, filas, col);

    for (int i=0; i<col*filas; i++){
        rellenar_matriz(principal, filas, col);
    }
    
    cout << "\nMostrando matriz..." << endl;
    ver_matriz(principal, filas, col);
    
    return 0;
}

void agregar(Lista_prim* &principal){
    Lista_prim* nuevo = new Lista_prim();
    nuevo->cabecera = NULL;
    
    Lista_prim* actual = principal;
    Lista_prim* anterior;

    while (actual != NULL){
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == principal){
        principal = nuevo;
    }
    else {
        anterior->siguiente = nuevo;
    }

    nuevo->siguiente = actual;
}

void agregar(Lista_sec* &cabecera){
    Lista_sec* nuevo = new Lista_sec();
    nuevo->dato = 0;

    Lista_sec* actual = cabecera;
    Lista_sec* anterior;

    while (actual != NULL){
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual == cabecera){
        cabecera = nuevo;
    }
    else {
        anterior->siguiente = nuevo;
    }

    nuevo->siguiente = actual;
}

void construir_matriz(Lista_prim* &principal, int filas, int col){
    for (int i=0; i<col; i++){
        agregar(principal);
    }

    Lista_prim* aux = principal;
    for (int i=0; i<col; i++){
        for (int i=0; i<filas; i++){
            agregar(aux->cabecera);
        }
        aux = aux->siguiente;
    }
}

void rellenar_matriz(Lista_prim* &principal, int filas, int col){
    int fPos, cPos;
    Lista_prim* aux = principal;
    
    cout << "\nIngrese la fila: ";
    cin >> fPos;
    cout << "Ingrese la columna: ";
    cin >> cPos;

    for (int i=0; i<cPos; i++){
        aux = aux->siguiente;
    }

    Lista_sec* aux2 = aux->cabecera;
    
    for (int i=0; i<fPos; i++){
        aux2 = aux2->siguiente;
    }

    cout << "Ingrese el dato: ";
    cin >> aux2->dato;
}

void ver_matriz(Lista_prim* principal, int filas, int col){
    Lista_prim* aux = principal;
    Lista_sec* aux2 = aux->cabecera;

    for (int i=0; i<filas; i++){
        aux = principal;
        aux2 = aux->cabecera;
        for (int j=0; j<col; j++){
            for (int k=0; k<i; k++){
                aux2 = aux2->siguiente;
            }
            cout << aux2->dato << " ";
            aux = aux->siguiente;

            if (aux != NULL){
                aux2 = aux->cabecera;
            }
        }
        cout << endl;
    }
}