#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream pasajeros("pasajeros_oroverde.txt");

    pasajeros<<"30111222\n";
    pasajeros<<"Perez\n";
    pasajeros<<"Juan\n";
    pasajeros<<"4\n";

    pasajeros<<"28999111\n";
    pasajeros<<"Garcia\n";
    pasajeros<<"Maria\n";
    pasajeros<<"4\n";

    pasajeros<<"33444555\n";
    pasajeros<<"Lopez\n";
    pasajeros<<"Carlos\n";
    pasajeros<<"1\n";

    pasajeros<<"40123123\n";
    pasajeros<<"Fernandez\n";
    pasajeros<<"Lucia\n";
    pasajeros<<"4\n";

    pasajeros<<"42111222\n";
    pasajeros<<"Martinez\n";
    pasajeros<<"Sofia\n";
    pasajeros<<"2\n";

    pasajeros<<"35000999\n";
    pasajeros<<"Gomez\n";
    pasajeros<<"Pedro\n";
    pasajeros<<"4\n";

    pasajeros<<"36555444\n";
    pasajeros<<"Diaz\n";
    pasajeros<<"Camila\n";
    pasajeros<<"4\n";

    pasajeros<<"38777111\n";
    pasajeros<<"Ruiz\n";
    pasajeros<<"Agustin\n";
    pasajeros<<"6\n";

    pasajeros<<"41222333\n";
    pasajeros<<"Benitez\n";
    pasajeros<<"Valentina\n";
    pasajeros<<"4\n";

    pasajeros<<"39999888\n";
    pasajeros<<"Alvarez\n";
    pasajeros<<"Nicolas\n";
    pasajeros<<"5\n";

    pasajeros.close();



    ofstream lineas("LINEAS_TRANSPORTE.txt");

    lineas<<"L1\n";
    lineas<<"Parana - Oro Verde\n";

    lineas<<"L2\n";
    lineas<<"Centro - FCYT\n";

    lineas<<"L3\n";
    lineas<<"Thompson - Oro Verde\n";

    lineas<<"L4\n";
    lineas<<"Paracao - UADER\n";

    lineas.close();

    cout<<"Archivos generados correctamente.";

    return 0;
}