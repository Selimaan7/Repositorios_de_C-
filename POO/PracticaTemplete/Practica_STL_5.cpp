#include <iostream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <string>

using namespace std;

template <typename T>
T encontrar_dato(map<T, T>& agenda, const T& clave) {
    map<T, T>::iterator it = agenda.find(clave);

    if (it != agenda.end()) {
        return it->second;
    }
    
    // Si no se encuentra la clave, se busca por el valor.
    map<T, T>::iterator actual = agenda.begin();
    while (actual != agenda.end()) {
        if (actual->second == clave) {
            return actual->first;
        }
        ++actual;
    }

    // Si no se encuentra la clave ni el valor, se puede lanzar una excepción o devolver un valor predeterminado.
    cout << "No se encontró el dato ingresado" << endl;
    return T(); // Devuelve un valor predeterminado del tipo T
}

int main() {
    map<string, string> agenda;

    agenda["Juan Perez"] = "123456789";
    agenda["Maria Lopez"] = "987654321";
    agenda["Carlos Sanchez"] = "456789123";
    agenda["Ana Torres"] = "789123456";

    cout << "Ingrese el nombre o numero de telefono de la persona que desea buscar: ";
    string dato;
    getline(cin, dato);

    string resultado = encontrar_dato(agenda, dato);

    if (!resultado.empty()) {
        cout << "El resultado de la busqueda es: " << resultado << endl;
    } else {
        cout << "No se encontró el dato ingresado." << endl;
    }
}