#include <iostream>

using namespace std;

struct NABinario {
    NABinario* der;
    NABinario* izq;
    int clave;
};

bool arbolKequilibrado (NABinario* arbol, int k, int &suma){
    if (arbol == NULL){
    suma = 0;
    return true;
    }

    int sumaizq = 0;
    int sumader = 0;

    bool izq = arbolKequilibrado (arbol->izq, k, sumaizq);
    bool der = arbolKequilibrado (arbol->der, k, sumader);
    
    suma = sumader + sumaizq + arbol->clave;

    if (!izq || !der) return false;

    return abs(sumader - sumaizq) <= k;
}