#include <iostream>
#include <cstring>

using namespace std;

class Categoria {
public:
    virtual bool aprueba() const = 0;
    virtual const char* tipo() const = 0;
    virtual void mostrarNotas() const = 0;
    virtual Categoria* clonar() const = 0;
    virtual ~Categoria() {}
};

class Invitado : public Categoria {
private:
    int nota;
public:
    Invitado(int notaExamen = 0) : nota(notaExamen) {}
    bool aprueba() const override {
        return nota > 60;
    }
    const char* tipo() const override {
        return "Invitado";
    }
    void mostrarNotas() const override {
        cout << "Nota examen: " << nota;
    }
    Categoria* clonar() const override {
        return new Invitado(nota);
    }
};

class Medio : public Categoria {
private:
    int* notas;
public:
    Medio(int n1 = 0, int n2 = 0, int n3 = 0) {
        notas = new int[3];
        notas[0] = n1;
        notas[1] = n2;
        notas[2] = n3;
    }
    Medio(const Medio& other) {
        notas = new int[3];
        for (int i = 0; i < 3; ++i) {
            notas[i] = other.notas[i];
        }
    }
    Medio& operator=(const Medio& other) {
        if (this != &other) {
            delete[] notas;
            notas = new int[3];
            for (int i = 0; i < 3; ++i) {
                notas[i] = other.notas[i];
            }
        }
        return *this;
    }
    ~Medio() {
        delete[] notas;
    }
    bool aprueba() const override {
        double promedio = (notas[0] + notas[1] + notas[2]) / 3.0;
        return promedio > 70.0;
    }
    const char* tipo() const override {
        return "Medio";
    }
    void mostrarNotas() const override {
        cout << "Notas: " << notas[0] << ", " << notas[1] << ", " << notas[2];
    }
    Categoria* clonar() const override {
        return new Medio(*this);
    }
};

class Premium : public Categoria {
private:
    int* notas;
public:
    Premium(int n1 = 0, int n2 = 0, int n3 = 0, int n4 = 0, int n5 = 0) {
        notas = new int[5];
        notas[0] = n1;
        notas[1] = n2;
        notas[2] = n3;
        notas[3] = n4;
        notas[4] = n5;
    }
    Premium(const Premium& other) {
        notas = new int[5];
        for (int i = 0; i < 5; ++i) {
            notas[i] = other.notas[i];
        }
    }
    Premium& operator=(const Premium& other) {
        if (this != &other) {
            delete[] notas;
            notas = new int[5];
            for (int i = 0; i < 5; ++i) {
                notas[i] = other.notas[i];
            }
        }
        return *this;
    }
    ~Premium() {
        delete[] notas;
    }
    bool aprueba() const override {
        for (int i = 0; i < 5; ++i) {
            if (notas[i] <= 70) {
                return false;
            }
        }
        double promedio = (notas[0] + notas[1] + notas[2] + notas[3] + notas[4]) / 5.0;
        return promedio > 80.0;
    }
    const char* tipo() const override {
        return "Premium";
    }
    void mostrarNotas() const override {
        cout << "Notas: ";
        for (int i = 0; i < 5; ++i) {
            cout << notas[i];
            if (i < 4) cout << ", ";
        }
    }
    Categoria* clonar() const override {
        return new Premium(*this);
    }
};

class Alumno {
private:
    int codigo;
    char nombre[50];
    char apellido[50];
    Categoria* categoria;
public:
    Alumno(int codigo = 0, const char* nombreTexto = "", const char* apellidoTexto = "", Categoria* categoriaPtr = nullptr)
        : codigo(codigo), categoria(categoriaPtr) {
        strncpy(nombre, nombreTexto, 49);
        nombre[49] = '\0';
        strncpy(apellido, apellidoTexto, 49);
        apellido[49] = '\0';
    }
    Alumno(const Alumno& other)
        : codigo(other.codigo), categoria(other.categoria ? other.categoria->clonar() : nullptr) {
        strncpy(nombre, other.nombre, 50);
        strncpy(apellido, other.apellido, 50);
    }
    Alumno& operator=(const Alumno& other) {
        if (this != &other) {
            codigo = other.codigo;
            strncpy(nombre, other.nombre, 50);
            strncpy(apellido, other.apellido, 50);
            delete categoria;
            categoria = other.categoria ? other.categoria->clonar() : nullptr;
        }
        return *this;
    }
    ~Alumno() {
        delete categoria;
    }
    bool aprueba() const {
        return categoria ? categoria->aprueba() : false;
    }
    void mostrar() const {
        cout << "Codigo: " << codigo
             << ", Nombre: " << nombre << " " << apellido
             << ", Categoria: " << (categoria ? categoria->tipo() : "Sin categoria")
             << ", ";
        if (categoria) {
            categoria->mostrarNotas();
        }
        cout << ", Aprueba: " << (aprueba() ? "Si" : "No") << "\n";
    }
    int getCodigo() const {
        return codigo;
    }
    const char* getTipoCategoria() const {
        return categoria ? categoria->tipo() : "Sin categoria";
    }
    void cambiarCategoria(Categoria* nuevaCategoria) {
        delete categoria;
        categoria = nuevaCategoria;
    }
};

class Curso {
private:
    Alumno* alumnos;
    int cantidad;
    int capacidad;
    void crecer() {
        int nuevaCapacidad = capacidad * 2;
        Alumno* nuevoArreglo = new Alumno[nuevaCapacidad];
        for (int i = 0; i < cantidad; ++i) {
            nuevoArreglo[i] = alumnos[i];
        }
        delete[] alumnos;
        alumnos = nuevoArreglo;
        capacidad = nuevaCapacidad;
    }
public:
    Curso() : cantidad(0), capacidad(10) {
        alumnos = new Alumno[capacidad];
    }
    ~Curso() {
        delete[] alumnos;
    }
    void agregarAlumno(const Alumno& alumno) {
        if (cantidad == capacidad) {
            crecer();
        }
        alumnos[cantidad++] = alumno;
    }
    void listarAprobados() const {
        cout << "Alumnos que aprobaron el curso:\n";
        for (int i = 0; i < cantidad; ++i) {
            if (alumnos[i].aprueba()) {
                alumnos[i].mostrar();
            }
        }
    }
    Alumno* buscarAlumno(int codigo) {
        for (int i = 0; i < cantidad; ++i) {
            if (alumnos[i].getCodigo() == codigo) {
                return &alumnos[i];
            }
        }
        return nullptr;
    }
};

int main() {
    Curso curso;

    curso.agregarAlumno(Alumno(1, "Juan", "Perez", new Invitado(65)));
    curso.agregarAlumno(Alumno(2, "Ana", "Gomez", new Medio(75, 80, 72)));
    curso.agregarAlumno(Alumno(3, "Luis", "Martinez", new Premium(82, 85, 90, 88, 81)));

    curso.listarAprobados();

    Alumno* alumno = curso.buscarAlumno(1);
    if (alumno != nullptr && strcmp(alumno->getTipoCategoria(), "Invitado") == 0) {
        cout << "\nCambiando categoria del alumno 1 a Medio...\n";
        alumno->cambiarCategoria(new Medio(72, 74, 78));
    }

    curso.listarAprobados();
    return 0;
}