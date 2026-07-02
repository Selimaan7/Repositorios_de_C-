#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


struct sedesmayor6 {
	string sede;
	int cant = 0;
};

struct servicio{
	string cod_serv;
	string sede;
	string nom_serv;
	int nivel;
	int capacidad_max;
	int dias_ultima_act;
};

struct incidentes {
	string cod_serv;
	int tipo_inci;
	int gravedad;
	int conecciones;
};


void guardarsede (string sede , sedesmayor6 mas6[], int n);

int main(int argc, char *argv[]) {
	int cant_clientes = 0;
	string auxstring;
	
	servicio servicio[999];
	incidentes incidentes[999];
	sedesmayor6 mas6 [999];
	sedesmayor6 mayormayor;
	
	ifstream archcli;
	
	archcli.open("servicios.txt", ios::in);
	
	if (archcli.fail()){
		cout << "error al abrir el archivo" << endl;
		return 0;
	}
	
	getline (archcli, servicio[cant_clientes].cod_serv);
	
	while (!archcli.eof()){
		getline (archcli, servicio[cant_clientes].sede);
		
		getline (archcli, servicio[cant_clientes].nom_serv);
		
		getline (archcli, auxstring);
		servicio[cant_clientes].nivel = stoi(auxstring);
		
		getline (archcli, auxstring);
		servicio[cant_clientes].capacidad_max = stoi(auxstring);
		
		getline (archcli, auxstring);
		servicio[cant_clientes].dias_ultima_act = stoi (auxstring);
		
		cant_clientes++;
		
		if (archcli.eof()) break;
		getline (archcli, servicio[cant_clientes].cod_serv);
	}
	archcli.close();
	
	ifstream archmov;
	int cant_mov = 0;
	archmov.open("incidentes.txt", ios::in);
	if (archmov.fail()) {
		cout << "error a abrir el archivo" << endl;
		return 0;
	}
	getline(archmov, incidentes[cant_mov].cod_serv);
	
	while (!archmov.eof()){
		getline(archmov, auxstring);
		incidentes[cant_mov].tipo_inci = stoi(auxstring);
		
		
		getline(archmov, auxstring);
		incidentes[cant_mov].gravedad = stoi(auxstring);
		
		
		getline(archmov, auxstring);
		incidentes[cant_mov].conecciones = stoi(auxstring);
		cant_mov++;
		
		if (archmov.eof()) break;
		
		getline(archmov, incidentes[cant_mov].cod_serv);
	}
	
	archmov.close();
	
	
	
	for (int i = 0; i < cant_clientes; i++){
		mas6[i].sede = servicio[i].sede;
	}
	
	cout << left << setw(10) << "Codigo" << setw(10) << "Nombre" << setw(8) << "Sede" << setw(25) << "Nivel de Criticidad" << setw(20) << "Dias sin parche" << endl;
	
	for (int i = 0; i < cant_clientes; i++){
		bool impreso = false;
		for (int j = 0;j < cant_mov; j++){
			if (servicio[i].cod_serv == incidentes[j].cod_serv && servicio[i].dias_ultima_act > 90){
				if (!impreso){
					cout << left << servicio[i].cod_serv << "   " << servicio[i].nom_serv << "   " << servicio[i].sede << "   " << servicio[i].nivel << "   " << servicio[i].dias_ultima_act << endl;
					impreso = true;
				}
				if (incidentes[j].gravedad > 6){
					guardarsede (servicio[i].sede, mas6, cant_clientes);
				}
			}
		}
	}
	
	
	for (int i = 0; i < cant_clientes; i++){
		
		if (mas6[i].cant > mayormayor.cant) mayormayor = mas6[i];
		
	}
	
	cout << "------------------------------------------------" << endl;
	
	cout << "Sede con mayor cantidad de eventos con gravedad mayor a 6 : " << mayormayor.sede << endl;
	
	
	
	
	
	
	
	
	
	return 0;
}


void guardarsede (string sede , sedesmayor6 mas6[], int n){
	for (int i = 0; i < n; i++){
		if (sede == mas6[i].sede){
			mas6[i].cant ++;
			return;
		}
	}
}

void mostrar_antiguo_incidente (servicio [], incidentes [], int );