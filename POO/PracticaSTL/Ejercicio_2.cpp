#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class Empleado {
    private:
        // Se respeta la restricción exacta del enunciado
        char dni[8];
        int horas;

    public:
        Empleado(const string& d, int horas) : horas(horas) {
            int i = 0;
            // Copiamos hasta 8 caracteres del string al array char[8]
            for (; i < 8 && i < d.length(); ++i) {
                dni[i] = d[i];
            }
            // Si el DNI tiene menos de 8 caracteres, rellenamos el resto con nulos
            for (; i < 8; ++i) {
                dni[i] = '\0';
            }
        }

        // Método para extraer el char[8] a string de forma segura para imprimir
        string getDni() const {
            string resultado;
            for (int i = 0; i < 8 && dni[i] != '\0'; ++i) {
                resultado += dni[i];
            }
            return resultado;
        }

        int getHoras() const {
            return horas;
        }
};

struct CompararPorHoras {
    bool operator()(const Empleado& empleado1, const Empleado& empleado2) const {
        return empleado1.getHoras() < empleado2.getHoras();
    }
};

struct CompararPorMenosHoras {
    bool operator()(const Empleado& empleado1, const Empleado& empleado2) const {
        return empleado1.getHoras() > empleado2.getHoras();
    }
};

int main() {
    int cantidad;
    cout << "Cantidad de registros a ingresar: ";
    cin >> cantidad;

    if (!cin || cantidad <= 0) {
        cerr << "La cantidad debe ser un numero mayor que cero." << endl;
        return 1;
    }

    // Mapas para consolidar y contar datos en la etapa de carga
    map<string, int> horasPorEmpleado;
    map<string, int> vecesCargado;

    for (int i = 0; i < cantidad; ++i) {
        string dniInput;
        int horasInput;

        cout << "\nRegistro " << i + 1 << endl;
        cout << "DNI: ";
        cin >> dniInput;
        cout << "Horas trabajadas: ";
        cin >> horasInput;

        if (!cin || horasInput < 0) {
            cerr << "El DNI o la cantidad de horas no es valido." << endl;
            return 1;
        }

        // 1. Consolidamos las horas (si el DNI ya existe, se suman a las que ya tenia)
        horasPorEmpleado[dniInput] += horasInput;
        
        // 2. Contamos un ingreso más para este DNI
        vecesCargado[dniInput]++;
    }

    // Ahora procesamos los datos ya unificados (consolidados)
    priority_queue<Empleado, vector<Empleado>, CompararPorHoras> porMasHoras;
    priority_queue<Empleado, vector<Empleado>, CompararPorMenosHoras> porMenosHoras;
    vector<Empleado> todosLosEmpleados;

    for (const auto& [dni, horasTotales] : horasPorEmpleado) {
        Empleado empleado(dni, horasTotales); // Acá se aplica la restricción char[8]
        todosLosEmpleados.push_back(empleado);
        porMasHoras.push(empleado);
        porMenosHoras.push(empleado);
    }

    if (todosLosEmpleados.empty()) return 0;

    const int maximoDeHoras = porMasHoras.top().getHoras();
    const int minimoDeHoras = porMenosHoras.top().getHoras();

    cout << "\n----------------------------------------" << endl;
    cout << "Empleados que MAS horas trabajaron (" << maximoDeHoras
         << " horas en total):" << endl;
    for (const Empleado& empleado : todosLosEmpleados) {
        if (empleado.getHoras() == maximoDeHoras) {
            cout << "- " << empleado.getDni() << endl;
        }
    }

    cout << "\nEmpleados que MENOS horas trabajaron (" << minimoDeHoras
         << " horas en total):" << endl;
    for (const Empleado& empleado : todosLosEmpleados) {
        if (empleado.getHoras() == minimoDeHoras) {
            cout << "- " << empleado.getDni() << endl;
        }
    }

    cout << "\nTop 5 de personas que mas trabajaron:" << endl;
    for (int posicion = 1;
         posicion <= 5 && !porMasHoras.empty();
         ++posicion) {
        const Empleado& empleado = porMasHoras.top();
        cout << posicion << ". " << empleado.getDni()
             << " - " << empleado.getHoras() << " horas" << endl;
        porMasHoras.pop();
    }

    // Informe de repetidos (funciona independientemente de la consolidación de horas)
    cout << "\nDNIs cargados mas de una vez:" << endl;
    bool hayRepetidos = false;
    for (const auto& [dni, cantidadDeVeces] : vecesCargado) {
        if (cantidadDeVeces > 1) {
            cout << "- " << dni << " (" << cantidadDeVeces << " ingresos detectados)" << endl;
            hayRepetidos = true;
        }
    }

    if (!hayRepetidos) {
        cout << "No hay DNIs repetidos." << endl;
    }

    return 0;
}