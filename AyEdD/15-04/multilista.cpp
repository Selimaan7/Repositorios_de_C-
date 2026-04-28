#include <iostream>
#include <cstdlib>
using namespace std;

struct nodo_ls_dato{
    int dato;
    nodo_ls_dato* link;
}typedef nlsd;
struct nodo_ls_fila{
    int indice;
    nlsd* listadatos;
    nodo_ls_fila* sigfila;
} typedef nlsf;


void agregardatofinal (nlsd* &lista, int dato);
void agregardatofinal(nlsf* &lista, int dato);


void agregardatofinal(nlsd* &lista, int dato){
//1) crear  nodo
nlsd* nnodo = new nlsd();
nnodo->dato = dato;
nnodo->link = NULL;
//2) ver si esta vacia
    if (lista == NULL){
        lista = nnodo;
    }else{
    //3) caso general
    nlsd* actual= lista;
        while (actual->link !=NULL){
        actual = actual->link;
        }
    actual->link = nnodo;
    }
}




void agregarfilafinal(nlsf* &lista, int dato){
//1) crear  nodo
nlsf* nnodo = new nlsf();
nnodo->indice = dato;
nnodo->sigfila = NULL;
nnodo->listadatos = NULL;
//2) ver si esta vacia
    if (lista == NULL){
        lista = nnodo;
    }else{
    //3) caso general
    nlsf* actual= lista;
        while (actual->sigfila !=NULL){
        actual = actual->sigfila;
        }
    actual->sigfila = nnodo;
    }
}

void mostrar(nlsf* lista){
    nlsf* actual = lista;
    while (actual != NULL){
        cout << "fila: "<< actual->indice;
        nlsd* dactual = actual->listadatos;
        while (dactual!=NULL){
            cout << dactual -> dato << "->";
            dactual = dactual->link;
        }        
    cout << "NUUL" << endl;
    actual = actual->sigfila;
    } 
}

int main(){
    nlsf* listafila = NULL ;
    for (int i = 0; i<2;i++){
    agregarfilafinal(listafila, i);
    }
    nlsf* aux = listafila;
    while (aux != NULL){
        for (int i = 0;i<2;i++){
            int r=rand()%100+1;
            agregardatofinal (aux->listadatos, r);
        }
        aux = aux->sigfila;
    }
mostrar (listafila);

return 0;
}


//tarea de haceer una funcion modificar un solo dato de toda la multilista










