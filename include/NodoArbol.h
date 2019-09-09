#ifndef NODOARBOL_H
#define NODOARBOL_H
#include "Matriz3D.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

class NodoArbol
{
    public:
        string nombre;
        Matriz3D matriz;
        NodoArbol *derecha;
        NodoArbol *izquierda;
        //////////////////////
        NodoArbol* crearNodo(string nombre, Matriz3D matriz);
        //NodoArbol *arbol;
        //NodoArbol(string nombre, Matriz3D matriz);
        NodoArbol();
        void insertarNodo(NodoArbol *&arbol,string nombre, Matriz3D matriz);
        //NodoArbol(string nombre, Matriz3D matriz, NodoArbol *ramaIzq, NodoArbol *ramaDer);
        ///////////////////////////////////////
        NodoArbol* subArbolIzqu();
        NodoArbol* subArbolDere();

        /////////////////
        void ramaIzqu(NodoArbol* n);
        void ramaDere(NodoArbol* n);

        virtual ~NodoArbol();

    protected:

    private:
};

#endif // NODOARBOL_H
