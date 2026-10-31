#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

vector<string> obtener_nombres(const map<string, string>& agenda, const string& fecha) {
    vector<string> nombres;
    for (const auto& entry : agenda) {
        if (entry.second == fecha) {
            nombres.push_back(entry.first);
        }
    }
    return nombres;
}

int main () {
    map<string, string> agenda;

    agenda["Juan Perez"] = "01/01/1990";
    agenda["Maria Lopez"] = "15/05/1985";
    agenda["Carlos Sanchez"] = "20/10/1992";
    agenda["Ana Torres"] = "15/05/1985";

    cout << "Ingrese la fecha de nacimiento (formato DD/MM/YYYY): ";
    string fecha;
    getline(cin, fecha);

    vector<string> nombres = obtener_nombres(agenda, fecha);

    if (!nombres.empty()) {
        cout << "Personas con fecha de nacimiento " << fecha << ":\n";
        for (const string& nombre : nombres) {
            cout << nombre << endl;
        }
    } else {
        cout << "No se encontraron personas con esa fecha de nacimiento." << endl;
    }
}