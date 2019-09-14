#include "MenuPrincipal.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <direct.h>
using namespace std;

MenuPrincipal::MenuPrincipal()
{
    //ctor
    this->auxGuardarNodo=NULL;
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

                break;
            case 5:
                    crearImagen();
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

          std::cout <<"Layer "<<layer<<" "<<'\n'; //IMPRIME
          std::cout <<"File "<<file<<" "<<'\n'; //IMPRIME
          std::cout <<"----------------------" << '\n';
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
                  contadorRaiz++;
                  //matriz.raiz->nivelCapa = numeroLayer;
                  matriz.raiz->dato = nombreArchivo;
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

                        std::cout <<"Confi "<<config1<<" "<<'\n'; //IMPRIME
                        std::cout <<"Value "<<value<<" "<<'\n'; //IMPRIME
                        std::cout <<"----------------------" << '\n';
                        //std::istringstream numeroValue2(layer);
                        //numeroValue2>>numeroValue;
                         //PARA CMABIAR EL NOMBRE DE LA RAIZ
                        if(config1=="image_width")
                        {
                            matriz.raiz->anchoImagen=value;
                            std::cout <<"---entro anchoImagen" << '\n';
                        }else if(config1=="image_height")
                        {
                            matriz.raiz->alturaImagen=value;
                            std::cout <<"---entro altoImagen" << '\n';
                        }else if(config1=="pixel_width")
                        {
                            matriz.raiz->anchoPixel=value;
                            std::cout <<"---entro anchoPixel" << '\n';
                        }else if(config1=="pixel_height")
                        {
                            matriz.raiz->alturaPixel=value;
                            std::cout <<"---entro altoPixel" << '\n';
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
                    std::cout<<contadorFila<<"  "<<fila<<" "<<endl;
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

                        }
                        matriz.insertarElemento(contadorColumnas,contadorFila,token); //MATRIZ
                        fila.erase(0, pos + delimitador.length());
                        contadorColumnas++;
                    }
                    //std::cout <<"LO QUE RESTA DEL DATO"<< std::endl;
                    //std::cout <<contadorColumnas<<" "<< fila << std::endl;
                    //std::cout <<"lo que resta del dato"<< std::endl;
                    matriz.insertarElemento(contadorColumnas,contadorFila,fila);


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
      arbolOriginal.insertarNodo(arbolOriginal.raiz,archivo,matriz); //GUARDA EL CUBO CON SU RESPECTIVO NOMBRE EN EL ARBOL
      arbolOriginal.contadorArbol++;
      arbolOriginal.mostrarArbol(arbolOriginal.raiz,contador8);//MUESTRA EL CUBO CON SU RESPRECTIVO NOMBRE EN EL ARBOL
      system("pause>nul");
      matriz.recorrerMatriz();
      system("pause>nul");
      matriz.imprimirRaiz();
      system("pause>nul");
      //crearImagen();
      }
}
void MenuPrincipal::menuSeleccionarImagen()
{
    //bool condicion = true;
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
            system("pause>nul");
        }

        //OPCIONES

    //}while(condicion);
}

std::string MenuPrincipal::limpiar_color(std::string color){

    for(int i = 0; i < color.size(); i++){
        if(color[i] == '-'){
            color[i] =',';
        }
    }
    return color;
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
        std::string auxCarpteNombre = "C://Users//USUARIO//Desktop//CodeBlocks//EDDProyecto1//Exports//"+auxGuardarNodo->nombre;
        const char *nombreCarpeta = auxCarpteNombre.c_str();
        if(mkdir(nombreCarpeta)==0) cout<<"Carpeta creada correctamente"<<endl;
        else cout<<"La carpeta ya existe"<<endl;
        system("pause>nul");
    //////////////////////////////////////////////////////////////////////CREAR HTML Y CSS
        std::string auxNombreMatriz = auxGuardarNodo->nombre+".html";
        std::string auxNombreMatriz3 = "C://Users//USUARIO//Desktop//CodeBlocks//EDDProyecto1//Exports//"+auxGuardarNodo->nombre+"//"+auxGuardarNodo->nombre+".html";
        const char *nombreArch = auxNombreMatriz3.c_str();
        archivoHtml.open(nombreArch,ios::out);
        std::string auxNombreMatriz2 = auxGuardarNodo->nombre+".css";
        std::string auxNombreMatriz4 ="C://Users//USUARIO//Desktop//CodeBlocks//EDDProyecto1//Exports//"+auxGuardarNodo->nombre+"//"+auxGuardarNodo->nombre+".css";
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

        cout << aux->dato<<endl;
        auxRaiz=aux->frente;
        bool condicion = true;
        int indice = 1;
        while(condicion){
            while(aux != NULL){
                cout<<"ENTRO EN EL PRIMER WHILE"<<endl;
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
                    if(aux1->dato!="x")
                {
                    //cout<< aux1->dato <<" asdasdas" <<endl;
                    archivoCss <<"\n.pixel:nth-child("<<indice<<"){\nbackground: rgb("<<limpiar_color(aux1->dato)<<");\n}";
                }
                //cout << aux1->dato<<" ";
                aux1 = aux1->siguiente;
                indice++;
            }
        //aux = aux->abajo;
        cout<<""<<endl;
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


                break;
            case 2:

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


                break;
            case 2:

                break;
            case 3:

                break;

            case 0:
                condicion = false;
                break;
        }
    }while(condicion);
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

                break;
            case 4:
                traversalReporte();
                break;
            case 5:

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
            tempGuardarNodo->matriz.pruebaGraficar(tempGuardarNodo->matriz.primeraMatriz,numero);
            system("pause>nul");
        }
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
