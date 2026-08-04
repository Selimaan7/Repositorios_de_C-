#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CURSOS = 100;
const int MAX_ASISTENTES = 500;

// Estructura para almacenar la información de los cursos
struct Curso {
    string codigo;
    string nombre;
};

// Estructura para almacenar la información de las personas (asistentes registrados)
struct Asistente {
    int dni;
    string nya;
};

// Funciones auxiliares según patrones de la cátedra
int buscarCurso(Curso v[], int cant, string codigo);
int buscarAsistente(Asistente v[], int cant, int dni);
int mayorAsistencia(int matriz[][3], int cantCursos, int &posCurso, int &posCaracter);

int main() {
    Curso cursos[MAX_CURSOS];
    int cantCursos = 0;

    Asistente asistentes[MAX_ASISTENTES];
    int cantAsistentes = 0;

    // Matriz de asistentes por curso (filas) y carácter de participación (3 columnas: 0=Investigadores, 1=Profesionales, 2=Productores)
    int matrizAsistencia[MAX_CURSOS][3] = {0};

    // Vector para controlar qué personas asistieron al menos a un curso
    bool participo[MAX_ASISTENTES];
    for (int i = 0; i < MAX_ASISTENTES; i++) {
        participo[i] = false;
    }

    // Vectores para totales e informe A
    int totalPorCurso[MAX_CURSOS] = {0};

    // Vector con los nombres de los caracteres de participación
    string nombresCaracter[3] = {"Investigadores", "Profesionales", "Productores"};

    // -------------------------------------------------------------------------
    // LECTURA DEL ARCHIVO CURSOS.TXT
    // -------------------------------------------------------------------------
    ifstream archCursos("cursos.txt");
    if (archCursos.fail()) {
        cout << "Error al abrir el archivo cursos.txt" << endl;
        return 1;
    }

    string codC, nomC;
    archCursos >> codC;
    while (!archCursos.eof()) {
        archCursos.ignore();
        getline(archCursos, nomC);

        cursos[cantCursos].codigo = codC;
        cursos[cantCursos].nombre = nomC;
        cantCursos++;

        archCursos >> codC;
    }
    archCursos.close();

    // -------------------------------------------------------------------------
    // LECTURA DEL ARCHIVO ASISTENTES.TXT
    // -------------------------------------------------------------------------
    ifstream archAsis("asistentes.txt");
    if (archAsis.fail()) {
        cout << "Error al abrir el archivo asistentes.txt" << endl;
        return 1;
    }

    int dniA;
    string nyaA;

    archAsis >> dniA;
    while (!archAsis.eof()) {
        archAsis.ignore();
        getline(archAsis, nyaA);

        asistentes[cantAsistentes].dni = dniA;
        asistentes[cantAsistentes].nya = nyaA;
        cantAsistentes++;

        archAsis >> dniA;
    }
    archAsis.close();

    // -------------------------------------------------------------------------
    // INGRESO DE DATOS DE PARTICIPACIÓN POR TECLADO
    // -------------------------------------------------------------------------
    int dniInput, caracterInput;
    string codCursoInput;

    cout << "Ingrese DNI del asistente (0 para finalizar): ";
    cin >> dniInput;

    while (dniInput != 0) {
        cout << "Ingrese Codigo del curso: ";
        cin >> codCursoInput;
        cout << "Ingrese Caracter de participacion (1. Investigadores, 2. Profesionales, 3. Productores): ";
        cin >> caracterInput;

        int posCurso = buscarCurso(cursos, cantCursos, codCursoInput);
        int posPersona = buscarAsistente(asistentes, cantAsistentes, dniInput);

        if (posCurso != -1 && caracterInput >= 1 && caracterInput <= 3) {
            // Se acumula en la matriz (caracterInput - 1 para posicionar en índice 0, 1 o 2)
            matrizAsistencia[posCurso][caracterInput - 1]++;
            totalPorCurso[posCurso]++;

            if (posPersona != -1) {
                participo[posPersona] = true;
            }
        }

        cout << "\nIngrese DNI del asistente (0 para finalizar): ";
        cin >> dniInput;
    }

    // -------------------------------------------------------------------------
    // ORDENAMIENTO POR CANTIDAD TOTAL DE ASISTENTES (DESCENDENTE)
    // -------------------------------------------------------------------------
    for (int i = 0; i < cantCursos - 1; i++) {
        for (int j = i + 1; j < cantCursos; j++) {
            if (totalPorCurso[j] > totalPorCurso[i]) {
                // Intercambio de total
                int auxTot = totalPorCurso[i];
                totalPorCurso[i] = totalPorCurso[j];
                totalPorCurso[j] = auxTot;

                // Intercambio de estructura Cursos
                Curso auxCurso = cursos[i];
                cursos[i] = cursos[j];
                cursos[j] = auxCurso;

                // Intercambio de las filas correspondientes de la matriz
                for (int k = 0; k < 3; k++) {
                    int auxMat = matrizAsistencia[i][k];
                    matrizAsistencia[i][k] = matrizAsistencia[j][k];
                    matrizAsistencia[j][k] = auxMat;
                }
            }
        }
    }

    // -------------------------------------------------------------------------
    // INFORME A
    // -------------------------------------------------------------------------
    cout << endl;
    cout << left << setw(12) << "Cod. Curso"
         << setw(30) << "Nombre Curso"
         << setw(22) << "Cant. Investigadores"
         << setw(21) << "Cant. Profesionales"
         << setw(20) << "Cant. Productores"
         << setw(15) << "Cant. Total" << endl;

    for (int i = 0; i < cantCursos; i++) {
        cout << left << setw(12) << cursos[i].codigo
             << setw(30) << cursos[i].nombre
             << right << setw(22) << matrizAsistencia[i][0]
             << setw(21) << matrizAsistencia[i][1]
             << setw(20) << matrizAsistencia[i][2]
             << setw(15) << totalPorCurso[i] << endl;
    }

    // -------------------------------------------------------------------------
    // INFORME B: MAYOR CANTIDAD DE ASISTENTES
    // -------------------------------------------------------------------------
    int posCursoMax = -1, posCaracterMax = -1;
    int maxAsistentes = mayorAsistencia(matrizAsistencia, cantCursos, posCursoMax, posCaracterMax);

    cout << endl;
    if (posCursoMax != -1 && maxAsistentes > 0) {
        cout << "El curso con mayor cantidad de asistentes fue: " << cursos[posCursoMax].nombre
             << " (" << cursos[posCursoMax].codigo << ")"
             << " en el caracter de: " << nombresCaracter[posCaracterMax]
             << " con " << maxAsistentes << " asistentes." << endl;
    } else {
        cout << "No se registraron asistencias a los cursos." << endl;
    }

    // -------------------------------------------------------------------------
    // PUNTO C (LIBRES): GENERAR ARCHIVO NO_ASISTENTES.TXT
    // -------------------------------------------------------------------------
    ofstream archNoAsis("no_asistentes.txt");
    for (int i = 0; i < cantAsistentes; i++) {
        if (!participo[i]) {
            archNoAsis << asistentes[i].dni << " - " << asistentes[i].nya << endl;
        }
    }
    archNoAsis.close();

    return 0;
}

// -------------------------------------------------------------------------
// FUNCIONES DE BÚSQUEDA Y PROCESAMIENTO
// -------------------------------------------------------------------------

// Busca un código de curso y devuelve la posición en el vector (-1 si no existe)
int buscarCurso(Curso v[], int cant, string codigo) {
    int pos = -1;
    for (int i = 0; i < cant; i++) {
        if (v[i].codigo == codigo) {
            pos = i;
            i = cant; // Corte del bucle
        }
    }
    return pos;
}

// Busca un DNI de asistente y devuelve la posición en el vector (-1 si no existe)
int buscarAsistente(Asistente v[], int cant, int dni) {
    int pos = -1;
    for (int i = 0; i < cant; i++) {
        if (v[i].dni == dni) {
            pos = i;
            i = cant; // Corte del bucle
        }
    }
    return pos;
}

// Devuelve en el nombre el valor máximo y por parámetros por referencia los índices de curso y carácter
int mayorAsistencia(int matriz[][3], int cantCursos, int &posCurso, int &posCaracter) {
    int maximo = -1;
    for (int i = 0; i < cantCursos; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] > maximo) {
                maximo = matriz[i][j];
                posCurso = i;
                posCaracter = j;
            }
        }
    }
    return maximo;
}