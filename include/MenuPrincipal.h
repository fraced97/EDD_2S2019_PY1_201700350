#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include <iostream>
#include "Matriz3D.h"
#include "NodoArbol.h"
#include "Arbol.h"
using namespace std;

class MenuPrincipal
{
    public:
        //MenuPrincipal();
        string archivo; //hice global para ver como resulta
        //NodoArbol arbolNodo;
        Arbol arbolOriginal;  //ARBOL ORIGINAL
        MenuPrincipal();
        int contador;
        int contadorFila;
        int contadorColumnas;
        //std::string ruta="";
        void Menu();
        void insertarImagen();
        //void archivos(std::string nombreArchivo);
        //void separarColumnas(std::string dato);
        //Matriz3D matriz;
        void menuSeleccionarImagen();
        void crearImagen();
        std::string limpiar_color(std::string color);
        NodoArbol *auxGuardarNodo; //AGREGADO PARA PROBAR SI FUNCIONA
        virtual ~MenuPrincipal();

    protected:

    private:
};

#endif // MENUPRINCIPAL_H
