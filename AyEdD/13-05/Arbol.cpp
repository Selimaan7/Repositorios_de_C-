#include <iostream>

using namespace std;

struct nodoarbol {
    int dato;
    nodoarbol* izq;
    nodoarbol* der;
} typedef na;

int main() {




    return 0;
}

na* BuscarIterativo (na* raiz, int ndato){
na* actual = raiz;
while ( actual != NULL){
    //caso 1
    if (actual->dato == ndato){
        return actual;
    }
    //caso 2 >
    if (actual->dato > ndato){
        actual = actual->izq;
    }else { //caso 3 <
        actual = actual->der;
    }
}// while
//Caso 4 (NO ENCONTRAR)
return NULL;
}

void AltaIterativo (na* raiz, int ndato){
    //paso 1 crear el nodo
    na* nuevo = new na();
    nuevo->dato = ndato;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    //Caso Arbol Vacio
    if (raiz == NULL){
        raiz = nuevo;
        return;
    }
    //Caso No Vacio
    na* actual = raiz;
    na* padre = NULL;
    while (actual !=NULL){
        if (actual->dato == ndato){
            delete nuevo;
            return;
        }
        padre = actual;
        if (actual->dato > ndato){
            actual = actual->izq;
        }else{
            actual = actual->der;
        }
    }
    //Paso Enlace
    if (padre ->dato > ndato){
        padre->izq = nuevo;
    } else{
        padre->der = nuevo;
    }
}   