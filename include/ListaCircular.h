#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include "NodoCircularDE.h"
#include "Matriz3D.h"

class ListaCircular
{
    public:
        NodoCircularDE *primero;
        NodoCircularDE *ultimo;
        bool estaVacio();
        ListaCircular();
        void insertarNodo(Matriz3D matrizFiltro,std::string filtro);
        void limpiarLista();
        void graficarListaCircular(ListaCircular copiaLista, string nombre);
        Matriz3D buscarMatriz(std::string nombre);
        void mostrarFiltros();
        virtual ~ListaCircular();

    protected:

    private:
};

#endif // LISTACIRCULAR_H
