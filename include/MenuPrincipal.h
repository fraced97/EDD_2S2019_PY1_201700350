#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include <iostream>
#include "Matriz3D.h"
#include "NodoArbol.h"
#include "Arbol.h"
#include "ListaCircular.h"
using namespace std;

class MenuPrincipal
{
    public:
        //MenuPrincipal();
        string archivo; //hice global para ver como resulta
        //NodoArbol arbolNodo;
        ListaCircular listaFiltros;
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
        std::string cambiarAComa(std::string dato);
        NodoArbol *auxGuardarNodo; //AGREGADO PARA PROBAR SI FUNCIONA
        NodoArbol *auxNodoArbol;
        Matriz3D auxMatrizFiltro;
        string filtro;
        void filtroNB(string filtro);
        void menuFiltros();
        void menuEspejo();
        void menuReportes();
        void traversalReporte();
        void menuSeleccionarCubo();
        void menuConfiguracionManual();
        void crearImagenFiltro();
        void reportesFiltro();
        void graficarTodoFiltro();
        virtual ~MenuPrincipal();
        bool espejo;
        bool volteado;
        bool dosEjes;
        void crearImagenEspejo(bool espejo,bool vuelta, bool dosEjes);
        void menuOpcionConfiguracionManual();
        void menuFiltroCambiarManualmente();
        void matrizLinealReporte();


    protected:

    private:
};

#endif // MENUPRINCIPAL_H
