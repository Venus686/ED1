#ifndef GESTORALQUILER_H
#define GESTORALQUILER_H
#include "comun.h"

struct TAlquiler{
    cadena Dni;
    cadena Matricula;
    int KmsCir;
    int NDiasCir;

};
class GestorAlquiler
{
    fstream fichero;
    int numAlquiler;
    int tam;
    TAlquiler *Alquileres;
    cadena nomFichero;
    void aumentarArray();
    public:
        //Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargará en el
        //vector dinámico Alquileres toda la información que contiene el fichero binario cuyo nombre es pasado
        //por parámetro. Una vez cargado el fichero se cerrará.
        GestorAlquiler(cadena nomPal);
        ~GestorAlquiler();
        int getNumAlquiler();
        void nuevo(TAlquiler A);
        int Buscar (cadena Datos, char DM);
        TAlquiler consultar (int posicion);
        bool modificar(TAlquiler A, int posicion);
        bool eliminarPorPosicion (int posicion);
};

#endif // GESTORALQUILER_H
