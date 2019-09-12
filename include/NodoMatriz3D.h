#ifndef NODOMATRIZ3D_H
#define NODOMATRIZ3D_H
#include <iostream>
using namespace std;

class NodoMatriz3D
{
    public:
        NodoMatriz3D *siguiente;
        NodoMatriz3D *anterior;
        NodoMatriz3D *abajo;
        NodoMatriz3D *arriba;
        NodoMatriz3D *fondo;
        NodoMatriz3D *frente;
        int x;
        int y;
        std::string dato;
        int nivelCapa;
        string anchoImagen;
        string alturaImagen;
        string anchoPixel;
        string alturaPixel;
        NodoMatriz3D(int x, int y, std::string dato,int nivelCapa,string anchoImagen,string alturaImagen,string anchoPixel,string alturaPixel);

        //NodoMatriz3D();
        virtual ~NodoMatriz3D();

    protected:

    private:
};

#endif // NODOMATRIZ3D_H
