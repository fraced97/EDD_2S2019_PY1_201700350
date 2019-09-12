#ifndef ARBOL_H
#define ARBOL_H
#include "NodoArbol.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>

class Arbol
{
    public:

        //Arbol();

        NodoArbol *raiz;
        NodoArbol aux;
        int contadorArbol;
        void insertarNodo(NodoArbol *&raiz,string nombre, Matriz3D matriz);
        void mostrarArbol(NodoArbol *arbol, int contador);
        void graficarArbol(NodoArbol *raiz, ofstream &archivo);
        void GraficarArbol();
        void inorden(NodoArbol *raiz,ofstream &archivo);
        void GraficarInorden();
        void postorden(NodoArbol *raiz,ofstream &archivo);
        void GraficarPostorden();
        void preorden(NodoArbol *raiz,ofstream &archivo);
        void GraficarPreorden();
        void menuArbol(NodoArbol *raiz);
        NodoArbol* buscarNodo(std::string nombre,NodoArbol *nodoAux);
        Arbol();
        virtual ~Arbol();

    protected:

    private:
};

#endif // ARBOL_H
