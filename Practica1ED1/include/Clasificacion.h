#ifndef CLASIFICACION_H
#define CLASIFICACION_H


struct Jugador {
 int indice;
 int resultado;
};

class Clasificacion {
 Jugador *elementos;
 int Jugadores;
 int tamano;
public:
 Clasificacion();
 void anadirjugador(Jugador j);
 void eliminar(int i);
 Jugador consultar(int n);
 bool vacio();
 int numjugadores();
 void ordenar();
 ~Clasificacion();
};


#endif // CLASIFICACION_H
