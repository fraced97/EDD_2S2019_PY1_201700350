#ifndef MATRIZ3D_H
#define MATRIZ3D_H
#include "NodoMatriz3D.h"

class Matriz3D
{
    public:
        NodoMatriz3D *primeraMatriz;
        NodoMatriz3D *ultimaMatriz;
        int tamanioCubo;
        Matriz3D();
        NodoMatriz3D *raiz;
        NodoMatriz3D* buscarFila(int y);
        NodoMatriz3D* buscarColumna(int x);
        void insertarElemento(int x, int y,std::string dato);
        NodoMatriz3D* insertarColumna(NodoMatriz3D *nuevo, NodoMatriz3D *cabezaCol);
        NodoMatriz3D* insertarFila(NodoMatriz3D *nuevo, NodoMatriz3D *cabezaFila);
        NodoMatriz3D* crearColumna(int x);
        NodoMatriz3D* crearFila(int y);
        void generarNuevaMatriz(int layer);
        void recorrerMatriz();
        void imprimirRaiz();
        //Matriz3D();
        virtual ~Matriz3D();

    protected:

    private:
};

#endif // MATRIZ3D_H
