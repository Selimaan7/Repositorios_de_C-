#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Servicio {
    string codigo;
    string sede;
    string nombre;
    int criticidad;
    int capacidad;
    int diasSinParche;
};

struct Incidente {
    string codigoServicio;
    int tipo;
    int gravedad;
    int conexiones;
};

int main() {
    srand(time(0)); // semilla para números aleatorios

    // ---------- DATOS DE EJEMPLO ----------
    vector<Servicio> servicios = {
        {"SRV001", "Sede Central", "API Gateway", 5, 1000, 120},
        {"SRV002", "Sede Norte", "Base de Datos", 4, 500, 45},
        {"SRV003", "Sede Sur", "Servidor Web", 3, 800, 95},
        {"SRV004", "Sede Central", "Sistema de Autenticación", 5, 300, 10},
        {"SRV005", "Sede Norte", "Servicio de Notificaciones", 2, 200, 60},
        {"SRV006", "Sede Sur", "Motor de Pagos", 5, 150, 130},
        {"SRV007", "Sede Central", "Firewall", 4, 600, 20},
        {"SRV008", "Sede Norte", "Balanceador de Carga", 3, 900, 75},
        {"SRV009", "Sede Sur", "Sistema de Monitoreo", 2, 250, 5},
        {"SRV010", "Sede Central", "Servicio de Correo", 3, 400, 110}
    };

    // ---------- GENERAR servicios.txt ----------
    ofstream archServicios("servicios.txt");
    if (!archServicios) {
        cerr << "Error al crear servicios.txt" << endl;
        return 1;
    }

    for (const auto& s : servicios) {
        archServicios << s.codigo << "\n";
        archServicios << s.sede << "\n";
        archServicios << s.nombre << "\n";
        archServicios << s.criticidad << "\n";
        archServicios << s.capacidad << "\n";
        archServicios << s.diasSinParche << "\n";
    }
    archServicios.close();
    cout << "Archivo servicios.txt generado con " << servicios.size() << " servicios." << endl;

    // ---------- GENERAR incidentes.txt ----------
    // Crear incidentes asociados a algunos servicios
    vector<string> codigosValidos = {"SRV001", "SRV002", "SRV003", "SRV004", "SRV005",
                                     "SRV006", "SRV007", "SRV008", "SRV009", "SRV010"};

    vector<Incidente> incidentes;

    // Generar entre 30 y 50 incidentes aleatorios
    int totalIncidentes = 30 + rand() % 21; // 30..50

    for (int i = 0; i < totalIncidentes; i++) {
        Incidente inc;
        // Elegir un servicio aleatorio
        int idx = rand() % codigosValidos.size();
        inc.codigoServicio = codigosValidos[idx];
        inc.tipo = rand() % 4;            // 0..3
        inc.gravedad = 1 + rand() % 10;   // 1..10
        inc.conexiones = rand() % 2000;   // 0..1999
        incidentes.push_back(inc);
    }

    // Agregar incidentes específicos para servicios con +90 días sin parche
    // SRV001, SRV003, SRV006, SRV010 tienen +90
    vector<string> serviciosConParcheAtrasado = {"SRV001", "SRV003", "SRV006", "SRV010"};
    for (const string& cod : serviciosConParcheAtrasado) {
        for (int i = 0; i < 3; i++) {  // 3 incidentes extra cada uno
            Incidente inc;
            inc.codigoServicio = cod;
            inc.tipo = rand() % 4;
            inc.gravedad = 1 + rand() % 10;
            inc.conexiones = rand() % 2000;
            incidentes.push_back(inc);
        }
    }

    // Guardar incidentes en archivo
    ofstream archIncidentes("incidentes.txt");
    if (!archIncidentes) {
        cerr << "Error al crear incidentes.txt" << endl;
        return 1;
    }

    for (const auto& inc : incidentes) {
        archIncidentes << inc.codigoServicio << "\n";
        archIncidentes << inc.tipo << "\n";
        archIncidentes << inc.gravedad << "\n";
        archIncidentes << inc.conexiones << "\n";
    }
    archIncidentes.close();
    cout << "Archivo incidentes.txt generado con " << incidentes.size() << " incidentes." << endl;

    return 0;
}