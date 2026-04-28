#include <iostream>
#include <string.h>
using namespace std;

struct nodo_pila {
    nodo_pila* link; // puntero a siguiente nodo
    int dato;  // dato a almacenar
} typedef NPila;

void AgregarPila(NPila* &tope, int data){
    NPila* Nnodo = new NPila(); // crear un nuevo nodo
    Nnodo->dato = data; // asignar el dato al nuevo nodo
    Nnodo->link = tope; // el nuevo nodo apunta al nodo que actualmente es el tope
    tope = Nnodo; // el nuevo nodo se convierte en el nuevo tope de la pila
}

int mostrardato(NPila* &tope){  // pasa por referencia para modificar tope
    if (tope != NULL) {
        int datoaux = tope->dato;  // guarda el dato antes de eliminar
        NPila* aux = tope;     // guarda el nodo actual
        tope = tope->link;      // mueve tope al siguiente
        delete aux;            // libera memoria
        return datoaux;            // devuelve el dato
    }
    return -1;  // indica pila vacía
}

void QuitarDato(NPila* &tope){  // pasa por referencia para modificar tope
    if (tope != NULL) {
        int datoaux = tope->dato;  // guarda el dato antes de eliminar
        NPila* aux = tope;     // guarda el nodo actual
        tope = tope->link;      // mueve tope al siguiente
        delete aux;   
    }    // libera memoria
}
int main (){
NPila* tope;
tope = NULL;
int dato;
      // cout << tope << endl;  // muestra a dónde apunta tope (NULL inicialmente)


for (int i = 0; i <= 5; i++) {;
    AgregarPila(tope, i);
}

for (int i = 0; i <=5; i++) {  // cambió a 6 porque agregaste 6 elementos
    cout << mostrardato(tope) << endl;  // llama correctamente a la función
}



/*cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;
cout << mostrardato(tope) << endl;*/  // muestra los datos de la pila hasta que esté vacía

// cout << tope << endl;  // muestra a dónde apunta tope después de vaciar la pila (debería ser NULL)




}


