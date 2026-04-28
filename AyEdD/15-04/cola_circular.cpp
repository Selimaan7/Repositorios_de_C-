//cola circular


#include <iostream>

using namespace std;
#define max 8

struct cola_circular{
    int cola[max];
    int tamanio;
    int frente;
    int fondo;
    bool llena;
    bool vacia;
    int cantidad_elementos;
}typedef cc;

//frente: referencia al primer elementos de la cola circular, aquel que sera devuelto. Esto es solos calido si la cola no  esta vacia
//fondo: referencia a la proxima pocision a ser ocupada en ela proxima alta
//llena: true si la cola esta llena , false en caso contrario
//vacia: true si la cola esta vacia de no ser asi no esta vacia

int main(){
    cc cc_ej;
    cc_ej.tamanio = max;
    cc_ej.frente = 0;
    cc_ej.fondo = 0;
    cc_ej.vacia = true;
    cc_ej.llena = false;
    cc_ej.cantidad_elementos = 0;

    return 0;
}

int alta (cc &cc, int dato){
    cc.vacia = false;
    if (cc.llena){
        return 0;
    }
    cc.cola[cc.fondo] = dato;
    cc.cantidad_elementos ++;
    if (cc.fondo == cc.tamanio - 1){
        cc.fondo = 0;
    } else {
        cc.fondo ++;
    }
    if (cc.frente == cc.fondo){
        cc.llena = true;
    }    
    return 0;
}



