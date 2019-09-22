#include "ListaCircular.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
using namespace std;
ListaCircular::ListaCircular()
{
    this->primero=NULL;
    this->ultimo=NULL;
}

ListaCircular::~ListaCircular()
{
    //dtor
}
bool ListaCircular::estaVacio()
{
    bool condicion;
    if(primero==NULL){
        condicion=true;
    }else{
        condicion=false;
    }
    return condicion;
}
void ListaCircular::insertarNodo(Matriz3D matrizFiltro,std::string filtro)
{

    NodoCircularDE *nuevo;
    nuevo = new NodoCircularDE(matrizFiltro,filtro);

    if(estaVacio()){
        //cout<<"ENTRO IF LISTACIRCULAR"<<endl;
        primero= nuevo;
        ultimo =nuevo;
        primero->anterior=ultimo;
        ultimo->siguiente=primero;
    }else{
        //cout<<"ENTRO ELSE LISTACIRCULAR"<<endl;
        ultimo->siguiente=nuevo;
        nuevo->anterior=ultimo;
        ultimo=nuevo;
        ultimo->siguiente=primero;
        primero->anterior=ultimo;
    }
}
void ListaCircular::limpiarLista()
{
    primero->siguiente=NULL;
    primero->anterior=NULL;
    primero=NULL;
    ultimo->siguiente=NULL;
    ultimo->anterior=NULL;
    ultimo=NULL;

}
void ListaCircular::graficarListaCircular(ListaCircular copiaLista, string nombre)
{
    NodoCircularDE *temp;
    temp = copiaLista.primero;
    ofstream archivo;
    std::string auxNombreMatriz3 =nombre+"\\"+"ListaCircular"+nombre+".dot";
    const char *nombreArch = auxNombreMatriz3.c_str();
    archivo.open(nombreArch,ios::out);//abriendo el archivo
    archivo<<"digraph G {"<<endl;
    archivo<<"rankdir = LR \n node [shape = square];\n"<<endl;
    while(temp->siguiente!=copiaLista.primero){
            archivo<<"\"" + (temp->filtro) + "\"->""\"" + temp->siguiente->filtro + "\";"<<endl;
            archivo<<"\"" + (temp->siguiente->filtro) + "\"->""\"" + temp->filtro + "\";"<<endl;
            //archivo<<"\""<<temp->filtro<<"\"->"<<"\""<<temp->siguiente->filtro<<"\""<<"[dir=both];"<<endl;
            temp=temp->siguiente;
    }
    //archivo<<"\""<<temp->filtro<<"\"->"<<"\""<<temp->siguiente->filtro<<"\""<<"[dir=both];"<<endl;
    archivo<<"\"" + (temp->filtro) + "\"->""\"" + temp->siguiente->filtro + "\";"<<endl;
    archivo<<"\"" + (temp->siguiente->filtro) + "\"->""\"" + temp->filtro + "\";"<<endl;
    archivo<<"}";
    archivo.close();
    std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+"ListaCircular"+nombre+".dot"+" -o imagenFiltros.jpg";
    const char *nombreArch2 = auxNombreMatriz4.c_str();
    system(nombreArch2); // CREANDO EL GRAPHVIZ
    system("imagenFiltros.jpg");

}
void ListaCircular::mostrarFiltros()
{
    if(primero!=NULL){
    NodoCircularDE *temp;
    temp=primero;
    temp=temp->siguiente;
    cout<<""<<endl;
    while(temp!=primero)
    {
       cout<<+"_____"+temp->filtro+"_____"<<endl;
       temp=temp->siguiente;
    }
    cout<<+"_____"+temp->filtro+"_____"<<endl;
    }else{
        cout<<"No ha seleccionado ningun filtro"<<endl;
    }
}
Matriz3D ListaCircular::buscarMatriz(std::string nombre)
{
    NodoCircularDE *temp;
    temp=primero;
    temp=temp->siguiente;
    cout<<""<<endl;
    while(temp!=primero)
    {
       if(temp->filtro==nombre){
        break;
       }
       temp=temp->siguiente;
    }
    if(temp->filtro==nombre){
        return temp->matrizFiltro;
    }else{
      return temp->matrizFiltro;
    }

}
