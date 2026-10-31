#include <iostream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

string numero_tel(string nombre_y_apellido, map<string, string> agenda) {
            //se puede poner auto directamente
    for (map<string, string>::iterator i = agenda.begin(); i != agenda.end(); ++i) {
        if (i->first == nombre_y_apellido) {
            return i->second;
        }
    }
    return "No se encontro la persona en la agenda.";

}

int main() {
    map<string, string> prueba_agenda;

    prueba_agenda["Juan Perez"] = "123456789";
    prueba_agenda["Maria Lopez"] = "987654321";
    prueba_agenda["Carlos Sanchez"] = "456789123";
    prueba_agenda["Ana Torres"] = "789123456";

    cout << "Ingrese el nombre y apellido de la persona que desea buscar: ";
    string nombre_y_apellido;
    getline(cin, nombre_y_apellido);

    cout << "El numero de telefono de " << nombre_y_apellido << " es: " << numero_tel(nombre_y_apellido, prueba_agenda) << endl;
}