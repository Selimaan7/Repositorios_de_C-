#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// -------------------------------------------------------------------------
// ESTRUCTURAS
// -------------------------------------------------------------------------
// Guarda los datos de cada pasajero registrado en el padron.
struct pasajero {
	int dni;
	string apellido;
	string nombre;
	int tipo;
};
// Guarda los datos de cada linea de colectivo.
struct linea {
	string codigo;
	string descripcion;
	int viajesS1;   // Cantidad de viajes en el 1er semestre.
	int viajesS2;   // Cantidad de viajes en el 2do semestre.
};
// Guarda los datos acumulados de cada estudiante (tipo 4) que viajo en el año.
struct estudiante {
	int dni;
	string apellido;
	string nombre;
	int viajesS1;
	int viajesS2;
};

int buscarDNI(pasajero pas[], int cant, int dni); // Busca un DNI en el vector de pasajeros.
int buscarLinea(linea lin[], int cant, string codigo); // Busca un codigo de linea.
int buscarEstudiante(estudiante est[], int cant, int dni); // Busca un DNI en el vector de estudiantes.
int obtenerSemestre(string fecha); // Devuelve 1 o 2 segun el mes de la fecha DDMMAAAA.
void ordenarTop(estudiante est[], int cant); // Ordena estudiantes de mayor a menor por cantidad de viajes.

int main() {
	pasajero pasajeros[500];      // Padron de pasajeros (pasajeros_oroverde.txt).
	linea lineas[100];            // Lineas de colectivo (LINEAS_TRANSPORTE.TXT).
	estudiante estudiantes[500];  // Estudiantes tipo 4 que efectivamente viajaron.
	
	int cantPasajeros = 0;
	int cantLineas = 0;
	int cantEstudiantes = 0;
	
	string fecha, codLinea;
	int dniViaje;
	int posPas, posLin, posEst;
	
	// -------------------------------------------------------------------------
	// LECTURA DEL ARCHIVO pasajeros_oroverde.txt
	// -------------------------------------------------------------------------
	ifstream archiPasajeros;
	archiPasajeros.open("pasajeros_oroverde.txt");
	
	if(archiPasajeros.fail()) {
		cout << "Error en la apertura del archivo pasajeros_oroverde.txt." << endl;
	}
	else {
		archiPasajeros >> pasajeros[cantPasajeros].dni;
		while(!archiPasajeros.eof()) {
			archiPasajeros.get();
			getline(archiPasajeros, pasajeros[cantPasajeros].apellido);
			getline(archiPasajeros, pasajeros[cantPasajeros].nombre);
			archiPasajeros >> pasajeros[cantPasajeros].tipo;
			cantPasajeros++;
			archiPasajeros >> pasajeros[cantPasajeros].dni;
		}
	}
	archiPasajeros.close();
	
	// -------------------------------------------------------------------------
	// LECTURA DEL ARCHIVO LINEAS_TRANSPORTE.TXT
	// -------------------------------------------------------------------------
	ifstream archiLineas;
	archiLineas.open("LINEAS_TRANSPORTE.TXT");
	
	if(archiLineas.fail()) {
		cout << "Error en la apertura del archivo LINEAS_TRANSPORTE.TXT." << endl;
	}
	else {
		archiLineas >> lineas[cantLineas].codigo;
		while(!archiLineas.eof()) {
			archiLineas.ignore();
			getline(archiLineas, lineas[cantLineas].descripcion);
			lineas[cantLineas].viajesS1 = 0;
			lineas[cantLineas].viajesS2 = 0;
			cantLineas++;
			archiLineas >> lineas[cantLineas].codigo;
		}
	}
	archiLineas.close();
	
	// -------------------------------------------------------------------------
	// CARGA POR TECLADO DE LOS VIAJES DE LOS ESTUDIANTES (TIPO 4)
	// Fin de la carga: fecha = "31129999"
	// -------------------------------------------------------------------------
	cout << "Ingrese fecha del viaje (DDMMAAAA) o 31129999 para finalizar: ";
	cin >> fecha;
	
	while(fecha != "31129999") {
		cin >> dniViaje;
		cin >> codLinea;
		
		posLin = buscarLinea(lineas, cantLineas, codLinea);
		posPas = buscarDNI(pasajeros, cantPasajeros, dniViaje);
		
		// Solo se procesan viajes de pasajeros que figuren en el padron como tipo 4
		// (universitario) y cuya linea de colectivo exista.
		if(posLin != -1 && posPas != -1 && pasajeros[posPas].tipo == 4) {
			
			posEst = buscarEstudiante(estudiantes, cantEstudiantes, dniViaje);
			if(posEst == -1) {
				estudiantes[cantEstudiantes].dni = dniViaje;
				estudiantes[cantEstudiantes].apellido = pasajeros[posPas].apellido;
				estudiantes[cantEstudiantes].nombre = pasajeros[posPas].nombre;
				estudiantes[cantEstudiantes].viajesS1 = 0;
				estudiantes[cantEstudiantes].viajesS2 = 0;
				posEst = cantEstudiantes;
				cantEstudiantes++;
			}
			
			if(obtenerSemestre(fecha) == 1) {
				lineas[posLin].viajesS1++;
				estudiantes[posEst].viajesS1++;
			}
			else {
				lineas[posLin].viajesS2++;
				estudiantes[posEst].viajesS2++;
			}
		}
		
		cout << "Ingrese fecha del viaje (DDMMAAAA) o 31129999 para finalizar: ";
		cin >> fecha;
	}
	
	// -------------------------------------------------------------------------
	// PUNTO A: LISTADO DE PASAJEROS TIPO 4 POR LINEA Y SEMESTRE
	// -------------------------------------------------------------------------
	float reduccion;
	
	cout << endl;
	cout << "LISTADO DE PASAJEROS TIPO 4 POR LINEA DE COLECTIVO" << endl;
	cout << left << setw(10) << "CODIGO" << setw(30) << "DESCRIPCION"
		<< setw(16) << "1er Semestre" << setw(16) << "2do Semestre"
		<< "%Reduccion" << endl;
	
	for(int i = 0; i < cantLineas; i++) {
		if(lineas[i].viajesS1 > 0) {
			reduccion = (lineas[i].viajesS1 - lineas[i].viajesS2) * 100.0 / lineas[i].viajesS1;
		}
		else { reduccion = 0; }
		
		cout << left << setw(10) << lineas[i].codigo << setw(30) << lineas[i].descripcion
		   << setw(16) << lineas[i].viajesS1 << setw(16) << lineas[i].viajesS2
		   << reduccion << "%" << endl;
	}
	
	// -------------------------------------------------------------------------
	// PUNTO B: PORCENTAJE DE PASAJEROS TIPO 4 QUE DEJAN DE VIAJAR EN EL 2DO SEMESTRE
	// -------------------------------------------------------------------------
	int dejaronDeViajar = 0;
	
	for(int i = 0; i < cantEstudiantes; i++) {
		if(estudiantes[i].viajesS1 > 0 && estudiantes[i].viajesS2 == 0) {
			dejaronDeViajar++;
		}
	}
	
	float porcentajeDejan;
	if(cantEstudiantes > 0) {
		porcentajeDejan = dejaronDeViajar * 100.0 / cantEstudiantes;
	}
	else { porcentajeDejan = 0; }
	
	cout << endl;
	cout << "Porcentaje de pasajeros tipo 4 que dejaron de viajar en el 2do semestre: ";
	cout << porcentajeDejan << "%" << endl;
	
	// -------------------------------------------------------------------------
	// PUNTO C: TOP 5 ESTUDIANTES QUE MAS VIAJARON EN 2024
	// -------------------------------------------------------------------------
	ordenarTop(estudiantes, cantEstudiantes);
	
	cout << endl;
	cout << "TOP 5 ESTUDIANTES QUE MAS VIAJARON EN 2024" << endl;
	cout << left << setw(12) << "DNI" << setw(20) << "APELLIDO"
		<< setw(20) << "NOMBRE" << "CANT. VIAJES" << endl;
	
	int topeTop5;
	if(cantEstudiantes < 5) { topeTop5 = cantEstudiantes; } else { topeTop5 = 5; }
	
	for(int i = 0; i < topeTop5; i++) {
		cout << left << setw(12) << estudiantes[i].dni << setw(20) << estudiantes[i].apellido
			<< setw(20) << estudiantes[i].nombre
			<< (estudiantes[i].viajesS1 + estudiantes[i].viajesS2) << endl;
	}
	
	// -------------------------------------------------------------------------
	// PUNTO D: ARCHIVO PASAJEROS_FCYT (SOLO VIAJARON EN EL 2DO SEMESTRE)
	// -------------------------------------------------------------------------
	ofstream archiFCYT;
	archiFCYT.open("PASAJEROS_FCYT.TXT");
	
	for(int i = 0; i < cantEstudiantes; i++) {
		if(estudiantes[i].viajesS1 == 0 && estudiantes[i].viajesS2 > 0) {
			archiFCYT << estudiantes[i].dni << endl;
			archiFCYT << estudiantes[i].apellido << endl;
			archiFCYT << estudiantes[i].nombre << endl;
		}
	}
	
	archiFCYT.close();
	
	return 0;
}

// Busca la posicion de un DNI dentro del vector de pasajeros.
int buscarDNI(pasajero pas[], int cant, int dni) {
	int p = -1;
	for(int i = 0; i < cant; i++) {
		if(pas[i].dni == dni) {
			p = i;
			i = cant;
		}
	}
	return p;
}

// Busca la posicion de un codigo de linea dentro del vector de lineas.
int buscarLinea(linea lin[], int cant, string codigo) {
	int p = -1;
	for(int i = 0; i < cant; i++) {
		if(lin[i].codigo == codigo) {
			p = i;
			i = cant;
		}
	}
	return p;
}

// Busca la posicion de un estudiante (por DNI) dentro del vector de estudiantes.
int buscarEstudiante(estudiante est[], int cant, int dni) {
	int p = -1;
	for(int i = 0; i < cant; i++) {
		if(est[i].dni == dni) {
			p = i;
			i = cant;
		}
	}
	return p;
}

// Devuelve el semestre (1 o 2) a partir de una fecha con formato DDMMAAAA.
int obtenerSemestre(string fecha) {
	string aux_mes;
	int mes;
	int semestre;
	
	aux_mes = fecha.substr(2,2);
	mes = stoi(aux_mes);
	
	if(mes >= 1 && mes <= 6) {
		semestre = 1;
	}
	else { semestre = 2; }
	
	return semestre;
}

// Ordena el vector de estudiantes de mayor a menor segun cantidad total de viajes.
void ordenarTop(estudiante est[], int cant) {
	estudiante aux;
	int totalI, totalJ;
	
	for(int i = 0; i < cant - 1; i++) {
		for(int j = i + 1; j < cant; j++) {
			totalI = est[i].viajesS1 + est[i].viajesS2;
			totalJ = est[j].viajesS1 + est[j].viajesS2;
			if(totalJ > totalI) {
				aux = est[i];
				est[i] = est[j];
				est[j] = aux;
			}
		}
	}
}
