#include <iostream>
#include <string>
#include <limits>
#define MAX_ALUMNOS 3
using namespace std;

struct pila_alumno {
    int DNI;
    string nya;
    int edad;
    pila_alumno* link;
} typedef alumnop;

struct lista_alumno{
    int DNI;
    string nya;
    int edad;
    lista_alumno* link;
}typedef alumnol;

void agregarpila (alumnop* &topepila, int dnip, int edadp, string nyap){
    alumnop* nnodo = new alumnop();
    nnodo->DNI = dnip;
    nnodo->nya = nyap;
    nnodo->edad = edadp;
    nnodo->link = topepila;
    topepila = nnodo;
}

bool quitarpila (alumnop* &topepila){
    if (topepila==NULL){
    return false;
    }
    alumnop* aux = topepila;
    topepila = aux->link;
    delete aux;
    return true;
}

void agregarlistaultimo (alumnol* &topelista, int dnil, int edadl, string nyal){
    alumnol* nnodo = new alumnol();
    alumnol* aux = topelista;
    nnodo->DNI = dnil;
    nnodo->nya = nyal;
    nnodo->edad = edadl;
    nnodo->link = NULL;
    if (topelista == NULL){
        topelista = nnodo;
    }else{
        while (aux->link != NULL){
            aux = aux->link;
        }
    aux->link = nnodo;
    }
}

void mostrarlista (alumnol* topelista){
    if (topelista !=NULL){
        cout << topelista->DNI << "---" << topelista->nya << "---" << topelista->edad << "--- \n";
        topelista = topelista->link;
        mostrarlista (topelista);
    }
}

void pasarpilalista (alumnol* &topelista, alumnop* &topepila){
    while (topepila !=NULL){
        if (topepila->edad >=19){
            alumnol* nnodo = new alumnol();
            nnodo->DNI = topepila->DNI;
            nnodo->edad = topepila->edad;
            nnodo->nya = topepila->nya;
            nnodo->link = NULL;
            if (topelista == NULL){
                topelista = nnodo;
            } else {
                alumnol * auxbusca = topelista;
                while (auxbusca->link != NULL){
                    auxbusca = auxbusca->link;
                }
                auxbusca->link = nnodo;
            }
        }
        quitarpila (topepila);
    }
}

int main(){
    alumnop* topepila=NULL;
    alumnol* topelista=NULL;
    int dnia;
    int edada;
    string nyaa;
    cout <<"\n  \n" "hola buenas tardes, por favor ingrese los siguientes datos de los: " << MAX_ALUMNOS;
    for (int i = 1; i<=MAX_ALUMNOS; i++){
        cout << "\n \n \n" "ahora por favor ingrese los datos del alumno: " << i << endl;
        cout << "\ningrese el nombre y apellido: "; getline(cin, nyaa); cout << endl;
        cout << "\ningrese la edad: "; cin >> edada; cout << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\ningrese el DNI: "; cin >> dnia; cout << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        agregarpila (topepila, dnia, edada, nyaa);
    }
    pasarpilalista (topelista, topepila);
    mostrarlista (topelista);
    return 0;
}

