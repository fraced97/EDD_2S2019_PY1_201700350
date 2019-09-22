#include "NodoArbol.h"
#include <cstring>
#include <conio.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

/*NodoArbol::NodoArbol(string nombre, Matriz3D matriz)
{
    this->nombre=nombre;
    this->matriz=matriz;
    this->derecha=NULL;
    this->izquierda=NULL;
}
NodoArbol::NodoArbol(string nombre, Matriz3D matriz, NodoArbol *ramaIzq, NodoArbol *ramaDer)
{
    this->nombre=nombre;
    this->matriz=matriz;
    this->izquierda=ramaIzq;
    this->derecha=ramaDer;
}
NodoArbol* NodoArbol::subArbolIzqu()
{
    return izquierda;
}
NodoArbol* NodoArbol::subArbolDere()
{
    return derecha;
}
void NodoArbol::ramaIzqu(NodoArbol* n)
{

}
void NodoArbol::ramaDere(NodoArbol* n)
{
    derecha = n;
}*/
NodoArbol::NodoArbol()
{
    //arbol=NULL;
    //this ->izquierda=NULL;
    //this->derecha=NULL;
}

NodoArbol* NodoArbol::crearNodo(string nombre, Matriz3D matriz, Matriz3D matrizNegativa, Matriz3D matrizBN, Matriz3D matrizEspejo,Matriz3D sinX)
{
    NodoArbol *nuevo = new NodoArbol();
    nuevo->nombre = nombre;
    nuevo-> matriz = matriz;
    nuevo->matrizNegativa=matrizNegativa;
    nuevo->matrizBN= matrizBN;
    nuevo->matrizEspejo=matrizEspejo;
    nuevo->sinX=sinX;
    nuevo ->izquierda=NULL;
    nuevo->derecha=NULL;
    return nuevo;

}
/*void NodoArbol::insertarNodo(NodoArbol *&arbol,string nombre, Matriz3D matriz)
{
    if(arbol==NULL)
    {
        NodoArbol *nuevo=crearNodo(nombre,matriz);
        arbol=nuevo;
    }
    else
    {
        const char *nombreAux = (arbol->nombre).c_str();
        const char *nombreAux2 = nombre.c_str();
        if(strcmp(nombreAux,nombreAux2)>0)
        {
            insertarNodo(arbol->izquierda,nombre,matriz);

        }
        else
        {
            insertarNodo(arbol->derecha,nombre,matriz);
        }
    }
}*/

NodoArbol::~NodoArbol()
{
    //dtor
}
