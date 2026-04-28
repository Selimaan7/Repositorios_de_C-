#include <iostream>
#define max 5
using namespace std;

struct documentos {
    int id;
    string ruta;
};

struct colaimpresion{
    documentos el [max];
    int frente;
    int fondo;
    bool vacia;
    bool llena;
}typedef cola;

void inicializar (colaimpresion &c){
    c.frente = 0;
    c.fondo = 0;
    c.vacia = true;
    c.llena = false;
}

bool agregar (cola &c, documentos d){
    if (c.llena) return false;
    c.el [c.fondo] = d;
    c.vacia = false;
    if (c.fondo == max-1){  //c.fondo = (c.fondo == max-1) ? 0 : c.fondo++;
        c.fondo = 0;
    }else{
        c.fondo++;
    }
    if (c.fondo == c.frente){   // c.llena = (c.fondo==c.frente)
        c.llena = true;
    }
    return true;
}

bool quitar (cola &c, documentos &retd){
    if (c.vacia) return false;
    retd = c.el[c.frente];
    if (c.frente == max-1){  //c.frente = (c.frente == max-1) ? 0 : c.frente++;
        c.frente = 0;
    }else{
        c.frente++;
    }
    c.llena = false;
    if (c.frente == c.fondo){   // c.fondo = (c.frente==c.fondo)
        c.vacia = true;
    }
    return true;
}
int main (){
    cola c; 
    documentos d;
    inicializar (c);
    for (int i = 0; i <10; i++){
        d.id = i;
        d.ruta = "papa"; //cin >> ......
        if (agregar(c,d)){
            cout << "docuemnto agregado correctamente";
        } else{
            cout << "ducmento" << d.id << "no se puedo agregar";
        }
    }
    if (quitar (c,d)){
        cout << d.id << "quitado exitosamente";
    }
}









