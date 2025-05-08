#include "Festival.h"
#include "comun.h"

 Festival::Festival(cadena nomFestival, cadena fIni, cadena fFin){
    strcpy(nombre, nomFestival);
    strcpy(fechaInicio,fIni);
    strcpy(fechaFin, fFin);
    numConciertos=0;
    conciertos=NULL;

 }

 void Festival:: getNombre(cadena nomFestival){
    strcpy(nomFestival, nombre);
 }

void Festival::getFechaInicio(cadena fIni){
    strcpy(fIni, fechaInicio);
}

void Festival:: getFechaFin (cadena fFin){
    strcpy(fFin, fechaFin);
}

int Festival:: getNumConciertos(){
    return numConciertos;
}

bool Festival::programarConcierto(int idConcierto, cadena nomGrupo, cadena fecha, int numEntradasMax){
    bool programar=false;
    Concierto *aux_c = conciertos;
    bool encontrado=false;

    while (aux_c!=NULL && !encontrado){
        if (aux_c->codId == idConcierto){
            encontrado=true;
            cout<< "El concierto ya ha sido registrado."<<endl;
            return programar;
        }else{
            aux_c=aux_c->sigC;
        }
    }

    while (aux_c!=NULL && !encontrado){
        if (strcmp (aux_c->nombreGrupo, nomGrupo)==0){
            encontrado=true;
            cout<< "Ya hay un concierto registrado para el mismo grupo."<<endl;
            return programar;
        }else{
            aux_c=aux_c->sigC;
        }
    }

    Concierto *nuevoconcierto= new Concierto;
    strcpy(nuevoconcierto->nombreGrupo,nomGrupo);
    strcpy(nuevoconcierto->fechaCelebracion, fecha);
    nuevoconcierto->numMaxEntradas= numEntradasMax;
    nuevoconcierto->numEntradasVendidas=0;
    nuevoconcierto->sigC = conciertos;

    if(conciertos==NULL){
        conciertos=nuevoconcierto;
    }else{
        nuevoconcierto->sigC=conciertos;
        conciertos=nuevoconcierto;
    }
    numConciertos ++;
    return programar=true;
}


 bool Festival::cargarConciertoDesdeFichero(cadena nomFichero)
{
    ifstream fichero;
	fichero.open(nomFichero, ios::binary);
	if (fichero.fail()) {
		fichero.close();
		fichero.clear();
		return false;
	}
	else {
	    int n, m, x;
	    Entrada e;
	    SolicitudCompra s;
	    fichero.seekg(0,ios::beg);
	    int codId, numMax;
	    cadena nombreGrupo, fecha, dni;
        fichero.read((char*)&codId,sizeof(int));
        fichero.read((char*)&nombreGrupo,sizeof(cadena));
        fichero.read((char*)&fecha,sizeof(cadena));
        fichero.read((char*)&numMax,sizeof(int));
        programarConcierto(codId, nombreGrupo, fecha, numMax);
        fichero.read((char*)&n, sizeof(int));
        for(int i=0;i<n;i++){
            fichero.read((char*)&e, sizeof(Entrada));
            comprarEntrada(codId,e.dniComprador);

        }
        fichero.read((char*)&m, sizeof(int));
        for(int i=0; i < m; i++){
            fichero.read((char*)&s, sizeof(SolicitudCompra));
            registrarReserva(codId, s);
        }
        }
	fichero.close();
	fichero.clear();
	return true;
}


bool Festival::cancelarConcierto(int idConcierto){
    Concierto* nodo_aux = conciertos;
    int pos=existeConcierto(idConcierto);
    bool ok = pos !=-1;
    if(numConciertos==1){
        delete conciertos;
    }else if(pos == 1){
        conciertos=conciertos->sigC;
        delete nodo_aux;
    }else{
        for(int i = 1;i<pos-1;i++){
            nodo_aux=nodo_aux->sigC;
        }
        Concierto* nodo_borr = nodo_aux->sigC;
        nodo_aux->sigC= nodo_borr->sigC;
        delete nodo_borr;
    }
    if(ok){
        numConciertos--;
    }
    return ok;

}


int Festival ::existeConcierto(int idConcierto){
	int pos = -1;
	Concierto* nodo_aux = conciertos;

	for(int i = 0;i<numConciertos;i++){
        if(idConcierto == nodo_aux->codId){
            pos= i+1;
            break;
        }
        if(i+i==numConciertos){
            break;
        }
        nodo_aux= nodo_aux->sigC;
	}
	return pos;


}

int Festival::existeConcierto(cadena nomGrupo){
    int pos = -1;
	Concierto* nodo_aux = conciertos;
		for(int i = 0;i<numConciertos;i++){
        if(strcmp(nomGrupo,nodo_aux->nombreGrupo)==0){
            pos= i+1;
            break;
        }
        if(i+i==numConciertos){
            break;
        }
        nodo_aux= nodo_aux->sigC;
	}
	return pos;
}

void Festival::mostrarInfoConcierto(int posicion){
    Concierto *aux_c= conciertos;
    int pos=posicion;
    for(int i=1; i<pos;i++){
     aux_c = aux_c->sigC;
    }
    if (aux_c != NULL) {
        cout <<setw(13)<<left<< aux_c->codId;
        cout<< setw(25)<<left<<aux_c->nombreGrupo;
        cout <<setw(15)<<left<< aux_c->fechaCelebracion;
        cout<< setw(8)<<left<<aux_c->numMaxEntradas;
        cout<<setw(21)<<left<<aux_c->numMaxEntradas-aux_c->numEntradasVendidas<<endl;

    }

}

int Festival::getCodIdConcierto(int posicion){
   int id=-1;
   Concierto* nodo_aux = conciertos;
   for(int i=1;i<posicion;i++){
    nodo_aux = nodo_aux->sigC;
   }
   id = nodo_aux->codId;
return id;
}


int Festival::comprarEntrada(int idConcierto, cadena dni){
	int pos = existeConcierto(idConcierto);
	bool existe;
	Entrada e, e2;
	if (pos != -1 ) {
		Concierto* nodo_aux = conciertos;
		for (int i = 1; i < pos; i++) {
			nodo_aux = nodo_aux->sigC;
		}
		if (nodo_aux->numMaxEntradas - nodo_aux->numEntradasVendidas > 0) {
			strcpy(e.dniComprador, dni);
			do {
				e.codIdEntrada = 10000 + rand() % 40001;
				existe = nodo_aux->entradasVendidas.pertenece(e);
			} while (existe);

			for (int i = 1; i <= nodo_aux->entradasVendidas.longitud(); i++) {
				e2 = nodo_aux->entradasVendidas.observar(i);
				if (strcmp(dni, e2.dniComprador) == 0) {
					existe = true;
					break;
				}
			}
			if (!existe) {

				nodo_aux->entradasVendidas.insertar(nodo_aux->numEntradasVendidas+1, e);
				nodo_aux->numEntradasVendidas++;
			}
			else {
				return -3;//Ya ha una entrada con el mismo dni;
			}
		}
		else {
			return -2;//no hay suficientes entradas
		}
	}
	else {
		return -1;//no existe concierto
	}
	return e.codIdEntrada;
}

bool Festival::registrarReserva(int idConcierto, SolicitudCompra s){
int pos = existeConcierto(idConcierto);
	Entrada e;
	cola c;
	bool existe=false;
	Concierto* nodo_aux=conciertos;
	SolicitudCompra s_aux;
	if (pos != -1) {
		for (int i = 1; i < pos; i++) {
			nodo_aux = nodo_aux->sigC;
		}
		if (nodo_aux->numMaxEntradas == nodo_aux->numEntradasVendidas) {
			for (int i = 1; i <= nodo_aux->entradasVendidas.longitud();i++) {
				e = nodo_aux->entradasVendidas.observar(i);
				if (strcmp(s.dni, e.dniComprador) == 0) {
					return false;
				}
			}
			for (int i = 0; i<nodo_aux->colaEspera.longitud(); i++) {
				s_aux=nodo_aux->colaEspera.primero();

				if (strcmp(s_aux.dni, s.dni)==0){
					existe=true;
				}
				nodo_aux->colaEspera.encolar(s_aux);
				nodo_aux->colaEspera.desencolar();
			}
			if(!existe){
				nodo_aux->colaEspera.encolar(s);
			}
			else {
				return false;
			}

		}
		else {
			return false;
		}

	}
	else {
		return false;
	}
	return true;

}


bool Festival::eliminarReserva(int idConcierto, cadena dni){
    int pos = existeConcierto(idConcierto);
	bool existe = false;
	int lon;
	SolicitudCompra s_aux;
	if (pos != -1) {
		Concierto* nodo_aux = conciertos;
		for (int i = 1; i < pos; i++) {
			nodo_aux = nodo_aux->sigC;
		}
		lon = nodo_aux->colaEspera.longitud();
		for (int i = 0; i < lon; i++) {
			s_aux = nodo_aux->colaEspera.primero();

			if (strcmp(s_aux.dni, dni) == 0) {
				existe = true;
				nodo_aux->colaEspera.desencolar();
			}
			else {
				nodo_aux->colaEspera.encolar(s_aux);
				nodo_aux->colaEspera.desencolar();
			}
		}
	}
	else {
		return false;
	}
	return existe;
}

bool Festival::eliminarEntrada(int idConcierto, int idEntrada) {
	int pos = existeConcierto(idConcierto);
	bool existe = false;
	Entrada e;
	SolicitudCompra s;
	if (pos != -1) {
		Concierto* nodo_aux = conciertos;
		for (int i = 1; i < pos; i++) {
			nodo_aux = nodo_aux->sigC;
		}
		pos = 1;
		while (pos <= nodo_aux->numEntradasVendidas && !existe) {
			e=nodo_aux->entradasVendidas.observar(pos);
			if (e.codIdEntrada == idEntrada) {
				existe = true;
			}
			else {
				pos++;
			}
		}
		if (existe) {
			if (nodo_aux->colaEspera.longitud() > 0) {
				s = nodo_aux->colaEspera.primero();
				strcpy(e.dniComprador, s.dni);
				nodo_aux->entradasVendidas.modificar(pos, e);
				nodo_aux->colaEspera.desencolar();

			}
			else {
				nodo_aux->entradasVendidas.eliminar(pos);
				nodo_aux->numEntradasVendidas--;
			}
		}
		else {
			return false;
		}

	}
	else {
		return false;
	}
	return true;
}




void Festival:: mostrarEntradasVendidas(int posicion){

        Entrada e;
        Concierto *aux_c= conciertos;

        for (int i = 1; i < posicion; ++i) {
            aux_c = aux_c->sigC;
        }
         cout << setw(20)<< left << "COD ID ENTRADA" << setw(15) << "DNI"<<endl;
         cout << "*************************************" << endl;

        for (int i = 1; i <= aux_c->numEntradasVendidas; i++) {
            e=aux_c->entradasVendidas.observar(i);
            cout << setw(20) << left << e.codIdEntrada
                 << setw(15) << left << e.dniComprador<< endl;
        }
    }


void Festival::mostrarSolicitudesDeCompra(int posicion){
    Concierto *aux_c = conciertos;
    for (int i = 1; i < posicion; i++) {
        aux_c = aux_c->sigC;
    }
    SolicitudCompra sol_c;

    int longitud = aux_c->colaEspera.longitud();
    cout << "Nombre                        Dni            Mail                          Número Teléfono\n";
	cout << "**************************************************************************************************\n";

		for (int i = 0; i < longitud; i++) {
			sol_c = aux_c->colaEspera.primero();
			cout << setw(30) << left << sol_c.nombre;
			cout << setw(15) << left << sol_c.dni;
			cout << setw(30) << left << sol_c.mail;
			cout << sol_c.numTlfn << endl;
			aux_c->colaEspera.encolar(sol_c);
			aux_c->colaEspera.desencolar();

		}
}

Festival::~Festival(){
    Concierto *Nodo_Borr=conciertos,*Nodo_Sig;
    while (Nodo_Borr!=NULL) {
        Nodo_Sig=Nodo_Borr->sigC;
        delete Nodo_Borr;
        Nodo_Borr=Nodo_Sig;
    }
}




void Festival:: esteticasolicitudes(){
    cout<< "DNI        NOMBRE                            TELEFONO      EMAIL             "<<endl;
    cout<< "*****************************************************************************"<<endl;
}

void Festival:: esteticaconcierto(){
    cout<< "ID           NOMBRE_GRUPO            FECHA      AFORO   ENTRADAS_DISPONIBLES "<<endl;
    cout<< "*****************************************************************************"<<endl;
}
