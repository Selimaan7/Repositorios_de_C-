#include <iostream>
#include <string>

using namespace std;

struct NABinario{
    NABinario* der;
    NABinario* izq;
    int clave;
    string texto;
};

struct Ncola{
    NABinario* nodo;
    Ncola* link;
};

void encolar (Ncola* &fr, Ncola* &fo, NABinario* nodo, int nivel);
void desencolar (Ncola* &fr, Ncola* &fo, NABinario* &nodo, int &nivel);
bool cola_vacia (Ncola* frente);

float promedio_de_nodos_mas_que_x (NABinario* actual,int x){
    if (actual == NULL) return 0;
    Ncola* fr = NULL;
    Ncola* fo = NULL;
    NABinario* aux = actual;
    float suma = 0;
    float nodos = 0;
    bool encontrado = false;
    int auxnivel = 0;

    encolar (fr, fo, aux, auxnivel);
    
    while (!cola_vacia(fr)){
        
        desencolar (fr, fo, aux, auxnivel);

        if (auxnivel > x){
        suma +=aux->clave;
        nodos ++;
        }
        
        if (aux->izq != NULL) encolar (fr, fo, aux->izq, auxnivel + 1);
        if (aux->der != NULL) encolar (fr, fo, aux->der, auxnivel + 1);
    }

    if (nodos == 0) return 0; 
    return suma / nodos;
}