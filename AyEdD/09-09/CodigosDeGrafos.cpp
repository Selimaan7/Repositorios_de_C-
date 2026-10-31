#include <iostream>
using namespace std;

struct nodo_arco {
    int id_arco;
    struct nodo_grafo* destino;
    nodo_arco* link;
};
typedef nodo_arco NArco;

struct nodo_grafo {
    int id_nodo;
    nodo_arco* lista_arco;
    nodo_grafo* link;
};
typedef nodo_grafo NGrafo;

void grafo_agregar_nodo(NGrafo* &g, int id_n){
    NGrafo* nuevo_nodo = new NGrafo;
    nuevo_nodo->id_nodo = id_n;
    nuevo_nodo->lista_arco = nullptr;
    nuevo_nodo->link = g;
    g = nuevo_nodo;
}

void grafo_agregar_arco(NGrafo* g, int id_nodo_origen, int id_nodo_destino, int id_arco) {
    NGrafo* nodo_origen = g;
    while (nodo_origen != nullptr && nodo_origen->id_nodo != id_nodo_origen) {
        nodo_origen = nodo_origen->link;
    }
    if (nodo_origen == nullptr) {
        cout << "Nodo origen no encontrado." << endl;
        return;
    }

    NGrafo* nodo_destino = g;
    while (nodo_destino != nullptr && nodo_destino->id_nodo != id_nodo_destino) {
        nodo_destino = nodo_destino->link;
    }
    if (nodo_destino == nullptr) {
        cout << "Nodo destino no encontrado." << endl;
        return;
    }

    NArco* nuevo_arco = new NArco;
    nuevo_arco->id_arco = id_arco;
    nuevo_arco->destino = nodo_destino;
    nuevo_arco->link = nodo_origen->lista_arco;
    nodo_origen->lista_arco = nuevo_arco;
}

bool grafo_eliminar_arco(NGrafo* lista_nodos, int id_nodo_origen, int id_nodo_destino) {
    NGrafo* nodo_origen = lista_nodos;
    while (nodo_origen != nullptr && nodo_origen->id_nodo != id_nodo_origen) {
        nodo_origen = nodo_origen->link;
    }
    if (nodo_origen == nullptr) {
        cout << "Nodo origen no encontrado." << endl;
        return false;
    }

    NArco* arco_actual = nodo_origen->lista_arco;
    NArco* arco_anterior = nullptr;
    while (arco_actual != nullptr && arco_actual->destino->id_nodo != id_nodo_destino) {
        arco_anterior = arco_actual;
        arco_actual = arco_actual->link;
    }
    if (arco_actual == nullptr) {
        cout << "Arco no encontrado." << endl;
        return false;
    }

    if (arco_anterior == nullptr) {
        nodo_origen->lista_arco = arco_actual->link;
    } else {
        arco_anterior->link = arco_actual->link;
    }
    delete arco_actual;
    return true; // Dijo el profe que dejamos como standard usar bool para la baja
}

int grafo_cantidad_arcos(NGrafo* lista_nodos) {
    int cantidad = 0;
    NGrafo* nodo_actual = lista_nodos;
    while (nodo_actual != nullptr) {
        NArco* arco_actual = nodo_actual->lista_arco;
        while (arco_actual != nullptr) {
            cantidad++;
            arco_actual = arco_actual->link;
        }
        nodo_actual = nodo_actual->link;
    }
    return cantidad;
}

void grafo_conjunto_derecho(NGrafo* lista_nodos, int id_nodo) {
    NGrafo* nodo = lista_nodos;
    while (nodo != nullptr && nodo->id_nodo != id_nodo) {
        nodo = nodo->link;
    }
    if (nodo == nullptr) {
        cout << "Nodo no encontrado." << endl;
        return;
    }
    NArco* arco = nodo->lista_arco;
    while (arco != nullptr) {
        cout << "Arco: " << arco->id_arco << " -> Nodo: " << arco->destino->id_nodo << endl;
        arco = arco->link;
    }
}

void grafo_conjunto_izquierdo(NGrafo* lista_nodos, int id_nodo) {
    NGrafo* nodo = lista_nodos;
    while (nodo != nullptr) {
        NArco* arco = nodo->lista_arco;
        while (arco != nullptr) {
            if (arco->destino->id_nodo == id_nodo) {
                cout << "Nodo: " << nodo->id_nodo << endl;
            }
            arco = arco->link;
        }
        nodo = nodo->link;
    }
}

void maximal(NGrafo* lista_nodos){
    NGrafo* nodo = lista_nodos;
    while (nodo != nullptr) {
        if (nodo->lista_arco == nullptr) {
            cout << "Nodo maximal: " << nodo->id_nodo << endl;
        }
        nodo = nodo->link;
    }
}

void minimal(NGrafo* lista_nodos){
    NGrafo* nodo = lista_nodos;
    while (nodo != nullptr) {
        bool es_minimal = true;
        NGrafo* nodo_aux = lista_nodos;
        while (nodo_aux != nullptr) {
            NArco* arco = nodo_aux->lista_arco;
            while (arco != nullptr) {
                if (arco->destino == nodo) {
                    es_minimal = false;
                    break;
                }
                arco = arco->link;
            }
            if (!es_minimal) break;
            nodo_aux = nodo_aux->link;
        }
        if (es_minimal) {
            cout << "Nodo minimal: " << nodo->id_nodo << endl;
        }
        nodo = nodo->link;
    }
}


void grafo_eliminar_nodo (NGrafo* lista_nodos, int id_nodo) {
    NGrafo* ant = NULL;
    NGrafo* act = lista_nodos;
    
    //PASO 1
    while ((act != NULL) && act->id_nodo != id_nodo) {
        ant = act;
        act = act->link;
    }
    if (act == NULL){
        cout << "Nodo no encontrado" << endl;
        return;
    }

    // PASO 2
    NGrafo* nodo = lista_nodos;
    while(nodo != NULL){
        NArco* arco_ant = NULL;
        NArco* arco_act = nodo->lista_arco;
        while(arco_act != NULL){
            if (arco_act->destino == act){
                NArco* BORRAR = arco_act;
                arco_act = arco_act->link;
                if (arco_ant == NULL){
                    nodo->lista_arco = arco_act;
                }else {
                    arco_ant->link = arco_act;
                }
                delete BORRAR;
            }else {
                arco_ant = arco_act;
                arco_act = arco_act->link;  
            }
        }
        nodo = nodo->link;
    }

    // PASO 3
    while (act->lista_arco != NULL){
        NArco* BORRAR = act->lista_arco;
        act->lista_arco = act->lista_arco->link;
        delete BORRAR;  
    }
    if (ant == NULL){
        lista_nodos = act->link;
    } else{
        ant->link = act->link;
    }
    delete act;
}

int main() {
    NGrafo* lista_n = nullptr;

    // Agregar nodos al grafo
    grafo_agregar_nodo(lista_n, 0);
    grafo_agregar_nodo(lista_n, 1);
    grafo_agregar_nodo(lista_n, 2);
    grafo_agregar_nodo(lista_n, 3);
    grafo_agregar_nodo(lista_n, 4);
    grafo_agregar_nodo(lista_n, 5);

    // Agregar arcos al grafo
    grafo_agregar_arco(lista_n, 1, 2, 1);
    grafo_agregar_arco(lista_n, 1, 3, 2);
    grafo_agregar_arco(lista_n, 3, 2, 3);
    grafo_agregar_arco(lista_n, 3, 3, 4);
    grafo_agregar_arco(lista_n, 3, 0, 5);
    grafo_agregar_arco(lista_n, 3, 4, 6);
    grafo_agregar_arco(lista_n, 4, 5, 7);

    // Mostrar cantidad de arcos
    cout << "Cantidad de arcos: " << grafo_cantidad_arcos(lista_n) << endl;

    // Mostrar conjunto derecho del nodo 0
    cout << "Conjunto derecho del nodo 0:" << endl;
    grafo_conjunto_derecho(lista_n, 0);

    // Mostrar conjunto izquierdo del nodo 4
    cout << "Conjunto izquierdo del nodo 4:" << endl;
    grafo_conjunto_izquierdo(lista_n, 4);

    // Mostrar nodos maximales
    cout << "Nodos maximales:" << endl;
    maximal(lista_n);

    // Mostrar nodos minimales
    cout << "Nodos minimales:" << endl;
    minimal(lista_n);
}