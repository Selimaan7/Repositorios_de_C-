#include <iostream>
#include <cstring>

using namespace std;


class categoria{
public:
    virtual bool aprueba() = 0;
    virtual const char* gettipo() const = 0;
    virtual void mostrarnotas() = 0;
    virtual categoria* clonar() = 0;
    virtual void setnotas(float) = 0;
    virtual ~categoria() {}
};

class invitado : public categoria{
private:
    float nota;
public:
    invitado(int notaexamen = 0) : nota (notaexamen){}
    bool aprueba() override{
        return nota > 60;
    }
    const char* gettipo()const override{
        return "invitado";
    }
    void mostrarnotas()override{
        cout << "Nota Examen" << this->nota;
    }
    void setnotas(float n1) override{
        nota = n1;
    }
    categoria* clonar() override{
        return new invitado (nota);
    }
};

class medio : public categoria{
private:
    float* notas;
    int cantnotas = 0;
public:
    medio (float nota1 = 0, float nota2 = 0, float nota3 = 0){
        notas = new float[3];
        notas[0] = nota1;
        notas[1] = nota2;
        notas[2] = nota3;
    }
    medio (float notas[]){
        for (int i = 0; i<3; i++){
            setnotas(notas[i]);
        }
    }
    medio (medio& other){
        notas = new float[3];
        for (int i = 0; i<3; i++){
            notas[i] = other.notas[i];
        }
    }

    medio& operator=(medio& other){
        if (this != &other){
            delete[] notas;
            notas = new float[3];
            for (int i = 0; i<3; i++){
                notas[i] = other.notas[i];
            }
        }
        return *this;
    }
    bool aprueba() override{
        return promedio() > 70;
    }
    float promedio(){
        return (notas[0]+ notas[1] + notas[2]) / 3;
    }
    const char* gettipo ()const override{
        return "Medio";
    }
    void setnotas(float nota){
        if(cantnotas < 3){     
        notas[cantnotas] = nota;
        cantnotas ++;
        }
    }

    void mostrarnotas() override{
        cout << "las notas son: " << notas[0] << "," << notas[1] << "," << notas[2] << endl;
    }
    categoria* clonar() override{
        return new medio(*this);
    }
    ~medio(){
        delete[] notas;
    }
};

class premium : public categoria{
private:
    float* notas;
    int cantnotas = 0;
public:
    premium(float nota1 = 0, float nota2 = 0, float nota3 = 0, float nota4 = 0, float nota5 = 0){
        notas= new float[5];
        notas[0] = nota1;
        notas[1] = nota2;
        notas[2] = nota3;
        notas[3] = nota4;
        notas[4] = nota5;
    }

    premium(float notas[]){
        for (int i = 0; i < 5; i++){
            setnotas(notas[i]);
        }
    }
    
    premium& operator=(premium& other){
        if (this != &other){
            delete[] notas;
            notas = new float[5];
            for (int i = 0; i<5; i++){
                notas[i] = other.notas[i];
            }
        }
        return *this;
    }
    
    void setnotas(float nota) override{
        if (cantnotas < 5){
            notas[cantnotas] = nota;
            cantnotas ++;
        }
    }
    
    bool aprueba(){
        for(int i = 0; i<5; i++){
            if (notas[i] <=70) return false;
        }
        return promedio() > 70;
    }

    float promedio(){
        return (notas[0] + notas[1] + notas[2] + notas[3] + notas[4]) / 3;
    }

    const char* gettipo() const override{
        return "Premium";
    }
    
    void mostrarnotas() override{
        cout << "las notas son: " << notas[0] << "," << notas[1] << "," << notas[2] << "," << notas[3] << "," << notas[4] << endl;
    }
    
    categoria* clonar() override {
        return new premium(*this);
    }
    
    ~premium(){
        delete[] notas;
    }
};

class alumno{
private:
    char* nombre;
    char* apellido;
    int codigo;
    categoria* categori;
    
public:
        alumno(int codigo = 0, const char* nombre = "", const char* apellido = "", categoria* categoriaPtr = nullptr)
        : codigo(codigo), categori(categoriaPtr) {
        this->nombre = new char[strlen(nombre) + 1];
        strcpy(this->nombre, nombre);
        this->apellido = new char[strlen(apellido) + 1];
        strcpy(this->apellido, apellido);
    }
    alumno (const alumno& other): codigo (other.codigo), categori (other.categori ? other.categori->clonar() : nullptr){
        nombre = new char[strlen(other.nombre) + 1];
        strcpy(nombre, other.nombre);
        apellido = new char[strlen(other.apellido) + 1];
        strcpy(apellido, other.apellido);
    }
    alumno& operator=(const alumno& other){
        if(this!= &other){
            codigo = other.codigo;
            delete[] nombre;
            delete[] apellido;
            nombre = new char[strlen(other.nombre) + 1];
            apellido = new char[strlen(other.apellido) + 1];
            strcpy(nombre, other.nombre);
            strcpy(apellido, other.apellido);   
            delete categori;
            categori = other.categori ? other.categori->clonar() : nullptr;
        }
        return *this;
    }
    ~alumno () {
        delete categori;
    }
    char* getnombre(){
        return nombre;
    }
    bool aprueba() {
        return categori ? categori->aprueba() : false;
    }
    void mostrar() {
        cout << "Codigo: " << codigo
        << ", Nombre: " << nombre << " " << apellido
        << ", Categoria: " << (categori ? categori->gettipo() : "Sin categoria") << ",";
        if (categori){
            categori->mostrarnotas();
        }
        cout << "Aprueba: " << (aprueba() ? "Si" : "No") << "\n";
    }
    int getcodigo() const{
        return codigo;
    }
    const char* gettipocategoria(){
        return categori ? categori->gettipo() : "Sin categoria";
    }
    void cambiarcategoria(categoria* nuevacategoria){
        delete categori;
        categori = nuevacategoria;
    }
};

class curso{
private:
    alumno* alumnos;
    int cantidad;
    int capacidad;
    void crecer(){
        int nuevacapacidad = capacidad *2;
        alumno* nuevoarreglo = new alumno[nuevacapacidad];
        for (int i = 0; i< cantidad; i++){
            nuevoarreglo[i] = alumnos [i]; 
        }
        delete[] alumnos;
        alumnos = nuevoarreglo;
        capacidad = nuevacapacidad;
    }
public:
    curso(): cantidad (0), capacidad(10){
        alumnos = new alumno[capacidad];
    }
    ~curso(){
        delete[] alumnos;
    }

    void agregaralumno(const alumno& alumno){
        if (cantidad == capacidad){
            crecer();
        }
        alumnos[cantidad++] = alumno;
    }
    void listaaprobados() const{
        cout << "alumnos que aprobaron el curso\n";
        for (int i = 0; i<cantidad; i++){
            if (alumnos[i].aprueba()){
                alumnos[i].mostrar();
            }
        }
    }
    alumno* buscaralumno (int codigo){
        for (int i = 0; i<cantidad; i++){
            if (alumnos[i].getcodigo() == codigo){
                return &alumnos[i];
            }
        }
        return nullptr;
    }
};

int main(){
    curso cur;

    cur.agregaralumno(alumno(1, "Emma", "Seli", new invitado(70)));
    cur.agregaralumno(alumno(2, "Yaz", "sch", new premium(71, 80, 90, 10,80)));
    cur.agregaralumno(alumno(3, "Bere", "sch", new medio(70, 40, 100)));
    cur.agregaralumno(alumno(4, "Vir", "and", new invitado(10)));

    cur.listaaprobados();

    alumno* alumno = cur.buscaralumno(1);
    if (alumno != nullptr && strcmp(alumno->gettipocategoria(), "Invitado") == 0){
        cout << "\n cambiando la categoria el alumno: " << alumno->getnombre() << " a medio\n";
        alumno->cambiarcategoria(new medio(70,70,70));
    }
    cur.listaaprobados();
    return 0;
}
