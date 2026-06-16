#include <iostream>

using namespace std;

struct NABinario {
    int dato;
    NABinario* izq;
    NABinario* der;
};

struct Ncola {
    NABinario* nodo;
    int nivel;
    Ncola* link;
};


void encolar (Ncola* &fr, Ncola* &fo, NABinario* arbol, int nivel);
void desencolar (Ncola* &fr, Ncola* &fo, NABinario* &arbol, int &nivel);
bool ColaVacia (Ncola* fr);

int Cuenta_Muestra_Por_Nivel (NABinario* arbol, int nivel){
    if (arbol == NULL) return -1;
    int cont = 0;
    Ncola* fr = NULL;
    Ncola* fo = NULL;
    NABinario* aux = arbol;
    int auxnivel = 0;

    encolar (fr, fo, aux, auxnivel);

    while (!ColaVacia){
        desencolar (fr, fo, aux, auxnivel);
        if (auxnivel == nivel){
            cont ++;
            cout << aux->dato << " ";
        }
        if (aux->izq != NULL) encolar (fr, fo, aux->izq, auxnivel + 1);
        if (aux->der != NULL) encolar (fr, fo, aux->der, auxnivel + 1);
    }
}