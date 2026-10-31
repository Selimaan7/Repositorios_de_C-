// CursoSyS: registro de alumnos y aprobacion del curso.
#include <iostream>
#include <cstring>

using namespace std;

class TipoAlumno {
public:
    virtual bool aprueba() const = 0;
    virtual const char* nombreTipo() const = 0;
    virtual void mostrarNotas() const = 0;
    virtual TipoAlumno* clonar() const = 0;
    virtual ~TipoAlumno() {}
};

class AlumnoInvitado : public TipoAlumno {
private:
    float nota;

public:
    AlumnoInvitado(float notaExamen = 0) : nota(notaExamen) {}

    bool aprueba() const override {
        return nota > 60;
    }

    const char* nombreTipo() const override {
        return "Invitado";
    }

    void mostrarNotas() const override {
        cout << "Nota del examen: " << nota;
    }

    TipoAlumno* clonar() const override {
        return new AlumnoInvitado(nota);
    }
};

class AlumnoMedio : public TipoAlumno {
private:
    float* notas;

public:
    AlumnoMedio(float nota1 = 0, float nota2 = 0, float nota3 = 0) {
        notas = new float[3];
        notas[0] = nota1;
        notas[1] = nota2;
        notas[2] = nota3;
    }

    AlumnoMedio(const AlumnoMedio& otro) {
        notas = new float[3];
        for (int i = 0; i < 3; i++) {
            notas[i] = otro.notas[i];
        }
    }

    AlumnoMedio& operator=(const AlumnoMedio& otro) {
        if (this != &otro) {
            for (int i = 0; i < 3; i++) {
                notas[i] = otro.notas[i];
            }
        }
        return *this;
    }

    ~AlumnoMedio() {
        delete[] notas;
    }

    float promedio() const {
        return (notas[0] + notas[1] + notas[2]) / 3;
    }

    bool aprueba() const override {
        return promedio() > 70;
    }

    const char* nombreTipo() const override {
        return "Medio";
    }

    void mostrarNotas() const override {
        cout << "Notas: " << notas[0] << ", " << notas[1] << ", " << notas[2]
             << " | Promedio: " << promedio();
    }

    TipoAlumno* clonar() const override {
        return new AlumnoMedio(*this);
    }
};

class AlumnoPremium : public TipoAlumno {
private:
    float* notas;

public:
    AlumnoPremium(float nota1 = 0, float nota2 = 0, float nota3 = 0,
                  float nota4 = 0, float nota5 = 0) {
        notas = new float[5];
        notas[0] = nota1;
        notas[1] = nota2;
        notas[2] = nota3;
        notas[3] = nota4;
        notas[4] = nota5;
    }

    AlumnoPremium(const AlumnoPremium& otro) {
        notas = new float[5];
        for (int i = 0; i < 5; i++) {
            notas[i] = otro.notas[i];
        }
    }

    AlumnoPremium& operator=(const AlumnoPremium& otro) {
        if (this != &otro) {
            for (int i = 0; i < 5; i++) {
                notas[i] = otro.notas[i];
            }
        }
        return *this;
    }

    ~AlumnoPremium() {
        delete[] notas;
    }

    float promedio() const {
        float suma = 0;
        for (int i = 0; i < 5; i++) {
            suma += notas[i];
        }
        return suma / 5;
    }

    bool aprueba() const override {
        for (int i = 0; i < 5; i++) {
            if (notas[i] <= 70) {
                return false;
            }
        }
        return promedio() > 80;
    }

    const char* nombreTipo() const override {
        return "Premium";
    }

    void mostrarNotas() const override {
        cout << "Notas: ";
        for (int i = 0; i < 5; i++) {
            cout << notas[i];
            if (i < 4) {
                cout << ", ";
            }
        }
        cout << " | Promedio: " << promedio();
    }

    TipoAlumno* clonar() const override {
        return new AlumnoPremium(*this);
    }
};

class Alumno {
private:
    int codigo;
    char nombre[50];
    char apellido[50];
    TipoAlumno* tipo;

    void copiarTexto(char destino[], const char* origen) {
        strncpy(destino, origen, 49);
        destino[49] = '\0';
    }

public:
    Alumno(int codigoAlumno = 0, const char* nombreAlumno = "",
           const char* apellidoAlumno = "", TipoAlumno* tipoAlumno = 0)
        : codigo(codigoAlumno), tipo(tipoAlumno) {
        copiarTexto(nombre, nombreAlumno);
        copiarTexto(apellido, apellidoAlumno);
    }

    Alumno(const Alumno& otro)
        : codigo(otro.codigo),
          tipo(otro.tipo ? otro.tipo->clonar() : 0) {
        strcpy(nombre, otro.nombre);
        strcpy(apellido, otro.apellido);
    }

    Alumno& operator=(const Alumno& otro) {
        if (this != &otro) {
            TipoAlumno* nuevoTipo = otro.tipo ? otro.tipo->clonar() : 0;
            codigo = otro.codigo;
            strcpy(nombre, otro.nombre);
            strcpy(apellido, otro.apellido);
            delete tipo;
            tipo = nuevoTipo;
        }
        return *this;
    }

    ~Alumno() {
        delete tipo;
    }

    int getCodigo() const {
        return codigo;
    }

    const char* getNombre() const {
        return nombre;
    }

    const char* getTipo() const {
        return tipo ? tipo->nombreTipo() : "Sin categoria";
    }

    bool aprueba() const {
        return tipo != 0 && tipo->aprueba();
    }

    void cambiarTipo(TipoAlumno* nuevoTipo) {
        delete tipo;
        tipo = nuevoTipo;
    }

    void mostrar() const {
        cout << "Codigo: " << codigo
             << " | Alumno: " << nombre << " " << apellido
             << " | Tipo: " << getTipo() << " | ";

        if (tipo) {
            tipo->mostrarNotas();
        }

        cout << " | Estado: " << (aprueba() ? "Aprobado" : "Desaprobado")
             << endl;
    }
};

class Curso {
private:
    Alumno* alumnos;
    int cantidad;
    int capacidad;

    void ampliar() {
        int nuevaCapacidad = capacidad * 2;
        Alumno* nuevosAlumnos = new Alumno[nuevaCapacidad];

        for (int i = 0; i < cantidad; i++) {
            nuevosAlumnos[i] = alumnos[i];
        }

        delete[] alumnos;
        alumnos = nuevosAlumnos;
        capacidad = nuevaCapacidad;
    }

public:
    Curso(int capacidadInicial = 5)
        : cantidad(0), capacidad(capacidadInicial) {
        alumnos = new Alumno[capacidad];
    }

    ~Curso() {
        delete[] alumnos;
    }

    void agregarAlumno(const Alumno& nuevoAlumno) {
        if (cantidad == capacidad) {
            ampliar();
        }
        alumnos[cantidad] = nuevoAlumno;
        cantidad++;
    }

    Alumno* buscarAlumno(int codigo) {
        for (int i = 0; i < cantidad; i++) {
            if (alumnos[i].getCodigo() == codigo) {
                return &alumnos[i];
            }
        }
        return 0;
    }

    void listarAprobados() const {
        cout << "\n--- Alumnos que aprobaron el curso ---" << endl;
        bool hayAprobados = false;

        for (int i = 0; i < cantidad; i++) {
            if (alumnos[i].aprueba()) {
                alumnos[i].mostrar();
                hayAprobados = true;
            }
        }

        if (!hayAprobados) {
            cout << "No hay alumnos aprobados." << endl;
        }
    }
};

int main() {
    Curso curso;

    curso.agregarAlumno(
        Alumno(1, "Juan", "Perez", new AlumnoInvitado(65)));
    curso.agregarAlumno(
        Alumno(2, "Ana", "Gomez", new AlumnoMedio(75, 80, 72)));
    curso.agregarAlumno(
        Alumno(3, "Luis", "Martinez",
               new AlumnoPremium(82, 85, 90, 88, 81)));
    curso.agregarAlumno(
        Alumno(4, "Sofia", "Lopez", new AlumnoInvitado(50)));

    curso.listarAprobados();

    Alumno* alumno = curso.buscarAlumno(1);
    if (alumno != 0 && strcmp(alumno->getTipo(), "Invitado") == 0) {
        cout << "\nEl alumno " << alumno->getNombre()
             << " cambia de Invitado a Medio." << endl;
        alumno->cambiarTipo(new AlumnoMedio(72, 74, 78));
    }

    curso.listarAprobados();
    return 0;
}