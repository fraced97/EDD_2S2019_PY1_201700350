#include "MenuPrincipal.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

MenuPrincipal::MenuPrincipal()
{
    //ctor
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

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:
                    //arbolOriginal.GraficarArbol();
                    //arbolOriginal.GraficarInorden();
                    //arbolOriginal.GraficarPreorden();
                    //arbolOriginal.GraficarPostorden();
                    //system("pause>nul");
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
      std::string rutaArchivo="";
      cout<<""<<endl;
      cout<<""<<endl;
      cout<<"----INSERTAR IMAGEN----"<<endl;
      cout<<"---------------------------------"<<endl;
      cout<<"--Ingrese nombre del archivo .csv--"<<endl;
      cin>>archivo;
      const char *nombre = archivo.c_str();

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
              nombreArchivo = file; //nombre de los otros archivos
              //archivos(nombreArchivo); //mando el nombre de
              ////////////////////////////////////////////////////////////////////////////METODO EN EL QUE SEPARO POR FILAS
              const char *nombre = nombreArchivo.c_str();
              ifstream myFile(nombre);

              if(!myFile.is_open()) std::cout<<"ERROR: AL ABRIR EL ARCHIVO"<<'\n';


                while(myFile.good()){

                    string columna="";

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
                if(contadorFila==0)
                {

                    matriz.generarNuevaMatriz(nombreArchivo);
                }
                myFile.close();
                //system("pause>nul");
              ////////////////////////////////////////////////////////////////////////////FIN METODO SEPARAR POR FILAS
          }
          contador++;
      }
      myFile.close();
      //system("pause>nul");
      int contador8=0;
      arbolOriginal.insertarNodo(arbolOriginal.raiz,archivo,matriz); //GUARDA EL CUBO CON SU RESPECTIVO NOMBRE EN EL ARBOL
      arbolOriginal.mostrarArbol(arbolOriginal.raiz,contador8);//MUESTRA EL CUBO CON SU RESPRECTIVO NOMBRE EN EL ARBOL
      system("pause>nul");
      matriz.recorrerMatriz();
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
