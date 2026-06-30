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

void encolar (Ncola* &fr, Ncola* &fo,NABinario* nodo, int nivel);
void desencolar (Ncola* &fr, Ncola* &fo, NABinario* &nodo, int &nivel);
bool ColaVacia (Ncola* frente);

void MuestraPorNiveles (NABinario* arbol){
    if (arbol == NULL) return;
    Ncola* fr = NULL;
    Ncola* fo = NULL;
    NABinario* aux = arbol;
    int NivelActual = 0, NivelAnterior = -1;

    encolar(fr,fo,aux,NivelActual);
    while (!ColaVacia){
        desencolar (fr,fo,aux,NivelActual);
        if (NivelActual != NivelAnterior){
            if (NivelAnterior != -1) cout << endl;
            cout << "Nivel " << NivelActual << ": ";
            NivelAnterior= NivelActual;
        }
        
        cout << aux->dato << " ";
        
        if (aux->izq != NULL) encolar (fr, fo, aux->izq, NivelActual + 1);

        if (aux->der != NULL) encolar (fr, fo, aux->der, NivelActual + 1);
    }
}