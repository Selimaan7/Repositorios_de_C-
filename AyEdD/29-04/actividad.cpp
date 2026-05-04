/*ACTIVIDAD
Realice uan funcion que busque en una LDE todos los codigos
de productos que se encuentran en una pila*/
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
struct ListaDoblementeEnlazada{
    ListaDoblementeEnlazada * izq;
    ListaDoblementeEnlazada * der;
    string codigol;
}typedef LDE;

struct pila{
    string codigop;
    pila* link;
};
void agregarlistaultimo (LDE* &topelista, string cod){
    LDE* nnodo = new LDE();
    nnodo->codigol = cod;
    if (topelista == NULL){
        topelista = nnodo;
        nnodo->izq = NULL;
        nnodo->der = NULL;
    }else {
        LDE* aux = topelista;
        while (aux->der !=NULL){
            aux = aux->der;
        }    
        aux->der = nnodo;
        nnodo->izq = aux;
        nnodo->der = NULL;
    }
}
void agregarpila(pila* &topepila, string cod){
    pila* nnodo = new pila();
    nnodo->codigop = cod;
    nnodo->link = topepila;
    topepila = nnodo;
}

void quitarpila (pila* &topepila){
    if (topepila == NULL){
        return;
    }
    pila * aux = topepila;
    topepila = topepila->link;
    delete aux;
}

bool buscacodigo (LDE* &topelista, string cod){
    LDE* aux =topelista;
    while (aux == NULL){
        aux = aux->der;

    if (aux->codigol == cod) return true;
    }
return false;
}

/*int comprobarpilaylista(LDE* &topelista, pila* &topepila){
    while (topepila !=NULL){
        buscacodigo (topelista, topepila->codigop);
        quitarpila (topepila);
    }


}*/

/*int sacapila (pila *&p){
    pila *aux = p;
    sacapila =p->codigop;
    p = p->link;
    delete aux;
}*/
int main (){
    LDE *topelista = NULL;
    pila *topepila = NULL;
    return 0;
    
    
    
    
    
    
    while (topepila !=NULL){
        bool codsi;
        codsi = buscacodigo (topelista, topepila->codigop);
        if (codsi){
            cout << topepila->codigop;
        }
        quitarpila (topepila);
    }


}