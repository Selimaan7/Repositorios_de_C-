#include <iostream>
using namespace std;
struct nodo_cola {
    nodo_cola* link; // va a apuntar al siguiente dato que ponga en la cola
    int dato; // lugar donde va a estar el dato que agrege al nodo
} typedef Ncola;

void AgregarCola (Ncola* &frente, Ncola* &fondo, int data) {
    Ncola* Nnodo = new Ncola(); // crear un nuevo nodo
    Nnodo->dato = data; // asignar el dato al nuevo nodo
    Nnodo->link = NULL; // Siempre el nuevo nodo va a tener que apuntar a NULL ya que va a ser el ultimo que se añadio
    if (frente == NULL) {
        frente = Nnodo;
        fondo = Nnodo;
    } else {
        fondo->link = Nnodo; // el nodo que actualmente es el fondo apunta al nuevo nodo
        fondo = Nnodo; // el nuevo nodo se convierte en el nuevo fondo de la cola
    }
}


int obtenerDato(Ncola* &frente, Ncola* &fondo) {
    if (frente != NULL) {
        int datoaux = frente->dato; // guarda el dato antes de eliminar
        Ncola* aux = frente; // guarda el nodo actual
        frente = frente->link; // mueve frente al siguiente
        delete aux; // libera memoria
        if (frente == NULL) { // Si después de eliminar el nodo, la cola queda vacía, también se debe actualizar fondo a NULL
            fondo = NULL; // para que el fondo no quede apuntando a un nodo que ya no existe, lo que podría causar errores si se intenta agregar un nuevo nodo después de vaciar la cola
        }
        return datoaux; // imprime el dato
    }
    
    cout << "Cola vacía" << endl; // indica cola vacía
return -1; // Devuelve un valor que indique que la cola está vacía
}



int main(){
    Ncola* frente = NULL;  // puntero que apunta a NULL, indicando que la cola está vacía
    Ncola* fondo = NULL;   // puntero que apunta a NULL, indicando que la cola está vacía
    int dato; // variable para almacenar el dato que se va a agregar a la cola
    for(int i = 0; i< 11; i++) {
        AgregarCola(frente, fondo, i); // Llamada a la función para agregar datos a la cola
    }
    for(int i = 0; i< 6; i++) {
    cout << obtenerDato(frente, fondo) << endl; // Llamada a la función para obtener un dato de la cola vacía, lo que debería imprimir "Cola vacíar )
    }
    cout << "eso fueron la mitad de los datos que se agregaron a la cola" << endl;
    cout << "\n" << endl;
    cout << "Ahora se van a mostrar los datos restantes en la cola" << endl;
    for(int i = 0; i< 5; i++) {
    cout << obtenerDato(frente, fondo) << endl; // Llamada a la función para obtener un dato de la cola vacía, lo que debería imprimir "Cola vacíar )
    }
}