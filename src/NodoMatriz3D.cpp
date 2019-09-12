#include "NodoMatriz3D.h"

NodoMatriz3D::NodoMatriz3D(int x, int y, std::string dato,int nivelCapa,std::string anchoImagen,std::string alturaImagen,std::string anchoPixel,std::string alturaPixel)
{
    this->x=x;
    this->y=y;
    this->dato =dato;
    this->nivelCapa = nivelCapa;
    this->anchoImagen = anchoImagen;
    this->alturaImagen = alturaImagen;
    this->anchoPixel = anchoPixel;
    this->alturaPixel = alturaPixel;
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
