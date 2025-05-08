#include "comun.h"

lista::lista() {
	elementos = new Entrada[INCREMENTO];
	if (elementos != NULL) {
		Tama = INCREMENTO;
		n = 0;
	}
	else {
		Tama = n = -1;
	}
}


lista::~lista() {
	if (elementos != NULL) {
		delete[] elementos;
	}
	elementos = NULL;
	Tama = n = 0;
}

void lista::aumentarTama() {
	Entrada* NuevaZona = new Entrada[Tama + INCREMENTO];
	if (NuevaZona != NULL) {
		for (int i = 0; i < n; i++) {
			NuevaZona[i] = elementos[i];
		}
		Tama += INCREMENTO;
		delete[] elementos;
		elementos = NuevaZona;
	}
}

void lista::insertar(int i, Entrada e) {
	int pos;
	if (n == Tama) {
		aumentarTama();
	}
	if (n < Tama) {
		for (pos = n-1; pos >= i; pos--) {
			elementos[pos+1] = elementos[pos];
		}
		elementos[i - 1] = e;
	}

}


void lista::modificar(int i, Entrada e) {
	elementos[i - 1] = e;
}

Entrada lista::observar(int i) {
	return elementos[i - 1];
}

bool lista::esvacia() {
	return(n == 0);
}

int lista::longitud() {
	return n;
}

void lista::eliminar(int i) {
	while (i < n) {
		elementos[i - 1] = elementos[i];
	}
	n--;
	if (Tama - n >= INCREMENTO && Tama > INCREMENTO) {
		Entrada* NuevaZona = new Entrada[Tama - INCREMENTO];
		if (NuevaZona != NULL) {
			for (int i = 0; i < n; i++) {
				NuevaZona[i] = elementos[i];
			}
			Tama -= INCREMENTO;
			delete[] elementos;
			elementos = NuevaZona;
		}
	}
}

int lista::posicion(Entrada e) {
	int i = 0;
	while (elementos[i].codIdEntrada != e.codIdEntrada && 1 < n) {
		i++;
	}
	return (i == n ? -1 : i + 1);
}

lista::lista(Entrada e) {
	elementos = new Entrada[INCREMENTO];
	if (elementos != NULL) {
		Tama = INCREMENTO;
		n = 1;
		elementos[0] = e;
	}
	else {
		Tama = n = -1;
	}
}

void lista::anadirIzq(Entrada e) {
	insertar(1, e);
}

void lista::anadirDch(Entrada e) {
	insertar(n + 1, e);
}

void lista::eliminarIzq() {
	eliminar(1);
}

void lista::eliminarDch() {
	eliminar(n + 1);
}

Entrada lista::observarIzq() {
	return elementos[0];
}

Entrada lista::observarDch() {
	return elementos[n - 1];
}

void lista::concatenar(lista l) {
	int lon = l.longitud();
	for (int i = 1; i <= lon; i++) {
		anadirDch(l.observar(i));
	}
}

bool lista::pertenece(Entrada e) {
	return(posicion(e) != -1);
}
