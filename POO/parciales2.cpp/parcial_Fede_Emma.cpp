#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <numeric>

using namespace std;

class Cliente{
    private:

        int id;
        char nombre[200];
        vector<string> emails;

    public:
        Cliente();
        Cliente(int id, char nombre[200]){
            this->id = id;
            strcpy(this->nombre, nombre);
        }

        void AgregarEmail(string email){
            emails.push_back(email);
        }

        void enviarCorreo(){
            for (int i = 0; i < emails.size(); i++){
                ofstream arch(emails[i]);

                if (arch.is_open()){
                    arch << "Hola " << nombre << "! Bienvenido al sistema de notificaciones " << endl;
                
                    arch.close();
                }
            }
        }
        int getId()const {
            return id;
        }
        int cantidadEmail()const {
            return emails.size();
        }
        string getNombre()const {
            return string(nombre);
        }
        vector<string> getEmail(){
            return emails;
        }
        bool sinEmails(){
            return emails.empty();
        }
};

class Empresa{
    private:

        struct cliente{
            int id;
            char nombre[200];
        };

        struct Email{
            int id_cliente;
            char email[200];
        };
        vector<Cliente> clientes;

    public:
        
        void leerClientes(){
            ifstream clie("clientes.bin", ios::binary);
            if (clie.fail()){
                cout << "El archivo no se puedo abrir correctamente." << endl;
                return;
            }else{
                cliente aux;

                while (clie.read((char*)&aux, sizeof(aux))){

                    Cliente C(aux.id, aux.nombre);
                    clientes.push_back(C);
                    
                    cout << "Cliente cargado: " << aux.id << " - " << aux.nombre << endl;
                }
            }        
        }
        
        void leerEmails(){
            ifstream mail;
            mail.open("email.bin", ios::binary);
            if (mail.fail()){
                cout << "El archivo de email fallo al abrirse" << endl;
            }else {
                Email aux;
                while (mail.read((char*)&aux, sizeof(aux))){
                    Cliente* c = buscarcliente(aux.id_cliente);

                    if (c != nullptr){
                        c->AgregarEmail(string(aux.email));
                    }

                    cout << "Email para ID: " << aux.id_cliente << " - " << aux.email << endl;

                }
                mail.close();
            }
        }
        void enviarEmail(){
            for (int i = 0; i<clientes.size(); i++){
                clientes[i].enviarCorreo();
            }
        }
        
        Cliente* buscarcliente(int id){

            for (int i = 0; i<clientes.size(); i++){
                if (clientes[i].getId() == id){
                    return &clientes[i];
                }
            }
            return NULL;
        }

        vector<Cliente>clientesconmasemail(){
            vector <Cliente> vectorclientesconemails;

            if (clientes.empty()){
                return vectorclientesconemails;
            }

            auto itMax= max_element(clientes.begin(), clientes.end(), [](Cliente a, Cliente b) {
                return a.cantidadEmail() < b.cantidadEmail();
            });

            int maximo = itMax->cantidadEmail();

            for (int i = 0; i<clientes.size(); i++){
                cout << clientes[i].getNombre() << clientes[i].cantidadEmail() << endl;
                

                if (clientes[i].cantidadEmail() == maximo){
                    vectorclientesconemails.push_back(clientes[i]);
                }
            }
            return vectorclientesconemails;
        }

        vector<string> obtenerEmailsRepetidos(){
            map <string, int> cantidad;

            for (int i = 0; i<clientes.size(); i++){
                vector <string> emails = clientes[i].getEmail();
                for (int j = 0; j<emails.size(); j++){
                    ++cantidad[emails[j]];
                }
            }

            vector<string> repetidos;
            for (pair<string, int> par : cantidad){
                if (par.second > 1){
                    repetidos.push_back(par.first);
                }
            }
            return repetidos;
        }

        vector<Cliente>obtenerClientesSinEmail(){
            
            vector <Cliente> clientesSinMail;
            for (int i = 0; i<clientes.size(); i++){
                if (clientes[i].sinEmails()){
                    clientesSinMail[i] = clientes[i]; 
                }
            }
            return clientesSinMail;
        }

        int totalEmailsAEnviar(){
            vector <int> cantidades;

            for (int i = 0; i<clientes.size(); i++){
                cantidades[i] = clientes[i].cantidadEmail();
            }

            return accumulate(cantidades.begin(), cantidades.end(),0);
        }
};

int main(){
    Empresa emp;

    emp.leerClientes();
    emp.leerEmails();
    emp.enviarEmail();


    cout << "Se leyeron todos los clientes" << endl;

    vector<Cliente>mayor= emp.clientesconmasemail();
    cout << "Los clientes con mas emails son: " << endl;
    for (int i = 0; i<mayor.size();i++){
        cout << mayor[i].getNombre() << "--->" << mayor[i].cantidadEmail() << endl; 
    }

    vector <string> emailsrepetidos = emp.obtenerEmailsRepetidos();
    cout << "Los emails repetidos son: " << endl;
    for (int i = 0; i<emailsrepetidos.size(); i++){
        cout << emailsrepetidos[i] << endl;
    }

    vector <Cliente> sinEmail = emp.obtenerClientesSinEmail();
    cout << "Los clientes sin Email son: " << endl;
    for (int i = 0; i <sinEmail.size();i++){
        cout << sinEmail[i].getNombre() << ", no tiene mail cargado."<<endl;
    }

    cout << "Total de emails a enviar: " << emp.totalEmailsAEnviar() << endl;

    return 0;
}