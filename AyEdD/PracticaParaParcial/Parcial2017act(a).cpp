#include <iostream>
#include <string>

using namespace std;

struct articulos{
    string codigo_articulo;
    string rubro;
    string descripcion;
    float precio;
};

struct LSE {
    articulos info;
    LSE* link;
};

struct Npila{
    Npila* link;
    articulos info;
};

void APILAR(Npila* &pila, LSE* nnodo){
    Npila* nuevo = new Npila();
    nuevo->info = nnodo->info;
    nuevo->link = NULL;
    if (pila == NULL){
        pila = nuevo;
        return;
    }    
    nuevo ->link = pila;
    pila = nuevo;
}

void eliminar_ocurrencia_LSE (LSE* &raiz, LSE* nodoelim){
    if (raiz == NULL) return;
    
    LSE* aux = raiz;
    LSE* auxant = NULL;

    if (raiz == nodoelim){
        raiz = raiz->link;;
        delete aux;
        return;
    }
    while  (aux !=nodoelim && aux != NULL){
        auxant = aux;
        aux = aux->link;
    }
    if (aux == NULL) return;
    auxant->link = aux->link;
    delete aux;
}

void SacarDeListaYPasarAPila (LSE* &raiz, Npila* &Pila){
    if (raiz == NULL) return;

    LSE* aux = raiz;
    
    while (aux!=NULL){
        LSE* siguiente = aux->link;
        if (aux->info.rubro == "relojeria" && aux->info.precio < 500){
            aux->info.precio+=aux->info.precio * 0.15;
            APILAR (Pila, aux);
            eliminar_ocurrencia_LSE (raiz, aux);
        }
        aux = siguiente;
    }
}