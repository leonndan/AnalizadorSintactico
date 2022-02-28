#ifndef GRAMATICA_H
#define GRAMATICA_H
#include <fstream>
#include<iostream>
#include<string>
#include <vector>
#include<stdlib.h>

using namespace std;

class Gramatica {
public:
	Gramatica(){}
	Gramatica(string);
	virtual ~Gramatica() {}

	string leerArchivo();
	void gramatica();
	string* separarElementos(string, unsigned int);

	int** tablaLR;
	int* idRegla;
	int* lonRegla;
	string* nomRegla;

	string nombreArchivo;
protected:

private:

};

Gramatica::Gramatica(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
}
string Gramatica::leerArchivo() {
	ifstream file;
	const char* archivo = nombreArchivo.c_str();
	file.open(archivo);

	string salida = "", linea = "";
	if (file.is_open()) {
		while (getline(file, linea)) {
			salida += linea;
		}
	}
	file.close();

	return salida;
}
void Gramatica::gramatica() {
	ifstream file;
	const char* archivo = nombreArchivo.c_str();
	file.open(archivo);

	if (file.is_open()) {

		string linea = "";
		getline(file, linea);
		unsigned int numero = atoi(linea.c_str());

		idRegla = new int[numero];
		lonRegla = new int[numero];
		nomRegla = new string[numero];

		for (unsigned int i = 0; i < numero; i++) {
			linea.clear();
			getline(file, linea);
			string* bloque = separarElementos(linea, 2);
			idRegla[i] = atoi(bloque[0].c_str());
			lonRegla[i] = atoi(bloque[1].c_str());
			nomRegla[i] = bloque[2];
		}

		linea.clear();
		unsigned int filas = 0, columnas = 0;

		getline(file, linea);

		string* bloque = separarElementos(linea, 1);
		filas = atoi(bloque[0].c_str());
		columnas = atoi(bloque[1].c_str());
		
		cout << "Filas: " << filas << " Columnas: " << columnas << endl;

		tablaLR = new int* [filas];
		for (unsigned int i = 0; i < filas; i++) {
			tablaLR[i] = new int[columnas];
		}
		for (unsigned int i = 0; i < filas; i++) {
			linea.clear();
			getline(file, linea);
			bloque = separarElementos(linea, columnas);
			for (unsigned int j = 0; j < columnas; j++) {
				tablaLR[i][j] = atoi(bloque[j].c_str());
			}
			bloque->clear();
		}
	}
	else {
		cout << "Error al leer el archivo" << endl;
	}
	file.close();
}

string* Gramatica::separarElementos(string linea, unsigned int numTabuladores) {
	string* bloque = new string[60];
	string elemento;

	unsigned int i = 0;
	unsigned int j = 0;

	for (; j < numTabuladores; j++) {
		while (linea[i] != '\t' && linea[i] != '\0') {
			elemento += linea[i];
			i++;
		}
		i++;
		bloque[j] = elemento;
		elemento.clear();
	}
	while (linea[i] != '\0') {
		elemento += linea[i];
		i++;
	}
	bloque[j++] = elemento;

	return bloque;
}
#endif 
