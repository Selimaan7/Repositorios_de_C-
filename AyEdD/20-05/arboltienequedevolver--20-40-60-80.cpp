#include <iostream>

using namespace std;

struct arbol {
    arbol* izq;
    arbol* der;
    int dato;
} typedef na;

struct Pila{
    Pila* link;
    arbol* num;
};
void pila_agregar ();

int main() {
    na* raiz;
    int dato;
    Pila* topepila;
    AltaIterativo (raiz, 50);
    AltaIterativo (raiz, 30);
    AltaIterativo (raiz, 20);
    AltaIterativo (raiz, 40);
    AltaIterativo (raiz, 70);
    AltaIterativo (raiz, 60);
    AltaIterativo (raiz, 80);

    BuscarIterativo ( raiz, dato);
    return 0;
}

na* BuscarIterativo (na* raiz, int ndato){
na* actual = raiz;
na* papa = NULL;
while ( actual != NULL){
    //caso 1
    if (actual->dato == ndato){
        cout << "no tiene papa";
        return actual;
    }
    //caso 2 >
    papa = actual;
    if (actual->dato > ndato){
        actual = actual->izq;
    }else { //caso 3 <
        actual = actual->der;
    }
}// while
//Caso 4 (NO ENCONTRAR)
return NULL;
}

void buscar_nodo_padre (arbol* arbo, int clave, arbol* &nodo, arbol *&padre){
    nodo = arbo;
    padre = NULL;
    while (nodo !=  NULL && nodo->dato != clave){
        padre = nodo;
        if (clave <nodo->dato){
            nodo = nodo->izq;
        }else{
            nodo = nodo->der;
        }
    }

}

void AltaIterativo (na* &raiz, int ndato){
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



void mostrar_hojas_f(arbol* arbo){
    if( arbo == NULL){
        return;
    }
    pilae* pila = NULL;
    arbol* aux;
    pila_agregar(pila,arbol);
    while (!pila_vacia(pila)){
    aux = pila_sacar(pila);
    if  (aux->izq == NULL && aux->der == NULL){
        cout << aux->dato;
    }                          // la pila guarda punteros de nodos
    if (aux->der != NULL){
    pila_agregar(pila, aux->der);
    }
    if (aux->izq != NULL){
        pila_agregar(pila,aux->izq);
    }
}
}

