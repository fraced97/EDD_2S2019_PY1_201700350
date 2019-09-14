#include "Arbol.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <string>
using namespace std;

Arbol::Arbol()
{
    raiz=NULL;
    contadorArbol = 0;
}
/*Arbol::Arbol(NodoArbol *r)
{
    raiz=r;

}*/

void Arbol::insertarNodo(NodoArbol *&raiz, string nombre, Matriz3D matriz)
{
    //contadorArbol++;
    if(raiz==NULL)
    {
        NodoArbol *nuevo = aux.crearNodo(nombre, matriz);
        raiz=nuevo;
        //contadorArbol++;
    }else
    {
        const char *nombreAux = (raiz->nombre).c_str();
        const char *nombreAux2 = nombre.c_str();
        if(strcmp(nombreAux,nombreAux2)>0) //VERIFICO ALFABETICAMENTE
        {
            insertarNodo(raiz->izquierda,nombre,matriz);
            //contadorArbol++;
        }
        else
        {
            insertarNodo(raiz->derecha,nombre,matriz);
            //contadorArbol++;
        }
    }
}
void Arbol::mostrarArbol(NodoArbol *arbol2,int contador)
{
    if(arbol2==NULL)
    {
        return;
    }
    else
    {
        mostrarArbol(arbol2->derecha,contador+1);
        for(int i=0;i<contador;i++)
        {
            cout<<"   ";
        }
        cout<<arbol2->nombre<<endl;
        mostrarArbol(arbol2->izquierda,contador+1);
    }
    //cout<<contadorArbol<<" ESTE ES EL CONTADOR DEL ARBOL"<<endl;
}
void Arbol::graficarArbol(NodoArbol *raiz,ofstream &archivo)
{
    /*ofstream archivo;
    archivo.open("Arbol.dot",ios::out);//abriendo el archivo

    if(archivo.fail())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }*/
    //archivo<<"digraph G {"<<endl;
    if(raiz!=NULL)
    {
        //std::cout<<"\""<<raiz->nombre << "\";"<<endl;
        archivo<<"\""<<raiz->nombre+", "+raiz->matriz.primeraMatriz->anchoImagen+", "+raiz->matriz.primeraMatriz->alturaImagen+", "+ raiz->matriz.primeraMatriz->anchoPixel+", "+raiz->matriz.primeraMatriz->alturaPixel << "\";"<<endl;
        if(raiz->izquierda!=NULL)
        {
            archivo<<"\""<<raiz->nombre+", "+raiz->matriz.primeraMatriz->anchoImagen+", "+raiz->matriz.primeraMatriz->alturaImagen+", "+ raiz->matriz.primeraMatriz->anchoPixel+", "+raiz->matriz.primeraMatriz->alturaPixel<<"\"->\""<<raiz->izquierda->nombre+", "+raiz->izquierda->matriz.primeraMatriz->anchoImagen+", "+raiz->izquierda->matriz.primeraMatriz->alturaImagen+", "+ raiz->izquierda->matriz.primeraMatriz->anchoPixel
            +", "+raiz->izquierda->matriz.primeraMatriz->alturaPixel<<"\";"<<endl;
            //cout << "\""<<raiz->nombre<<"\"->\""<<raiz->izquierda->nombre<<"\";"<<endl;
        }
        if(raiz->derecha)
        {
            archivo<<"\""<<raiz->nombre+", "+raiz->matriz.primeraMatriz->anchoImagen+", "+raiz->matriz.primeraMatriz->alturaImagen+", "+ raiz->matriz.primeraMatriz->anchoPixel+", "+raiz->matriz.primeraMatriz->alturaPixel<<"\"->\""<<raiz->derecha->nombre+", "+raiz->derecha->matriz.primeraMatriz->anchoImagen+", "+raiz->derecha->matriz.primeraMatriz->alturaImagen+", "+ raiz->derecha->matriz.primeraMatriz->anchoPixel
            +", "+raiz->derecha->matriz.primeraMatriz->alturaPixel<<"\";"<<endl;
            //std::cout << "\""<<raiz->nombre<<"\"->\""<<raiz->derecha->nombre<<"\";"<<std::endl;
        }

        graficarArbol(raiz->izquierda,archivo);
        graficarArbol(raiz->derecha,archivo);

    }

    /*if(raiz!=NULL)
    {
        std::cout<<"\""<<raiz->nombre << "\";"<<endl;
        if(raiz->izquierda!=NULL)
        {
            cout << "\""<<raiz->nombre<<"\"->\""<<raiz->izquierda->nombre<<"\";"<<endl;
        }
        if(raiz->derecha)
        {
            std::cout << "\""<<raiz->nombre<<"\"->\""<<raiz->derecha->nombre<<"\";"<<std::endl;
        }
        graficarArbol(raiz->izquierda);
        graficarArbol(raiz->derecha);
    }*/
}
void Arbol::GraficarArbol()
{
    ofstream archivo;
    archivo.open("Arbol.dot",ios::out);//abriendo el archivo

    if(archivo.fail())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
    archivo<<"digraph G {"<<endl;
   // std::cout<<"Digraph G {"<<std::endl;
    graficarArbol(this->raiz,archivo);
    archivo <<"}"<<endl;
    archivo.close();
    system("dot -Tjpg Arbol.dot -o imagenArbol.jpg"); // CREANDO EL GRAPHVIZ
    system("imagenArbol.jpg"); //ABRO LA IMAGEN
    //std::cout<<"}"<<std::endl;
}
void Arbol::inorden(NodoArbol *raiz,ofstream &archivo)
{
    if(raiz!=NULL)
    {
        inorden(raiz->izquierda,archivo);
        archivo<<"\""<<raiz->nombre+", "+raiz->matriz.primeraMatriz->anchoImagen+", "+raiz->matriz.primeraMatriz->alturaImagen+", "+ raiz->matriz.primeraMatriz->anchoPixel+", "+raiz->matriz.primeraMatriz->alturaPixel <<"\"->";
        inorden(raiz->derecha,archivo);
    }
}
void Arbol::GraficarInorden()
{
    ofstream archivo;
    archivo.open("Inorden.dot",ios::out);//abriendo el archivo

    if(archivo.fail())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
    archivo<<"digraph G {"<<endl;
    archivo<<"rankdir=LR;"<<endl;
   // std::cout<<"Digraph G {"<<std::endl;
    inorden(this->raiz,archivo);
    archivo.width();
    archivo <<"}"<<endl;
    archivo.close();
    ///////////////////////////////// QUITAR LA ULTIMA FLECHA
    std::ifstream fileIn( "Inorden.dot" );                   // Open for reading

    std::stringstream buffer;                             // Store contents in a std::string
    buffer << fileIn.rdbuf();
    std::string contents = buffer.str();

    fileIn.close();
    if(!contents.empty())
    {
        contents.resize(contents.size()-4);
    }                                    // Remove last character


    std::ofstream fileOut( "Inorden.dot" , std::ios::out); // Open for writing (while also clearing file)
    fileOut << contents;
    fileOut<<"}";                                  // Output contents with removed character
    fileOut.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
    system("dot -Tjpg Inorden.dot -o imagenInorden.jpg"); // CREANDO EL GRAPHVIZ
    system("imagenInorden.jpg"); //ABRO LA IMAGEN
}
void Arbol::preorden(NodoArbol *raiz,ofstream &archivo)
{
    if(raiz!=NULL)
    {
        archivo<<"\""<<raiz->nombre+", "+raiz->matriz.primeraMatriz->anchoImagen+", "+raiz->matriz.primeraMatriz->alturaImagen+", "+ raiz->matriz.primeraMatriz->anchoPixel+", "+raiz->matriz.primeraMatriz->alturaPixel <<"\"->";
        preorden(raiz->izquierda,archivo);
        preorden(raiz->derecha,archivo);
    }

}
void Arbol::GraficarPreorden()
{
    ofstream archivo;
    archivo.open("Preorden.dot",ios::out);//abriendo el archivo

    if(archivo.fail())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
    archivo<<"digraph G {"<<endl;
    archivo<<"rankdir=LR;"<<endl;
   // std::cout<<"Digraph G {"<<std::endl;
    preorden(this->raiz,archivo);
    archivo <<"}"<<endl;
    archivo.close();
    ///////////////////////////////// QUITAR LA ULTIMA FLECHA
    std::ifstream fileIn( "Preorden.dot" );                   // Open for reading

    std::stringstream buffer;                             // Store contents in a std::string
    buffer << fileIn.rdbuf();
    std::string contents = buffer.str();

    fileIn.close();
    if(!contents.empty())
    {
        contents.resize(contents.size()-4);
    }                                    // Remove last character


    std::ofstream fileOut( "Preorden.dot" , std::ios::out); // Open for writing (while also clearing file)
    fileOut << contents;
    fileOut<<"}";                                  // Output contents with removed character
    fileOut.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
    system("dot -Tjpg Preorden.dot -o imagenPreorden.jpg"); // CREANDO EL GRAPHVIZ
    system("imagenPreorden.jpg"); //ABRO LA IMAGEN
}
void Arbol::postorden(NodoArbol *raiz,ofstream &archivo)
{
    if(raiz!=NULL)
    {
        preorden(raiz->izquierda,archivo);
        preorden(raiz->derecha,archivo);
        archivo<<"\""<<raiz->nombre+", "+raiz->matriz.primeraMatriz->anchoImagen+", "+raiz->matriz.primeraMatriz->alturaImagen+", "+ raiz->matriz.primeraMatriz->anchoPixel+", "+raiz->matriz.primeraMatriz->alturaPixel <<"\"->";
    }

}
void Arbol::GraficarPostorden()
{
    ofstream archivo;
    archivo.open("Postorden.dot",ios::out);//abriendo el archivo

    if(archivo.fail())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
    archivo<<"digraph G {"<<endl;
    archivo<<"rankdir=LR;"<<endl;
   // std::cout<<"Digraph G {"<<std::endl;
    postorden(this->raiz,archivo);
    archivo <<"}"<<endl;
    archivo.close();
    ///////////////////////////////// QUITAR LA ULTIMA FLECHA
    std::ifstream fileIn( "Postorden.dot" );                   // Open for reading

    std::stringstream buffer;                             // Store contents in a std::string
    buffer << fileIn.rdbuf();
    std::string contents = buffer.str();

    fileIn.close();
    if(!contents.empty())
    {
        contents.resize(contents.size()-4);
    }                                    // Remove last character


    std::ofstream fileOut( "Postorden.dot" , std::ios::out); // Open for writing (while also clearing file)
    fileOut << contents;
    fileOut<<"}";                                  // Output contents with removed character
    fileOut.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
    system("dot -Tjpg Postorden.dot -o imagenPostorden.jpg"); // CREANDO EL GRAPHVIZ
    system("imagenPostorden.jpg"); //ABRO LA IMAGEN
}
void Arbol::menuArbol(NodoArbol *raiz)
{

    if(raiz!=NULL)
    {

        menuArbol(raiz->izquierda);
        cout<<""<<endl;
        cout<<"_________"<<raiz->nombre<<"__________"<<endl;
        menuArbol(raiz->derecha);
    }
}
NodoArbol* Arbol::buscarNodo(std::string nombre,NodoArbol *nodoAux)
{

    NodoArbol *nodoArbolAux = NULL;
    if(raiz!=NULL)
    {
        //cout<< "asdasdaa"<<nodoAux->nombre;
        if(nombre==nodoAux->nombre)
        {
            //cout << "hola que ace"<<endl;

            return nodoAux;
            cout<<"ENTRO EN EL PRIMER IF"<<endl;
        }
        else
        {
            const char *nombreAux = (nodoAux->nombre).c_str();
            const char *nombreAux2 = nombre.c_str();
            cout<<"ENTRO EN EL PRIMER ELSE"<<endl;
           if(nodoAux->derecha !=NULL || nodoAux->izquierda !=NULL)
           {
               cout<<"ENTRO EN EL SEGUNDO IF"<<endl;
               if(strcmp(nombreAux,nombreAux2)>0) //VERIFICO ALFABETICAMENTE
                {
                    nodoArbolAux = buscarNodo(nombre, nodoAux->izquierda);

                }
                else{
                    nodoArbolAux = buscarNodo(nombre, nodoAux->derecha);
                }
               /*if(nombre < nodoAux->nombre)
               {
                   nodoArbolAux = buscarNodo(nombre, nodoAux->izquierda);

               }
               else
               {
                   nodoArbolAux = buscarNodo(nombre, nodoAux->derecha);
               }*/
           }
        }
    }
    return nodoArbolAux;
}
Arbol::~Arbol()
{
    //dtor
}
