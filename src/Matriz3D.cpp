#include "Matriz3D.h"
#include <iostream>
#include <string>
#include <sstream>

Matriz3D::Matriz3D()
{
    this->raiz= new NodoMatriz3D(-1,-1,"Primera Capa");
    this->primeraMatriz=raiz;
    this->ultimaMatriz=raiz;
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
    aux= new NodoMatriz3D(x,-1,"Col");
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
    aux= new NodoMatriz3D(-1,y,"Fila");
    ///////////////////////
    NodoMatriz3D *fila;
    fila = insertarFila(aux,cabezaFila);
    return fila;
}
void Matriz3D::insertarElemento(int x, int y, std::string dato)
{
    NodoMatriz3D *nuevo;
    nuevo= new NodoMatriz3D(x,y,dato);
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
void Matriz3D::generarNuevaMatriz(std::string nombreArchivo)
{
    tamanioCubo++;
    std::cout << raiz->dato<< std::endl;
    std::cout << "=============================="<< std::endl;

    std::string copiaTamanio ="";
    copiaTamanio = static_cast<std::ostringstream*>(&(std::ostringstream() << tamanioCubo))->str();
    //Unir las raices como una lista doblemnte Enlazada
    NodoMatriz3D *nuevaMatriz = new NodoMatriz3D(-1,-1,(nombreArchivo));
    std::cout << nuevaMatriz->dato<< std::endl;
    std::cout << "+++++++++++++++"<< std::endl;
    //NodoMatriz3D *aux;
    //aux=raiz;
   /* while(raiz->frente!=nullptr)
    {
        raiz=raiz->frente;
    }*/
    /*ultimaMatriz=nuevaMatriz;
    raiz->frente=ultimaMatriz;
    ultimaMatriz->fondo = raiz;*/

    raiz->frente=nuevaMatriz;
    nuevaMatriz->fondo=raiz;
    raiz=nuevaMatriz;
    ultimaMatriz=raiz;
    std::cout << raiz->dato<< std::endl;
    std::cout << "-----------------------"<< std::endl;
    std::cout << primeraMatriz->dato<< std::endl;
    std::cout << "////////////////////////////"<< std::endl;


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
            aux1 = aux;
            while(aux1 != NULL){
                cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
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
