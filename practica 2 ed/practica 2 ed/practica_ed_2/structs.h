#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
#include "comun.h"


struct Concierto{
     int codId; //codigo unico identificativo del concierto
     cadena nombreGrupo; //nombre del grupo o artista que realiza la actuaci�n
     cadena fechaCelebracion; //fecha de celebraci�n del concierto. Formato: AAAAMMDD
     int numMaxEntradas; //numero maximo de entradas disponibles para el concierto
     int numEntradasVendidas; //n�mero de entradas vendidas para el concierto
     cola colaEspera; //cola de solicitudes de compra de entradas
     lista entradasVendidas; //lista de entradas vendidas
     Concierto *sigC;
};



#endif // STRUCTS_H_INCLUDED
