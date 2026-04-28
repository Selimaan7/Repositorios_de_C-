#include <iostream>
using namespace std;
struct lista {
    int dato;
    lista*siguiente;
};

void agregar_final (lista* &lse, int valor);
void agregar_ordenado(lista* &lse,int valor);
void listase_mostrar (lista* listase);
bool listase_eliminar_ocurrencia (lista* &listase, int datoe);
void listase_eliminar_ocurrencias (lista* &listase, int datoe);
int main() {
    lista* lse;
    int dato;
    for (int i; i<=3; i++){
    cout << "ingrese dato\n ";
    cin >> dato;
    agregar_final(lse, dato);
    }
    cout << listase_mostrar(lse);
    
    return 0;

}


void agregar_final (lista* &lse, int valor)
{
    lista*aux=lse; //guardamos la cabeza de la lista para no perderla
    if (lse==NULL)  //si la lista esta vacia
    {
        lse=new lista; //creamos un nodo
        lse->dato=valor; //le damos un dato al nodo
        lse->siguiente=NULL; // hacemos que el nodo apunte a null
        return;
    }
    while (aux->siguiente!=NULL) // mientras siguiente sea distinto de NULL
    {
        aux=aux->siguiente; //vamos recorriendo la lista hasta llegar al ultimo nodo
    }
    aux->siguiente=new lista; //hacemos que siguiente apunte al nuevo nodo para enlazarlo a lista
    aux->siguiente->dato=valor; //asignamos un dato al nuevo nodo enlazado a la lista
    aux->siguiente->siguiente=NULL; //hacemos que el nuevo nodo termine apunto a null
}

void agregar_ordenado(lista* &lse,int valor)
{
    lista*actual=lse;  //creamos un punterio para recorrer la lista
    lista*anterior=NULL; //creamos otro puntero para poder comparar los valores 
    lista*nuevon=new lista; // creamos un nuevo nodo
    if(actual==NULL) //si la lista esta vacia creamos simplemente un nuevo nodo y le damos un valor para despues retornar
    {
        lse=nuevon;
        nuevon->dato=valor;
        nuevon->siguiente=NULL;
        return;
    }
    while ( (actual!=NULL) && (actual->dato<valor)) //mientras que actual no llegue al final y el valor del nodo sea menor que el valor ingresado por parametro (ya que se ordena de menor a mayor)
    {
        anterior=actual; //anterior se va a apuntar al mismo nodo que actual
        actual=actual->siguiente; //actual va a apuntar al siguiente nodo para seguir recorriendo

    }
    if (anterior == NULL) // si la anterior es null , es decir, que no se recorrio la lista porque tiene un nodo unicamente
    {
        nuevon->siguiente=lse; //el nuevo nodo apunta a la antigua cabeza
        nuevon->dato=valor; //la nueva cabeza es el nodo insertado
    }
    if (anterior!=NULL){ //si se rcorrio la lista as de una una vez
        nuevon->siguiente=anterior->siguiente; //eenlazamos con el siguiente nodo al nuevo nodo
        anterior ->siguiente=nuevon; //el anterior apunta al nuevo nodo
    }
return;
    }


    void listase_mostrar (lista* listase)
{
	cout<< "Lista Simplemente Enlazada:\n\n";
	while (listase != NULL)
	{
		cout << listase->dato << " -> ";
		listase = listase->siguiente;
	}
	cout << "NULL\n";
	cout << endl;
	cout << endl;
}


bool listase_eliminar_ocurrencia (lista* &listase, int datoe)
{
	lista* actual = listase; //definimos actual
	lista* anterior = NULL; //definimos la posicion anterior
	lista* aux = NULL; //definir aux como NULL
	
	while ((actual != NULL) and (actual->dato != datoe)) //verificamos que no encontramos todavia el dato a eleiminar para seguir reocrriendo la lista
	{
		anterior = actual;
		actual = actual->siguiente;
	}
	
	if ((actual != NULL) and (anterior == NULL))
	{
		aux = actual;
		listase = listase->siguiente; // hacemos que listase apunte al siguiente nodo para borrar el primero y no perder la lista
		delete (aux); //borramos el nodo que tiene el valor
		return true; //retornamos
	} else if ((actual != NULL) and (anterior != NULL))
	{
		aux = actual;
		anterior->siguiente = actual->siguiente; //hacemos que el nodo anterior apunte al siguiente nodo del nodo a eliminar para no perder la lista
		delete (aux);
		return true;		
	}

	return false;
}

void listase_eliminar_ocurrencias (lista* &listase, int datoe)
{
	while (listase_eliminar_ocurrencia (listase, datoe)); //mientras que se pueda eliminar una ocurrencia del dato a eliminar, se va a seguir eliminando
}

bool esAsendente(lista* lse){
    if (lse == NULL) or (lse->link==NULL){
        return true;
    }
    lista* actual = lse;
    while (actual->link !=NULL){
        if (actual->data > actual->link->dato)
        return false;
        actual = actual->link;
    }

return true;

}