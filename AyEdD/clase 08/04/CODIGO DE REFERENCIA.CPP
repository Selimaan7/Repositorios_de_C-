// Version: 20200415

#include <iostream>
#include <stdlib.h>

using namespace std;


// DEFINICION DE TIPOS.

struct nodo_pila
{
	int dato;
	struct nodo_pila* link;
};
typedef struct nodo_pila NPila;

struct nodo_cola
{
	int dato;
	struct nodo_cola* link;
};
typedef struct nodo_pila NCola;

struct nodo_listase
{
	int dato;
	struct nodo_listase* link;
};
typedef struct nodo_listase NListaSE;


// DECLARACION DE FUNCIONES.

void pila_agregar (NPila* &pila, int ndato);
int pila_obtener (NPila* &pila);
bool pila_vacia (NPila* pila);

void cola_agregar (NCola* &frete, NCola* &fondo, int ndato);
int cola_obtener (NCola* &frete, NCola* &fondo);
bool cola_vacia (NCola* frete, NCola* fondo);

void listase_mostrar (NListaSE* listase);
void listase_agregar_final (NListaSE* &listase, int ndato);
void listase_agregar_ordenado (NListaSE* &listase, int ndato);
bool listase_eliminar_ocurrencia (NListaSE* &listase, int datoe);
void listase_eliminar_ocurrencias (NListaSE* &listase, int datoe);

void menu_opcion1 (NListaSE* listase);
void menu_opcion2 (NListaSE* &listase);
void menu_opcion3 (NListaSE* &listase);
void menu_opcion4 (NListaSE* &listase);
void menu_opcion5 (NListaSE* &listase);


// DEFINICION DE FUNCIONES.

int main (void)
{
//	NPila* pila = NULL;
//	NCola* cola_frente = NULL, cola_fondo = NULL;
	NListaSE* listase = NULL;
	
	int opcion = 0;
    do {
		cout << "************Menu de Opciones************\n";
		cout << endl;
		cout << "****** Lista Simplemente Enlazada ******\n";
		cout << endl;
		cout << "1- Mostrar.\n";
		cout << "2- Insertar N elementos al final.\n";
		cout << "3- Insertar N elementos ordenados.\n";
		cout << "4- Elminar primer ocurrencia de N.\n";
		cout << "5- Elminar todas las ocurrencias de N.\n";
		cout << endl;
		cout << "    0- Salir\n";
		cout << endl;
		cout << "                        Ingrese opcion: ";
		cin >> opcion;
		cout << endl;
		cout << endl;
		
		switch(opcion)
		{
			case 1:
				menu_opcion1 (listase);
			break;
			case 2:
				menu_opcion2 (listase);
			break;
			case 3:
				menu_opcion3 (listase);
			break;
			case 4:
				menu_opcion4 (listase);
			break;
			case 5:
				menu_opcion5 (listase);
			break;
		}
	} while ( opcion != 0);

	return 0;
}


void menu_opcion1 (NListaSE* listase)
{
	listase_mostrar (listase);
}

void menu_opcion2 (NListaSE* &listase)
{
	int nuevo_dato, cantidad;
	
	cout << "Cuantos datos aleatorios desea cargar?: ";
	cin >> cantidad;
	cout << endl;
	cout << "Lista de datos cargados:\n";
	cout << endl;
	for (int i=0; i<cantidad; i++)
	{
		nuevo_dato = (rand () % 100) + 1;
		listase_agregar_final (listase, nuevo_dato);
		cout << nuevo_dato << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

void menu_opcion3 (NListaSE* &listase)
{
	int nuevo_dato, cantidad;
	
	cout << "Cuantos datos aleatorios desea cargar?: ";
	cin >> cantidad;
	cout << endl;
	cout << "Lista de datos cargados:\n";
	cout << endl;
	for (int i=0; i<cantidad; i++)
	{
		nuevo_dato = (rand () % 100) + 1;
		listase_agregar_ordenado (listase, nuevo_dato);
		cout << nuevo_dato << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

void menu_opcion4 (NListaSE* &listase)
{
	int dato_eliminar;
	bool elimino;

	cout << "Que dato desea eliminar?: ";
	cin >> dato_eliminar;
	cout << endl;

	elimino = listase_eliminar_ocurrencia (listase, dato_eliminar);
	
	if (elimino)
		cout << "Fue encontrado y eliminado un dato.\n\n";
	else
		cout << "No fue encontrado el dato.\n\n";
	cout << endl;
}

void menu_opcion5 (NListaSE* &listase)
{
	int dato_eliminar;
	
	cout << "Que dato desea eliminar?: ";
	cin >> dato_eliminar;
	
	listase_eliminar_ocurrencias (listase, dato_eliminar);

	cout << endl;
	cout << endl;
}


void listase_mostrar (NListaSE* listase)
{
	cout << "Lista Simplemente Enlazada:\n\n";
	while (listase != NULL)
	{
		cout << listase->dato << " -> ";
		listase = listase->link;
	}
	cout << "NULL\n";
	cout << endl;
	cout << endl;
}

void listase_agregar_final (NListaSE* &listase, int ndato)
{
	NListaSE* aux_lse = listase;
	NListaSE* nuevo_nodo = new (NListaSE);
	nuevo_nodo->dato = ndato;
	nuevo_nodo->link = NULL;
	
	if (aux_lse == NULL)
		listase = nuevo_nodo;
	else
	{
		while (aux_lse->link != NULL)
			aux_lse = aux_lse->link;
		aux_lse->link = nuevo_nodo;
	}	
}

void listase_agregar_ordenado (NListaSE* &listase, int ndato)
{
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

bool listase_eliminar_ocurrencia (NListaSE* &listase, int datoe)
{
	NListaSE* actual = listase;
	NListaSE* anterior = NULL;
	NListaSE* aux = NULL;
	
	while ((actual != NULL) and (actual->dato != datoe))
	{
		anterior = actual;
		actual = actual->link;
	}
	
	if ((actual != NULL) and (anterior == NULL))
	{
		aux = actual;
		listase = listase->link;
		free (aux);
		return true;
	} else if ((actual != NULL) and (anterior != NULL))
	{
		aux = actual;
		anterior->link = actual->link;
		free (aux);
		return true;		
	}

	return false;
}

void listase_eliminar_ocurrencias (NListaSE* &listase, int datoe)
{
	while (listase_eliminar_ocurrencia (listase, datoe));
}