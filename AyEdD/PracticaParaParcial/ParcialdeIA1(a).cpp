#include <iostream>
#include <string>

using namespace std;

struct automovil{
    string patente;
    string marca;
    int hora;
    bool es_abonado;
    float monto_pago;
};

struct LDE{
    LDE* ant;
    LDE* sig;
    automovil info;
};

struct Ncola{
    LDE* nodo;
    Ncola* link;
};

void encolar (Ncola* &fr, Ncola* &fo, LDE* nodo);

void eliminar_ocurrencia_LDE (LDE* &listaDE, LDE* nodo);


int estacionamiento (LDE* &actual,Ncola* &frente, Ncola*&fondo){
    LDE* aux = actual;
    int contador = 0;
    while (aux !=NULL){
        if (!aux->info.es_abonado && actual->info.hora > 4){
            encolar (fondo,frente,aux);
            eliminar_ocurrencia_LDE (actual, aux);
            contador ++;
        }   
        aux = aux->sig;
    }
}
