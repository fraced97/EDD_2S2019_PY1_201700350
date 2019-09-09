#include "NodoMatriz3D.h"

NodoMatriz3D::NodoMatriz3D(int x, int y, std::string dato)
{
    this->x=x;
    this->y=y;
    this->dato =dato;
    this->siguiente =NULL;
    this->anterior =NULL;
    this->arriba =NULL;
    this->abajo =NULL;
    this->fondo =NULL;
    this->frente =NULL;
}

NodoMatriz3D::~NodoMatriz3D()
{
    //dtor
}
