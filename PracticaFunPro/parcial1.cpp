#include <iostream>
#include <fstream>
#include <string>

using namespace std;


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


void mostrar_antiguo_incidente(){
	
zint main(int argc, char *argv[]) {
	int i = 0;
	string auxstring;
	
	servicio servicio[999];
	incidentes incidentes[999];
	
	
	ifstream archcli;
	
	archcli.open("servicios.txt", ios::in);
	
	if (archcli.fail()){
		cout << "error al abrir el archivo" << endl;
		return 0;
	}
	
	getline (archcli, servicio[i].cod_serv);
	
	while (!archcli.eof()){
		getline (archcli, servicio[i].sede);
		
		getline (archcli, servicio[i].nom_serv);
		
		getline (archcli, auxstring);
		servicio[i].nivel = stoi(auxstring);
		
		getline (archcli, auxstring);
		servicio[i].capacidad_max = stoi(auxstring);
		
		getline (archcli, auxstring);
		servicio[i].dias_ultima_act = stoi (auxstring);
		
		i++;
		
		if (archcli.eof()) break;
		getline (archcli, servicio[i].cod_serv);
	}
	archcli.close();
	
	ifstream archmov;
	int j = 0;
	archmov.open("movimientos.txt", ios::in);

	getline(archmov, incidentes[j].cod_serv);
	
	while (!archmov.eof()){
		getline(archmov, auxstring);
		incidentes[j].tipo_inci = stoi(auxstring);
		
		
		getline(archmov, auxstring);
		incidentes[j].gravedad = stoi(auxstring);
		
		
		getline(archmov, auxstring);
		incidentes[j].conecciones = stoi(auxstring);
		j++;
		
		if (archmov.eof()) break;
		
		getline(archmov, incidentes[j].cod_serv);
	}
	
	archmov.close();
	
	
	
	
	
	
	
	return 0;
}

