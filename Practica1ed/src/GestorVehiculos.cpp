#include "GestorVehiculos.h"
#include "comun.h"
#include <iomanip>

void esteticaVehiculos(){
cout<<"MODELO           MATRICULA     PROVINCIA    KILOMETROS    PRECIO POR KM  ESTADO"<<endl;
cout<<"*********************************************************************************************"<<endl;
}

GestorVehiculos::GestorVehiculos(cadena NomPpal){

    }


GestorVehiculos::~GestorVehiculos(){
    ficheroPrincipal.close();
}

int GestorVehiculos::getNumVehiculos(){
    return numVehiculos;
}

void GestorVehiculos::mostrar(cadena provincia){
}


//int GestorVehiculos::consultar(int posicion);
//void GestorVehiculos::insertar(Vehiculo v);
//void GestorVehiculos::modificar Vehiculo v,int posicion);
//void GestorVehiculos::eliminarPorPosicion(int posicion);


