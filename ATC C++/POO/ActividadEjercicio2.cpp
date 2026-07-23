#include <iostream>
#include <string>

using namespace std;

class Tiempo{

    private:
        int horas, minutos, segundos;
    public:
    Tiempo(int,int,int);
    Tiempo (int);
    void MostrarTiempo();
    
};


Tiempo::Tiempo (int horas, int minutos,int segundos){
    this->horas = horas;
    this->minutos = minutos;
    this->segundos = segundos;
}
Tiempo::Tiempo(int segundos){
    this->segundos = segundos;
    this->minutos = (this->segundos/60); 
    this->horas = (minutos/60);
}   

void Tiempo::MostrarTiempo() {
    cout << "Horas: " << horas << endl;
    cout << "Minutos: " << minutos << endl;
    cout << "Segundos: " << segundos << "\n \n";
}

int main(){
    Tiempo p1(14, 55, 59);
    Tiempo p2(112233);
    p1.MostrarTiempo();
    p2.MostrarTiempo();
}