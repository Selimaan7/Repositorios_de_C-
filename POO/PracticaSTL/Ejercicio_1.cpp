#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Nodo_Cola{
    T& dato;
    int prioridad = 0;
    Nodo_Cola* link;
};



template <typename T>
class Cola_Prioridad {
    private:
        Nodo_Cola* frente;
        Nodo_Cola* fondo;
    
    public:
        Cola_Prioridad(){
            frente = NULL;
        }

        void agregar(T& dato, int prioridad){
            Nodo_Cola* nodo = new Nodo_Cola();
            nodo->dato = dato;
            nodo->priridad = prioridad;
            nodo->link = NULL;
            if (frente == NULL || frente->prioridad < nodo->prioridad){
                nodo->link = frente
                frente = nodo;
                return;
            }

            Nodo_Cola* actual = frente;
            Nodo_Cola* anterior = frente;

            while (actual != NULL && actual->prioridad >= nodo->prioridad){
                anterior = actual;
                actual == actual->link;

            }

            if (actual == NULL){
                anterior->link = nodo;
            } else{
                anterior->link = nodo;
                nodo->link = actual;
            }
        }


        bool empty(){
            return frente == NULL;
        }

        T& sacar(){
            if (empty()) return;
            Nodo_Cola* borrar = frente;
            T& dato = borrar->dato;
            frente = frente->link;
            delete borrar;
            return dato;
        }

};