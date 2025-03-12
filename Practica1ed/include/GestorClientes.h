#ifndef GESTORCLIENTES_H
#define GESTORCLIENTES_H
#include "comun.h"

struct TCliente{
    cadena Dni;
    cadena Nombre;
    cadena Provincia;
    int AcumuKm;
    float AcumuEuros;
    bool VEnAlquiler;
};

class GestorClientes
{
    fstream fichero;
    int numclientes;

public:
        GestorClientes(cadena NomFile);
        ~GestorClientes();
        int getNumClientes();
        bool mostrar (cadena Dni);
        int buscar (cadena Dni);
        TCliente consultar(int Posicion);
        void insertar (TCliente C);
        bool modificar (TCliente C, int Posicion);
        bool eliminar (int Posicion);
};

void esteticaClientes();

#endif // GESTORCLIENTES_H
