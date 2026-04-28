#include <iostream>
using namespace std;

struct ListaSimplementeEnlazada {
    int dato;
    ListaSimplementeEnlazada* link;
} typedef NListaSE;

void agregar(NListaSE* &inicio, int data) {
    NListaSE* Nnodo = new NListaSE();
    Nnodo->dato = data;
    Nnodo->link= NULL;
    if (inicio == NULL){
        inicio = Nnodo;
    }else { 
        NListaSE* aux = inicio;
        while (aux->link!=NULL) {
            aux = aux->link;
        }
        aux->link = Nnodo;
    }


}
void listase_agregar_ordenado (NListaSE* &listase, int ndato){
	NListaSE* actual = listase;
	NListaSE* anterior = NULL;
	NListaSE* nuevo_nodo = new (NListaSE);
	nuevo_nodo->dato = ndato;
	
	while (actual != NULL && actual->dato < ndato)
	{
		anterior = actual;
		actual = actual->link;
	}
	
	if (anterior == NULL)
	{
		nuevo_nodo->link = listase;
		listase = nuevo_nodo;
	} else
	{
		nuevo_nodo->link = anterior->link;
		anterior->link = nuevo_nodo;
	}
}

void Eliminar_ocurrencia_lista (NListaSE* &listase, int dato)


int main () {
    NListaSE* listase = NULL;
    int dato = 1;

}


