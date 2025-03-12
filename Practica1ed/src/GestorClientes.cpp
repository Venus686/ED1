#include "comun.h"
#include "GestorClientes.h"
#include <iomanip>
#include "comun.h"

void esteticaClientes(){
cout<<"DNI        NOMBRE                             PROVINCIA     ACUMU KM       ACUMU $   VEHICULO"<<endl;
cout<<"*********************************************************************************************"<<endl;
}

GestorClientes::GestorClientes(cadena NomFile){
    fichero.open("ClientesSin.dat", ios::in | ios::out | ios::binary);
    if (fichero.fail()){
        cout<< "Se ha producido un error al abrir el fichero";
        fichero.close();
        fichero.clear();
        fichero.open("ClientesSin.dat", ios::in | ios::out | ios::binary);
        numclientes=0;
        fichero.write((char*)&numclientes, sizeof(int));
        fichero.close();
        fichero.open("ClientesSin.dat", ios::in | ios::out | ios::binary);

    }else{
        fichero.seekg(0,ios::beg);
        fichero.read((char*)&numclientes, sizeof(int));
    }
}

GestorClientes::~GestorClientes(){
    fichero.close();
}

int GestorClientes::getNumClientes(){
    return numclientes;
}

bool GestorClientes::mostrar (cadena Dni){
    bool mostrado=false;
    cadena vehiculo;
    TCliente cliente;
        if(strcmp(Dni,"*")==0){
            fichero.seekg(sizeof(int), ios::beg);
            esteticaClientes();
            while (!fichero.eof()){
                fichero.read((char*)&cliente, sizeof(TCliente));
                cout<<setw(11)<<left<<cliente.Dni;
                cout<<setw(35)<<left<<cliente.Nombre;
                cout<<setw(14)<<left<<cliente.Provincia;
                cout<<setw(15)<<left<<cliente.AcumuKm;
                cout<<setw(10)<<left<<cliente.AcumuEuros;
                if(cliente.VEnAlquiler){
                    strcpy(vehiculo,"Si");
                }else{
                    strcpy(vehiculo,"No");
                }
                cout<<setw(8)<<left<<vehiculo<<endl;
                mostrado=true;
            }
            fichero.clear();
        }else{
            fichero.seekg(sizeof(int), ios::beg);
            esteticaClientes();
            while (!fichero.eof()){
                fichero.read((char*)&cliente, sizeof(TCliente));
                if(strcmp(cliente.Dni,Dni)==0){
                cout<<setw(11)<<left<<cliente.Dni;
                cout<<setw(35)<<left<<cliente.Nombre;
                cout<<setw(14)<<left<<cliente.Provincia;
                cout<<setw(15)<<left<<cliente.AcumuKm;
                cout<<setw(10)<<left<<cliente.AcumuEuros;
                if(cliente.VEnAlquiler){
                    strcpy(vehiculo,"Si");
                }else{
                    strcpy(vehiculo,"No");
                }
                cout<<setw(8)<<left<<vehiculo<<endl;
                mostrado=true;
                break;
                }
            }

        }
        return mostrado;
    }


int GestorClientes::buscar(cadena Dni){
    TCliente cliente;
    int posicion=-1;
    fichero.seekg(0, ios:: beg);
    while (!fichero.eof()){
        fichero.read((char*)&cliente, sizeof(TCliente));
        if(strcmp (cliente.Dni, Dni)==0){
            posicion=fichero.tellg()-sizeof(TCliente);
            break;
        }
    }
    return posicion;
}


TCliente GestorClientes::consultar(int Posicion){
    TCliente cliente;

    if (Posicion =-1){
        strcpy(cliente.Dni, "*");
        strcpy(cliente.Nombre, "*");
        strcpy(cliente.Provincia, "*");
        cliente.AcumuKm = 0.00;
        cliente.AcumuEuros = 0.00;
        cliente.VEnAlquiler = false;
    }else {
        fichero.seekg(Posicion * sizeof (TCliente), ios::beg);
        fichero.read ((char*)&cliente, sizeof (TCliente));
    }
    return cliente;

}

/*
void GestorClientes::insertar (TCliente C) {
    fichero.seekg(0, ios::beg);
    bool encontrado =false;
   // for(i=0;i<=numcliente;i++){

   // }
    while (!fichero.eof()){
        fichero.read((char*)&cliente, sizeof(TCliente));
        if (strcmp(C.Dni, )==0) {
            cout<< "Error, el dni que has introducido ya existe";
            encontrado=true;
            break;
        }
        if (strcmp(C.Dni, cliente.Dni)<0){
            pos=fichero.tellg()- sizeof(TCliente);
            encontrado=true;
            break;
        }
        pos=fichero.tellg();
    }
    if(!encontrado){
        pos=fichero.tellg();
    }
    fichero.seekp(pos);
    fichero.write((char*)&C, sizeof(TCliente));
}*/


bool GestorClientes:: modificar (TCliente C, int Posicion){
    fichero.seekp(Posicion *sizeof(TCliente));
    fichero.write((char*)&C, sizeof(TCliente));
}


bool GestorClientes::eliminar (int Posicion){
    bool eliminado= false;
    TCliente cliente;
    if (Posicion !=-1){
        fichero.seekg(Posicion, ios::beg);
        fichero.read((char*)&cliente, sizeof(TCliente));
        if (strcmp(cliente.Dni, "") != 0) {
            fichero.seekp(Posicion, ios::beg);
            strcpy(cliente.Dni, "");
            fichero.write((char*)&cliente, sizeof(TCliente));

        }
        eliminado =true;
    }


    return eliminado;
}
