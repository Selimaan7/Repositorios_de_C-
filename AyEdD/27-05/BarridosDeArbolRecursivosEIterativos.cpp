#include <iostream>

using namespace std;

struct NABinario{
    NABinario* izq;
    NABinario* der;
    int dato;
};

struct Nodo_Pila {
    Nodo_Pila* link;
    NABinario* dato;
};
typedef Nodo_Pila NPila;

struct Nodo_Cola{
    NABinario* dato;
    Nodo_Cola* FR;
    Nodo_Cola* FO;
}; typedef Nodo_Cola Ncola;

void inicializar_pila(NPila*& pila) {
    pila = nullptr;
}

bool PILA_VACIA(NPila* pila) {
    return pila == nullptr;
}

void APILAR(NPila*& pila, NABinario* valor) {
    NPila* nuevo = new NPila{pila, valor};
    pila = nuevo;
}

NABinario* DESAPILAR(NPila*& pila) {
    if (pila == nullptr) return nullptr;
    NPila* nodo = pila;
    NABinario* valor = nodo->dato;
    pila = nodo->link;
    delete nodo;
    return valor;
}

void inicializar_cola(Ncola*& cola){
    cola = nullptr;
}

bool COLA_VACIA(Ncola* cola){
    return cola == nullptr;
}

void ENCOLAR(Ncola*& cola, NABinario* valor){
    Ncola* nuevo = new Ncola{valor, nullptr, nullptr};
    if (cola == nullptr){
        cola = nuevo;
        return;
    }
    Ncola* cur = cola;
    while (cur->FO != nullptr) cur = cur->FO;
    cur->FO = nuevo;
}

NABinario* DESENCOLAR(Ncola*& cola){
    if (cola == nullptr) return nullptr;
    Ncola* nodo = cola;
    NABinario* val = nodo->dato;
    cola = nodo->FO;
    delete nodo;
    return val;
}

void PreOrden_Recorrido (NABinario* actual){
    if (actual == NULL) return;

    cout << actual->dato << "";

    PreOrden_Recorrido(actual->izq);
    PreOrden_Recorrido(actual->der);
}

void InOrden_Recorrido (NABinario* actual){
    if (actual == NULL) return;

    InOrden_Recorrido (actual->izq);
    cout << actual->dato;
    InOrden_Recorrido (actual->der);
}

void PostOrden_Recorrido (NABinario* actual){
    if (actual == NULL) return;

    PostOrden_Recorrido(actual->izq);
    PostOrden_Recorrido(actual->der);
    cout << actual->dato;
}

void PreOrden_Recorrido_Iterativo (NABinario* actual){
    if (actual == NULL) return;
    NPila* PILA;
    inicializar_pila(PILA);
    APILAR(PILA, actual);

    while (!PILA_VACIA(PILA)){
        NABinario* aux = DESAPILAR(PILA);
        cout << aux->dato << " ";
        if (aux->der != NULL){
            APILAR(PILA, aux->der);
        }
        if (aux->izq != NULL){
            APILAR(PILA, aux->izq);
        }
    }
}

void InOrden_Recorrido_Iterativo (NABinario* actual){
    if (actual == NULL) return;
    NPila* PILA;
    inicializar_pila (PILA);
    NABinario* aux = actual;
    while (aux !=NULL || !PILA_VACIA (PILA)){
        //PASO 1 -> FULL IZQ

        while (aux != NULL){
            APILAR(PILA,aux);
            aux=aux->izq;
        }
        aux = DESAPILAR(PILA);
        cout << aux->dato << " ";
        aux = aux->der;
    }
}

void PostOrden_Recorrido_Iterativo (NABinario* actual){
    if (actual == NULL) return;
    NPila* P1;
    NPila* P2;
    inicializar_pila(P1);
    inicializar_pila(P2);
    APILAR(P1, actual);
    while (!PILA_VACIA(P1)){
        NABinario* aux = DESAPILAR(P1);
        APILAR(P2, aux);
        if (aux->izq != NULL){
            APILAR (P1,aux->izq);
        }
        if (aux->der !=NULL){
            APILAR (P1,aux->der);
        }
    }

    while (!PILA_VACIA(P2)){
        NABinario* aux = DESAPILAR(P2);
        cout << aux->dato << " ";
    }
}

void PORNIVELES (NABinario* actual){
    if (actual == NULL){
        return;
    }
    Ncola* C;
    inicializar_cola(C);
    ENCOLAR(C,actual);
    while(!COLA_VACIA(C)){
        NABinario* aux = DESENCOLAR(C);
        cout << aux->dato<< " ";
        if (aux->izq !=NULL){
            ENCOLAR (C,aux->izq);
        }
        if (aux->der != NULL){
            ENCOLAR(C,aux->der);
        }
    }
}

void AltaIterativo (NABinario* raiz, int ndato){
    //paso 1 crear el nodo
    NABinario* nuevo = new NABinario();
    nuevo->dato = ndato;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    //Caso Arbol Vacio
    if (raiz == NULL){
        raiz = nuevo;
        return;
    }
    //Caso No Vacio
    NABinario* actual = raiz;
    NABinario* padre = NULL;
    while (actual !=NULL){
        if (actual->dato == ndato){
            delete nuevo;
            return;
        }
        padre = actual;
        if (actual->dato > ndato){
            actual = actual->izq;
        } else{
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

NABinario* crear_nodo (int dato){
    NABinario* nuevo = new NABinario();
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}
void insertar_recursivo (NABinario* &raiz, int dato) {
    if (raiz == NULL){
        raiz = crear_nodo(dato);
        return;
    }
    if (dato < raiz ->dato) {
        insertar_recursivo(raiz->izq,dato);
    }else{
        insertar_recursivo(raiz->der,dato);
    }
}