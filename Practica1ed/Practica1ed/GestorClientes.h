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
        GestorClientes(cadena NomPpal);
        ~GestorClientes();
        int getNumClientes();
        bool mostrar (cadena Dni);
        //Devolver� la posici�n del primer cliente del fichero cuyo Dni coincida con el pasado por par�metro.
        //Si no se encuentra ning�n cliente devolver� -1.
        int buscar (cadena Dni);
        TCliente consultar(int Posicion);
        void insertar (TCliente C);
        bool modificar (TCliente C, int Posicion);
        bool eliminar (int Posicion);
};

void esteticaClientes();

#endif // GESTORCLIENTES_H
