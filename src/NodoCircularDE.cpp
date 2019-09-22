#include "NodoCircularDE.h"

NodoCircularDE::NodoCircularDE(Matriz3D matrizFiltro,std::string filtro)
{
    this->filtro=filtro;
    this->matrizFiltro=matrizFiltro;
    this->siguiente=NULL;
    this->anterior=NULL;
}

NodoCircularDE::~NodoCircularDE()
{
    //dtor
}
