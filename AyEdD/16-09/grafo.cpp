#include <iostream>

using namespace std;

struct nodo_grafo{
    int id_dato;
    nodo_arco* lista_arco;
    nodo_grafo* link;
};
typedef nodo_grafo NGrafo;

struct nodo_arco{
    int id_arco;
    nodo_grafo* destino;
    nodo_grafo* inicio;
};
typedef nodo_arco NArco
