#include "Clasificacion.h"
#define SALTO 4
Clasificacion::Clasificacion(){
    tamano=0;
    Jugadores=0;
}

Clasificacion::~Clasificacion()
{
    delete[]elementos;
}

void Clasificacion::anadirjugador(Jugador j){
    if(Jugadores==tamano){
        tamano+= SALTO;
        Jugador *nJugador = new Jugador[tamano];
        for (int i=0; i<Jugadores;i++){
            nJugador[i]=elementos[i];
        }
        delete[]elementos;
        elementos=nJugador;
    }
    elementos[Jugadores]= j;
    Jugadores++;
}

void Clasificacion::eliminar(int i){
    if (i>=0 || i<=Jugadores){
        for(int j=i; i< Jugadores-1;i++){
            elementos[i]=elementos[i+1];
        }
        Jugadores--;
    }
}

Jugador Clasificacion::consultar(int n){
     if (n>=0 || n<=Jugadores){
        return elementos[n];
    }
}
bool Clasificacion::vacio(){
    bool vacio=false;
    if (Jugadores==0){
        vacio =true;
    }
    return vacio;
}

int Clasificacion::numjugadores(){
    return Jugadores;
}
/*
void vector::Burbuja(int inicio, int fin){
    int pos,ele;
    for (pos=inicio; pos<fin; pos++)
        for (ele=inicio+1; ele<fin ; ele++)
            if(celda[ele-1]>celda[ele])
                intercambiar(celda[ele-1],celda[ele]);//Función genérica que tendrá que ser implementada
}*/
void  Clasificacion::ordenar(){
   /* if (Jugadores > 1) {
        Burbuja(0, Jugadores);
    }*/
}
