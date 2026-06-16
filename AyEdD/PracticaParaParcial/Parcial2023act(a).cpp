#include <iostream>
#include <string>

using namespace std;

struct LDE {
    LDE* izq;
    LDE* der;
    string NYA, NYAT;
    int edad;
    float distancia;
    int telefono;
    string salita; 
};

struct Ncola{
    LDE* nodo;
    Ncola* link;
};

void Encolar (Ncola* &negra, LDE* nodo);

void PonerEnCola (LDE* &raiz, Ncola* &verde, Ncola* &negra){
    LDE* aux = raiz;
    LDE* auxant; 
    LDE* auxsig;
    while (aux->der !=NULL){
        if (aux->edad = 3 && aux->distancia > 2){
            Encolar (verde, aux);
        } else if (aux->edad >= 4 && aux->edad < 6 && aux->distancia > 2){
            Encolar (negra, aux);
            auxant = aux->izq;
            auxsig = aux->der;
            delete aux;
            auxant->der = auxsig;
            auxsig->izq = auxant;
        }
    }
}

void eliminarnodo (LDE* &raiz, LDE* nodo){
    LDE* aux = raiz;
    LDE* auxant;
    LDE* auxsig;
    if (raiz == nodo){
        raiz = raiz->der;
        delete aux;
        raiz->izq = NULL;
    }
    while (aux != nodo) {
        aux = aux->der; 
    }
    auxant=aux->izq;
    auxsig = aux->der;
    delete aux;
    auxant->der = auxsig;
    if (auxsig !=NULL) auxsig->izq = auxant;
}