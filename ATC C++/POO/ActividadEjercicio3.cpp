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
    float Promedio(int, int, int);
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
    cout << "Nombre y apellido: " << nombre << apellido << endl;
    cout << "Edad: " << edad;
}

Empleado::Empleado (string nombre, string apellido, int edad, string CodigoEmpleado, float salario) : Persona (nombre, apellido, edad){
    this->CodigoEmpleado = CodigoEmpleado;
    this->salario = salario;
}

int main(){



    return 0;
}