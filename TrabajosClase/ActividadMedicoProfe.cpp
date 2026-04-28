#include <iostream>
using namespace std;

struct nodo_cola{
    nodo_cola* link;
    int dni;
}typedef Ncola;

void agregar_c(Ncola* &frente, Ncola* &fondo, int dni){
    Ncola* Nnodo = new Ncola();
    Nnodo->dni = dni;
    Nnodo->link = NULL;
    if (frente == NULL){
        frente = Nnodo;
        fondo = Nnodo;
    } else {
        fondo->link = Nnodo;
        fondo = Nnodo;
    }
}

int elimino(Ncola* &frente, Ncola* &fin){
    if (frente != NULL){
        int dato = frente->dni;
        Ncola* aux = frente;
        frente = frente->link;
        if (frente == NULL){
            fin = NULL;
        }
        delete aux;
        return dato;
    } else {
        cout << "Cola vacía" << endl;
        return -1;
    }
}

int main(){
Ncola *frente = NULL;
Ncola *fin = NULL;   
int dato;


}