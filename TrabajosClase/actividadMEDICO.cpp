#include <iostream>
using namespace std;
struct nodo_cola{
    nodo_cola* link;
    int dato;
}typedef Ncola;

void AgregarCola (Ncola* &frente, Ncola* &fondo, int data){
    Ncola* Nnodo = new Ncola();
    Nnodo->dato = data;
    Nnodo->link = NULL;
    if (frente == NULL){
        frente = Nnodo;
        fondo = Nnodo;
    } else {
        fondo->link = Nnodo;
        fondo = Nnodo;
    }
}
int obtenerDato (Ncola* &frente, Ncola* &fondo){
    if (frente !=NULL){
        int datoaux = frente->dato;
        Ncola* aux= frente;
        frente = frente->link;
        delete aux;
        return datoaux;

    } else{
        cout << "Cola vacía" << endl;
        return -1;
    }



}




int main(){
Ncola *frente = NULL;
Ncola *fondo = NULL;
int dato;





}