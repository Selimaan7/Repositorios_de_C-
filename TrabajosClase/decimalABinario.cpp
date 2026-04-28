#include <iostream>

using namespace std;


struct Nodo_Pila{
    Nodo_Pila* link;
    int dato;
}typedef Npila;

void AgregarPila(Npila* &tope, int data){
    Npila* Nnodo = new Npila();
    Nnodo->dato = data%2;
    Nnodo->link = tope;
    tope = Nnodo;
}
int mostrardato (Npila* &tope){
    if (tope !=NULL)
    {
        int datoaux = tope->dato;
        Npila* aux = tope;
        tope = tope->link;
        delete aux;
        return datoaux;
    }
    return -1;

}
int main() {
    Npila* tope = NULL;
    int decimal= 0;
    if (decimal == 0){
        AgregarPila(tope, decimal);
    }else{
    for (int i = decimal; i > 0; i /= 2) {
        AgregarPila(tope, i);
    }
    }
    while (tope != NULL){
    cout << mostrardato(tope);
    }
    return 0;
}
