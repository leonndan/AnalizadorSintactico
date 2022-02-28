#include <cstdlib>
#include <iostream>
#include <string>
#include "Lexico.h"
#include "Pila.h"
#include "Gramatica.h"

using namespace std;

int main()
{
    Lexico lexico;
    Pila pila;
    Gramatica gram("Prueba.txt");
    bool aceptacion = false;
    unsigned int contador;

    string entrada=gram.leerArchivo();
    lexico.entrada(entrada);
    
    gram.nombreArchivo = "compilador.lr";
    gram.gramatica();

    int** tablaLR = gram.tablaLR;
    int* idRegla = gram.idRegla;
    int* lonRegla = gram.lonRegla;
    string* nomRegla = gram.nomRegla;

    pila.push(new Terminal("$"));
    pila.push(new Estado(0));

    lexico.sigSimbolo();

    while (!aceptacion || lexico.tipo != -1) {
        pila.fila = pila.top()->getEstado();
        pila.columna = lexico.tipo;
        pila.accion = tablaLR[pila.fila][pila.columna];

        pila.mostrarDatos(lexico.simbolo);

        if (pila.accion < -1) {
            contador = (-pila.accion) - 2;
            for (int i = 0; i < lonRegla[contador]; i++) {
                pila.pop();
                pila.pop();
            }
            pila.fila = pila.top()->getEstado();
            pila.columna = idRegla[contador];
            pila.accion = tablaLR[pila.fila][pila.columna];
            pila.push(new Terminal(nomRegla[contador]));
            pila.push(new Estado(pila.accion));

        }
        else if (pila.accion > 0) {
            pila.push(new Terminal(lexico.simbolo));
            pila.push(new Estado(pila.accion));
            if (lexico.simbolo.compare("$") != 0) {
                lexico.sigSimbolo();
            }
        }
        else if (pila.accion == 0) {
            cout << "Error" << endl;
            break;
        }
        else if (pila.accion == -1) {
            cout << "Aceptacion" << endl;
            break;
        }
    }
    return 0;
}