#include "MenuPrincipal.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <direct.h>
#include <algorithm>
using namespace std;

MenuPrincipal::MenuPrincipal()
{
    //ctor
    this->auxGuardarNodo=NULL;
    this->auxNodoArbol=NULL;
    this->espejo=false;
    this->volteado=false;
    this->dosEjes=false;

}

MenuPrincipal::~MenuPrincipal()
{
    //dtor
}
void MenuPrincipal::Menu()
{
    bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu Principal----"<<endl;
        cout<<"[1] Insertar Imagen"<<endl;
        cout<<"[2] Seleccionar Imagen"<<endl;
        cout<<"[3] Aplicar Filtro"<<endl;
        cout<<"[4] Edicion Manual"<<endl;
        cout<<"[5] Exportar Imagen"<<endl;
        cout<<"[6] Reportes"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:
                system("cls");
                //Matriz3D matriz;
                insertarImagen();

                break;
            case 2:
                menuSeleccionarImagen();
                break;
            case 3:
                menuFiltros();
                break;
            case 4:
                //menuConfiguracionManual();
                menuOpcionConfiguracionManual();
                break;
            case 5:
                if(auxMatrizFiltro.primeraMatriz!=NULL){
                    crearImagenFiltro();
                }else if(espejo){
                    crearImagenEspejo(espejo,volteado,dosEjes);
                }else if(volteado){
                    crearImagenEspejo(espejo,volteado,dosEjes);
                }else if(dosEjes){

                }
                else{

                    crearImagen();
                }

                break;
            case 6:
                    menuReportes();
                break;
            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}
void MenuPrincipal::insertarImagen()
{
      Matriz3D matriz; //CREO UNA NUEVA MATRIZ
      Matriz3D matrizNegativa;
      Matriz3D matrizBN;
      Matriz3D matrizEspejo;
      Matriz3D matrizSinX;
      archivo="";
      contador=0;
      contadorFila=0;
      contadorColumnas=0;
      int contadorRaiz=0; //PARA CAMBIAR EL NOMBRE DE LA CAPA DE LA MATRIZ
      std::string copiaContadorRaiz =""; //PARA CAMBIAR EL NOMBRE DE LA CAPA DE LA MATRIZ
      std::string rutaArchivo="";
      std::string archivoCSV="";
      cout<<""<<endl;
      cout<<""<<endl;
      cout<<"----INSERTAR IMAGEN----"<<endl;
      cout<<"---------------------------------"<<endl;
      cout<<"--Ingrese el Nombre de la carpeta--"<<endl;
      cin>>archivo;
      cout<<"---------------------------------"<<endl;
      cout<<"--Ingrese nombre del archivo .csv--"<<endl;
      cin>>archivoCSV;
      string auxArchivo="";
      auxArchivo=archivo+"/"+archivoCSV;
      //cin>>archivo;
      const char *nombre = auxArchivo.c_str();

      ////LEER ARCHIVO
      ifstream myFile(nombre);

      if(!myFile.is_open())
      {
          std::cout<<"ERROR: AL ABRIR EL ARCHIVO"<<'\n';
          system("pause>nul");
      }else
      {


      while(myFile.good()){

          string layer="";
          getline(myFile,layer,','); // lee hasta donde llegue la coma
          string file="";
          string nombreArchivo = "";
          getline(myFile,file,'\n'); // lee hasta donde exista un salto de linea

          //std::cout <<"Layer "<<layer<<" "<<'\n'; //IMPRIME
          //std::cout <<"File "<<file<<" "<<'\n'; //IMPRIME
          //std::cout <<"----------------------" << '\n';
          if(contador>0){//CAMBIAR PORQUE LA POSICION 0 TENDRA EL ARCHIVO DE CONFIGURACION
              nombreArchivo = file;
              int numeroLayer;
              std::istringstream iss(layer);
              iss>>numeroLayer; //nombre de los otros archivos
              //archivos(nombreArchivo); //mando el nombre de
              ////////////////////////////////////////////////////////////////////////////METODO EN EL QUE SEPARO POR FILAS
              if(layer=="0")
              {
                  matriz.generarNuevaMatriz(numeroLayer);
                  matrizNegativa.generarNuevaMatriz(numeroLayer);
                  matrizBN.generarNuevaMatriz(numeroLayer);
                  matrizEspejo.generarNuevaMatriz(numeroLayer);
                  matrizSinX.generarNuevaMatriz(numeroLayer);
                  contadorRaiz++;
                  //matriz.raiz->nivelCapa = numeroLayer;
                  matriz.raiz->dato = nombreArchivo;
                  matrizNegativa.raiz->dato = nombreArchivo;
                  matrizBN.raiz->dato = nombreArchivo;
                  matrizEspejo.raiz->dato = nombreArchivo;
                  matrizSinX.raiz->dato = nombreArchivo;
                  string auxNArchivo="";
                  auxNArchivo=archivo+"/"+nombreArchivo;
                  const char *nArchivo =  auxNArchivo.c_str();
                  //int numeroValue;
                  ifstream myFile1(nArchivo);

                  if(!myFile1.is_open())
                    {
                    std::cout<<"ERROR: AL ABRIR EL ARCHIVO"<<'\n';
                    system("pause>nul");
                    }else
                    {

                        while(myFile1.good()){

                        string  config1="";
                        getline(myFile1,config1,','); // lee hasta donde llegue la coma
                        string value="";
                        string nombreArchivo = "";
                        getline(myFile1,value,'\n'); // lee hasta donde exista un salto de linea

                        //std::cout <<"Confi "<<config1<<" "<<'\n'; //IMPRIME
                        //std::cout <<"Value "<<value<<" "<<'\n'; //IMPRIME
                        //std::cout <<"----------------------" << '\n';
                        //std::istringstream numeroValue2(layer);
                        //numeroValue2>>numeroValue;
                         //PARA CMABIAR EL NOMBRE DE LA RAIZ
                        if(config1=="image_width")
                        {
                            matriz.raiz->anchoImagen=value;
                            matrizNegativa.raiz->anchoImagen=value;
                            matrizBN.raiz->anchoImagen=value;
                            matrizEspejo.raiz->anchoImagen=value;
                            matrizSinX.raiz->anchoImagen=value;
                            //std::cout <<"---entro anchoImagen" << '\n';
                        }else if(config1=="image_height")
                        {
                            matriz.raiz->alturaImagen=value;
                            matrizNegativa.raiz->alturaImagen=value;
                            matrizBN.raiz->alturaImagen=value;
                            matrizEspejo.raiz->alturaImagen=value;
                            matrizSinX.raiz->alturaImagen=value;
                            //std::cout <<"---entro altoImagen" << '\n';
                        }else if(config1=="pixel_width")
                        {
                            matriz.raiz->anchoPixel=value;
                            matrizNegativa.raiz->anchoPixel=value;
                            matrizBN.raiz->anchoPixel=value;
                            matrizEspejo.raiz->anchoPixel=value;
                            matrizSinX.raiz->anchoPixel=value;
                            //std::cout <<"---entro anchoPixel" << '\n';
                        }else if(config1=="pixel_height")
                        {
                            matriz.raiz->alturaPixel=value;
                            matrizNegativa.raiz->alturaPixel=value;
                            matrizBN.raiz->alturaPixel=value;
                            matrizEspejo.raiz->alturaPixel=value;
                            matrizSinX.raiz->alturaPixel=value;
                            //std::cout <<"---entro altoPixel" << '\n';
                        }

                        }
                        ///////////////////
                        myFile1.close();

                        ///////////////////
                    }
              }else if(layer=="")
              {
                  cout<<"Espacio en blanco"<<endl;
              }
              else
              {
                  matriz.generarNuevaMatriz(numeroLayer);
                  matrizNegativa.generarNuevaMatriz(numeroLayer);
                  matrizBN.generarNuevaMatriz(numeroLayer);
                  matrizEspejo.generarNuevaMatriz(numeroLayer);
                  matrizSinX.generarNuevaMatriz(numeroLayer);
                  contadorRaiz++; //PARA CMABIAR EL NOMBRE DE LA RAIZ
                  string auxNArchivo="";
                  auxNArchivo=archivo+"/"+nombreArchivo;
                  const char *nombre = auxNArchivo.c_str();
                  ifstream myFile(nombre);

              if(!myFile.is_open())
              {
                std::cout<<"ERROR: AL ABRIR EL ARCHIVO"<<'\n';
              }
              else
              {

                while(myFile.good()){

                    //string columna="";

                    string fila="";
                    getline(myFile,fila,'\n'); // lee hasta donde exista un salto de linea
                    //std::cout<<contadorFila<<"  "<<fila<<" "<<endl;
                    /////////////////////////////////////////////////////////////////////METODO EN EL QUE SEPARO POR COLUMNAS
                    std::string delimitador = ",";

                    size_t pos = 0;
                    std::string token;
                    while ((pos = fila.find(delimitador)) != std::string::npos) {
                        token = fila.substr(0, pos);
                        //std::cout <<"++++++++++++++++++++++++++"<< std::endl;
                        //std::cout << contadorColumnas<<" "<< token << std::endl;
                        //std::cout <<"*************************"<< std::endl;
                        copiaContadorRaiz = static_cast<std::ostringstream*>(&(std::ostringstream() << contadorRaiz))->str();
                        if(matriz.raiz->dato=="Raiz "+copiaContadorRaiz) //ARRIBA CONVIERTO EL IN A UN STRING Y DESPUES CONCATENO
                        {
                            matriz.raiz->dato=nombreArchivo;
                            matrizNegativa.raiz->dato=nombreArchivo;
                            matrizBN.raiz->dato=nombreArchivo;
                            matrizEspejo.raiz->dato=nombreArchivo;
                            matrizSinX.raiz->dato=nombreArchivo;

                        }
                        string sinX=token;
                        transform(sinX.begin(), sinX.end(), sinX.begin(), ::tolower);
                        if(sinX!="x")
                        {
                            matrizSinX.insertarElemento(contadorColumnas,contadorFila,token);
                        }
                        matriz.insertarElemento(contadorColumnas,contadorFila,token); //MATRIZ
                        matrizNegativa.insertarElemento(contadorColumnas,contadorFila,token);
                        matrizBN.insertarElemento(contadorColumnas,contadorFila,token);
                        matrizEspejo.insertarElemento(contadorColumnas,contadorFila,token);
                        fila.erase(0, pos + delimitador.length());
                        contadorColumnas++;
                    }
                    //std::cout <<"LO QUE RESTA DEL DATO"<< std::endl;
                    //std::cout <<contadorColumnas<<" "<< fila << std::endl;
                    //std::cout <<"lo que resta del dato"<< std::endl;
                    string sinX=fila;
                    transform(sinX.begin(), sinX.end(), sinX.begin(), ::tolower);
                    if(sinX!="x")
                    {
                        matrizSinX.insertarElemento(contadorColumnas,contadorFila,fila);
                    }
                    matriz.insertarElemento(contadorColumnas,contadorFila,fila);
                    matrizNegativa.insertarElemento(contadorColumnas,contadorFila,fila);
                    matrizBN.insertarElemento(contadorColumnas,contadorFila,fila);
                    matrizEspejo.insertarElemento(contadorColumnas,contadorFila,fila);


                    /////////////////////////////////////////////////////////////////////////////////FIN METODO SEPARA COLUMNAS
                    //separarColumnas(fila); //metodo en el que separon las palabras que tengan coma
                    contadorColumnas=0; // reinicio el contador Contar Columnas

                    contadorFila++;

                }
                contadorFila=0; //Reinicio el contador Fila
                /*if(contadorFila==0)
                {

                    matriz.generarNuevaMatriz(numeroLayer);
                    contadorRaiz++; //PARA CMABIAR EL NOMBRE DE LA RAIZ
                }*/
                myFile.close();
                //system("pause>nul");
              ////////////////////////////////////////////////////////////////////////////FIN METODO SEPARAR POR FILAS
              }
              }



          }
          contador++;
      }
      myFile.close();
      //system("pause>nul");
      int contador8=0;
      /*if(!archivo.empty())
        {
        archivo.resize(archivo.size()-4);
        }*/
      arbolOriginal.insertarNodo(arbolOriginal.raiz,archivo,matriz,matrizNegativa,matrizBN,matrizEspejo,matrizSinX); //GUARDA EL CUBO CON SU RESPECTIVO NOMBRE EN EL ARBOL
      arbolOriginal.contadorArbol++;
      arbolOriginal.mostrarArbol(arbolOriginal.raiz,contador8);//MUESTRA EL CUBO CON SU RESPRECTIVO NOMBRE EN EL ARBOL
      //system("pause>nul");
      //matriz.recorrerMatriz();
      //system("pause>nul");
      //matriz.imprimirRaiz();
      system("pause>nul");
      //crearImagen();
      }
}
void MenuPrincipal::menuSeleccionarImagen()
{
    //bool condicion = true;
    auxMatrizFiltro.primeraMatriz=NULL;
    std::string opcion="";
    NodoArbol *tempGuardarNodo;
    //do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Seleccionar Imagen----"<<endl;
        arbolOriginal.menuArbol(arbolOriginal.raiz);
        cout<<""<<endl;
        cout<<"Escriba el nombre de la imagen que desea utilizar"<<endl;
        cin>>opcion;
        tempGuardarNodo =arbolOriginal.buscarNodo(opcion,arbolOriginal.raiz);
        if(tempGuardarNodo==NULL)
        {
            cout<<"ERROR: No se ha encontrado el nombre ingresado"<<endl;
            system("pause>nul");
        }
        else
        {
            auxGuardarNodo = arbolOriginal.buscarNodo(opcion,arbolOriginal.raiz); //PROBAR
            cout<<"Se ha encontrado el Archivo, seleccion Exitosa"<<endl;
            if(listaFiltros.primero!=NULL){
                listaFiltros.limpiarLista(); //Limpio la lista
            }
            espejo=false;
            volteado=false;
            dosEjes=false;
            //listaFiltros->limpiarLista(); //Limpio la lista
            system("pause>nul");
        }

        //OPCIONES

    //}while(condicion);
}

std::string MenuPrincipal::cambiarAComa(std::string dato){

    for(int i = 0; i < dato.size(); i++){
        if(dato[i] == '-'){
            dato[i] =',';
        }
    }
    return dato;
}

void MenuPrincipal::crearImagen()
{
    if(auxGuardarNodo==NULL){
        cout<<"No se ha seleccionado ninguna Imagen"<<endl;
        system("pause>nul");
    }else
    {
        ofstream archivoHtml;
        ofstream archivoCss;
    //////////////////////////////////////CREAR CARPETA
        std::string auxCarpteNombre = "Exports//"+auxGuardarNodo->nombre;
        const char *nombreCarpeta = auxCarpteNombre.c_str();
        if(mkdir(nombreCarpeta)==0) cout<<"Carpeta creada correctamente"<<endl;
        else cout<<"La carpeta ya existe"<<endl;
        system("pause>nul");
    //////////////////////////////////////////////////////////////////////CREAR HTML Y CSS
        std::string auxNombreMatriz = auxGuardarNodo->nombre+".html";
        std::string auxNombreMatriz3 = "Exports\\"+auxGuardarNodo->nombre+"\\"+auxGuardarNodo->nombre+".html";
        const char *nombreArch = auxNombreMatriz3.c_str();
        archivoHtml.open(nombreArch,ios::out);
        std::string auxNombreMatriz2 = auxGuardarNodo->nombre+".css";
        std::string auxNombreMatriz4 ="Exports//"+auxGuardarNodo->nombre+"//"+auxGuardarNodo->nombre+".css";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        archivoCss.open(nombreArch2,ios::out);
    /////////////////////////////////////////////////////////////////////////

        archivoCss << "body{background: #333333;height: 100vh;display:flex;justify-content: center;align-items: center;}" <<endl;
        int altoImagen;
        std::istringstream altImagen(auxGuardarNodo->matriz.primeraMatriz->alturaImagen);
        altImagen>>altoImagen; //int de altura de la imagen

        int anchoImagen;
        std::istringstream anImagen(auxGuardarNodo->matriz.primeraMatriz->anchoImagen);
        anImagen>>anchoImagen; //int del ancho de la imagen

        int altoPixel;
        std::istringstream altPixel(auxGuardarNodo->matriz.primeraMatriz->alturaPixel);
        altPixel>>altoPixel; //int del alto del pixel

        int anchoPixel;
        std::istringstream anPixel(auxGuardarNodo->matriz.primeraMatriz->anchoPixel);
        anPixel>>anchoPixel; //int del ancho del pixel

        int AlturaTotal;
        AlturaTotal = altoImagen*altoPixel;
        int AnchoTotal;
        AnchoTotal= anchoImagen * anchoPixel;
        archivoCss << ".canvas{"<<endl;
        archivoCss << "width: "<<AnchoTotal<<"px;"<<endl;
        archivoCss <<"height: "<<AlturaTotal<<"px;}"<<endl;

        archivoCss <<".pixel{"<<endl;
        archivoCss << "float: left;\nwidth: "<<auxGuardarNodo->matriz.primeraMatriz->anchoPixel<<"px;"<<endl;
        archivoCss <<"height: "<<auxGuardarNodo->matriz.primeraMatriz->alturaPixel<<"px;}"<<endl;

        archivoHtml << "<!DOCTYPE html><html><head><link rel=\"stylesheet\" href=\""<<auxNombreMatriz2<<"\"></head><body>" << endl;
        archivoHtml<< "<div class=\"canvas\">"<< endl;

        NodoMatriz3D *aux;
        NodoMatriz3D *aux1;
        NodoMatriz3D *auxRaiz;
        aux = arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matriz.primeraMatriz; //OBTENGO LA PRIMERA MATRIZ

        //cout << aux->dato<<endl;
        auxRaiz=aux->frente;
        bool condicion = true;
        int indice = 1;
        while(condicion){
            while(aux != NULL){
               // cout<<"ENTRO EN EL PRIMER WHILE"<<endl;
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

                while(aux1 != NULL){
                //cout << "hola que ace"<<endl;
                    archivoHtml<<"<div class=\"pixel\"></div>"<<endl;
                    string ignorarDato=aux1->dato;
                    transform(ignorarDato.begin(), ignorarDato.end(), ignorarDato.begin(), ::tolower);
                    if(ignorarDato!="x")
                {
                    //cout<< aux1->dato <<" asdasdas" <<endl;
                    archivoCss <<"\n.pixel:nth-child("<<indice<<"){\nbackground: rgb("<<cambiarAComa(aux1->dato)<<");\n}";
                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
                indice++;
            }
        //aux = aux->abajo;
        //cout<<""<<endl;
        }
        aux=auxRaiz;
        if(aux!=NULL){
            //aux= aux->frente;
            auxRaiz=auxRaiz->frente;
            indice=1;
        }else
        {
            condicion= false;
            break;
        }
    }
    archivoHtml<<"</div></body></html>"<<endl;
    archivoHtml.close();
    archivoCss.close();
    system(nombreArch);
    }


}


void MenuPrincipal::menuFiltros()
{
    bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu filtros----"<<endl;
        cout<<"[1] Negativo"<<endl;
        cout<<"[2] Escala de Grises"<<endl;
        cout<<"[3] Espejo"<<endl;
        cout<<"[4] Collage"<<endl;
        cout<<"[5] Mosaico"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:
                system("cls");
                //Matriz3D matriz;
                filtro="n";
                filtroNB(filtro);
                break;
            case 2:
                filtro="g";
                filtroNB(filtro);
                break;
            case 3:
                menuEspejo();
                break;
            case 4:

                break;
            case 5:

                break;

            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}
void MenuPrincipal::filtroNB(string filtro)
{
    //auxMatrizFiltro.primeraMatriz=NULL;

    //Matriz3D nuevaMatriz;
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    if(filtro=="n"){
        Matriz3D matrizFiltro;
        matrizFiltro = arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matrizNegativa;
        NodoMatriz3D *aux;
        NodoMatriz3D *aux1;
        NodoMatriz3D *auxRaiz;
        aux = matrizFiltro.primeraMatriz;
        //cout<<aux->dato<<endl;
        auxRaiz=aux->frente;
        bool condicion = true;
    while(condicion){
        while(aux != NULL){
                //cout<<aux->dato<<endl;
                //cout<<aux->x<<endl;
                //cout<<aux->x<<endl;
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
                //cout<<aux1->dato<<endl;

                if(aux1->dato=="x"||aux1->dato=="X"){
                    //aux1 = aux1->siguiente;
                }else{
                    if(filtro=="g"){


                       // aux1 = aux1->siguiente;
                    }else if(filtro=="n"){
                        if(aux1->dato!=""){
                        //cout<<aux1->dato+" ENTRO EN NEGATIVO"<<endl;
                        //cout<<aux1->x<<endl;
                       // cout<<aux1->y<<endl;
                        string R="";
                        string G="";
                        string B="";
                        string color="";
                        int contador=0;
                        color=aux1->dato;
                        std::string delimitador = "-";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = color.find(delimitador)) != std::string::npos) {
                        token = color.substr(0, pos);

                        if(contador==0){
                            R=token;
                           // cout<<R+" VALOR DE R"<<endl;
                        }else if(contador==1)
                        {
                            G=token;
                            //cout<<G+" VALOR DE G"<<endl;
                        }

                        color.erase(0, pos + delimitador.length());
                       contador++;
                    }
                       B=color;
                      // cout<<B+" VALOR DE B"<<endl;
                       int r=0;
                       std::istringstream Re(R);
                       Re>>r;
                       int g=0;
                       std::istringstream Ge(G);
                       Ge>>g;
                       int b=0;
                       std::istringstream Be(B);
                       Be>>b;
                        int r2=255-r;
                        int g2=255-g;
                        int b2=255-b;
                        //int RGB = r2+g2+b2;
                        string rnuevo;
                        rnuevo=static_cast<std::ostringstream*>(&(std::ostringstream() << r2))->str();
                        string gnuevo;
                        gnuevo=static_cast<std::ostringstream*>(&(std::ostringstream() << g2))->str();
                        string bnuevo;
                        bnuevo=static_cast<std::ostringstream*>(&(std::ostringstream() << b2))->str();
                        //color=static_cast<std::ostringstream*>(&(std::ostringstream() << RGB))->str();
                        string datoNuevo="";
                        datoNuevo= rnuevo+"-"+gnuevo+"-"+bnuevo;
                        aux1->dato=datoNuevo;
                        //cout<<aux1->dato+" NUEVO COLOR"<<endl;
                        //aux1 = aux1->siguiente;
                    }
                    }
                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
            }
       // aux = aux->abajo;
        //cout<<""<<endl;
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
        auxMatrizFiltro=matrizFiltro;
        cout<<"Filtro Negativo aplicado a la Imagen"<<endl;
        listaFiltros.insertarNodo(matrizFiltro,"NEGATIVO");
        system("pause>nul");
        //auxMatrizFiltro = matrizFiltro.filtroNB("Negativo",matrizFiltro);
    }else if(filtro=="g"){
        //auxMatrizFiltro = matrizFiltro.filtroNB("BlancoNegro",matrizFiltro);
    Matriz3D matrizFiltro;
    matrizFiltro = arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matrizBN;
    NodoMatriz3D *aux;
    NodoMatriz3D *aux1;
    NodoMatriz3D *auxRaiz;
    aux = matrizFiltro.primeraMatriz;
    //cout<<aux->dato<<endl;
    auxRaiz=aux->frente;
    bool condicion = true;
    while(condicion){
        while(aux != NULL){
                //cout<<aux->dato<<endl;
                //cout<<aux->x<<endl;
                //cout<<aux->x<<endl;
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
                //cout<<aux1->dato<<endl;

                if(aux1->dato=="x"||aux1->dato=="X"){
                    //aux1 = aux1->siguiente;
                }else{
                    if(filtro=="n"){


                       // aux1 = aux1->siguiente;
                    }else if(filtro=="g"){
                        if(aux1->dato!=""){
                        //cout<<aux1->dato+" ENTRO EN BLANCO Y NEGRO"<<endl;
                        //cout<<aux1->x<<endl;
                        //cout<<aux1->y<<endl;
                        string R="";
                        string G="";
                        string B="";
                        string color="";
                        int contador=0;
                        color=aux1->dato;
                        std::string delimitador = "-";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = color.find(delimitador)) != std::string::npos) {
                        token = color.substr(0, pos);

                        if(contador==0){
                            R=token;
                           // cout<<R+" VALOR DE R"<<endl;
                        }else if(contador==1)
                        {
                            G=token;
                            //cout<<G+" VALOR DE G"<<endl;
                        }

                        color.erase(0, pos + delimitador.length());
                       contador++;
                    }
                       B=color;
                       //cout<<B+" VALOR DE B"<<endl;
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
                        //cout<<aux1->dato+" NUEVO COLOR"<<endl;
                        //aux1 = aux1->siguiente;
                    }
                    }
                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
            }
       // aux = aux->abajo;
        //cout<<""<<endl;
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
    auxMatrizFiltro=matrizFiltro;
        cout<<"Escala de Grises aplicada a la Imagen"<<endl;
        listaFiltros.insertarNodo(matrizFiltro,"GRIS");
        system("pause>nul");
    }


}
void MenuPrincipal::crearImagenFiltro()
{
     if(auxGuardarNodo==NULL){
        cout<<"No se ha seleccionado ninguna Imagen"<<endl;
        system("pause>nul");
    }else
    {
        ofstream archivoHtml;
        ofstream archivoCss;
    //////////////////////////////////////CREAR CARPETA
        std::string auxCarpteNombre = "Exports//"+auxGuardarNodo->nombre;
        const char *nombreCarpeta = auxCarpteNombre.c_str();
        if(mkdir(nombreCarpeta)==0) cout<<"Carpeta creada correctamente"<<endl;
        else cout<<"La carpeta ya existe"<<endl;
        system("pause>nul");
    //////////////////////////////////////////////////////////////////////CREAR HTML Y CSS
        std::string auxNombreMatriz = "Filtro"+auxGuardarNodo->nombre+".html";
        std::string auxNombreMatriz3 = "Exports\\"+auxGuardarNodo->nombre+"\\"+"Filtro"+auxGuardarNodo->nombre+".html";
        const char *nombreArch = auxNombreMatriz3.c_str();
        archivoHtml.open(nombreArch,ios::out);
        std::string auxNombreMatriz2 = "Filtro"+auxGuardarNodo->nombre+".css";
        std::string auxNombreMatriz4 ="Exports//"+auxGuardarNodo->nombre+"//"+"Filtro"+auxGuardarNodo->nombre+".css";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        archivoCss.open(nombreArch2,ios::out);
    /////////////////////////////////////////////////////////////////////////

        archivoCss << "body{background: #333333;height: 100vh;display:flex;justify-content: center;align-items: center;}" <<endl;
        int altoImagen;
        std::istringstream altImagen(auxGuardarNodo->matriz.primeraMatriz->alturaImagen);
        altImagen>>altoImagen; //int de altura de la imagen

        int anchoImagen;
        std::istringstream anImagen(auxGuardarNodo->matriz.primeraMatriz->anchoImagen);
        anImagen>>anchoImagen; //int del ancho de la imagen

        int altoPixel;
        std::istringstream altPixel(auxGuardarNodo->matriz.primeraMatriz->alturaPixel);
        altPixel>>altoPixel; //int del alto del pixel

        int anchoPixel;
        std::istringstream anPixel(auxGuardarNodo->matriz.primeraMatriz->anchoPixel);
        anPixel>>anchoPixel; //int del ancho del pixel

        int AlturaTotal;
        AlturaTotal = altoImagen*altoPixel;
        int AnchoTotal;
        AnchoTotal= anchoImagen * anchoPixel;
        archivoCss << ".canvas{"<<endl;
        archivoCss << "width: "<<AnchoTotal<<"px;"<<endl;
        archivoCss <<"height: "<<AlturaTotal<<"px;}"<<endl;

        archivoCss <<".pixel{"<<endl;
        archivoCss << "float: left;\nwidth: "<<auxGuardarNodo->matriz.primeraMatriz->anchoPixel<<"px;"<<endl;
        archivoCss <<"height: "<<auxGuardarNodo->matriz.primeraMatriz->alturaPixel<<"px;}"<<endl;

        archivoHtml << "<!DOCTYPE html><html><head><link rel=\"stylesheet\" href=\""<<auxNombreMatriz2<<"\"></head><body>" << endl;
        archivoHtml<< "<div class=\"canvas\">"<< endl;

        NodoMatriz3D *aux;
        NodoMatriz3D *aux1;
        NodoMatriz3D *auxRaiz;
        //aux = arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matriz.primeraMatriz; //OBTENGO LA PRIMERA MATRIZ
        aux = auxMatrizFiltro.primeraMatriz;
        //cout << aux->dato<<endl;
        auxRaiz=aux->frente;
        bool condicion = true;
        int indice = 1;
        while(condicion){
            while(aux != NULL){
                //cout<<"ENTRO EN EL PRIMER WHILE"<<endl;
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

                while(aux1 != NULL){
                //cout << "hola que ace"<<endl;
                    archivoHtml<<"<div class=\"pixel\"></div>"<<endl;
                    string ignorarDato=aux1->dato;
                    transform(ignorarDato.begin(), ignorarDato.end(), ignorarDato.begin(), ::tolower);
                    if(ignorarDato!="x")
                {
                    //cout<< aux1->dato <<" asdasdas" <<endl;
                    archivoCss <<"\n.pixel:nth-child("<<indice<<"){\nbackground: rgb("<<cambiarAComa(aux1->dato)<<");\n}";
                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
                indice++;
            }
        //aux = aux->abajo;
        //cout<<""<<endl;
        }
        aux=auxRaiz;
        if(aux!=NULL){
            //aux= aux->frente;
            auxRaiz=auxRaiz->frente;
            indice=1;
        }else
        {
            condicion= false;
            break;
        }
    }
    archivoHtml<<"</div></body></html>"<<endl;
    archivoHtml.close();
    archivoCss.close();
    system(nombreArch);
    }
}

void MenuPrincipal::menuEspejo()
{
    bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu Espejo----"<<endl;
        cout<<"[1] Espejo en Eje X"<<endl;
        cout<<"[2] Espejo en Y"<<endl;
        cout<<"[3] Espejo en ambos Ejes"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:
                system("cls");
                //Matriz3D matriz;
                espejo=true;
                volteado=false;
                dosEjes=false;
                cout<<"Filtro de espejo Aplicado a la Imagen"<<endl;
                listaFiltros.insertarNodo(auxGuardarNodo->sinX,"ESPEJO");
                break;
            case 2:
                espejo=false;
                volteado=true;
                dosEjes=false;
                listaFiltros.insertarNodo(auxGuardarNodo->sinX,"VOLTEADO");
                break;
            case 3:
                espejo=false;
                volteado=false;
                dosEjes=true;
                break;

            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}

void MenuPrincipal::crearImagenEspejo(bool espejo,bool vuelta, bool dosEjes){
    if(espejo){
        if(auxGuardarNodo==NULL){
        cout<<"No se ha seleccionado ninguna Imagen"<<endl;
        system("pause>nul");
    }else
    {
        ofstream archivoHtml;
        ofstream archivoCss;
    //////////////////////////////////////CREAR CARPETA
        std::string auxCarpteNombre = "Exports//"+auxGuardarNodo->nombre;
        const char *nombreCarpeta = auxCarpteNombre.c_str();
        if(mkdir(nombreCarpeta)==0) cout<<"Carpeta creada correctamente"<<endl;
        else cout<<"La carpeta ya existe"<<endl;
        system("pause>nul");
    //////////////////////////////////////////////////////////////////////CREAR HTML Y CSS
        std::string auxNombreMatriz = "Espejo"+auxGuardarNodo->nombre+".html";
        std::string auxNombreMatriz3 = "Exports\\"+auxGuardarNodo->nombre+"\\"+"Espejo"+auxGuardarNodo->nombre+".html";
        const char *nombreArch = auxNombreMatriz3.c_str();
        archivoHtml.open(nombreArch,ios::out);
        std::string auxNombreMatriz2 = "Espejo"+auxGuardarNodo->nombre+".css";
        std::string auxNombreMatriz4 ="Exports//"+auxGuardarNodo->nombre+"//"+"Espejo"+auxGuardarNodo->nombre+".css";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        archivoCss.open(nombreArch2,ios::out);
    /////////////////////////////////////////////////////////////////////////

        archivoCss << "body{background: #333333;height: 100vh;display:flex;justify-content: center;align-items: center;}" <<endl;
        int altoImagen;
        std::istringstream altImagen(auxGuardarNodo->matriz.primeraMatriz->alturaImagen);
        altImagen>>altoImagen; //int de altura de la imagen

        int anchoImagen;
        std::istringstream anImagen(auxGuardarNodo->matriz.primeraMatriz->anchoImagen);
        anImagen>>anchoImagen; //int del ancho de la imagen

        int altoPixel;
        std::istringstream altPixel(auxGuardarNodo->matriz.primeraMatriz->alturaPixel);
        altPixel>>altoPixel; //int del alto del pixel

        int anchoPixel;
        std::istringstream anPixel(auxGuardarNodo->matriz.primeraMatriz->anchoPixel);
        anPixel>>anchoPixel; //int del ancho del pixel

        int AlturaTotal;
        AlturaTotal = altoImagen*altoPixel;
        int AnchoTotal;
        AnchoTotal= anchoImagen * anchoPixel;
        archivoCss << ".canvas{"<<endl;
        archivoCss << "width: "<<AnchoTotal<<"px;"<<endl;
        archivoCss <<"height: "<<AlturaTotal<<"px;}"<<endl;

        archivoCss <<".pixel{"<<endl;
        archivoCss << "float: left;\nwidth: "<<auxGuardarNodo->matriz.primeraMatriz->anchoPixel<<"px;"<<endl;
        archivoCss <<"height: "<<auxGuardarNodo->matriz.primeraMatriz->alturaPixel<<"px;}"<<endl;

        archivoHtml << "<!DOCTYPE html><html><head><link rel=\"stylesheet\" href=\""<<auxNombreMatriz2<<"\"></head><body>" << endl;
        archivoHtml<< "<div class=\"canvas\">"<< endl;

        NodoMatriz3D *matrizEspejo;
        NodoMatriz3D *temp3;
        NodoMatriz3D *temp;
        NodoMatriz3D *temp2;
        Matriz3D matrizEspejoOriginal =arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matrizEspejo;
        matrizEspejo=arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matrizEspejo.primeraMatriz; //OBTENGO LA PRIMERA MATRIZ
        temp=matrizEspejo->frente;
        while(temp!=NULL){
                cout<<matrizEspejo->anchoImagen<<endl;
                //cout<<temp2->dato<<endl;
            if(temp->abajo!=NULL)
            {
               temp = temp->abajo;
            }
            else
            {
                break;
            }
            if(temp->siguiente!=NULL)
            {
                temp2 = temp->siguiente;
            }
            else
            {
                break;
            }
            cout<<temp2->dato<<endl;
            while(temp2 != NULL){
                cout<<temp2->x<<endl;
                string copiaX;
                copiaX=static_cast<std::ostringstream*>(&(std::ostringstream() << temp2->x+1))->str();
                if(copiaX==matrizEspejo->anchoImagen){
                        cout<<matrizEspejo->anchoImagen<<endl;
                        cout<<copiaX+"entro en el if"<<endl;
                    break;
                }

                temp2 = temp2->siguiente;
            }
            break;
        }



        NodoMatriz3D *aux;
        NodoMatriz3D *aux1;
        NodoMatriz3D *auxRaiz;
        aux=temp2;
        //aux = arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matriz.primeraMatriz; //OBTENGO LA PRIMERA MATRIZ
        //aux = auxMatrizFiltro.primeraMatriz;
        cout << aux->dato<<endl;
        auxRaiz=matrizEspejo->frente->frente;
        bool condicion = true;
        int indice = 1;
        while(condicion){
            while(aux != NULL){
               // cout<<"ENTRO EN EL PRIMER WHILE"<<endl;
                /*if(aux->abajo!=NULL)
                {
                    aux = aux->abajo;
                }
                else
                {
                break;
                }
                if(aux->anterior!=NULL)
                {
                aux1 = aux->anterior;
                }
                else
                {
                    break;
                }*/
                aux1=aux;
                while(aux1 != NULL){
                //cout << "hola que ace"<<endl;
                    archivoHtml<<"<div class=\"pixel\"></div>"<<endl;
                    if(aux1->dato=="Fila"){
                        break;
                    }
                    string ignorarDato=aux1->dato;
                    transform(ignorarDato.begin(), ignorarDato.end(), ignorarDato.begin(), ::tolower);
                    if(ignorarDato!="x")
                {
                    //if(aux1->dato!="Fila"){
                        archivoCss <<"\n.pixel:nth-child("<<indice<<"){\nbackground: rgb("<<cambiarAComa(aux1->dato)<<");\n}";
                    //}
                    //cout<< aux1->dato <<" asdasdas" <<endl;

                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->anterior;
                indice++;
            }
        aux = aux->abajo;
        //cout<<""<<endl;
        }
        aux=auxRaiz;
        if(aux!=NULL){
            //aux= aux->frente;
            auxRaiz=auxRaiz->frente;
            aux=aux->siguiente;
            aux=aux->abajo;
            while(aux!=NULL){
                string copiaX;
                copiaX=static_cast<std::ostringstream*>(&(std::ostringstream() << aux->x+1))->str();
                if(copiaX==matrizEspejo->anchoImagen){
                    break;
                }
                aux=aux->siguiente;
            }
            indice=1;
        }else
        {
            condicion= false;
            break;
        }
    }
    archivoHtml<<"</div></body></html>"<<endl;
    archivoHtml.close();
    archivoCss.close();
    system(nombreArch);

    }
    }else if(volteado){


        if(auxGuardarNodo==NULL){
        cout<<"No se ha seleccionado ninguna Imagen"<<endl;
        system("pause>nul");
    }else
    {
        ofstream archivoHtml;
        ofstream archivoCss;
    //////////////////////////////////////CREAR CARPETA
        std::string auxCarpteNombre = "Exports//"+auxGuardarNodo->nombre;
        const char *nombreCarpeta = auxCarpteNombre.c_str();
        if(mkdir(nombreCarpeta)==0) cout<<"Carpeta creada correctamente"<<endl;
        else cout<<"La carpeta ya existe"<<endl;
        system("pause>nul");
    //////////////////////////////////////////////////////////////////////CREAR HTML Y CSS
        std::string auxNombreMatriz = "Volteado"+auxGuardarNodo->nombre+".html";
        std::string auxNombreMatriz3 = "Exports\\"+auxGuardarNodo->nombre+"\\"+"Volteado"+auxGuardarNodo->nombre+".html";
        const char *nombreArch = auxNombreMatriz3.c_str();
        archivoHtml.open(nombreArch,ios::out);
        std::string auxNombreMatriz2 = "Volteado"+auxGuardarNodo->nombre+".css";
        std::string auxNombreMatriz4 ="Exports//"+auxGuardarNodo->nombre+"//"+"Volteado"+auxGuardarNodo->nombre+".css";
        const char *nombreArch2 = auxNombreMatriz4.c_str();
        archivoCss.open(nombreArch2,ios::out);
    /////////////////////////////////////////////////////////////////////////

        archivoCss << "body{background: #333333;height: 100vh;display:flex;justify-content: center;align-items: center;}" <<endl;
        int altoImagen;
        std::istringstream altImagen(auxGuardarNodo->matriz.primeraMatriz->alturaImagen);
        altImagen>>altoImagen; //int de altura de la imagen

        int anchoImagen;
        std::istringstream anImagen(auxGuardarNodo->matriz.primeraMatriz->anchoImagen);
        anImagen>>anchoImagen; //int del ancho de la imagen

        int altoPixel;
        std::istringstream altPixel(auxGuardarNodo->matriz.primeraMatriz->alturaPixel);
        altPixel>>altoPixel; //int del alto del pixel

        int anchoPixel;
        std::istringstream anPixel(auxGuardarNodo->matriz.primeraMatriz->anchoPixel);
        anPixel>>anchoPixel; //int del ancho del pixel

        int AlturaTotal;
        AlturaTotal = altoImagen*altoPixel;
        int AnchoTotal;
        AnchoTotal= anchoImagen * anchoPixel;
        archivoCss << ".canvas{"<<endl;
        archivoCss <<"transform: scale(1,-1);"<<endl;
        archivoCss << "width: "<<AnchoTotal<<"px;"<<endl;
        archivoCss <<"height: "<<AlturaTotal<<"px;}"<<endl;

        archivoCss <<".pixel{"<<endl;
        archivoCss << "float: left;\nwidth: "<<auxGuardarNodo->matriz.primeraMatriz->anchoPixel<<"px;"<<endl;
        archivoCss <<"height: "<<auxGuardarNodo->matriz.primeraMatriz->alturaPixel<<"px;}"<<endl;

        archivoHtml << "<!DOCTYPE html><html><head><link rel=\"stylesheet\" href=\""<<auxNombreMatriz2<<"\"></head><body>" << endl;
        archivoHtml<< "<div class=\"canvas\">"<< endl;

        NodoMatriz3D *aux;
        NodoMatriz3D *aux1;
        NodoMatriz3D *auxRaiz;
        aux = arbolOriginal.buscarNodo(auxGuardarNodo->nombre,arbolOriginal.raiz)->matriz.primeraMatriz; //OBTENGO LA PRIMERA MATRIZ

        //cout << aux->dato<<endl;
        auxRaiz=aux->frente;
        bool condicion = true;
        int indice = 1;
        while(condicion){
            while(aux != NULL){
               // cout<<"ENTRO EN EL PRIMER WHILE"<<endl;
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

                while(aux1 != NULL){
                //cout << "hola que ace"<<endl;
                    archivoHtml<<"<div class=\"pixel\"></div>"<<endl;
                    string ignorarDato=aux1->dato;
                    transform(ignorarDato.begin(), ignorarDato.end(), ignorarDato.begin(), ::tolower);
                    if(ignorarDato!="x")
                {
                    //cout<< aux1->dato <<" asdasdas" <<endl;
                    archivoCss <<"\n.pixel:nth-child("<<indice<<"){\nbackground: rgb("<<cambiarAComa(aux1->dato)<<");\n}";
                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
                indice++;
            }
        //aux = aux->abajo;
        //cout<<""<<endl;
        }
        aux=auxRaiz;
        if(aux!=NULL){
            //aux= aux->frente;
            auxRaiz=auxRaiz->frente;
            indice=1;
        }else
        {
            condicion= false;
            break;
        }
    }
    archivoHtml<<"</div></body></html>"<<endl;
    archivoHtml.close();
    archivoCss.close();
    system(nombreArch);
    }

    }else if(dosEjes){

    }

}


void MenuPrincipal::matrizLinealReporte()
{
    std::string opcion="";
        int numero;
        NodoArbol *tempGuardarNodo;
        //do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Seleccionar Imagen----"<<endl;
        arbolOriginal.menuArbol(arbolOriginal.raiz);
        cout<<""<<endl;
        cout<<"Escriba el nombre de la imagen que Graficar Lineal"<<endl;
        cin>>opcion;
        tempGuardarNodo =arbolOriginal.buscarNodo(opcion,arbolOriginal.raiz);
        if(tempGuardarNodo==NULL)
        {
            cout<<"ERROR: No se ha encontrado el nombre ingresado"<<endl;
            system("pause>nul");
        }
        else
        {
            auxNodoArbol = tempGuardarNodo;

            cout<<"Se ha encontrado el Archivo, seleccion Exitosa"<<endl;
            system("pause>nul");
            system("cls");

            tempGuardarNodo->matriz.mostrarCapasConfigM(tempGuardarNodo->matriz.primeraMatriz);
            cout<<"Ingrese el numero de capa de desea Graficar"<<endl;
            cin>>numero;
            cout<<"Ingrese si lo desea Graficar en Filas o Columnas"<<endl;
            string filaC;
            cin>>filaC;
            tempGuardarNodo->sinX.graficarLineal(tempGuardarNodo->sinX.primeraMatriz,numero,filaC);
            system("pause>nul");
        }
}

void MenuPrincipal::menuReportes()
{
     bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu Reportes----"<<endl;
        cout<<"[1] IMPORTED IMAGES REPORT"<<endl;
        cout<<"[2] IMAGE LAYER REPORT"<<endl;
        cout<<"[3] LINEAR MATRIX REPORT"<<endl;
        cout<<"[4] TRAVERSAL REPORT"<<endl;
        cout<<"[5] FILTERS REPORT"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:

                arbolOriginal.GraficarArbol();

                break;
            case 2:
                menuSeleccionarCubo();
                break;
            case 3:
                matrizLinealReporte();
                break;
            case 4:
                traversalReporte();
                break;
            case 5:
                reportesFiltro();
                break;
            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}
void MenuPrincipal::traversalReporte()
{
    bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu Reportes Transversal----"<<endl;
        cout<<"[1] Inorder Traversal"<<endl;
        cout<<"[2] Postorder Traversal"<<endl;
        cout<<"[3] Preorder Traversal"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:

                arbolOriginal.GraficarInorden();

                break;
            case 2:
                 arbolOriginal.GraficarPostorden();
                break;
            case 3:
                arbolOriginal.GraficarPreorden();
                break;
            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}

void MenuPrincipal::menuSeleccionarCubo()
{
        std::string opcion="";
        int numero;
        NodoArbol *tempGuardarNodo;
        //do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Seleccionar Imagen----"<<endl;
        arbolOriginal.menuArbol(arbolOriginal.raiz);
        cout<<""<<endl;
        cout<<"Escriba el nombre de la imagen que desea utilizar"<<endl;
        cin>>opcion;
        tempGuardarNodo =arbolOriginal.buscarNodo(opcion,arbolOriginal.raiz);
        if(tempGuardarNodo==NULL)
        {
            cout<<"ERROR: No se ha encontrado el nombre ingresado"<<endl;
            system("pause>nul");
        }
        else
        {
            auxNodoArbol = tempGuardarNodo;
            NodoMatriz3D *aux;
            aux = arbolOriginal.buscarNodo(auxNodoArbol->nombre,arbolOriginal.raiz)->matriz.primeraMatriz;
            cout<<"Se ha encontrado el Archivo, seleccion Exitosa"<<endl;
            system("pause>nul");
            system("cls");
            //auxNodoArbol = arbolOriginal.buscarNodo(opcion,arbolOriginal.raiz); //PROBAR
            /*while(aux!=NULL){
                if(aux->nivelCapa!=0)
                {
                    std::cout << aux->nivelCapa<<" "<<aux->dato<<std::endl;

                }
                aux=aux->frente;
            }*/
            //cout<<"Ingrese el numero de capa de desea Grafica o escriba TODO si desea graficar todo el Cubo"<<endl;
            //cin>>numero;
            tempGuardarNodo->matriz.mostrarCapasCubo(tempGuardarNodo->matriz.primeraMatriz);
            cout<<"Ingrese el numero de capa de desea Grafica o escriba -1 si desea graficar todo el Cubo"<<endl;
            cin>>numero;
            tempGuardarNodo->matriz.pruebaGraficar(tempGuardarNodo->matriz.primeraMatriz,numero,tempGuardarNodo->nombre);
            system("pause>nul");
        }
}

void MenuPrincipal::reportesFiltro()
{
    bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu Reportes----"<<endl;
        cout<<"[1] TODOS LOS FILTROS"<<endl;
        cout<<"[2] REPORTE FILTRO INDIVIDUAL"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:
                if(listaFiltros.primero!=NULL){
                    listaFiltros.graficarListaCircular(listaFiltros,auxGuardarNodo->nombre);
                }else{
                    cout<<"No ha seleccionado ningun filtro"<<endl;
                    system("pause>nul");
                }


                break;
            case 2:
                graficarTodoFiltro();
                break;
            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}

void MenuPrincipal::menuFiltroCambiarManualmente()
{
    string nombreFiltro;
    Matriz3D aux;
    int capa;
    cout<<"SELECCIONAR FILTRO"<<endl;
    if(listaFiltros.primero!=NULL){
    listaFiltros.mostrarFiltros();
    cout<<" Escriba el nombre del filtro que desea modificar"<<endl;
    cin>>nombreFiltro;
    aux=listaFiltros.buscarMatriz(nombreFiltro);
    //system("pause>nul");
    system("cls");
    aux.mostrarCapasCubo(aux.primeraMatriz);
    cout<<"Ingrese el numero de capa de desea modificar"<<endl;
    cin>>capa;
    int x;
    int y;
    string color;
    std::cout << ""<<std::endl;
    std::cout << "ESCRIBA LA COORDENADA EN X"<<std::endl;
    cin>>x;
    std::cout << ""<<std::endl;
    std::cout << "ESCRIBA LA COORDENADA EN Y"<<std::endl;
    cin>>y;
    std::cout << ""<<std::endl;
    std::cout << "ESCRIBA EL COLOR QUE DESEA PINTAR"<<std::endl;
    cin>>color;
    system("pause>nul");
    aux.edicionManualColor(aux.primeraMatriz,capa,x,y,color);
    auxMatrizFiltro=aux;
    std::cout << "Cambio realizado con exito"<<std::endl;
    //aux.graficarFiltro(aux.primeraMatriz,capa,auxGuardarNodo->nombre);
    system("pause>nul");
    }else{
        cout<<"No ha aplicado ningun filtro"<<endl;
        system("pause>nul");
    }
}

void MenuPrincipal::graficarTodoFiltro()
{
    string nombreFiltro;
    Matriz3D aux;
    int capa;
    cout<<"SELECCIONAR FILTRO"<<endl;
    if(listaFiltros.primero!=NULL){
    listaFiltros.mostrarFiltros();
    cout<<" Escriba el nombre del filtro que desea graficar"<<endl;
    cin>>nombreFiltro;
    aux=listaFiltros.buscarMatriz(nombreFiltro);
    //system("pause>nul");
    system("cls");
    aux.mostrarCapasCubo(aux.primeraMatriz);
    cout<<"Ingrese el numero de capa de desea Grafica o escriba -1 si desea graficar todo el Cubo"<<endl;
    cin>>capa;
    if(espejo){
        //aux.graficarEspejo(auxGuardarNodo->sinX.primeraMatriz,capa,auxGuardarNodo->nombre);
    }else if(volteado){
        aux.graficarEspejo(auxGuardarNodo->sinX.primeraMatriz,capa,auxGuardarNodo->nombre);
    }else if(dosEjes){

    }else{
        aux.graficarFiltro(aux.primeraMatriz,capa,auxGuardarNodo->nombre);
    }

    system("pause>nul");
    }else{
        cout<<"No ha aplicado ningun filtro"<<endl;
        system("pause>nul");
    }
    //aux.pruebaGraficar(aux,)

}
void MenuPrincipal::menuConfiguracionManual()
{
    if(auxGuardarNodo==NULL){
        cout<<"No se ha seleccionado una imagen"<<endl;
        system("pause>nul");
    }else
    {
        system("cls");
        int nivelCapa;
        std::cout << ""<<std::endl;
        std::cout << ""<<std::endl;
        std::cout << "----ESCRIBA EL NUMERO DE CAPA QUE DESEA MODIFICAR----"<<std::endl;
        auxNodoArbol->matriz.mostrarCapasConfigM(auxGuardarNodo->matriz.primeraMatriz);
        cin>>nivelCapa;

        system("pause>nul");

        int x;
        int y;
        string color;
        std::cout << ""<<std::endl;
        std::cout << "ESCRIBA LA COORDENADA EN X"<<std::endl;
        cin>>x;
        std::cout << ""<<std::endl;
        std::cout << "ESCRIBA LA COORDENADA EN Y"<<std::endl;
        cin>>y;
        std::cout << ""<<std::endl;
        std::cout << "ESCRIBA EL COLOR QUE DESEA PINTAR"<<std::endl;
        cin>>color;
        auxNodoArbol->matriz.edicionManualColor(auxGuardarNodo->matriz.primeraMatriz,nivelCapa,x,y,color);
        std::cout << "Cambio realizado con excito"<<std::endl;
        system("pause>nul");
    }
}
void MenuPrincipal::menuOpcionConfiguracionManual()
{
    bool condicion = true;
    int opcion;
    do{
        system("cls");

        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"----Menu Reportes----"<<endl;
        cout<<"[1] OG Image"<<endl;
        cout<<"[2] Filters"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Escriba un numero"<<endl;
        cin>>opcion;



        //OPCIONES
        switch (opcion) {
            case 1:

                menuConfiguracionManual();

                break;
            case 2:
                menuFiltroCambiarManualmente();
            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
}
/*void MenuPrincipal::separarColumnas(std::string dato)
{
    //Matriz3D matriz;

    std::string delimitador = ",";

    size_t pos = 0;
    std::string token;
    while ((pos = dato.find(delimitador)) != std::string::npos) {
        token = dato.substr(0, pos);
        std::cout <<"++++++++++++++++++++++++++"<< std::endl;
        std::cout << contadorColumnas<<" "<< token << std::endl;
        std::cout <<"*************************"<< std::endl;
        matriz.insertarElemento(contadorColumnas,contadorFila,token); //MATRIZ
        dato.erase(0, pos + delimitador.length());
        contadorColumnas++;
    }
    std::cout <<"LO QUE RESTA DEL DATO"<< std::endl;
    std::cout <<contadorColumnas<<" "<< dato << std::endl;
    std::cout <<"lo que resta del dato"<< std::endl;
    matriz.insertarElemento(contadorColumnas,contadorFila,dato); //MATRIZ
}*/
/*void MenuPrincipal::archivos(std::string nombreArchivo)
{

    const char *nombre = nombreArchivo.c_str();
    ifstream myFile(nombre);

    if(!myFile.is_open()) std::cout<<"ERROR: AL ABRIR EL ARCHIVO"<<'\n';


    while(myFile.good()){

        string columna="";

        string fila="";
        getline(myFile,fila,'\n'); // lee hasta donde exista un salto de linea
        std::cout<<contadorFila<<"  "<<fila<<" "<<endl;
        separarColumnas(fila); //metodo en el que separon las palabras que tengan coma
        contadorColumnas=0; // reinicio el contador Contar Columnas

        contadorFila++;

    }
    contadorFila=0; //Reinicio el contador Fila
    if(contadorFila==0)
    {

        matriz.generarNuevaMatriz();
    }
    myFile.close();
    system("pause>nul");


}*/
