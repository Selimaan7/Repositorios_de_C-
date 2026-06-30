#include <iostream>

using namespace std;

struct NABinario {
    NABinario* der;
    NABinario* izq;
    int frecuencia;
    char caracter;
};
                                                    // en el main se declara como falsa
int suma_ancestros (NABinario* actual, char c, bool &E){
    int  i;
    if (actual == NULL) return -1;

    if (actual->caracter == c){
        E = true;
        return 0;
    }
    i = suma_ancestros (actual->izq, c, E);
    if (E) return actual->frecuencia + i;

    i = suma_ancestros (actual->der, c, E);
    if (E) return actual->frecuencia + i;

    return -1;
}