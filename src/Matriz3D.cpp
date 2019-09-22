#include "Matriz3D.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
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
        //std::cout << "caso 1"<< std::endl;
        nodoColumna = crearColumna(x);
        nodoFila = crearFila(y);
        nuevo = insertarColumna(nuevo,nodoFila);
        nuevo = insertarFila(nuevo,nodoColumna);
        return;
     //2 caso: Columna no exista y fila exista
    }else if(nodoColumna==NULL && nodoFila!=NULL){
        //std::cout << "caso 2"<< std::endl;
        nodoColumna=crearColumna(x);
        nuevo=insertarColumna(nuevo,nodoFila);
        nuevo=insertarFila(nuevo,nodoColumna);
        return;
     //3 caso: Columna exista y fila no exista
    }else if(nodoColumna!=NULL && nodoFila==NULL){
        //std::cout << "caso 3"<< std::endl;
        nodoFila=crearFila(y);
        nuevo=insertarColumna(nuevo,nodoFila);
        nuevo=insertarFila(nuevo,nodoColumna);
        return;
    //4 caso: Columna exista y fila exista
    }else if(nodoColumna!=NULL && nodoFila!=NULL){
        //std::cout << "caso 4"<< std::endl;
        nuevo=insertarColumna(nuevo,nodoFila);
        nuevo=insertarFila(nuevo,nodoColumna);
        return;
    }


}
void Matriz3D::generarNuevaMatriz(int layer)
{
    tamanioCubo++;
    //std::cout << raiz->dato<< std::endl;
    //std::cout << "=============================="<< std::endl;

    std::string copiaTamanio ="";
    copiaTamanio = static_cast<std::ostringstream*>(&(std::ostringstream() << tamanioCubo))->str();
    //Unir las raices como una lista doblemnte Enlazada
    NodoMatriz3D *nuevaMatriz = new NodoMatriz3D(-1,-1,("Raiz "+copiaTamanio),layer,"","","","");
    //std::cout << nuevaMatriz->dato<< std::endl;
    //std::cout << "+++++++++++++++"<< std::endl;
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
        //std::cout << "ENTRO EN PRIMER IF"<< std::endl;
    }
    else{
        temp1=primeraMatriz;
        //std::cout << "ENTRO EN ELSE"<< std::endl;
        while(temp1!=NULL){
            temp2=temp1->frente;
            if(raiz->nivelCapa<temp1->nivelCapa){
                raiz->frente=primeraMatriz;
                primeraMatriz->fondo=raiz;
                primeraMatriz=raiz;
                //std::cout << "ENTRO EN SEGUNDO IF"<< std::endl;
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
                        //std::cout << "ENTRO EN TERCER IF"<< std::endl;
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
    //std::cout << raiz->dato<< std::endl;
    //std::cout << "-----------------------"<< std::endl;
    //std::cout << primeraMatriz->dato<< std::endl;
    //std::cout << "////////////////////////////"<< std::endl;


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
Matriz3D Matriz3D::filtroNB(std::string filtro, Matriz3D copiaMatriz)
{
    NodoMatriz3D *aux;
    NodoMatriz3D *aux1;
    NodoMatriz3D *auxRaiz;
    aux = copiaMatriz.primeraMatriz;
    cout<<aux->dato<<endl;
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
                if(aux1->dato=="x"||aux1->dato=="X"){
                    aux1 = aux1->siguiente;
                }else{
                    if(filtro=="Negativo"){


                        aux1 = aux1->siguiente;
                    }else if(filtro=="BlancoNegro"){
                        cout<<aux->dato<<endl;
                        system("pause>nul");
                        string R="";
                        string G="";
                        string B="";
                        string color="";
                        int contador=0;
                        color=aux->dato;
                        std::string delimitador = "-";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = color.find(delimitador)) != std::string::npos) {
                        token = color.substr(0, pos);
                        cout<<token+"dentrowhile"<<endl;
                        system("pause>nul");
                        if(contador==0){
                            R=token;
                        }else if(contador==1)
                        {
                            G=token;
                        }

                        color.erase(0, pos + delimitador.length());
                       contador++;
                    }
                       B=color;
                       int r=0;
                       std::istringstream Re(R);
                       Re>>r;
                       int g=0;
                       std::istringstream Ge(G);
                       Ge>>g;
                       int b=0;
                       std::istringstream Be(B);
                       Be>>b;
                        float r2=r*0.299;
                        float g2=g*0.587;
                        float b2=b*0.144;
                        int RGB = r2+g2+b2;
                        color=static_cast<std::ostringstream*>(&(std::ostringstream() << RGB))->str();
                        string datoNuevo="";
                        datoNuevo= color+"-"+color+"-"+color;
                        aux1->dato=datoNuevo;
                        cout<<aux1->dato+"RESULTADO"<<endl;
                        system("pause>nul");
                        aux1 = aux1->siguiente;
                    }
                }
                //cout << aux1->dato<<" ";

            }
       // aux = aux->abajo;
        //cout<<""<<endl;
        }
        aux=auxRaiz;
        cout<<aux->dato<<endl;
        if(aux!=NULL){
            //aux= aux->frente;
            auxRaiz=auxRaiz->frente;
        }else
        {
            condicion= false;
            break;
        }
    }
    return copiaMatriz;
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
void Matriz3D::mostrarCapasConfigM(NodoMatriz3D *auxNodo)
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
}
void Matriz3D::edicionManualColor(NodoMatriz3D *nodoAux, int capa, int x, int y, string color)
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
    std::cout << temp->nivelCapa<<std::endl;
    if(temp==NULL){
        cout<<"Numero de Capa incorrecto"<<endl;
    }else
    {
    NodoMatriz3D *aux;
    NodoMatriz3D *aux1;
    std::cout << temp->siguiente->dato+"  "<<temp->siguiente->x<<std::endl;
    aux = temp->siguiente;

        while(aux != NULL){
            if(aux->abajo!=NULL)
            {
               aux = aux->abajo;
               std::cout << "entro en if de abajo"<<std::endl;
            }
            else
            {
                break;
            }
            if(aux->siguiente!=NULL)
            {
                aux1 = aux->siguiente;
                std::cout << "entro en if siguiente"<<std::endl;
            }
            else
            {
                break;
            }
            //aux1=aux;
            while(aux1 != NULL){
                std::cout << aux1->x<<std::endl;
                if(aux1->x==x){
                    std::cout << aux1->y<<std::endl;
                    if(aux1->y==y){
                        aux1->dato=color;
                        cout<<"Todo bien"<<endl;
                        break;
                    }
                }
                aux1 = aux1->siguiente;
            }
       // aux = aux->abajo;
        //cout<<""<<endl;
        if(aux1!=NULL){
            if(aux1->x==x){
                if(aux1->y==y){
                //aux1->dato=color;
                    break;
                    }
                }
            }
        }


    }



}

void Matriz3D::pruebaGraficar(NodoMatriz3D *nodoAux, int capa,string nombre)
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
    if(capa==-1)
    {
            NodoMatriz3D *temp2;
            temp2 =nodoAux;
            int contador=1;
            std::string copiaContador="";
            std::cout << ""<<std::endl;
            while(temp2!=NULL){
            if(temp2->nivelCapa==contador)
                {
                    std::cout << temp2->nivelCapa<<std::endl;
                break;

                    }
                temp2=temp2->frente;
            }

            std::cout <<"GRAFICAR TODO EL CUBO"<<std::endl;
            ofstream archivo;   /////////Generar Capa por capa

            NodoMatriz3D *aux;
            NodoMatriz3D *aux1;
            //NodoMatriz3D *auxRaiz;

            //auxRaiz=aux->frente;
            bool condicion1=true;
            bool condicion = true;

            while(condicion1){
                    aux = temp2;
                    condicion=true;
            //std::cout << temp2->nivelCapa<<std::endl;
            copiaContador= static_cast<std::ostringstream*>(&(std::ostringstream() << contador))->str();
            std::string auxNombreMatriz3 =nombre+"\\"+nombre+copiaContador+".dot";
            const char *nombreArch = auxNombreMatriz3.c_str();
            archivo.open(nombreArch,ios::out);//abriendo el archivo
            archivo<<"digraph G {"<<endl;
            archivo<<"node [shape=box, color=cornflowerblue ];"<<endl;
                    //aux = temp2;
                while(condicion){
        while(aux != NULL){
            //std::cout << "WHILE AUX!=NULL"<<std::endl;
            aux1=aux;
            while(aux1 != NULL){
                string ignorarX="x";
                string ingorarDato=aux1->dato;
                transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!=ignorarX)
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
                        string ignorarX="x";
                        string ingorarDato2=aux1->abajo->dato;
                        transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                        if(ingorarDato2=="x"){//SI EL DATO QUE ESTA ABAJO ES X ESTO ES PARA LAS COLUMNAS

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                    string ignorarX="x";
                                    string ingorarDato3 = recorrer->dato;
                                    transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                                    transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                    if(ingorarDato3=="x"){
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
                                        if(recorrer->dato!=""){
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            //archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                        }

                                }


                        }else if (aux1->dato=="Fila"||temp2->dato==aux1->dato){//ESTO ES PARA LAS FILAS
                            if(aux1->siguiente!=NULL)
                            {
                                string ingorarDato4=aux1->siguiente->dato;
                                transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                if(ingorarDato4=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                    string ingorarDato5=recorrer->dato;
                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                    if(ingorarDato5=="x"){
                                        recorrer=recorrer->siguiente;//SI ENCUNTRA UN VALOR QUE NO SEA X EN LA FILA LO GUARDA
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){ //BUSCAMOS EL SIGUIENTE VALOR PARA ENLZARLO CON EL ANTERIOR
                                     if(aux1->abajo!=NULL)
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->abajo;
                                            while(aux3!=NULL){
                                            string ingorarDato6=aux3->siguiente->dato;
                                            transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                            if(ingorarDato6=="x")// SI EL VALOR QUE ESTA ABAJO DEL ANTERIROR EL SIGUIENTE A ESE ES X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->siguiente;
                                                while(recorrer2!=NULL)
                                                {
                                                    string ingorarDato7=recorrer2->dato;
                                                    transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                    if(ingorarDato7=="x")
                                                    {
                                                        recorrer2=recorrer2->siguiente;//BUSCAMOS UN VALOR HASTA QUE YA NO SEA X
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;//LO GURDAMOS Y LO ESCRIBIMOS EN EL ARCHIVO
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();

                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                }
                                            }else{// DE LO CONTRARIO SOLO LO VA A ESCRIBIR
                                                if(aux1->dato!=""){

                                                    if(aux3->siguiente->dato!=""){
                                                        string rx7;
                                                        rx7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                                                        string ry7;
                                                        ry7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();
                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<"[dir=both];"<<endl;
                                                        //archivo<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            aux3=aux3->abajo;
                                          }
                                        }
                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{
                                    //if(aux1->dato==temp->dato){
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                    //cout<<aux1->dato+" TERCERO "<<"+"+x<<"-"+y+"*"<<endl;

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                    //}else{

                                    //}
                                }
                            }

                        }
                        else{// PARA ESCRIBIR TODO LO QUE ESTA DENTRO DE LA MATRIZ
                            if(aux1->siguiente!=NULL)
                            {

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;
                                    //archivo<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;




                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 aux = temp2;
while(aux != NULL){

            aux1=aux;
            while(aux1 != NULL){
                string ingorarDato=aux1->dato;
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->siguiente!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->y))->str();
                        string ingorarDato2=aux1->siguiente->dato;
                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                        if(ingorarDato2=="x"){ ////SI EL DATO QUE ESTA DESPUES ES UNA X

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->siguiente;
                                while(recorrer!=NULL){
                                    string ingorarDato3=recorrer->dato;
                                    transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                    if(ingorarDato3=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                        if(recorrer->dato!=""){
                                                if(aux1->dato!=""){
                                            archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            archivo<<"}"<<endl;
                                            /*archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                             archivo<<"}"<<endl;*/
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                                }
                                        }

                                }


                        }else if (aux1->dato=="Col"||temp2->dato==aux1->dato){ ////ESTO ES PARA INGRESAR COLUMNAS Y EL NODO RAIZ
                            if(aux1->abajo!=NULL)
                            {
                                string ingorarDato4=aux1->abajo->dato;
                                transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                if(ingorarDato4=="x") //SI EL DATO ABAJO DE LA COLUMNA ES UNA X
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->abajo;
                                    while(recorrer!=NULL){//RECORRO PARA ABAJO HASTA ENCONTRAR UNA X
                                        string ingorarDato5=recorrer->dato;
                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                    if(ingorarDato5=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                     if(aux1->siguiente!=NULL)//AHORA VOY BUSCANDO COLUMNAS PARA ENLAZAR LA ANTERIOR
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->siguiente;
                                            while(aux3!=NULL){//RECORRO TODAS LAS COLUMNAS
                                            string ingorarDato6=aux3->abajo->dato;
                                            transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                            if(ingorarDato6=="x")//SI LO QUE HAY ABAJO ES UNA X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->abajo;
                                                while(recorrer2!=NULL) //EN CADA COLUMNA LOS NODOS DE ABAJO HASTA ENCONTRAR NO X
                                                {
                                                    string ingorarDato7=recorrer2->dato;
                                                    transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                    if(ingorarDato7=="x")
                                                    {
                                                        recorrer2=recorrer2->abajo;
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();
                                                    if(aux3->dato!=""){
                                                      if(aux1->dato!=""){
                                                    archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;
                                                    /*archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;*/
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                    }
                                                    }
                                                }
                                            }
                                            else{//SI LO QUE HAY ABAJO NO ES UNA X
                                                    if(aux1->siguiente->dato!=""){
                                                        if(aux1->dato!=""){
                                                archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;

                                                archivo<<"}"<<endl;
                                                /*archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                archivo<<"}"<<endl;*/
                                                break;
                                                        }
                                                    }
                                            }
                                            aux3=aux3->siguiente;
                                          }
                                        }

                                }
                                }
                                else{//SI LO QUE ES ABAJO NO ES X
                                        //if(aux1->dato==temp->dato)
                                        //{
                                            if (aux1->siguiente!=NULL){//SI NO HAY X RECORRO LAS COLUMNAS
                                                NodoMatriz3D *aux4;
                                                aux4=aux1->siguiente;
                                                while(aux4!=NULL){
                                                    if(aux4->abajo!=NULL){
                                                        string ingorarDato8=aux4->abajo->dato;
                                                        transform(ingorarDato8.begin(), ingorarDato8.end(), ingorarDato8.begin(), ::tolower);
                                                        if(ingorarDato8=="x"){
                                                             NodoMatriz3D *recorrer;
                                                            recorrer=aux4->abajo;
                                                            while(recorrer!=NULL){//RECORRO TODAS LAS FILAS EN BUSCA DE UNA X
                                                                string ingorarDato9=recorrer->dato;
                                                                transform(ingorarDato9.begin(), ingorarDato9.end(), ingorarDato9.begin(), ::tolower);
                                                                if(ingorarDato9=="x"){
                                                                    recorrer=recorrer->abajo;
                                                                }else{
                                                                    break;
                                                                }

                                                            }
                                                            if(recorrer!=NULL){//SI ENCUENTRO ALGO QUE NO SEA X
                                                                if(recorrer->dato!=""){// SI ES DIFERENTE DE VACIO
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                                                        if(recorrer->dato!=""){
                                                                        if(aux1->dato==temp2->dato)//PARA EL PRIMERO NODO, NODO RAIZ
                                                                        {
                                                                            if(recorrer->arriba!=NULL){
                                                                                NodoMatriz3D *aux6;
                                                                                aux6=recorrer->arriba;
                                                                                while(recorrer!=NULL){
                                                                                        string ingorarDato10=aux6->dato;
                                                                                        transform(ingorarDato10.begin(), ingorarDato10.end(), ingorarDato10.begin(), ::tolower);
                                                                                    if(ingorarDato10=="x"){
                                                                                        aux6= aux6->arriba;
                                                                                    }else{
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(aux6!=NULL){//ENLAZA EL PRIMERO NODO CON OTRO NODO QUE TENGA UN VALOR
                                                                                   string rx4;
                                                                                    rx4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->x))->str();
                                                                                    string ry4;
                                                                                    ry4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->y))->str();
                                                                                    if(aux6->dato!=""){
                                                                                            if(aux1->dato!=""){
                                                                                    archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\""<<"[dir=both];"<<endl;

                                                                                    archivo<<"}"<<endl;
                                                                                    /*archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                                    archivo<<"}"<<endl;*/
                                                                                    break;
                                                                                            }
                                                                                    }
                                                                                }
                                                                            }

                                                                        }else{//SI NO ES EL NODO RAIZ
                                                                            string rx5;
                                                                            rx5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                            string ry5;
                                                                            ry5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->y))->str();
                                                                            if(aux4->dato!=""){
                                                                                    if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                    }
                                                                            }
                                                                        }
                                                                        }
                                                                }
                                                            }
                                                        }else{//SI LO QUE HAY ABAJO DE UNA COLUMNA NO ES UNA X
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() <<  aux4->y))->str();
                                                                        if(aux4->dato!=""){
                                                                                if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<< aux4->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<< aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                }
                                                                        }
                                                        }
                                                    }

                                                    aux4=aux4->siguiente;
                                                }
                                            }

                                }
                            }

                        }
                        else{//INGRESA TODO LO QUE ESTAN EN MEDIO
                            if(aux1->siguiente!=NULL)
                            {       if(aux1->dato!=""){
                                    if(aux1->siguiente->dato!=""){
                                    archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;


                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;
                                    archivo<<"}"<<endl;
                                    /*archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    archivo<<"}"<<endl;*/
                                    }
                            }


                            }

                        }

                    }


                }
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
            std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+nombre+copiaContador+".dot"+" -o imagenCapaMatriz"+copiaContador+".jpg";
            const char *nombreArch2 = auxNombreMatriz4.c_str();
            system(nombreArch2); // CREANDO EL GRAPHVIZ
            std::string auxNombreMatriz5 ="imagenCapaMatriz"+copiaContador+".jpg";
            const char *nombreArch3 = auxNombreMatriz5.c_str();
            system(nombreArch3);
            contador=contador+1;
            while(temp2!=NULL){
            if(temp2->nivelCapa==contador)
                {
                    //std::cout <<"HOLA WAPO"<<temp2->nivelCapa<<std::endl;
                    break;
                    }
                temp2=temp2->frente;
            }
            if(temp2==NULL){
                condicion1=false;
                break;
            }
            }

    }else if(temp==NULL){
        std::cout <<"Numero de capa Incorrecto"<<std::endl;
    }
    else
    {

        //{
    ofstream archivo;   /////////Generar Capa por capa
    std::string auxNombreMatriz3 =nombre+"\\"+nombre+".dot";
    const char *nombreArch = auxNombreMatriz3.c_str();
    archivo.open(nombreArch,ios::out);//abriendo el archivo
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
                string ingorarDato=aux1->dato;
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
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
                        string ingorarDato1=aux1->abajo->dato;
                        transform(ingorarDato1.begin(), ingorarDato1.end(), ingorarDato1.begin(), ::tolower);
                        if(ingorarDato1=="x"){//SI EL DATO QUE ESTA ABAJO ES X ESTO ES PARA LAS COLUMNAS

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                        string ingorarDato2=recorrer->dato;
                                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                                    if(ingorarDato2=="x"){
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
                                        if(recorrer->dato!=""){
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            //archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                        }

                                }


                        }else if (aux1->dato=="Fila"||temp->dato==aux1->dato){//ESTO ES PARA LAS FILAS
                            if(aux1->siguiente!=NULL)
                            {
                                string ingorarDato3=aux1->siguiente->dato;
                                transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                if(ingorarDato3=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                        string ingorarDato4=recorrer->dato;
                                        transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                    if(ingorarDato4=="x"){
                                        recorrer=recorrer->siguiente;//SI ENCUNTRA UN VALOR QUE NO SEA X EN LA FILA LO GUARDA
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){ //BUSCAMOS EL SIGUIENTE VALOR PARA ENLZARLO CON EL ANTERIOR
                                     if(aux1->abajo!=NULL)
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->abajo;
                                            while(aux3!=NULL){
                                                    string ingorarDato5=aux3->siguiente->dato;
                                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                            if(ingorarDato5=="x")// SI EL VALOR QUE ESTA ABAJO DEL ANTERIROR EL SIGUIENTE A ESE ES X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->siguiente;
                                                while(recorrer2!=NULL)
                                                {
                                                    string ingorarDato6=recorrer2->dato;
                                                    transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                                    if(ingorarDato6=="x")
                                                    {
                                                        recorrer2=recorrer2->siguiente;//BUSCAMOS UN VALOR HASTA QUE YA NO SEA X
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;//LO GURDAMOS Y LO ESCRIBIMOS EN EL ARCHIVO
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();

                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                }
                                            }else{// DE LO CONTRARIO SOLO LO VA A ESCRIBIR
                                                if(aux1->dato!=""){
                                                    if(aux3->siguiente->dato!=""){
                                                        string rx7;
                                                        rx7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                                                        string ry7;
                                                        ry7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();
                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<"[dir=both];"<<endl;
                                                        //archivo<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            aux3=aux3->abajo;
                                          }
                                        }
                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{
                                    //if(aux1->dato==temp->dato){
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                    //cout<<aux1->dato+" TERCERO "<<"+"+x<<"-"+y+"*"<<endl;

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                    //}else{

                                    //}
                                }
                            }

                        }
                        else{// PARA ESCRIBIR TODO LO QUE ESTA DENTRO DE LA MATRIZ
                            if(aux1->siguiente!=NULL)
                            {

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;
                                    //archivo<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;




                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 aux = temp;
while(aux != NULL){

            aux1=aux;
            while(aux1 != NULL){
                    string ingorarDato=aux1->dato;
                    transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->siguiente!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->y))->str();
                        string ingorarDato1=aux1->siguiente->dato;
                        transform(ingorarDato1.begin(), ingorarDato1.end(), ingorarDato1.begin(), ::tolower);
                        if(ingorarDato1=="x"){ ////SI EL DATO QUE ESTA DESPUES ES UNA X

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->siguiente;
                                while(recorrer!=NULL){
                                        string ingorarDato2=recorrer->dato;
                                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                                    if(ingorarDato2=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                        if(recorrer->dato!=""){
                                                if(aux1->dato!=""){
                                            archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            archivo<<"}"<<endl;
                                            /*archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                             archivo<<"}"<<endl;*/
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                                }
                                        }

                                }


                        }else if (aux1->dato=="Col"||temp->dato==aux1->dato){ ////ESTO ES PARA INGRESAR COLUMNAS Y EL NODO RAIZ
                            if(aux1->abajo!=NULL)
                            {
                                string ingorarDato3=aux1->abajo->dato;
                                transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                if(ingorarDato3=="x") //SI EL DATO ABAJO DE LA COLUMNA ES UNA X
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->abajo;
                                    while(recorrer!=NULL){//RECORRO PARA ABAJO HASTA ENCONTRAR UNA X
                                    string ingorarDato4=recorrer->dato;
                                    transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                    if(ingorarDato4=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                     if(aux1->siguiente!=NULL)//AHORA VOY BUSCANDO COLUMNAS PARA ENLAZAR LA ANTERIOR
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->siguiente;
                                            while(aux3!=NULL){//RECORRO TODAS LAS COLUMNAS
                                            string ingorarDato5=aux3->abajo->dato;
                                            transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                            if(ingorarDato5=="x")//SI LO QUE HAY ABAJO ES UNA X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->abajo;
                                                while(recorrer2!=NULL) //EN CADA COLUMNA LOS NODOS DE ABAJO HASTA ENCONTRAR NO X
                                                {
                                                    string ingorarDato6=recorrer2->dato;
                                                    transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                                    if(ingorarDato6=="x")
                                                    {
                                                        recorrer2=recorrer2->abajo;
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();
                                                    if(aux3->dato!=""){
                                                      if(aux1->dato!=""){
                                                    archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;
                                                    /*archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;*/
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                    }
                                                    }
                                                }
                                            }
                                            else{//SI LO QUE HAY ABAJO NO ES UNA X
                                                    if(aux1->siguiente->dato!=""){
                                                        if(aux1->dato!=""){
                                                archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;

                                                archivo<<"}"<<endl;
                                                /*archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                archivo<<"}"<<endl;*/
                                                break;
                                                        }
                                                    }
                                            }
                                            aux3=aux3->siguiente;
                                          }
                                        }

                                }
                                }
                                else{//SI LO QUE ES ABAJO NO ES X
                                        //if(aux1->dato==temp->dato)
                                        //{
                                            if (aux1->siguiente!=NULL){//SI NO HAY X RECORRO LAS COLUMNAS
                                                NodoMatriz3D *aux4;
                                                aux4=aux1->siguiente;
                                                while(aux4!=NULL){
                                                    if(aux4->abajo!=NULL){
                                                            string ingorarDato7=aux4->abajo->dato;
                                                            transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                        if(ingorarDato7=="x"){
                                                             NodoMatriz3D *recorrer;
                                                            recorrer=aux4->abajo;
                                                            while(recorrer!=NULL){//RECORRO TODAS LAS FILAS EN BUSCA DE UNA X
                                                                string ingorarDato8=recorrer->dato;
                                                                transform(ingorarDato8.begin(), ingorarDato8.end(), ingorarDato8.begin(), ::tolower);
                                                                if(ingorarDato8=="x"){
                                                                    recorrer=recorrer->abajo;
                                                                }else{
                                                                    break;
                                                                }

                                                            }
                                                            if(recorrer!=NULL){//SI ENCUENTRO ALGO QUE NO SEA X
                                                                if(recorrer->dato!=""){// SI ES DIFERENTE DE VACIO
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                                                        if(recorrer->dato!=""){
                                                                        if(aux1->dato==temp->dato)//PARA EL PRIMERO NODO, NODO RAIZ
                                                                        {
                                                                            if(recorrer->arriba!=NULL){
                                                                                NodoMatriz3D *aux6;
                                                                                aux6=recorrer->arriba;
                                                                                while(recorrer!=NULL){
                                                                                    string ingorarDato9=aux6->dato;
                                                                                    transform(ingorarDato9.begin(), ingorarDato9.end(), ingorarDato9.begin(), ::tolower);
                                                                                    if(ingorarDato9=="x"){
                                                                                        aux6= aux6->arriba;
                                                                                    }else{
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(aux6!=NULL){//ENLAZA EL PRIMERO NODO CON OTRO NODO QUE TENGA UN VALOR
                                                                                   string rx4;
                                                                                    rx4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->x))->str();
                                                                                    string ry4;
                                                                                    ry4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->y))->str();
                                                                                    if(aux6->dato!=""){
                                                                                            if(aux1->dato!=""){
                                                                                    archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\""<<"[dir=both];"<<endl;

                                                                                    archivo<<"}"<<endl;
                                                                                    /*archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                                    archivo<<"}"<<endl;*/
                                                                                    break;
                                                                                            }
                                                                                    }
                                                                                }
                                                                            }

                                                                        }else{//SI NO ES EL NODO RAIZ
                                                                            string rx5;
                                                                            rx5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                            string ry5;
                                                                            ry5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->y))->str();
                                                                            if(aux4->dato!=""){
                                                                                    if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                    }
                                                                            }
                                                                        }
                                                                        }
                                                                }
                                                            }
                                                        }else{//SI LO QUE HAY ABAJO DE UNA COLUMNA NO ES UNA X
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() <<  aux4->y))->str();
                                                                        if(aux4->dato!=""){
                                                                                if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<< aux4->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<< aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                }
                                                                        }
                                                        }
                                                    }

                                                    aux4=aux4->siguiente;
                                                }
                                            }

                                }
                            }

                        }
                        else{//INGRESA TODO LO QUE ESTAN EN MEDIO
                            if(aux1->siguiente!=NULL)
                            {       if(aux1->dato!=""){
                                    if(aux1->siguiente->dato!=""){
                                    archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;


                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;
                                    archivo<<"}"<<endl;
                                    /*archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    archivo<<"}"<<endl;*/
                                    }
                            }


                            }

                        }

                    }


                }
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
        std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+nombre+".dot"+" -o imagenCapaMatriz.jpg";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        system(nombreArch2); // CREANDO EL GRAPHVIZ
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
        //}

    }




}
void Matriz3D::graficarFiltro(NodoMatriz3D *nodoAux, int capa,std::string nombre)
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
    if(capa==-1)
    {
            NodoMatriz3D *temp2;
            temp2 =nodoAux;
            int contador=1;
            std::string copiaContador="";
            std::cout << ""<<std::endl;
            while(temp2!=NULL){
            if(temp2->nivelCapa==contador)
                {
                    std::cout << temp2->nivelCapa<<std::endl;
                break;

                    }
                temp2=temp2->frente;
            }

            std::cout <<"GRAFICAR TODO EL CUBO"<<std::endl;
            ofstream archivo;   /////////Generar Capa por capa

            NodoMatriz3D *aux;
            NodoMatriz3D *aux1;
            //NodoMatriz3D *auxRaiz;

            //auxRaiz=aux->frente;
            bool condicion1=true;
            bool condicion = true;

            while(condicion1){
                    aux = temp2;
                    condicion=true;
            //std::cout << temp2->nivelCapa<<std::endl;
            copiaContador= static_cast<std::ostringstream*>(&(std::ostringstream() << contador))->str();
            std::string auxNombreMatriz3 =nombre+"\\"+"Filtro"+nombre+copiaContador+".dot";
            const char *nombreArch = auxNombreMatriz3.c_str();
            archivo.open(nombreArch,ios::out);//abriendo el archivo
            archivo<<"digraph G {"<<endl;
            archivo<<"node [shape=box, color=cornflowerblue ];"<<endl;
                    //aux = temp2;
                while(condicion){
        while(aux != NULL){
            //std::cout << "WHILE AUX!=NULL"<<std::endl;
            aux1=aux;
            while(aux1 != NULL){
                string ignorarX="x";
                string ingorarDato=aux1->dato;
                transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!=ignorarX)
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
                        string ignorarX="x";
                        string ingorarDato2=aux1->abajo->dato;
                        transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                        if(ingorarDato2=="x"){//SI EL DATO QUE ESTA ABAJO ES X ESTO ES PARA LAS COLUMNAS

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                    string ignorarX="x";
                                    string ingorarDato3 = recorrer->dato;
                                    transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                                    transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                    if(ingorarDato3=="x"){
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
                                        if(recorrer->dato!=""){
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            //archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                        }

                                }


                        }else if (aux1->dato=="Fila"||temp2->dato==aux1->dato){//ESTO ES PARA LAS FILAS
                            if(aux1->siguiente!=NULL)
                            {
                                string ingorarDato4=aux1->siguiente->dato;
                                transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                if(ingorarDato4=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                    string ingorarDato5=recorrer->dato;
                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                    if(ingorarDato5=="x"){
                                        recorrer=recorrer->siguiente;//SI ENCUNTRA UN VALOR QUE NO SEA X EN LA FILA LO GUARDA
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){ //BUSCAMOS EL SIGUIENTE VALOR PARA ENLZARLO CON EL ANTERIOR
                                     if(aux1->abajo!=NULL)
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->abajo;
                                            while(aux3!=NULL){
                                            string ingorarDato6=aux3->siguiente->dato;
                                            transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                            if(ingorarDato6=="x")// SI EL VALOR QUE ESTA ABAJO DEL ANTERIROR EL SIGUIENTE A ESE ES X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->siguiente;
                                                while(recorrer2!=NULL)
                                                {
                                                    string ingorarDato7=recorrer2->dato;
                                                    transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                    if(ingorarDato7=="x")
                                                    {
                                                        recorrer2=recorrer2->siguiente;//BUSCAMOS UN VALOR HASTA QUE YA NO SEA X
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;//LO GURDAMOS Y LO ESCRIBIMOS EN EL ARCHIVO
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();

                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                }
                                            }else{// DE LO CONTRARIO SOLO LO VA A ESCRIBIR
                                                if(aux1->dato!=""){

                                                    if(aux3->siguiente->dato!=""){
                                                        string rx7;
                                                        rx7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                                                        string ry7;
                                                        ry7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();
                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<"[dir=both];"<<endl;
                                                        //archivo<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            aux3=aux3->abajo;
                                          }
                                        }
                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{
                                    //if(aux1->dato==temp->dato){
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                    //cout<<aux1->dato+" TERCERO "<<"+"+x<<"-"+y+"*"<<endl;

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                    //}else{

                                    //}
                                }
                            }

                        }
                        else{// PARA ESCRIBIR TODO LO QUE ESTA DENTRO DE LA MATRIZ
                            if(aux1->siguiente!=NULL)
                            {

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;
                                    //archivo<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;




                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 aux = temp2;
while(aux != NULL){

            aux1=aux;
            while(aux1 != NULL){
                string ingorarDato=aux1->dato;
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->siguiente!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->y))->str();
                        string ingorarDato2=aux1->siguiente->dato;
                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                        if(ingorarDato2=="x"){ ////SI EL DATO QUE ESTA DESPUES ES UNA X

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->siguiente;
                                while(recorrer!=NULL){
                                    string ingorarDato3=recorrer->dato;
                                    transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                    if(ingorarDato3=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                        if(recorrer->dato!=""){
                                                if(aux1->dato!=""){
                                            archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            archivo<<"}"<<endl;
                                            /*archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                             archivo<<"}"<<endl;*/
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                                }
                                        }

                                }


                        }else if (aux1->dato=="Col"||temp2->dato==aux1->dato){ ////ESTO ES PARA INGRESAR COLUMNAS Y EL NODO RAIZ
                            if(aux1->abajo!=NULL)
                            {
                                string ingorarDato4=aux1->abajo->dato;
                                transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                if(ingorarDato4=="x") //SI EL DATO ABAJO DE LA COLUMNA ES UNA X
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->abajo;
                                    while(recorrer!=NULL){//RECORRO PARA ABAJO HASTA ENCONTRAR UNA X
                                        string ingorarDato5=recorrer->dato;
                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                    if(ingorarDato5=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                     if(aux1->siguiente!=NULL)//AHORA VOY BUSCANDO COLUMNAS PARA ENLAZAR LA ANTERIOR
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->siguiente;
                                            while(aux3!=NULL){//RECORRO TODAS LAS COLUMNAS
                                            string ingorarDato6=aux3->abajo->dato;
                                            transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                            if(ingorarDato6=="x")//SI LO QUE HAY ABAJO ES UNA X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->abajo;
                                                while(recorrer2!=NULL) //EN CADA COLUMNA LOS NODOS DE ABAJO HASTA ENCONTRAR NO X
                                                {
                                                    string ingorarDato7=recorrer2->dato;
                                                    transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                    if(ingorarDato7=="x")
                                                    {
                                                        recorrer2=recorrer2->abajo;
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();
                                                    if(aux3->dato!=""){
                                                      if(aux1->dato!=""){
                                                    archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;
                                                    /*archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;*/
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                    }
                                                    }
                                                }
                                            }
                                            else{//SI LO QUE HAY ABAJO NO ES UNA X
                                                    if(aux1->siguiente->dato!=""){
                                                        if(aux1->dato!=""){
                                                archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;

                                                archivo<<"}"<<endl;
                                                /*archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                archivo<<"}"<<endl;*/
                                                break;
                                                        }
                                                    }
                                            }
                                            aux3=aux3->siguiente;
                                          }
                                        }

                                }
                                }
                                else{//SI LO QUE ES ABAJO NO ES X
                                        //if(aux1->dato==temp->dato)
                                        //{
                                            if (aux1->siguiente!=NULL){//SI NO HAY X RECORRO LAS COLUMNAS
                                                NodoMatriz3D *aux4;
                                                aux4=aux1->siguiente;
                                                while(aux4!=NULL){
                                                    if(aux4->abajo!=NULL){
                                                        string ingorarDato8=aux4->abajo->dato;
                                                        transform(ingorarDato8.begin(), ingorarDato8.end(), ingorarDato8.begin(), ::tolower);
                                                        if(ingorarDato8=="x"){
                                                             NodoMatriz3D *recorrer;
                                                            recorrer=aux4->abajo;
                                                            while(recorrer!=NULL){//RECORRO TODAS LAS FILAS EN BUSCA DE UNA X
                                                                string ingorarDato9=recorrer->dato;
                                                                transform(ingorarDato9.begin(), ingorarDato9.end(), ingorarDato9.begin(), ::tolower);
                                                                if(ingorarDato9=="x"){
                                                                    recorrer=recorrer->abajo;
                                                                }else{
                                                                    break;
                                                                }

                                                            }
                                                            if(recorrer!=NULL){//SI ENCUENTRO ALGO QUE NO SEA X
                                                                if(recorrer->dato!=""){// SI ES DIFERENTE DE VACIO
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                                                        if(recorrer->dato!=""){
                                                                        if(aux1->dato==temp2->dato)//PARA EL PRIMERO NODO, NODO RAIZ
                                                                        {
                                                                            if(recorrer->arriba!=NULL){
                                                                                NodoMatriz3D *aux6;
                                                                                aux6=recorrer->arriba;
                                                                                while(recorrer!=NULL){
                                                                                        string ingorarDato10=aux6->dato;
                                                                                        transform(ingorarDato10.begin(), ingorarDato10.end(), ingorarDato10.begin(), ::tolower);
                                                                                    if(ingorarDato10=="x"){
                                                                                        aux6= aux6->arriba;
                                                                                    }else{
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(aux6!=NULL){//ENLAZA EL PRIMERO NODO CON OTRO NODO QUE TENGA UN VALOR
                                                                                   string rx4;
                                                                                    rx4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->x))->str();
                                                                                    string ry4;
                                                                                    ry4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->y))->str();
                                                                                    if(aux6->dato!=""){
                                                                                            if(aux1->dato!=""){
                                                                                    archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\""<<"[dir=both];"<<endl;

                                                                                    archivo<<"}"<<endl;
                                                                                    /*archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                                    archivo<<"}"<<endl;*/
                                                                                    break;
                                                                                            }
                                                                                    }
                                                                                }
                                                                            }

                                                                        }else{//SI NO ES EL NODO RAIZ
                                                                            string rx5;
                                                                            rx5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                            string ry5;
                                                                            ry5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->y))->str();
                                                                            if(aux4->dato!=""){
                                                                                    if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                    }
                                                                            }
                                                                        }
                                                                        }
                                                                }
                                                            }
                                                        }else{//SI LO QUE HAY ABAJO DE UNA COLUMNA NO ES UNA X
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() <<  aux4->y))->str();
                                                                        if(aux4->dato!=""){
                                                                                if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<< aux4->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<< aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                }
                                                                        }
                                                        }
                                                    }

                                                    aux4=aux4->siguiente;
                                                }
                                            }

                                }
                            }

                        }
                        else{//INGRESA TODO LO QUE ESTAN EN MEDIO
                            if(aux1->siguiente!=NULL)
                            {       if(aux1->dato!=""){
                                    if(aux1->siguiente->dato!=""){
                                    archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;


                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;
                                    archivo<<"}"<<endl;
                                    /*archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    archivo<<"}"<<endl;*/
                                    }
                            }


                            }

                        }

                    }


                }
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
            std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+"Filtro"+nombre+copiaContador+".dot"+" -o imagenCapaMatrizFiltro"+copiaContador+".jpg";
            const char *nombreArch2 = auxNombreMatriz4.c_str();
            system(nombreArch2); // CREANDO EL GRAPHVIZ
            std::string auxNombreMatriz5 ="imagenCapaMatrizFiltro"+copiaContador+".jpg";
            const char *nombreArch3 = auxNombreMatriz5.c_str();
            system(nombreArch3);
            contador=contador+1;
            while(temp2!=NULL){
            if(temp2->nivelCapa==contador)
                {
                    //std::cout <<"HOLA WAPO"<<temp2->nivelCapa<<std::endl;
                    break;
                    }
                temp2=temp2->frente;
            }
            if(temp2==NULL){
                condicion1=false;
                break;
            }
            }

    }else if(temp==NULL){
        std::cout <<"Numero de capa Incorrecto"<<std::endl;
    }
    else
    {

        //{
    ofstream archivo;   /////////Generar Capa por capa
    std::string auxNombreMatriz3 =nombre+"\\"+"Filtro"+nombre+".dot";
    const char *nombreArch = auxNombreMatriz3.c_str();
    archivo.open(nombreArch,ios::out);//abriendo el archivo
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
                string ingorarDato=aux1->dato;
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
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
                        string ingorarDato1=aux1->abajo->dato;
                        transform(ingorarDato1.begin(), ingorarDato1.end(), ingorarDato1.begin(), ::tolower);
                        if(ingorarDato1=="x"){//SI EL DATO QUE ESTA ABAJO ES X ESTO ES PARA LAS COLUMNAS

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                        string ingorarDato2=recorrer->dato;
                                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                                    if(ingorarDato2=="x"){
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
                                        if(recorrer->dato!=""){
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            //archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                        }

                                }


                        }else if (aux1->dato=="Fila"||temp->dato==aux1->dato){//ESTO ES PARA LAS FILAS
                            if(aux1->siguiente!=NULL)
                            {
                                string ingorarDato3=aux1->siguiente->dato;
                                transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                if(ingorarDato3=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                        string ingorarDato4=recorrer->dato;
                                        transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                    if(ingorarDato4=="x"){
                                        recorrer=recorrer->siguiente;//SI ENCUNTRA UN VALOR QUE NO SEA X EN LA FILA LO GUARDA
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){ //BUSCAMOS EL SIGUIENTE VALOR PARA ENLZARLO CON EL ANTERIOR
                                     if(aux1->abajo!=NULL)
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->abajo;
                                            while(aux3!=NULL){
                                                    string ingorarDato5=aux3->siguiente->dato;
                                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                            if(ingorarDato5=="x")// SI EL VALOR QUE ESTA ABAJO DEL ANTERIROR EL SIGUIENTE A ESE ES X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->siguiente;
                                                while(recorrer2!=NULL)
                                                {
                                                    string ingorarDato6=recorrer2->dato;
                                                    transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                                    if(ingorarDato6=="x")
                                                    {
                                                        recorrer2=recorrer2->siguiente;//BUSCAMOS UN VALOR HASTA QUE YA NO SEA X
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;//LO GURDAMOS Y LO ESCRIBIMOS EN EL ARCHIVO
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();

                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                }
                                            }else{// DE LO CONTRARIO SOLO LO VA A ESCRIBIR
                                                if(aux1->dato!=""){
                                                    if(aux3->siguiente->dato!=""){
                                                        string rx7;
                                                        rx7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                                                        string ry7;
                                                        ry7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();
                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<"[dir=both];"<<endl;
                                                        //archivo<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            aux3=aux3->abajo;
                                          }
                                        }
                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{
                                    //if(aux1->dato==temp->dato){
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                    //cout<<aux1->dato+" TERCERO "<<"+"+x<<"-"+y+"*"<<endl;

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                    //}else{

                                    //}
                                }
                            }

                        }
                        else{// PARA ESCRIBIR TODO LO QUE ESTA DENTRO DE LA MATRIZ
                            if(aux1->siguiente!=NULL)
                            {

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;
                                    //archivo<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;




                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 aux = temp;
while(aux != NULL){

            aux1=aux;
            while(aux1 != NULL){
                    string ingorarDato=aux1->dato;
                    transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->siguiente!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->y))->str();
                        string ingorarDato1=aux1->siguiente->dato;
                        transform(ingorarDato1.begin(), ingorarDato1.end(), ingorarDato1.begin(), ::tolower);
                        if(ingorarDato1=="x"){ ////SI EL DATO QUE ESTA DESPUES ES UNA X

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->siguiente;
                                while(recorrer!=NULL){
                                        string ingorarDato2=recorrer->dato;
                                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                                    if(ingorarDato2=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                        if(recorrer->dato!=""){
                                                if(aux1->dato!=""){
                                            archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            archivo<<"}"<<endl;
                                            /*archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                             archivo<<"}"<<endl;*/
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                                }
                                        }

                                }


                        }else if (aux1->dato=="Col"||temp->dato==aux1->dato){ ////ESTO ES PARA INGRESAR COLUMNAS Y EL NODO RAIZ
                            if(aux1->abajo!=NULL)
                            {
                                string ingorarDato3=aux1->abajo->dato;
                                transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                if(ingorarDato3=="x") //SI EL DATO ABAJO DE LA COLUMNA ES UNA X
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->abajo;
                                    while(recorrer!=NULL){//RECORRO PARA ABAJO HASTA ENCONTRAR UNA X
                                    string ingorarDato4=recorrer->dato;
                                    transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                    if(ingorarDato4=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                     if(aux1->siguiente!=NULL)//AHORA VOY BUSCANDO COLUMNAS PARA ENLAZAR LA ANTERIOR
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->siguiente;
                                            while(aux3!=NULL){//RECORRO TODAS LAS COLUMNAS
                                            string ingorarDato5=aux3->abajo->dato;
                                            transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                            if(ingorarDato5=="x")//SI LO QUE HAY ABAJO ES UNA X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->abajo;
                                                while(recorrer2!=NULL) //EN CADA COLUMNA LOS NODOS DE ABAJO HASTA ENCONTRAR NO X
                                                {
                                                    string ingorarDato6=recorrer2->dato;
                                                    transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                                    if(ingorarDato6=="x")
                                                    {
                                                        recorrer2=recorrer2->abajo;
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();
                                                    if(aux3->dato!=""){
                                                      if(aux1->dato!=""){
                                                    archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;
                                                    /*archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;*/
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                    }
                                                    }
                                                }
                                            }
                                            else{//SI LO QUE HAY ABAJO NO ES UNA X
                                                    if(aux1->siguiente->dato!=""){
                                                        if(aux1->dato!=""){
                                                archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;

                                                archivo<<"}"<<endl;
                                                /*archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                archivo<<"}"<<endl;*/
                                                break;
                                                        }
                                                    }
                                            }
                                            aux3=aux3->siguiente;
                                          }
                                        }

                                }
                                }
                                else{//SI LO QUE ES ABAJO NO ES X
                                        //if(aux1->dato==temp->dato)
                                        //{
                                            if (aux1->siguiente!=NULL){//SI NO HAY X RECORRO LAS COLUMNAS
                                                NodoMatriz3D *aux4;
                                                aux4=aux1->siguiente;
                                                while(aux4!=NULL){
                                                    if(aux4->abajo!=NULL){
                                                            string ingorarDato7=aux4->abajo->dato;
                                                            transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                        if(ingorarDato7=="x"){
                                                             NodoMatriz3D *recorrer;
                                                            recorrer=aux4->abajo;
                                                            while(recorrer!=NULL){//RECORRO TODAS LAS FILAS EN BUSCA DE UNA X
                                                                string ingorarDato8=recorrer->dato;
                                                                transform(ingorarDato8.begin(), ingorarDato8.end(), ingorarDato8.begin(), ::tolower);
                                                                if(ingorarDato8=="x"){
                                                                    recorrer=recorrer->abajo;
                                                                }else{
                                                                    break;
                                                                }

                                                            }
                                                            if(recorrer!=NULL){//SI ENCUENTRO ALGO QUE NO SEA X
                                                                if(recorrer->dato!=""){// SI ES DIFERENTE DE VACIO
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                                                        if(recorrer->dato!=""){
                                                                        if(aux1->dato==temp->dato)//PARA EL PRIMERO NODO, NODO RAIZ
                                                                        {
                                                                            if(recorrer->arriba!=NULL){
                                                                                NodoMatriz3D *aux6;
                                                                                aux6=recorrer->arriba;
                                                                                while(recorrer!=NULL){
                                                                                    string ingorarDato9=aux6->dato;
                                                                                    transform(ingorarDato9.begin(), ingorarDato9.end(), ingorarDato9.begin(), ::tolower);
                                                                                    if(ingorarDato9=="x"){
                                                                                        aux6= aux6->arriba;
                                                                                    }else{
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(aux6!=NULL){//ENLAZA EL PRIMERO NODO CON OTRO NODO QUE TENGA UN VALOR
                                                                                   string rx4;
                                                                                    rx4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->x))->str();
                                                                                    string ry4;
                                                                                    ry4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->y))->str();
                                                                                    if(aux6->dato!=""){
                                                                                            if(aux1->dato!=""){
                                                                                    archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\""<<"[dir=both];"<<endl;

                                                                                    archivo<<"}"<<endl;
                                                                                    /*archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                                    archivo<<"}"<<endl;*/
                                                                                    break;
                                                                                            }
                                                                                    }
                                                                                }
                                                                            }

                                                                        }else{//SI NO ES EL NODO RAIZ
                                                                            string rx5;
                                                                            rx5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                            string ry5;
                                                                            ry5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->y))->str();
                                                                            if(aux4->dato!=""){
                                                                                    if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                    }
                                                                            }
                                                                        }
                                                                        }
                                                                }
                                                            }
                                                        }else{//SI LO QUE HAY ABAJO DE UNA COLUMNA NO ES UNA X
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() <<  aux4->y))->str();
                                                                        if(aux4->dato!=""){
                                                                                if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<< aux4->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<< aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                }
                                                                        }
                                                        }
                                                    }

                                                    aux4=aux4->siguiente;
                                                }
                                            }

                                }
                            }

                        }
                        else{//INGRESA TODO LO QUE ESTAN EN MEDIO
                            if(aux1->siguiente!=NULL)
                            {       if(aux1->dato!=""){
                                    if(aux1->siguiente->dato!=""){
                                    archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;


                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;
                                    archivo<<"}"<<endl;
                                    /*archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    archivo<<"}"<<endl;*/
                                    }
                            }


                            }

                        }

                    }


                }
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
        std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+"Filtro"+nombre+".dot"+" -o imagenCapaMatrizFiltro.jpg";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        system(nombreArch2); // CREANDO EL GRAPHVIZ
        system("imagenCapaMatrizFiltro.jpg");


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
        //}

    }
}


void Matriz3D::graficarLineal(NodoMatriz3D *nodoAux,int capa,string columnaFila)
{
    NodoMatriz3D *temp3;
    temp3 =nodoAux;
    std::cout << ""<<std::endl;
    while(temp3!=NULL){
        if(temp3->nivelCapa==capa)
            {
               break;

            }
            temp3=temp3->frente;
    }

    if(columnaFila=="Filas"){
        int contador = 1;
        NodoMatriz3D *auxiliar = temp3->abajo;
        NodoMatriz3D *auxiliar2 = temp3;

        ofstream archivo;
        string aux= "LineaFilas.dot";
        const char *nombreArch = aux.c_str();
        archivo.open(nombreArch, ios::out);
        archivo << "digraph G {" << endl;
        archivo<< "node [shape = rectangle];" << endl;
        archivo<< "rankdir=LR;" << endl;




        if (auxiliar != NULL) {
            auxiliar2 = auxiliar->siguiente;
        }

        while (auxiliar != NULL) {
            if (auxiliar2 != NULL) {
                archivo << "\"" << contador << "\"[label=\" (" << auxiliar2->x << "," << auxiliar2->y << ") " << auxiliar2->dato << "\"];"
                        << endl;
                if (contador != 1) {
                    int condicion = contador - 1;
                    archivo << "\"" << condicion << "\"->\"" << contador << "\";" << endl;
                }
                contador++;
                auxiliar2 = auxiliar2->siguiente;
            } else {
                auxiliar= auxiliar->abajo;
                if (auxiliar != NULL) {
                    auxiliar2 = auxiliar->siguiente;
                }
            }
        }

        archivo << "}";

        archivo.close();

        string aux2 = "dot -Tjpg LineaFilas.dot -o imagenLineaFilas.jpg";
        const char *nombreArch2 = aux2.c_str();
        system(nombreArch2);

        aux2 = "imagenLineaFilas.jpg";
        const char *nombreArch3 = aux2.c_str();
        system(nombreArch3);


    }else if(columnaFila=="Columnas"){
        NodoMatriz3D *auxiliar2 = temp3;
        int contador = 1;
        NodoMatriz3D *auxiliar = temp3->siguiente;
        ofstream archivo;
        string aux= "LineaColumnas.dot";
        const char *nombreArch = aux.c_str();
        archivo.open(nombreArch, ios::out);
        archivo << "digraph G {" << endl;
        archivo<< "node [shape = rectangle];" << endl;
        archivo<< "rankdir=LR;" << endl;





        if (auxiliar != NULL) {
            auxiliar2 = auxiliar->abajo;
        }

        while (auxiliar != NULL) {
            if (auxiliar2 != NULL) {
                archivo << "\"" << contador << "\"[label=\" (" << auxiliar2->x << "," << auxiliar2->y << ") " << auxiliar2->dato << "\"];"
                        << endl;
                if (contador != 1) {
                    int condicion = contador - 1;
                    archivo << "\"" << condicion << "\"->\"" << contador << "\";" << endl;
                }
                contador++;
                auxiliar2 = auxiliar2->abajo;
            } else {
                auxiliar= auxiliar->siguiente;
                if (auxiliar != NULL) {
                    auxiliar2 = auxiliar->abajo;
                }
            }
        }

        archivo << "}";

        archivo.close();

        string aux2 = "dot -Tjpg LineaColumnas.dot -o imagenLineaColumnas.jpg";
        const char *nombreArch2 = aux2.c_str();
        system(nombreArch2);

        aux2 = "imagenLineaColumnas.jpg";
        const char *nombreArch3 = aux2.c_str();
        system(nombreArch3);
    }

}



void Matriz3D::graficarEspejo(NodoMatriz3D *nodoAux, int capa,std::string nombre)
{
    NodoMatriz3D *temp;
    temp =nodoAux;
    //std::cout << ""<<std::endl;
    while(temp!=NULL){
        if(temp->nivelCapa==capa)
            {
               break;

            }
            temp=temp->frente;
    }
        if(capa==-1)
    {
            NodoMatriz3D *temp2;
            temp2 =nodoAux;
            int contador=1;
            std::string copiaContador="";
            std::cout << ""<<std::endl;
            while(temp2!=NULL){
            if(temp2->nivelCapa==contador)
                {
                    std::cout << temp2->nivelCapa<<std::endl;
                break;

                    }
                temp2=temp2->frente;
            }

            std::cout <<"GRAFICAR TODO EL CUBO"<<std::endl;
            ofstream archivo;   /////////Generar Capa por capa

            NodoMatriz3D *aux;
            NodoMatriz3D *aux1;
            //NodoMatriz3D *auxRaiz;

            //auxRaiz=aux->frente;
            bool condicion1=true;
            bool condicion = true;

            while(condicion1){
                    aux = temp2;
                    condicion=true;
            //std::cout << temp2->nivelCapa<<std::endl;
            copiaContador= static_cast<std::ostringstream*>(&(std::ostringstream() << contador))->str();
            std::string auxNombreMatriz3 =nombre+"\\"+nombre+copiaContador+".dot";
            const char *nombreArch = auxNombreMatriz3.c_str();
            archivo.open(nombreArch,ios::out);//abriendo el archivo
            archivo<<"digraph G {"<<endl;
            archivo<<"node [shape=box, color=cornflowerblue ];"<<endl;
            archivo<< "rankdir=TB;" << endl;
                    //aux = temp2;
                while(condicion){
        while(aux != NULL){
            //std::cout << "WHILE AUX!=NULL"<<std::endl;
            aux1=aux;
            while(aux1 != NULL){
                string ignorarX="x";
                string ingorarDato=aux1->dato;
                transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!=ignorarX)
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
                        string ignorarX="x";
                        string ingorarDato2=aux1->abajo->dato;
                        transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                        if(ingorarDato2=="x"){//SI EL DATO QUE ESTA ABAJO ES X ESTO ES PARA LAS COLUMNAS

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                    string ignorarX="x";
                                    string ingorarDato3 = recorrer->dato;
                                    transform(ignorarX.begin(), ignorarX.end(), ignorarX.begin(), ::tolower);
                                    transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                    if(ingorarDato3=="x"){
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
                                        if(recorrer->dato!=""){
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            //archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                        }

                                }


                        }else if (aux1->dato=="Fila"||temp2->dato==aux1->dato){//ESTO ES PARA LAS FILAS
                            if(aux1->siguiente!=NULL)
                            {
                                string ingorarDato4=aux1->siguiente->dato;
                                transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                if(ingorarDato4=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                    string ingorarDato5=recorrer->dato;
                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                    if(ingorarDato5=="x"){
                                        recorrer=recorrer->siguiente;//SI ENCUNTRA UN VALOR QUE NO SEA X EN LA FILA LO GUARDA
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){ //BUSCAMOS EL SIGUIENTE VALOR PARA ENLZARLO CON EL ANTERIOR
                                     if(aux1->abajo!=NULL)
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->abajo;
                                            while(aux3!=NULL){
                                            string ingorarDato6=aux3->siguiente->dato;
                                            transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                            if(ingorarDato6=="x")// SI EL VALOR QUE ESTA ABAJO DEL ANTERIROR EL SIGUIENTE A ESE ES X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->siguiente;
                                                while(recorrer2!=NULL)
                                                {
                                                    string ingorarDato7=recorrer2->dato;
                                                    transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                    if(ingorarDato7=="x")
                                                    {
                                                        recorrer2=recorrer2->siguiente;//BUSCAMOS UN VALOR HASTA QUE YA NO SEA X
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;//LO GURDAMOS Y LO ESCRIBIMOS EN EL ARCHIVO
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();

                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                }
                                            }else{// DE LO CONTRARIO SOLO LO VA A ESCRIBIR
                                                if(aux1->dato!=""){

                                                    if(aux3->siguiente->dato!=""){
                                                        string rx7;
                                                        rx7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                                                        string ry7;
                                                        ry7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();
                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<"[dir=both];"<<endl;
                                                        //archivo<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            aux3=aux3->abajo;
                                          }
                                        }
                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{
                                    //if(aux1->dato==temp->dato){
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                    //cout<<aux1->dato+" TERCERO "<<"+"+x<<"-"+y+"*"<<endl;

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                    //}else{

                                    //}
                                }
                            }

                        }
                        else{// PARA ESCRIBIR TODO LO QUE ESTA DENTRO DE LA MATRIZ
                            if(aux1->siguiente!=NULL)
                            {

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;
                                    //archivo<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;




                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 aux = temp2;
while(aux != NULL){

            aux1=aux;
            while(aux1 != NULL){
                string ingorarDato=aux1->dato;
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->siguiente!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->y))->str();
                        string ingorarDato2=aux1->siguiente->dato;
                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                        if(ingorarDato2=="x"){ ////SI EL DATO QUE ESTA DESPUES ES UNA X

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->siguiente;
                                while(recorrer!=NULL){
                                    string ingorarDato3=recorrer->dato;
                                    transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                    if(ingorarDato3=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                        if(recorrer->dato!=""){
                                                if(aux1->dato!=""){
                                            archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            archivo<<"}"<<endl;
                                            /*archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                             archivo<<"}"<<endl;*/
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                                }
                                        }

                                }


                        }else if (aux1->dato=="Col"||temp2->dato==aux1->dato){ ////ESTO ES PARA INGRESAR COLUMNAS Y EL NODO RAIZ
                            if(aux1->abajo!=NULL)
                            {
                                string ingorarDato4=aux1->abajo->dato;
                                transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                if(ingorarDato4=="x") //SI EL DATO ABAJO DE LA COLUMNA ES UNA X
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->abajo;
                                    while(recorrer!=NULL){//RECORRO PARA ABAJO HASTA ENCONTRAR UNA X
                                        string ingorarDato5=recorrer->dato;
                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                    if(ingorarDato5=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                     if(aux1->siguiente!=NULL)//AHORA VOY BUSCANDO COLUMNAS PARA ENLAZAR LA ANTERIOR
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->siguiente;
                                            while(aux3!=NULL){//RECORRO TODAS LAS COLUMNAS
                                            string ingorarDato6=aux3->abajo->dato;
                                            transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                            if(ingorarDato6=="x")//SI LO QUE HAY ABAJO ES UNA X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->abajo;
                                                while(recorrer2!=NULL) //EN CADA COLUMNA LOS NODOS DE ABAJO HASTA ENCONTRAR NO X
                                                {
                                                    string ingorarDato7=recorrer2->dato;
                                                    transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                    if(ingorarDato7=="x")
                                                    {
                                                        recorrer2=recorrer2->abajo;
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();
                                                    if(aux3->dato!=""){
                                                      if(aux1->dato!=""){
                                                    archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;
                                                    /*archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;*/
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                    }
                                                    }
                                                }
                                            }
                                            else{//SI LO QUE HAY ABAJO NO ES UNA X
                                                    if(aux1->siguiente->dato!=""){
                                                        if(aux1->dato!=""){
                                                archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;

                                                archivo<<"}"<<endl;
                                                /*archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                archivo<<"}"<<endl;*/
                                                break;
                                                        }
                                                    }
                                            }
                                            aux3=aux3->siguiente;
                                          }
                                        }

                                }
                                }
                                else{//SI LO QUE ES ABAJO NO ES X
                                        //if(aux1->dato==temp->dato)
                                        //{
                                            if (aux1->siguiente!=NULL){//SI NO HAY X RECORRO LAS COLUMNAS
                                                NodoMatriz3D *aux4;
                                                aux4=aux1->siguiente;
                                                while(aux4!=NULL){
                                                    if(aux4->abajo!=NULL){
                                                        string ingorarDato8=aux4->abajo->dato;
                                                        transform(ingorarDato8.begin(), ingorarDato8.end(), ingorarDato8.begin(), ::tolower);
                                                        if(ingorarDato8=="x"){
                                                             NodoMatriz3D *recorrer;
                                                            recorrer=aux4->abajo;
                                                            while(recorrer!=NULL){//RECORRO TODAS LAS FILAS EN BUSCA DE UNA X
                                                                string ingorarDato9=recorrer->dato;
                                                                transform(ingorarDato9.begin(), ingorarDato9.end(), ingorarDato9.begin(), ::tolower);
                                                                if(ingorarDato9=="x"){
                                                                    recorrer=recorrer->abajo;
                                                                }else{
                                                                    break;
                                                                }

                                                            }
                                                            if(recorrer!=NULL){//SI ENCUENTRO ALGO QUE NO SEA X
                                                                if(recorrer->dato!=""){// SI ES DIFERENTE DE VACIO
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                                                        if(recorrer->dato!=""){
                                                                        if(aux1->dato==temp2->dato)//PARA EL PRIMERO NODO, NODO RAIZ
                                                                        {
                                                                            if(recorrer->arriba!=NULL){
                                                                                NodoMatriz3D *aux6;
                                                                                aux6=recorrer->arriba;
                                                                                while(recorrer!=NULL){
                                                                                        string ingorarDato10=aux6->dato;
                                                                                        transform(ingorarDato10.begin(), ingorarDato10.end(), ingorarDato10.begin(), ::tolower);
                                                                                    if(ingorarDato10=="x"){
                                                                                        aux6= aux6->arriba;
                                                                                    }else{
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(aux6!=NULL){//ENLAZA EL PRIMERO NODO CON OTRO NODO QUE TENGA UN VALOR
                                                                                   string rx4;
                                                                                    rx4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->x))->str();
                                                                                    string ry4;
                                                                                    ry4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->y))->str();
                                                                                    if(aux6->dato!=""){
                                                                                            if(aux1->dato!=""){
                                                                                    archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\""<<"[dir=both];"<<endl;

                                                                                    archivo<<"}"<<endl;
                                                                                    /*archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                                    archivo<<"}"<<endl;*/
                                                                                    break;
                                                                                            }
                                                                                    }
                                                                                }
                                                                            }

                                                                        }else{//SI NO ES EL NODO RAIZ
                                                                            string rx5;
                                                                            rx5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                            string ry5;
                                                                            ry5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->y))->str();
                                                                            if(aux4->dato!=""){
                                                                                    if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                    }
                                                                            }
                                                                        }
                                                                        }
                                                                }
                                                            }
                                                        }else{//SI LO QUE HAY ABAJO DE UNA COLUMNA NO ES UNA X
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() <<  aux4->y))->str();
                                                                        if(aux4->dato!=""){
                                                                                if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<< aux4->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<< aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                }
                                                                        }
                                                        }
                                                    }

                                                    aux4=aux4->siguiente;
                                                }
                                            }

                                }
                            }

                        }
                        else{//INGRESA TODO LO QUE ESTAN EN MEDIO
                            if(aux1->siguiente!=NULL)
                            {       if(aux1->dato!=""){
                                    if(aux1->siguiente->dato!=""){
                                    archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;


                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;
                                    archivo<<"}"<<endl;
                                    /*archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    archivo<<"}"<<endl;*/
                                    }
                            }


                            }

                        }

                    }


                }
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
            std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+nombre+copiaContador+".dot"+" -o imagenCapaMatriz"+copiaContador+".jpg";
            const char *nombreArch2 = auxNombreMatriz4.c_str();
            system(nombreArch2); // CREANDO EL GRAPHVIZ
            std::string auxNombreMatriz5 ="imagenCapaMatriz"+copiaContador+".jpg";
            const char *nombreArch3 = auxNombreMatriz5.c_str();
            system(nombreArch3);
            contador=contador+1;
            while(temp2!=NULL){
            if(temp2->nivelCapa==contador)
                {
                    //std::cout <<"HOLA WAPO"<<temp2->nivelCapa<<std::endl;
                    break;
                    }
                temp2=temp2->frente;
            }
            if(temp2==NULL){
                condicion1=false;
                break;
            }
            }

    }else if(temp==NULL){
        std::cout <<"Numero de capa Incorrecto"<<std::endl;
    }
    else
    {

        //{
    ofstream archivo;   /////////Generar Capa por capa
    std::string auxNombreMatriz3 =nombre+"\\"+nombre+".dot";
    const char *nombreArch = auxNombreMatriz3.c_str();
    archivo.open(nombreArch,ios::out);//abriendo el archivo
    archivo<<"digraph G {"<<endl;
    archivo<<"node [shape=box, color=cornflowerblue ];"<<endl;
    archivo<< "rankdir=TB;" << endl;
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
                string ingorarDato=aux1->dato;
                transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
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
                        string ingorarDato1=aux1->abajo->dato;
                        transform(ingorarDato1.begin(), ingorarDato1.end(), ingorarDato1.begin(), ::tolower);
                        if(ingorarDato1=="x"){//SI EL DATO QUE ESTA ABAJO ES X ESTO ES PARA LAS COLUMNAS

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->abajo;
                                while(recorrer!=NULL){
                                        string ingorarDato2=recorrer->dato;
                                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                                    if(ingorarDato2=="x"){
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
                                        if(recorrer->dato!=""){
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            //archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                        }

                                }


                        }else if (aux1->dato=="Fila"||temp->dato==aux1->dato){//ESTO ES PARA LAS FILAS
                            if(aux1->siguiente!=NULL)
                            {
                                string ingorarDato3=aux1->siguiente->dato;
                                transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                if(ingorarDato3=="x")
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->siguiente;
                                    while(recorrer!=NULL){
                                        string ingorarDato4=recorrer->dato;
                                        transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                    if(ingorarDato4=="x"){
                                        recorrer=recorrer->siguiente;//SI ENCUNTRA UN VALOR QUE NO SEA X EN LA FILA LO GUARDA
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){ //BUSCAMOS EL SIGUIENTE VALOR PARA ENLZARLO CON EL ANTERIOR
                                     if(aux1->abajo!=NULL)
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->abajo;
                                            while(aux3!=NULL){
                                                    string ingorarDato5=aux3->siguiente->dato;
                                                    transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                            if(ingorarDato5=="x")// SI EL VALOR QUE ESTA ABAJO DEL ANTERIROR EL SIGUIENTE A ESE ES X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->siguiente;
                                                while(recorrer2!=NULL)
                                                {
                                                    string ingorarDato6=recorrer2->dato;
                                                    transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                                    if(ingorarDato6=="x")
                                                    {
                                                        recorrer2=recorrer2->siguiente;//BUSCAMOS UN VALOR HASTA QUE YA NO SEA X
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;//LO GURDAMOS Y LO ESCRIBIMOS EN EL ARCHIVO
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();

                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                }
                                            }else{// DE LO CONTRARIO SOLO LO VA A ESCRIBIR
                                                if(aux1->dato!=""){
                                                    if(aux3->siguiente->dato!=""){
                                                        string rx7;
                                                        rx7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->x))->str();
                                                        string ry7;
                                                        ry7=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->abajo->y))->str();
                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<"[dir=both];"<<endl;
                                                        //archivo<<"\""<<aux1->abajo->dato+", ("+rx7+","+ry7+")"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            aux3=aux3->abajo;
                                          }
                                        }
                                        /*string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->arriba->y))->str();*/
                                        //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                }
                                }
                                else{
                                    //if(aux1->dato==temp->dato){
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->";
                                    //cout<<aux1->dato+" TERCERO "<<"+"+x<<"-"+y+"*"<<endl;

                                    //cout<<"entra el inicial"<<endl;
                                    //archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<endl;
                                    //}else{

                                    //}
                                }
                            }

                        }
                        else{// PARA ESCRIBIR TODO LO QUE ESTA DENTRO DE LA MATRIZ
                            if(aux1->siguiente!=NULL)
                            {

                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;
                                    //archivo<<"\""<<aux1->abajo->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;




                            }

                        }

                    }


                }
                aux1 = aux1->abajo;
            }
        aux = aux->siguiente;
        //cout<<""<<endl;
        }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 aux = temp;
while(aux != NULL){

            aux1=aux;
            while(aux1 != NULL){
                    string ingorarDato=aux1->dato;
                    transform(ingorarDato.begin(), ingorarDato.end(), ingorarDato.begin(), ::tolower);
                if(ingorarDato!="x")
                {
                    //cout<<"Entro en el primero if"<<endl;
                    if(aux1->siguiente!=NULL)
                    {
                        string x;
                        x=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->x))->str();

                        string y;
                        y=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->y))->str();

                        string ax;
                        ax=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->x))->str();
                        string ay;
                        ay=static_cast<std::ostringstream*>(&(std::ostringstream() << aux1->siguiente->y))->str();
                        string ingorarDato1=aux1->siguiente->dato;
                        transform(ingorarDato1.begin(), ingorarDato1.end(), ingorarDato1.begin(), ::tolower);
                        if(ingorarDato1=="x"){ ////SI EL DATO QUE ESTA DESPUES ES UNA X

                            NodoMatriz3D *recorrer;
                                recorrer=aux1->siguiente;
                                while(recorrer!=NULL){
                                        string ingorarDato2=recorrer->dato;
                                        transform(ingorarDato2.begin(), ingorarDato2.end(), ingorarDato2.begin(), ::tolower);
                                    if(ingorarDato2=="x"){
                                        recorrer=recorrer->siguiente;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                        string rx;
                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                        string ry;
                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                        if(recorrer->dato!=""){
                                                if(aux1->dato!=""){
                                            archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                            archivo<<"}"<<endl;
                                            /*archivo<<"rank=same{"<<endl;
                                            archivo<<"\""<<recorrer->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                             archivo<<"}"<<endl;*/
                                            //cout<<aux1->dato+" PRIMERO "<<x+"+"<<y+"-"<<recorrer->dato<<rx+"+"<<ry+"-"+"****"<<endl;
                                                }
                                        }

                                }


                        }else if (aux1->dato=="Col"||temp->dato==aux1->dato){ ////ESTO ES PARA INGRESAR COLUMNAS Y EL NODO RAIZ
                            if(aux1->abajo!=NULL)
                            {
                                string ingorarDato3=aux1->abajo->dato;
                                transform(ingorarDato3.begin(), ingorarDato3.end(), ingorarDato3.begin(), ::tolower);
                                if(ingorarDato3=="x") //SI EL DATO ABAJO DE LA COLUMNA ES UNA X
                                {
                                    NodoMatriz3D *recorrer;
                                    recorrer=aux1->abajo;
                                    while(recorrer!=NULL){//RECORRO PARA ABAJO HASTA ENCONTRAR UNA X
                                    string ingorarDato4=recorrer->dato;
                                    transform(ingorarDato4.begin(), ingorarDato4.end(), ingorarDato4.begin(), ::tolower);
                                    if(ingorarDato4=="x"){
                                        recorrer=recorrer->abajo;
                                    }else{
                                        break;
                                    }

                                }
                                if(recorrer!=NULL){
                                     if(aux1->siguiente!=NULL)//AHORA VOY BUSCANDO COLUMNAS PARA ENLAZAR LA ANTERIOR
                                        {
                                            NodoMatriz3D *aux3;
                                            aux3=aux1->siguiente;
                                            while(aux3!=NULL){//RECORRO TODAS LAS COLUMNAS
                                            string ingorarDato5=aux3->abajo->dato;
                                            transform(ingorarDato5.begin(), ingorarDato5.end(), ingorarDato5.begin(), ::tolower);
                                            if(ingorarDato5=="x")//SI LO QUE HAY ABAJO ES UNA X
                                            {
                                                NodoMatriz3D *recorrer2;
                                                recorrer2=aux3->abajo;
                                                while(recorrer2!=NULL) //EN CADA COLUMNA LOS NODOS DE ABAJO HASTA ENCONTRAR NO X
                                                {
                                                    string ingorarDato6=recorrer2->dato;
                                                    transform(ingorarDato6.begin(), ingorarDato6.end(), ingorarDato6.begin(), ::tolower);
                                                    if(ingorarDato6=="x")
                                                    {
                                                        recorrer2=recorrer2->abajo;
                                                    }else
                                                    {
                                                        break;
                                                    }
                                                }
                                                if(recorrer2!=NULL)
                                                {
                                                    string rx;
                                                    rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->x))->str();
                                                    string ry;
                                                    ry=static_cast<std::ostringstream*>(&(std::ostringstream() << aux3->y))->str();
                                                    if(aux3->dato!=""){
                                                      if(aux1->dato!=""){
                                                    archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;
                                                    //archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;
                                                    /*archivo<<"rank=same{"<<endl;
                                                    archivo<<"\""<<aux3->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                    archivo<<"}"<<endl;*/
                                                    //cout<<aux1->dato+" SEGUNDO "<<x+"+"<<y+"-"<<aux3->dato<<rx+"+"<<ry+"-"+"***"<<endl;
                                                    break;
                                                    }
                                                    }
                                                }
                                            }
                                            else{//SI LO QUE HAY ABAJO NO ES UNA X
                                                    if(aux1->siguiente->dato!=""){
                                                        if(aux1->dato!=""){
                                                archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;

                                                archivo<<"}"<<endl;
                                                /*archivo<<"rank=same{"<<endl;
                                                archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                archivo<<"}"<<endl;*/
                                                break;
                                                        }
                                                    }
                                            }
                                            aux3=aux3->siguiente;
                                          }
                                        }

                                }
                                }
                                else{//SI LO QUE ES ABAJO NO ES X
                                        //if(aux1->dato==temp->dato)
                                        //{
                                            if (aux1->siguiente!=NULL){//SI NO HAY X RECORRO LAS COLUMNAS
                                                NodoMatriz3D *aux4;
                                                aux4=aux1->siguiente;
                                                while(aux4!=NULL){
                                                    if(aux4->abajo!=NULL){
                                                            string ingorarDato7=aux4->abajo->dato;
                                                            transform(ingorarDato7.begin(), ingorarDato7.end(), ingorarDato7.begin(), ::tolower);
                                                        if(ingorarDato7=="x"){
                                                             NodoMatriz3D *recorrer;
                                                            recorrer=aux4->abajo;
                                                            while(recorrer!=NULL){//RECORRO TODAS LAS FILAS EN BUSCA DE UNA X
                                                                string ingorarDato8=recorrer->dato;
                                                                transform(ingorarDato8.begin(), ingorarDato8.end(), ingorarDato8.begin(), ::tolower);
                                                                if(ingorarDato8=="x"){
                                                                    recorrer=recorrer->abajo;
                                                                }else{
                                                                    break;
                                                                }

                                                            }
                                                            if(recorrer!=NULL){//SI ENCUENTRO ALGO QUE NO SEA X
                                                                if(recorrer->dato!=""){// SI ES DIFERENTE DE VACIO
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() << recorrer->y))->str();
                                                                        if(recorrer->dato!=""){
                                                                        if(aux1->dato==temp->dato)//PARA EL PRIMERO NODO, NODO RAIZ
                                                                        {
                                                                            if(recorrer->arriba!=NULL){
                                                                                NodoMatriz3D *aux6;
                                                                                aux6=recorrer->arriba;
                                                                                while(recorrer!=NULL){
                                                                                    string ingorarDato9=aux6->dato;
                                                                                    transform(ingorarDato9.begin(), ingorarDato9.end(), ingorarDato9.begin(), ::tolower);
                                                                                    if(ingorarDato9=="x"){
                                                                                        aux6= aux6->arriba;
                                                                                    }else{
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(aux6!=NULL){//ENLAZA EL PRIMERO NODO CON OTRO NODO QUE TENGA UN VALOR
                                                                                   string rx4;
                                                                                    rx4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->x))->str();
                                                                                    string ry4;
                                                                                    ry4=static_cast<std::ostringstream*>(&(std::ostringstream() << aux6->y))->str();
                                                                                    if(aux6->dato!=""){
                                                                                            if(aux1->dato!=""){
                                                                                    archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\""<<"[dir=both];"<<endl;

                                                                                    archivo<<"}"<<endl;
                                                                                    /*archivo<<"rank=same{"<<endl;
                                                                                    archivo<<"\""<<aux6->dato+", ("+rx4+","+ry4+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                                    archivo<<"}"<<endl;*/
                                                                                    break;
                                                                                            }
                                                                                    }
                                                                                }
                                                                            }

                                                                        }else{//SI NO ES EL NODO RAIZ
                                                                            string rx5;
                                                                            rx5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                            string ry5;
                                                                            ry5=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->y))->str();
                                                                            if(aux4->dato!=""){
                                                                                    if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx5+","+ry5+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                    }
                                                                            }
                                                                        }
                                                                        }
                                                                }
                                                            }
                                                        }else{//SI LO QUE HAY ABAJO DE UNA COLUMNA NO ES UNA X
                                                                        string rx;
                                                                        rx=static_cast<std::ostringstream*>(&(std::ostringstream() << aux4->x))->str();
                                                                        string ry;
                                                                        ry=static_cast<std::ostringstream*>(&(std::ostringstream() <<  aux4->y))->str();
                                                                        if(aux4->dato!=""){
                                                                                if(aux1->dato!=""){
                                                                        archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<< aux4->dato+", ("+rx+","+ry+")"<<"\""<<"[dir=both];"<<endl;

                                                                        archivo<<"}"<<endl;
                                                                        /*archivo<<"rank=same{"<<endl;
                                                                        archivo<<"\""<<aux4->dato+", ("+rx+","+ry+")"<<"\"->"<<"\""<< aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                                                        archivo<<"}"<<endl;*/
                                                                        break;
                                                                                }
                                                                        }
                                                        }
                                                    }

                                                    aux4=aux4->siguiente;
                                                }
                                            }

                                }
                            }

                        }
                        else{//INGRESA TODO LO QUE ESTAN EN MEDIO
                            if(aux1->siguiente!=NULL)
                            {       if(aux1->dato!=""){
                                    if(aux1->siguiente->dato!=""){
                                    archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\"->"<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\""<<"[dir=both];"<<endl;


                                    //cout<<aux1->dato+" CUARTO "<<x<<y<<aux1->abajo->dato<<ax<<ay<<endl;
                                    archivo<<"}"<<endl;
                                    /*archivo<<"rank=same{"<<endl;
                                    archivo<<"\""<<aux1->siguiente->dato+", ("+ax+","+ay+")"<<"\"->"<<"\""<<aux1->dato+", ("+x+","+y+")"<<"\""<<endl;
                                    archivo<<"}"<<endl;*/
                                    }
                            }


                            }

                        }

                    }


                }
                aux1 = aux1->siguiente;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        archivo.close();
    ///////////////////////////////// FIN METODO QUTAR LA ULTIMA FLECHA
        std::string auxNombreMatriz4 ="dot -Tjpg "+nombre+"\\"+nombre+".dot"+" -o imagenCapaMatriz.jpg";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        system(nombreArch2); // CREANDO EL GRAPHVIZ
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
        //}

    }

}
