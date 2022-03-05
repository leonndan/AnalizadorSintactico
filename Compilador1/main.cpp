#include <iostream>
#include <cstring>
#include <fstream>

#include "lexico.h"
#include "lista_tokens.h"
#include "sintactico.h"
#include "reglas.h"

using namespace std;

int main(){
    lista<tokens> datos;
    lexico lex1;
    Sintacico sint1;
    Regla *arbol;

    string archivo;
    ifstream lectura("entrada.txt");
    char cadena[1000];

    if(!lectura.good()){
        cout << "error";
        cout<<"No se pudo abrir el archivo"<<endl;
    }
    else{
        lectura.getline((char*)&cadena, 10000, lectura.eof());
        lectura.close();
    }

    datos = lex1.lex(cadena);
    datos.imprimir();
    arbol = sint1.sint(datos);
    arbol->validaTipo("global");


    arbol->muestra();
    //arbol->mostrarLista();
    //arbol->generarCodigo();

    return 0;
}
