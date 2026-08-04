#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CURSOS = 100;
const int MAX_ASISTENTES = 500;

// Guarda el codigo y el nombre de cada curso.
struct Curso {
    string codigo;
    string nombre;
};

// Guarda el DNI y el nombre y apellido de cada asistente registrado.
struct Asistente {
    int dni;
    string nombreApellido;
};

int buscarCurso(Curso v[], int cant, string codigo);
int buscarAsistente(Asistente v[], int cant, int dni);
void ordenarCursosPorTotal(Curso cursos[], int matriz[][3], int cant);
int buscarMaximo(int matriz[][3], Curso cursos[], int cant, int &caracterMax, string &nombreCursoMax);

int main() {

    Curso cursos[MAX_CURSOS];
    int cantCursos = 0;

    Asistente asistentes[MAX_ASISTENTES];
    int cantAsistentes = 0;

    // Filas = cursos, columnas = caracter de participacion (0=Investigador,1=Profesional,2=Productor).
    int matrizAsistencia[MAX_CURSOS][3]{};

    // Vector paralelo a asistentes: indica si el asistente participo de al menos un curso.
    bool asistio[MAX_ASISTENTES];
    for(int i = 0; i < MAX_ASISTENTES; i++) {
        asistio[i] = false;
    }

    // -------------------------------------------------------------------------
    // LECTURA DEL ARCHIVO cursos.txt (codigo,nombre)
    // -------------------------------------------------------------------------
    ifstream archCursos("cursos.txt");
    string codigo, nombreCurso;

    getline(archCursos, codigo, ',');
    while(!archCursos.eof()) {
        getline(archCursos, nombreCurso);

        cursos[cantCursos].codigo = codigo;
        cursos[cantCursos].nombre = nombreCurso;

        cantCursos++;
        getline(archCursos, codigo, ',');
    }
    archCursos.close();

    // -------------------------------------------------------------------------
    // LECTURA DEL ARCHIVO asistentes.txt (dni,nombre y apellido)
    // -------------------------------------------------------------------------
    ifstream archAsistentes("asistentes.txt");
    string dniStr, nombreApellido;

    getline(archAsistentes, dniStr, ',');
    while(!archAsistentes.eof()) {
        getline(archAsistentes, nombreApellido);

        asistentes[cantAsistentes].dni = stoi(dniStr);
        asistentes[cantAsistentes].nombreApellido = nombreApellido;

        cantAsistentes++;
        getline(archAsistentes, dniStr, ',');
    }
    archAsistentes.close();

    // -------------------------------------------------------------------------
    // CARGA POR TECLADO DE LA PARTICIPACION EN LOS CURSOS
    // Fin de la carga: DNI = 0
    // -------------------------------------------------------------------------
    int dni, caracter, posCurso, posAsistente;
    string codCurso;

    cout << "Ingrese DNI del asistente (0 para finalizar): ";
    cin >> dni;

    while(dni != 0) {
        cout << "Ingrese codigo del curso: ";
        cin >> codCurso;
        cout << "Ingrese caracter de participacion (1.Investigador 2.Profesional 3.Productor): ";
        cin >> caracter;

        posCurso = buscarCurso(cursos, cantCursos, codCurso);
        posAsistente = buscarAsistente(asistentes, cantAsistentes, dni);

        if(posCurso != -1 && posAsistente != -1 && caracter >= 1 && caracter <= 3) {
            matrizAsistencia[posCurso][caracter - 1]++;
            asistio[posAsistente] = true;
        }

        cout << "Ingrese DNI del asistente (0 para finalizar): ";
        cin >> dni;
    }

    // -------------------------------------------------------------------------
    // PUNTO A: INFORME POR CURSO, ORDENADO POR CANTIDAD TOTAL DE ASISTENTES
    // -------------------------------------------------------------------------
    ordenarCursosPorTotal(cursos, matrizAsistencia, cantCursos);

    cout << endl;
    cout << left << setw(12) << "Cod.Curso" << setw(40) << "Nombre Curso"
         << setw(18) << "Cant.Investig." << setw(18) << "Cant.Profesion."
         << setw(16) << "Cant.Product." << "Cant.Total" << endl;

    for(int i = 0; i < cantCursos; i++) {
        int total = matrizAsistencia[i][0] + matrizAsistencia[i][1] + matrizAsistencia[i][2];
        // Se agregan dos espacios al nombre para garantizar un separador
        // aunque el nombre del curso supere el ancho fijado con setw.
        string nombrePad = cursos[i].nombre + "  ";

        cout << left << setw(12) << cursos[i].codigo << setw(40) << nombrePad
             << setw(18) << matrizAsistencia[i][0] << setw(18) << matrizAsistencia[i][1]
             << setw(16) << matrizAsistencia[i][2] << total << endl;
    }

    // -------------------------------------------------------------------------
    // PUNTO B: CURSO Y CARACTER DE PARTICIPACION CON MAYOR CANTIDAD DE ASISTENTES
    // -------------------------------------------------------------------------
    int caracterMax;
    string nombreCursoMax;
    int cantMax = buscarMaximo(matrizAsistencia, cursos, cantCursos, caracterMax, nombreCursoMax);

    string textoCaracter;
    if(caracterMax == 1) { textoCaracter = "Investigadores"; }
    else { if(caracterMax == 2) { textoCaracter = "Profesionales"; }
        else { textoCaracter = "Productores"; }
    }

    cout << endl;
    if(cantMax > 0) {
        cout << "Curso con mayor cantidad de asistentes en un caracter de participacion: "
             << nombreCursoMax << " (" << textoCaracter << ") con " << cantMax << " asistentes." << endl;
    }
    else {
        cout << "No se registraron asistentes en ningun curso." << endl;
    }

    // -------------------------------------------------------------------------
    // PUNTO C: ARCHIVO no_asistentes.txt (asistentes que no participaron de ningun curso)
    // -------------------------------------------------------------------------
    ofstream archNoAsistentes("no_asistentes.txt");

    for(int i = 0; i < cantAsistentes; i++) {
        if(!asistio[i]) {
            archNoAsistentes << asistentes[i].dni << "," << asistentes[i].nombreApellido << endl;
        }
    }
    archNoAsistentes.close();

    return 0;
}

// Busca la posicion de un codigo de curso dentro del vector de cursos.
int buscarCurso(Curso v[], int cant, string codigo) {
    int pos = -1;
    for(int i = 0; i < cant; i++) {
        if(v[i].codigo == codigo) {
            pos = i;
            i = cant;
        }
    }
    return pos;
}

// Busca la posicion de un DNI dentro del vector de asistentes.
int buscarAsistente(Asistente v[], int cant, int dni) {
    int pos = -1;
    for(int i = 0; i < cant; i++) {
        if(v[i].dni == dni) {
            pos = i;
            i = cant;
        }
    }
    return pos;
}

// Ordena los cursos (y su fila correspondiente en la matriz de asistencia) de mayor
// a menor segun la cantidad total de asistentes.
void ordenarCursosPorTotal(Curso cursos[], int matriz[][3], int cant) {
    Curso auxCurso;
    int auxCol;

    for(int i = 0; i < cant - 1; i++) {
        for(int j = i + 1; j < cant; j++) {
            int totalI = matriz[i][0] + matriz[i][1] + matriz[i][2];
            int totalJ = matriz[j][0] + matriz[j][1] + matriz[j][2];

            if(totalJ > totalI) {
                // Intercambio los cursos.
                auxCurso = cursos[i];
                cursos[i] = cursos[j];
                cursos[j] = auxCurso;

                // Intercambio la fila de la matriz para que no se rompa la relacion de indices.
                for(int k = 0; k < 3; k++) {
                    auxCol = matriz[i][k];
                    matriz[i][k] = matriz[j][k];
                    matriz[j][k] = auxCol;
                }
            }
        }
    }
}

// Busca en toda la matriz de asistencia la mayor cantidad de asistentes registrada
// para un curso y un caracter de participacion determinados.
// Devuelve por return la cantidad maxima, y por parametro el caracter y el nombre
// del curso correspondientes.
int buscarMaximo(int matriz[][3], Curso cursos[], int cant, int &caracterMax, string &nombreCursoMax) {
    int max = -1;
    caracterMax = -1;
    nombreCursoMax = "";

    for(int i = 0; i < cant; i++) {
        for(int c = 0; c < 3; c++) {
            if(matriz[i][c] > max) {
                max = matriz[i][c];
                caracterMax = c + 1;
                nombreCursoMax = cursos[i].nombre;
            }
        }
    }
    return max;
}