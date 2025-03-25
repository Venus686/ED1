#ifndef GESTORVEHICULOS_H
#define GESTORVEHICULOS_H
#include "comun.h"

struct Vehiculo{
    cadena modelo;
    cadena matricula;
    cadena provincia;
    int kilometros;
    float precio_km;
    cadena estado;
};


class GestorVehiculos{

    fstream ficheroPrincipal;
    int numVehiculos;
    int tam;
    Vehiculo *vehiculos;
    cadena nomFichero;

    void aumentarArray();

public:
    GestorVehiculos (cadena nomPpal);
    ~GestorVehiculos();
    int getNumVehiculos();
    void mostrar (cadena provincia);
    Vehiculo consultar (int posicion);
    int consultar (cadena matricula);
    void insertar (Vehiculo v);
    void modificar (Vehiculo v, int posicion);
    void eliminarPorPosicion (int posicion);

};

#endif // GESTORVEHICULOS_H
