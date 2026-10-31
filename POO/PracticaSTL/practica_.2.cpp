#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class Empleado {
    private:
        char dni[8];
        int horas;

    public:
        Empleado(const string& d, int horas) : horas(horas){
            int i = 0;
            for (;i < 8 && i < d.length() ;++i){
                dni[i] = d[i];
            }

            for (; i<8 ; ++i){
                dni[i] = '\0';
            }
        }

        string getDni() const{
            string resultado;
            for (int i = 0; i<8 && dni[i] != '\0'; ++i ){
                resultado += dni[i];
            }
            return resultado;
        }

        int gethoras() const{
            return horas;
        }
};

struct comprarporhoras {
    bool operator()(const Empleado& empleado1, const Empleado& empleado2) const{
        return empleado1.gethoras() < empleado2.gethoras();
    }
};

struct comprarPorMenosHoras {
    bool operator()(const Empleado& empleado1, const Empleado& empleado2) const{
        return empleado1.gethoras() > empleado2.gethoras();
    }
};

int main () {
    int cantidad;
    cout << "Cantidad de registros a ingresar: ";
    cin >> cantidad;

    if (!cin || cantidad <= 0) {
        cerr << "La cantidad debe ser un numero mayor que cero." << endl;
        return 1;
    }
    map <string, int> horasPorEmpleado;
    map <string, int> VecesCargado;

    for (int i = 0; i< cantidad; i++){
        string dniInput;
        int horasInput;

        cout << "\Registro " << i + 1 << endl;
        cout << "DNI: ";
        cin >> dniInput;
        cout << "Horas trabajadas: ";
        cin >> horasInput;

        if (!cin || horasInput < 0){
            cerr << "El DNI o la cantidad de horas no es valido." << endl;
            return 1;
        }

        horasPorEmpleado [dniInput] += horasInput;
        
        VecesCargado[dniInput]++;
    }

    priority_queue<Empleado, vector<Empleado>, comprarporhoras> porMasHoras;
    priority_queue<Empleado, vector<Empleado>, comprarPorMenosHoras>  porMenosHoras;
    vector<Empleado> TodosLosEmpleados;

    for (const auto& [dni, horasTotales] : horasPorEmpleado){
        Empleado empleado(dni, horasTotales);
        TodosLosEmpleados.push_back(empleado);
        porMasHoras.push(empleado);
        porMenosHoras.push(empleado);
    }

    if (TodosLosEmpleados.empty()) return 0;

    const int maximoDeHoras = porMasHoras.top().gethoras();
    const int minimoDeHoras = porMenosHoras.top().gethoras();

    cout << "\n----------------------------------------" << endl;
    cout << "Empleados que MAS horas trabajaron (" << maximoDeHoras << " horas en total): " << endl;

    for (const Empleado& empleado : TodosLosEmpleados){
        if (empleado.gethoras() == maximoDeHoras) {
            cout << "- " << empleado.getDni() << endl;
        }
    }

    cout << "\n Empleados que MENOS horas trabajaron (" << minimoDeHoras << " horas en total): " << endl;
    
    for (const Empleado& empleado : TodosLosEmpleados){
        if (empleado.gethoras() == minimoDeHoras) {
            cout << "- " << empleado.getDni() << endl;
        }
    }



    cout << "\n Top 5 de personas que mas trabajaron: " << endl;
    for (int posicion = 1; posicion <=5 && !porMasHoras.empty(); ++posicion){
        const Empleado& empleado = porMasHoras.top();
        cout << posicion << ". " << empleado.getDni() << "- " << empleado.gethoras() << " horas" << endl;
        porMasHoras.pop();
    }




    cout << "\n DNIs cargados mas de una vez: " << endl;
    bool hayRepetidos = false;
    for (const auto& [dni,cantidadDeVeces] : VecesCargado){
        if (cantidadDeVeces > 1){
            cout << "- " << dni << " (" << cantidadDeVeces << " ingresos detectados)" << endl;
            hayRepetidos = true;
        }
    }
    if (!hayRepetidos) {
        cout << "No hay DNIs repetidos." << endl;
    }

    return 0;
}