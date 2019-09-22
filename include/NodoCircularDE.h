#ifndef NODOCIRCULARDE_H
#define NODOCIRCULARDE_H
#include "Matriz3D.h"

class NodoCircularDE
{
    public:
        std::string filtro;
        Matriz3D matrizFiltro;
        NodoCircularDE *siguiente;
        NodoCircularDE *anterior;
        NodoCircularDE(Matriz3D matrizFiltro,std::string filtro);
        virtual ~NodoCircularDE();

    protected:

    private:
};

#endif // NODOCIRCULARDE_H
