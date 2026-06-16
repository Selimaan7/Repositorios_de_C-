#include <iostream>
#include <string>

using namespace std;

struct LDE {
    int id_cliente;
    string nombre;
    string direccion;
    int edad;
    float saldo;
    LDE* der;
    LDE* izq;
};


bool EliminarMedio (LDE* &raiz){
    LDE* aux = raiz;
    LDE* aux2 = NULL;
    LDE* aux3 = NULL;
    int contadorbor;
    int contador = 0;
    if (aux == NULL){
        return false;
    }
    while (aux != NULL){
        aux = aux->der;
        contador++;
    }
    contadorbor = contador / 2;
    aux = raiz;
    if (contador == 1){
        raiz = NULL;
        delete aux;
        return true;
    }
    if (contador == 2){
        aux2 = aux->der;
        raiz = NULL;
        delete aux; 
        delete aux2;
        return true;
    }
    if (contador % 2 == 0){
        for (int i = 1; i < contadorbor; i++){
            aux = aux->der;
        }
        aux2 = aux->izq;
        aux3 = aux->der;
        delete aux;
        aux = aux3->der;
        delete aux3;
        aux->izq = aux2;
        aux2->der = aux;
    } else {
            for (int i = 0; i < contadorbor; i++){
            aux = aux->der;
        }
        aux2 = aux->izq;
        aux3 = aux->der;
        delete aux;
        aux2->der = aux3;
        aux3->izq = aux2;
    }
    return true;
}

void AgregarNodo(LDE* &raiz, int id, string nombre, string dir, int edad, float saldo) {
    LDE* nuevo = new LDE();
    nuevo->id_cliente = id;
    nuevo->nombre = nombre;
    nuevo->direccion = dir;
    nuevo->edad = edad;
    nuevo->saldo = saldo;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    
    if (raiz == NULL) {
        raiz = nuevo;
    } else {
        LDE* aux = raiz;
        while (aux->der != NULL) {
            aux = aux->der;
        }
        aux->der = nuevo;
        nuevo->izq = aux;
    }
}

void MostrarLista(LDE* raiz) {
    if (raiz == NULL) {
        cout << "Lista vacía\n";
        return;
    }
    cout << "Lista actual: ";
    LDE* aux = raiz;
    while (aux != NULL) {
        cout << aux->id_cliente << " ";
        aux = aux->der;
    }
    cout << "\n";
}

int main() {
    LDE* lista = NULL;
    
    cout << "=== PRUEBA 1: Lista con 5 nodos ===\n";
    AgregarNodo(lista, 1, "Juan", "Calle 1", 25, 1000);
    AgregarNodo(lista, 2, "Pedro", "Calle 2", 30, 2000);
    AgregarNodo(lista, 3, "Maria", "Calle 3", 28, 1500);
    AgregarNodo(lista, 4, "Ana", "Calle 4", 35, 3000);
    AgregarNodo(lista, 5, "Luis", "Calle 5", 32, 2500);
    MostrarLista(lista);
    cout << "Eliminando nodo del medio...\n";
    if (EliminarMedio(lista)) {
        MostrarLista(lista);
    }
    
    cout << "\n=== PRUEBA 2: Lista con 4 nodos ===\n";
    lista = NULL;
    AgregarNodo(lista, 10, "Cliente1", "Dir1", 20, 500);
    AgregarNodo(lista, 20, "Cliente2", "Dir2", 25, 600);
    AgregarNodo(lista, 30, "Cliente3", "Dir3", 30, 700);
    AgregarNodo(lista, 40, "Cliente4", "Dir4", 35, 800);
    MostrarLista(lista);
    cout << "Eliminando 2 nodos del medio...\n";
    if (EliminarMedio(lista)) {
        MostrarLista(lista);
    }
    
    cout << "\n=== PRUEBA 3: Lista con 1 nodo ===\n";
    lista = NULL;
    AgregarNodo(lista, 100, "SoloUno", "DirUnica", 40, 9999);
    MostrarLista(lista);
    cout << "Eliminando único nodo...\n";
    if (EliminarMedio(lista)) {
        MostrarLista(lista);
    }
    
    cout << "\n=== PRUEBA 4: Lista con 2 nodos ===\n";
    lista = NULL;
    AgregarNodo(lista, 50, "Dos1", "Dir1", 22, 300);
    AgregarNodo(lista, 60, "Dos2", "Dir2", 24, 400);
    MostrarLista(lista);
    cout << "Eliminando ambos nodos...\n";
    if (EliminarMedio(lista)) {
        MostrarLista(lista);
    }
    
    return 0;
}