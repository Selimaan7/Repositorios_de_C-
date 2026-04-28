#include <iostream>
#include <string>
using namespace std;
struct alumno_pila{
    float dni;
    string nya;
    int edad;
    alumno_pila*siguiente;
};

void agregar(alumno_pila *&pila, float dni, string nya, int edad);
void quitar(alumno_pila *&pila, float &dni, string &nya, int &edad);



struct alumno_19{
    float dni;
    string nya;
    int edad;
    alumno_19*siguiente;
};

void agregar_final (alumno_19* &lista, float dni, string nya, int edad);
void listase_mostrar (alumno_19* listase);



int main(int argc, char const *argv[])
{
    alumno_pila*pila=NULL;
    alumno_19*lista=NULL;
   float dni,dni19;
    string nya,nya19;
     int edad,edad19;
     for (int i=0;i<3;i++)
     {
        cout<<"ingrese el dni del alumno"<<endl;
        cin>>dni;
        cout<<"ingrese el nombre y apellido del alumno"<<endl;
        cin>>nya;
        cout<<"ingrese la edad del alumno"<<endl;
        cin>>edad;
        agregar(pila,dni,nya,edad);
     }
     
     for (int i=0;i<3;i++)
     {
        quitar (pila,dni19,nya19,edad19);
        if (edad19>=19)
        {
            agregar_final(lista,dni19,nya19,edad19);
        }
     }
     listase_mostrar(lista);
    return 0;
}





void agregar(alumno_pila *&pila, float dni, string nya, int edad)
{
    alumno_pila *nuevo = new alumno_pila(); //reservas memoria
    nuevo->dni = dni;
    nuevo->nya = nya; 
    nuevo->edad = edad;
    nuevo->siguiente = pila; // apuntas al siguiente
    pila = nuevo; // apuntas pila al ultimo agregado
}

void quitar(alumno_pila *&pila, float &dni, string &nya, int &edad)
{
    alumno_pila *aux = pila; // creamos un puntero aux que apunte al tope
    dni = aux->dni; 
    nya = aux->nya;
    edad= aux->edad;
    pila = aux->siguiente; // pasamos el tope al otro nodo
    delete aux; // borramos el tope apuntado por aux
}



void agregar_final (alumno_19* &lista, float dni, string nya, int edad)
{
    alumno_19*aux=lista; //guardamos la cabeza de la lista para no perderla
    if (lista==NULL)  //si la lista esta vacia
    {
        lista=new alumno_19; //creamos un nodo
        lista->dni = dni;
    lista->nya = nya; 
    lista->edad = edad;//le damos un dato al nodo
        lista->siguiente=NULL; // hacemos que el nodo apunte a null
        return;
    }
    while (aux->siguiente!=NULL) // mientras siguiente sea distinto de NULL
    {
        aux=aux->siguiente; //vamos recorriendo la lista hasta llegar al ultimo nodo
    }
    aux->siguiente=new alumno_19; //hacemos que siguiente apunte al nuevo nodo para enlazarlo a lista
    aux->siguiente->dni = dni;
    aux->siguiente->nya = nya; 
    aux->siguiente->edad = edad;
    aux->siguiente->siguiente=NULL;
}
void listase_mostrar (alumno_19* listase){
cout<< "Lista de alumnos mayores a 19:\n\n";
	while (listase != NULL)
	{
		cout << "DNI del alumno: " << listase->dni<<endl;
        cout << "Nombre y Apellido del alumno: " << listase->nya<< endl;
        cout << "Edad del alumno: " << listase->edad<< endl;
		listase = listase->siguiente;
	}
	cout << "NULL\n";
	cout << endl;
	cout << endl;
}