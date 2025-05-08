#ifndef LISTA_H
#define LISTA_H
#include "comun.h"

struct Entrada {
     int codIdEntrada; //c�digo identificativo de la entrada
     cadena dniComprador; //dni del dueño de la entrada
};

class lista {
	Entrada* elementos;
	int n;
	int Tama;
public:
	lista();
	~lista();
	lista(Entrada e);
	void aumentarTama();
	bool esvacia();
	int longitud();
	void anadirIzq(Entrada e);
	void anadirDch(Entrada e);
	void eliminarIzq();
	void eliminarDch();
	Entrada observarIzq();
	Entrada observarDch();
	void concatenar(lista l);
	bool pertenece(Entrada e);
	void insertar(int i, Entrada e);
	void eliminar(int i);
	void modificar(int i, Entrada e);
	Entrada observar(int i);
	int posicion(Entrada e);
};
#endif // LISTA_H
