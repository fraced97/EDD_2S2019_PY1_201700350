#include "Matriz3D.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
using namespace std;
Matriz3D::Matriz3D()
{
    this->raiz= new NodoMatriz3D(-1,-1,"Raiz 0",0,"","","","");
    //this->raiz->frente=primeraMatriz;
    //this->primeraMatriz->fondo=raiz;
    this->primeraMatriz=NULL;
    this->ultimaMatriz=NULL;
    //this->primeraMatriz=raiz;
    //this->ultimaMatriz=raiz;
    this->tamanioCubo=0;
}

Matriz3D::~Matriz3D()
{
    //dtor
}
NodoMatriz3D* Matriz3D::buscarFila(int y)
{
    NodoMatriz3D *temp;
    temp=raiz;
    while(temp!=NULL){
        if(temp->y==y){
            return temp;
        }
        temp = temp->abajo;

    }
    return NULL;
}
NodoMatriz3D* Matriz3D::buscarColumna(int x)
{
    NodoMatriz3D *temp;
    temp=raiz;
    while(temp!=NULL){
        if(temp->x==x){
            return temp;
        }
        temp = temp->siguiente;

    }
    return NULL;
}

NodoMatriz3D* Matriz3D::insertarColumna(NodoMatriz3D *nuevo, NodoMatriz3D *cabezaCol)
{
    NodoMatriz3D *aux;
    aux=cabezaCol;
    bool condicion = false;
    while(true){
        if(aux->x==nuevo->x){
            aux->y = nuevo->y;
            aux->dato= nuevo->dato;
            return aux;
        }else if(aux->x > nuevo->x)
        {
            condicion= true;
            break;
        }
        if(aux->siguiente!=NULL)
        {
            aux = aux->siguiente;

        }else{
            break;
        }
    }
    if(condicion){
        nuevo->siguiente=aux;
        aux->anterior->siguiente=nuevo;
        nuevo->anterior=aux->anterior;
        aux->anterior=nuevo;
    }else{
        aux->siguiente=nuevo;
        nuevo->anterior=aux;

    }
    return nuevo;

}
NodoMatriz3D* Matriz3D::insertarFila(NodoMatriz3D *nuevo, NodoMatriz3D *cabezaFila)
{
    NodoMatriz3D *aux;
    aux=cabezaFila;
    bool condicion = false;
    while(true){
        if(aux->y==nuevo->y){
            //SI LA POSICION ES LA MISMA LA SOBRE ESCRIBO
            aux->x = nuevo->x;
            aux->dato= nuevo->dato;
            return aux; //RETORNAMOS EL PUNTERO
        }else if(aux->y>nuevo->y)
        {
            //SE INSERTA ANTES DEL TEMP
            condicion= true;
            break;
        }
        if(aux->abajo!=NULL)
        {
            aux = aux->abajo;

        }else{
            break;
        }
    }
    if(condicion){
        //INSERTARLO ANTES DE TEMPORAL
        nuevo->abajo=aux;
        aux->arriba->abajo=nuevo;
        nuevo->arriba=aux->arriba;
        aux->arriba=nuevo;
    }else{
        //INSERCION AL FINAL
        aux->abajo=nuevo;
        nuevo->arriba=aux;

    }
    return nuevo;
}
NodoMatriz3D* Matriz3D::crearColumna(int x)
{
    NodoMatriz3D *cabezaColumna;
    cabezaColumna=raiz;
    /////////////////////////
    NodoMatriz3D *aux;
    aux= new NodoMatriz3D(x,-1,"Col",0,"","","","");
    ///////////////////////
    NodoMatriz3D *columna;
    columna = insertarColumna(aux,cabezaColumna);
    return columna;
}
NodoMatriz3D* Matriz3D::crearFila(int y)
{
    NodoMatriz3D *cabezaFila;
    cabezaFila=raiz;
    /////////////////////////
    NodoMatriz3D *aux;
    aux= new NodoMatriz3D(-1,y,"Fila",0,"","","","");
    ///////////////////////
    NodoMatriz3D *fila;
    fila = insertarFila(aux,cabezaFila);
    return fila;
}
void Matriz3D::insertarElemento(int x, int y, std::string dato)
{
    NodoMatriz3D *nuevo;
    nuevo= new NodoMatriz3D(x,y,dato,0,"","","","");
    NodoMatriz3D *nodoColumna;
    nodoColumna = buscarColumna(x);
    NodoMatriz3D *nodoFila;
    nodoFila = buscarFila(y);
    //1 caso: Columna no exista y fila no exista
    if(nodoColumna==NULL && nodoFila==NULL){
        std::cout << "caso 1"<< std::endl;
        nodoColumna = crearColumna(x);
        nodoFila = crearFila(y);
        nuevo = insertarColumna(nuevo,nodoFila);
        nuevo = insertarFila(nuevo,nodoColumna);
        return;
     //2 caso: Columna no exista y fila exista
    }else if(nodoColumna==NULL && nodoFila!=NULL){
        std::cout << "caso 2"<< std::endl;
        nodoColumna=crearColumna(x);
        nuevo=insertarColumna(nuevo,nodoFila);
        nuevo=insertarFila(nuevo,nodoColumna);
        return;
     //3 caso: Columna exista y fila no exista
    }else if(nodoColumna!=NULL && nodoFila==NULL){
        std::cout << "caso 3"<< std::endl;
        nodoFila=crearFila(y);
        nuevo=insertarColumna(nuevo,nodoFila);
        nuevo=insertarFila(nuevo,nodoColumna);
        return;
    //4 caso: Columna exista y fila exista
    }else if(nodoColumna!=NULL && nodoFila!=NULL){
        std::cout << "caso 4"<< std::endl;
        nuevo=insertarColumna(nuevo,nodoFila);
        nuevo=insertarFila(nuevo,nodoColumna);
        return;
    }


}
void Matriz3D::generarNuevaMatriz(int layer)
{
    tamanioCubo++;
    std::cout << raiz->dato<< std::endl;
    std::cout << "=============================="<< std::endl;

    std::string copiaTamanio ="";
    copiaTamanio = static_cast<std::ostringstream*>(&(std::ostringstream() << tamanioCubo))->str();
    //Unir las raices como una lista doblemnte Enlazada
    NodoMatriz3D *nuevaMatriz = new NodoMatriz3D(-1,-1,("Raiz "+copiaTamanio),layer,"","","","");
    std::cout << nuevaMatriz->dato<< std::endl;
    std::cout << "+++++++++++++++"<< std::endl;
    ////////////////////////
    raiz=nuevaMatriz;
    ////////////////ORDENAR MATRIZ


    NodoMatriz3D *temp1;
    NodoMatriz3D *temp2;
    if(primeraMatriz==NULL)
    {
        //primeraMatriz=nuevaMatriz;
        primeraMatriz=raiz;
        raiz->frente=NULL;
        raiz->fondo=NULL;
        //nuevaMatriz->frente=NULL;
        //nuevaMatriz->fondo=NULL;
        std::cout << "ENTRO EN PRIMER IF"<< std::endl;
    }
    else{
        temp1=primeraMatriz;
        std::cout << "ENTRO EN ELSE"<< std::endl;
        while(temp1!=NULL){
            temp2=temp1->frente;
            if(raiz->nivelCapa<temp1->nivelCapa){
                raiz->frente=primeraMatriz;
                primeraMatriz->fondo=raiz;
                primeraMatriz=raiz;
                std::cout << "ENTRO EN SEGUNDO IF"<< std::endl;
                break;
            }
            else{
                if(raiz->nivelCapa>temp1->nivelCapa&&temp2==NULL){
                    temp1->frente=raiz;
                    raiz->fondo=temp1;
                    raiz->frente=NULL;
                    break;
                }
                else{
                    if(temp1->nivelCapa<raiz->nivelCapa&&temp2->nivelCapa>raiz->nivelCapa){
                        temp1->frente=raiz;
                        raiz->fondo=temp1;
                        raiz->frente=temp2;
                        temp2->fondo=raiz;
                        std::cout << "ENTRO EN TERCER IF"<< std::endl;
                        break;
                    }else{
                        temp1=temp1->frente;
                    }

                }
            }
        }
    }
    /*if(raiz->frente==NULL){
        raiz->frente=primeraMatriz;
        std::cout << "ENTRO EN CUARTO IF IF"<< std::endl;
    }*/
    //NodoMatriz3D *aux;
    //aux=raiz;
   /* while(raiz->frente!=nullptr)
    {
        raiz=raiz->frente;
    }*/
    /*ultimaMatriz=nuevaMatriz;
    raiz->frente=ultimaMatriz;
    ultimaMatriz->fondo = raiz;

    raiz->frente=nuevaMatriz;
    nuevaMatriz->fondo=raiz;
    raiz=nuevaMatriz;
    ultimaMatriz=raiz;*/
    std::cout << raiz->dato<< std::endl;
    std::cout << "-----------------------"<< std::endl;
    std::cout << primeraMatriz->dato<< std::endl;
    std::cout << "////////////////////////////"<< std::endl;


}
void Matriz3D::imprimirRaiz()
{
    NodoMatriz3D *temporal;
    temporal = primeraMatriz;
    while(temporal!=NULL){
        std::cout << temporal->nivelCapa<<temporal->dato<<" RECORRIDO"<< std::endl;
        temporal=temporal->frente;
    }
}
void Matriz3D::recorrerMatriz()
{
    NodoMatriz3D *aux;
    NodoMatriz3D *aux1;
    NodoMatriz3D *auxRaiz;
    aux = primeraMatriz;
    auxRaiz=aux->frente;
    bool condicion = true;
    while(condicion){
        while(aux != NULL){
            if(aux->abajo!=NULL)
            {
               aux = aux->abajo;
            }
            else
            {
                break;
            }
            if(aux->siguiente!=NULL)
            {
                aux1 = aux->siguiente;
            }
            else
            {
                break;
            }
            //aux1=aux;
            while(aux1 != NULL){
                cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
            }
       // aux = aux->abajo;
        cout<<""<<endl;
        }
        aux=auxRaiz;
        if(aux!=NULL){
            //aux= aux->frente;
            auxRaiz=auxRaiz->frente;
        }else
        {
            condicion= false;
            break;
        }
    }

}
void Matriz3D::mostrarCapasCubo(NodoMatriz3D *auxNodo)
{
    NodoMatriz3D *aux;
    aux =auxNodo;
    std::cout << ""<<std::endl;
    while(aux!=NULL){
        if(aux->nivelCapa!=0)
            {
                std::cout <<"---  "<<aux->nivelCapa<<" "<<aux->dato<<"  ---"<<std::endl;

            }
            aux=aux->frente;
    }
    std::cout <<"--  "<<"-1 Todo el Cubo"<<"  ---"<<std::endl;
}
void Matriz3D::pruebaGraficar(NodoMatriz3D *nodoAux, int capa)
{
    NodoMatriz3D *temp;
    temp =nodoAux;
    std::cout << ""<<std::endl;
    while(temp!=NULL){
        if(temp->nivelCapa==capa)
            {
               break;

            }
            temp=temp->frente;
    }
    if(temp==NULL)
    {
         std::cout <<"Numero de capa Incorrecto"<<std::endl;
    }
    else
    {
        if(capa==-1)
        {
            std::cout <<"GRAFICAR TODO EL CUBO"<<std::endl;
        }else
        {
            ofstream archivo;
    archivo.open("CapaMatriz.dot",ios::out);//abriendo el archivo
    archivo<<"digraph G {"<<endl;
    archivo<<"node [shape=box, color=cornflowerblue ];"<<endl;
    NodoMatriz3D *aux;
    NodoMatriz3D *aux1;
    //NodoMatriz3D *auxRaiz;
    aux = temp;
    //auxRaiz=aux->frente;
    bool condicion = true;
    while(condicion){
        while(aux != NULL){
            /*if(aux->siguiente!=NULL)
            {
               aux = aux->siguiente;
            }
            else
            {
                break;
            }
            if(aux->abajo!=NULL)
            {
                aux1 = aux->abajo;
            }
            else
            {
                break;
            }*/
            aux1=aux;
            while(aux1 != NULL){
                if(aux1->dato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->abajo!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();

                        if(aux1->abajo->dato=="x"){
                                std::ifstream fileIn( "CapaMatriz.dot" );                   // Open for reading

                                std::stringstream buffer;                             // Store contents in a std::string
                                buffer << fileIn.rdbuf();
                                std::string contents = buffer.str();

                                fileIn.close();
                                if(!contents.empty())
                                {
                                    contents.resize(contents.size()-4);
                                }                                    // Remove last character


                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                    if(recorrer->dato=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<endl;
                                }


                        }else if (aux1->dato=="Fila"||temp->dato==aux1->dato){
                            if(aux1->siguiente!=NULL)
                            {
                                if(aux1->siguiente->dato=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                    if(recorrer->dato=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){

                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                }
                            }

                        }else{
                            if(aux1->siguiente!=NULL)
                            {


                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;

                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
        //aux=auxRaiz;
        //if(aux!=NULL){
            //aux= aux->frente;
          //  auxRaiz=auxRaiz->frente;
        //}else
        //{
            condicion= false;
            break;
        //}
        }
        archivo<<"}";                                  // Output contents with removed character
        //archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
        system("dot -Tjpg CapaMatriz.dot -o imagenCapaMatriz.jpg"); // CREANDO EL GRAPHVIZ
        system("imagenCapaMatriz.jpg");


    /*while(condicion){
        while(aux != NULL){
            if(aux->abajo!=NULL)
            {
               aux = aux->abajo;
            }
            else
            {
                break;
            }
            if(aux->siguiente!=NULL)
            {
                aux1 = aux->siguiente;
            }
            else
            {
                break;
            }
            //aux1=aux;
            while(aux1 != NULL){
                if(aux1->dato!="x")
                {
                    cout << aux1->dato<<" ";

                }
                aux1 = aux1->siguiente;
            }
       // aux = aux->abajo;
        cout<<""<<endl;
        }
        //aux=auxRaiz;
        //if(aux!=NULL){
            //aux= aux->frente;
          //  auxRaiz=auxRaiz->frente;
        //}else
        //{
            condicion= false;
            break;
        //}
    }*/
        }

    }




}
