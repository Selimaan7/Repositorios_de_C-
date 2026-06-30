#include <iostream>
#include <string>
using namespace std;

struct Entrega {
    int id_paquete;
    float peso;
    string ciudad_destino;
    int prioridad;
};

struct NodoLDE {
    Entrega info;
    NodoLDE* ant;
    NodoLDE* sig;
};

struct NodoLSE {
    Entrega info;
    NodoLSE* sig;
};

void listaDE_eliminar_ocurrencia (NodoLDE* &listaDE, NodoLDE* nodo);
void listaSE_agregar_ordenado (NodoLSE* &listaSE, NodoLDE* nodo);

NodoLSE* entregasPorId (NodoLDE* &listaDE) {
    NodoLSE* listaSE = NULL;
    NodoLDE* actual = listaDE;

    while (actual != NULL) {
        NodoLDE* siguiente = actual->sig; // Guardar el siguiente nodo antes de eliminar el actual

        if (actual->info.peso > 500 && actual->info.prioridad <= 3) {
            listaSE_agregar_ordenado(listaSE, actual);
            listaDE_eliminar_ocurrencia(listaDE, actual);
        }
        actual = siguiente;
    }
    return listaSE;
}

void listaDE_eliminar_ocurrencia (NodoLDE* &listaDE, NodoLDE* nodo) {
    if (listaDE == NULL  nodo == NULL) return;

    if (nodo == listaDE) {
        listaDE = nodo->sig;
        if (listaDE != NULL) listaDE->ant = NULL;
    } else {
        if (nodo->ant != NULL) nodo->ant->sig = nodo->sig;
        if (nodo->sig != NULL) nodo->sig->ant = nodo->ant;
    }
    delete nodo;
}

void listaSE_agregar_ordenado (NodoLSE* &listaSE, NodoLDE* nodo) {
    NodoLSE* nuevo = new NodoLSE;
    nuevo->info = nodo->info;
    nuevo->sig = NULL;

    if (listaSE == NULL && listaSE->info.id_paquete >= nuevo->info.id_paquete) {
        nuevo->sig = listaSE;
        listaSE = nuevo;
    } else {
        NodoLSE* actual = listaSE;
        while (actual->sig != NULL && actual->sig->info.id_paquete < nuevo->info.id_paquete) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
}