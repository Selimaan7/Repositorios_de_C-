/*Realice un programa en C++, de tal manera que se contruya una solucion 
para la jerarquia (herencia) de clases mostrada en la siguiente figura.*/

#include <iostream>
#include <string>

using namespace std;

class Persona{
    private:
        string nombre, apellido;
        int edad;
    public:
        Persona(string, string, int);
        void MostrarPersona();
};

class Empleado : public Persona{
    private:
        string CodigoEmpleado;
        float salario;
    public:
        Empleado(string, string, int, string, float);
        void MostrarEmpleado();
};


class Estudiante : public Persona{
    private: 
        float nota1, nota2, nota3;
    public:
    Estudiante(string, string, int, float, float, float);
    double Promedio();
    void mostrarEstudiante();
};

class Universitario : public Estudiante{
    private:
        string CodigoMatricula;
    public:
        Universitario(string, string, int, float, float, float, string);
        void MostrarUniversitario();
};


Persona::Persona (string nombre, string apellido, int edad){
    this->edad = edad;
    this->apellido = apellido;
    this->nombre = nombre;
}

void Persona::MostrarPersona (){
    cout << "Nombre y apellido: " << nombre << " " << apellido << endl;
    cout << "Edad: " << edad << endl;
}

Empleado::Empleado (string nombre, string apellido, int edad, string CodigoEmpleado, float salario) : Persona (nombre, apellido, edad){
    this->CodigoEmpleado = CodigoEmpleado;
    this->salario = salario;
}
void Empleado :: MostrarEmpleado(){
    MostrarPersona();

    cout << "El codigo del empleado es: " << CodigoEmpleado;
    cout << "\nEl salario del empleado es: " << salario << endl; 
}
Estudiante :: Estudiante(string nombre, string apellido, int edad, float nota1, float nota2, float nota3) : Persona (nombre, apellido, edad){
    this->nota1 = nota1;
    this->nota2 = nota2;
    this->nota3 = nota3;
}

double Estudiante :: Promedio (){
    return (nota1 + nota2 + nota3) / 3;
}

void Estudiante :: mostrarEstudiante (){
    MostrarPersona();
    cout << "Las notas del estudiante son: "<< "\n" << "1er nota: " << nota1 << "\n" << "2da nota" << nota2 << "3er nota" << nota3 << endl;
    cout << "\nEl promedio de las notas es: " << Promedio();
}

Universitario :: Universitario (string nombre, string apellido, int edad, float nota1, float nota2, float nota3, string codigomatricula) : Estudiante (nombre, apellido, edad, nota1, nota2, nota3){
    this->CodigoMatricula = codigomatricula;
}

int main(){
    Empleado E1("Emma", "Seli", 20, "30DAS", 1123.321);

    E1.MostrarPersona();

    cout << "\n\n";

    E1.MostrarEmpleado();
    return 0;
}