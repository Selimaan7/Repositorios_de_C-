#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class contacto {
    private:
    string tipo_contacto;
    string valor;

    public:
        contacto(string tipo, string valor) : tipo_contacto(tipo), valor(valor){}
        string getTipo() const{
            return tipo_contacto;
        }
        string getValor() const{
            return valor;
        }
        friend ostream& operator<<(ostream& os, const contacto& c) {
        // Construimos el formato que queremos mostrar
        os << "Tipo: " << c.tipo_contacto << ", valor: " << c.valor;
        // IMPORTANTE: Retornar el flujo para permitir el encadenamiento
        return os;
        }
};


class Persona {
    private:
        string nombre;
        string apellido;
        string direccion;
        vector<contacto> contactos;

    public:
        Persona(string nombre, string apellido, string direccion, contacto contactos) : nombre(nombre), apellido(apellido), direccion(direccion), contactos(contactos){}
        Persona(string nombre, string apellido, string direccion, int cant_contactos) : nombre(nombre), apellido(apellido), direccion(direccion){
            string TipoDeContacto;
            string valor;
            for (int i = 0; i<cant_contactos; i++){
                cout << "Tipo de contacto: "; 
                cin >> TipoDeContacto;    
                
                cout << "\nCual es el valor de contacto: ";
                cin >> valor;

                cout << "\n \n ";

                contacto contacto(TipoDeContacto, valor);
                contactos.push_back(contacto);
            }
        }

        friend ostream& operator<<(ostream& os, const Persona& p) {
            // Construimos el formato que queremos mostrar
            os << "Nombre: " << p.nombre << ", Apellido: " << p.apellido << ", Direccion: "<< p.direccion << "\n \n";

            // IMPORTANTE: Retornar el flujo para permitir el encadenamiento

            os << "Los contactos son: " << endl;
            for (int i = 0; i < p.contactos.size(); i++){
                os << p.contactos[i];
                os << "\n";
        }


        return os;
        }
        string getNombre() const {
            return nombre;
        }   

        string getApellido() const {
            return apellido;
        }

        string getDireccion() const {
            return direccion;
        }

        const vector<contacto>& getContactos() const {
            return contactos;
        }

};

void escribirString(ofstream& archivo, string texto) {
    int cantidad = texto.size();

    archivo.write((char*)&cantidad, sizeof(cantidad));
    archivo.write(texto.c_str(), cantidad);
}

class Agenda{
    private:
        vector <Persona> Personas;
        int cantidad_personas;
    public:
        Agenda(int cant_perso){
            string nombre;
            string apellido;
            string direccion;
            int cant;
            for (int i = 0; i<cant_perso; i++){
                cout << "\nIngrese el nombre de la persona: ";
                cin >> nombre;

                cout << "\nIngrese el apellido de la persona: ";
                cin >> apellido;

                cout << "\nIngrese la direccion: ";
                cin.ignore();
                getline(cin, direccion);

                cout << "\nIngrese la cantidad de contactos que tiene: ";
                cin >> cant;

                Persona humano(nombre, apellido, direccion, cant);
                Personas.push_back(humano);
            }
        }

        friend ostream& operator<<(ostream& os, const Agenda& a){
            os << "La agenda esta compuesta por: " << endl;

            for (int i = 0; i<a.Personas.size(); i++){
                os << a.Personas[i];
                os << "\n";
            }
            return os;
        }

        void GuardarArchivos (string nombreArchivo){
            ofstream arch(nombreArchivo.c_str, ios::binary);
            
            if (arch.fail()){
                cout << "No se peudo crear/abrir el archivo." << endl;
                return;
            }

            int cantidadPersonas = Personas.size();

            arch.write((char*)&cantidad_personas, sizeof(cantidad_personas));
            for (int i = 0; i<Personas.size(); i++){
                escribirString (arch, Personas[i].getNombre());
                escribirString (arch, Personas[i].getApellido());
                escribirString (arch, Personas[i].getDireccion());

                int cantidadDeContactos = Personas[i].getContactos().size();
                arch.write((char*)&cantidadDeContactos, sizeof(cantidadDeContactos));

                for (int j = 0; j<Personas[i].getContactos().size(); j++){
                    escribirString(arch, Personas[i].getContactos()[j].getTipo());
                    escribirString(arch, Personas[i].getContactos()[j].getValor());

                }

                
            }   
            
            arch.close();

            cout << "Agenda guardada correctamente" << endl;
        }
    
      
};



int main() {
    int cantidad;

    cout << "Cuantas personas desea cargar: ";
    cin >> cantidad;

    Agenda agenda(cantidad);

    agenda.GuardarArchivos("agenda.txt");

    return 0;
}