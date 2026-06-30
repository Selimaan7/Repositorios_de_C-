#include <iostream>
#include <string>
using namespace std;

struct paciente{
    int id_paciente;
    string apellido;
    int codigo_sintoma;
    float costo_consulta;
    bool obra_social;
};

struct LDE{
    LDE* izq;
    LDE* der;
    paciente info;
};

void eliminarocurrenciaDE (LDE* &listaDE, LDE* nnodo){
    if (listaDE == NULL) return;

    LDE* aux = listaDE;

    if (listaDE == nnodo){
        listaDE = listaDE->der;
        delete aux;
        if (listaDE != NULL) listaDE->izq = NULL;
        return;
    }
    
    LDE* ant = NULL;
    LDE* sig = NULL;
    while (aux !=NULL){
        sig = aux->der;
        ant = aux->izq;
        if (aux == nnodo){
            ant->der = sig;
            if (sig != NULL) sig->izq = ant;
            delete aux;
        }
        aux = sig;
    }
}

int eliminarduplicados (LDE* &listaDE) {
    if (listaDE == NULL) return 0;

    LDE* aux = listaDE->der;
    LDE* auxant = listaDE;
    LDE* auxsig = NULL;

    int nodoselim = 0;
    while (aux != NULL){
        
        while (aux != NULL && aux->info.id_paciente == auxant->info.id_paciente){
            auxsig = aux->der;
            auxant->info.costo_consulta += aux->info.costo_consulta;
            eliminarocurrenciaDE(listaDE, aux);
            aux = auxsig;
            nodoselim ++;

        }
        auxant = aux;
        aux = aux->der;
    }
    return nodoselim;
}