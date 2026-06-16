#include <iostream>

using namespace std;

struct NABinario{
    NABinario* izq;
    NABinario* der;
    int dato;
};


int main ( ){
    int c= 0, ac=0;
    NABinario* raiz;
    promedio_recursivo (raiz, c, ac);
    cout << (float) ac/c;
}


//promedio de arbol
void promedio_recursivo (NABinario* actual, int &cont, int &acum){
    if (actual == NULL) return;
    cont ++;
    acum += actual->dato;
    promedio_recursivo (actual->izq, cont, acum);
    promedio_recursivo (actual->der, cont, acum);
}


//act 3
void BuscarPadreHijo (NABinario* actual,int clave, NABinario* &padre, NABinario* &hijo){
    hijo = actual;



    while (hijo != NULL && hijo->dato != clave){
        padre = hijo;
        padre = NULL;
        if (clave<hijo->dato){
            hijo = hijo->izq;
        }else{
            hijo = hijo->der;
        }
    }
}


int altura_Iterativa (NABinario* actual){
    NABinario* aux;
    Ncola* C;
    incializar_cola(C);
    int nivel = 0, max = -1;
    if (actual == NULL){
        return 0;
    }
    ENCOLAR (C,actual,nivel);
    while (!cola_vacia(C)){
        aux = DESENCOLAR (C,nivel);
        if (nivel > max){
            max = nivel;
        }
    
        if (aux->izq != NULL) ENCOLAR (C, aux->izq, nivel+1);
        if (aux->der != NULL) ENCOLAR (C, aux->der, nivel+1);
    }
    return max+1;
}

//act 5 y 6 de tarea


//act 7
bool bajahoja (NABinario* &raiz, int clave){
    NABinario* H;
    NABinario* P;
    BuscarPadreHijo (raiz, clave, P, H);
    if (H==NULL){
        return false; //no existe clave en arbol
    }
    if (H->izq != NULL || H->der != NULL){
        return false; //no es hoja
    }
    //caso solo raiz
    if (P == NULL){
        raiz = NULL;
        delete H;
        return true;
    }
    if (P->izq == H){
        P->izq = NULL;
    }else{ P->der = NULL;}
    delete H;
    return true;
}