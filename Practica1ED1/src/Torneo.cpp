#include "Torneo.h"
#include <cstring>
#include "Clasificacion.h"
Torneo::Torneo(){
    strcpy(nomFichero," ");
    strcpy(nomTorneo, " ");
    numGolfistas=0;
}

 Torneo::~Torneo(){
    fichero.close();
}

int Torneo::getNumGolfistas(){
    return numGolfistas;
}

void Torneo::putNumGolfistas(int n){
    numGolfistas=n;
}
void Torneo::getNomTorneo(cadena nombre){
     strcpy(nombre,nomTorneo);
}

void Torneo::getNomFichero(cadena nombre){
    strcpy(nombre,nomFichero);
}

void Torneo::putNomTorneo(cadena nombre){
    strcpy(nomTorneo,nombre);
}

void Torneo::putNomFichero(cadena nombre){
    strcpy(nomFichero, nombre);
}

void Torneo::crearFichero(char nombreFichero[]){
    putNomFichero(nombreFichero);
    fichero.open(nomFichero, ios::binary | ios::in | ios::out);
    if (fichero.fail()) {
        cout<< "Error, en la apertura del fichero";
        fichero.close();
        fichero.clear();
        fichero.open(nomFichero, ios::binary | ios::out);
         numGolfistas = 0;
        fichero.seekp(0,ios::beg);
        fichero.write((char*)&numGolfistas, sizeof(int));
        fichero.close();
        fichero.clear();
        fichero.open(nomFichero, ios::binary| ios::in | ios::out);
    }else{
        fichero.seekg(0,ios::beg);
        fichero.read((char*)&numGolfistas, sizeof(int));
        //fichero.clear();
    }
}

void Torneo::mostrar(float hdcp) {

    cout<< "Golfistas: "<<numGolfistas<<endl;
    fichero.seekg(sizeof(int), ios::beg);
    Golfista g;
    cout << "Golfistas registrados:" << endl;
    fichero.seekg(sizeof(int), ios::beg);
    for (int i = 0; i < numGolfistas; i++) {
        fichero.read((char*)&g, sizeof(Golfista));
        if (hdcp == -1 || hdcp==g.handicap){
            cout << "Licencia: " << g.licencia << endl;
            cout << "Handicap: " << g.handicap << endl;
            cout << "Nombre: " << g.nombre << endl;
            cout << "Apellidos: " << g.apellidos << endl;
            cout << "Golpes: " << g.golpes << endl;
            cout << "Resultado: " << g.resultado << endl;
            cout << "---------------------------" << endl;
        }
    }
}

Golfista Torneo::consultar(int posicion){
    Golfista g;
        if (posicion > 0 && posicion <= numGolfistas) {
            fichero.seekg((posicion - 1) * sizeof(Golfista) + sizeof(int), ios::beg);
            fichero.read((char*)&g, sizeof(Golfista));
        }
        return g;
}

int Torneo::buscar(cadena licencia){
    int pos=-1;
    Golfista golf;
    fichero.seekg(sizeof(int),ios::beg);
    while(!fichero.eof()){
        if(strcmp(golf.licencia,licencia)==0){
            pos=(fichero.tellg()-sizeof(int))/sizeof(Golfista);
            break;
        }
        fichero.read((char*)&golf, sizeof(Golfista));
    }
    if(pos==-1){
        fichero.clear();
    }
    return pos;
}

void Torneo::insertar(Golfista g){
    fichero.seekg(0,ios::beg);
    numGolfistas++;
    fichero.write((char*)&numGolfistas,sizeof(int));

    Golfista golf;
    int pos;
    if(numGolfistas>0){
        while(!fichero.eof()){
            if(g.handicap>golf.handicap){
                pos=(fichero.tellg()-sizeof(int))/sizeof(Golfista);
                break;
            }
            fichero.read((char*)&golf, sizeof(Golfista));
        }
    }

         for(int i=numGolfistas; i>=pos;i++){
            fichero.seekg((i-1)*sizeof(Golfista)+sizeof(int),ios::beg);
            fichero.read((char*)&golf, sizeof(Golfista));
            fichero.seekp(i*sizeof(Golfista)+sizeof(int),ios::beg);
            fichero.write((char*)&golf,sizeof(Golfista));
        }
}

void Torneo::modificar(Golfista c, int posicion){
    Golfista golf;
    int pos= buscar(c.licencia);
    if(pos!=-1&& posicion>0 &&posicion<numGolfistas){
        fichero.seekp((posicion-1)*sizeof(Golfista)+sizeof(int),ios::beg);
        strcpy(golf.licencia,c.licencia);
        strcpy(golf.nombre,c.nombre);
        strcpy(golf.apellidos,c.apellidos);
        golf.golpes=c.golpes;
        golf.resultado=c.resultado;
        fichero.write((char*)&golf, sizeof(Golfista));
    }else{
        cout<<"Ese golfista no ha sido inscrito dodavía";
    }
}

void Torneo::eliminar(int posicion){
    Golfista golf;
    if (posicion>0 && posicion<numGolfistas){
        for(int i=posicion-1; i<=numGolfistas;i++){
            fichero.seekg((i+1)*sizeof(Golfista)+sizeof(int),ios::beg);
            fichero.read((char*)&golf, sizeof(Golfista));
            fichero.seekp(i*sizeof(Golfista)+sizeof(int),ios::beg);
            fichero.write((char*)&golf,sizeof(Golfista));
        }
        numGolfistas--;
        fichero.seekp(0,ios::beg);
        fichero.write((char*)&numGolfistas,sizeof(int));
    }else{
        cout<< "Error, la posición que has introducido no es la correcta. "<<endl;
    }
}

void Torneo::Clasificar(){
    Clasificacion clasificacion;
        fichero.seekg(sizeof(int), ios::beg);
        Golfista g;
        for (int i = 0; i < numGolfistas; i++) {
            fichero.read((char*)&g, sizeof(Golfista));
            g.resultado = rand() % 100; // Simula el resultado del torneo
            clasificacion.anadirjugador({ i, g.resultado });
        }

        clasificacion.ordenar();

        cout << "Clasificación final:" << endl;
        for (int i = 0; i < clasificacion.numjugadores(); i++) {
            Jugador j = clasificacion.consultar(i);
            fichero.seekg(j.indice * sizeof(Golfista) + sizeof(int), ios::beg);
            fichero.read((char*)&g, sizeof(Golfista));
            cout << "Posición " << i + 1 << ": " << g.nombre << " " << g.apellidos << " - Resultado: " << j.resultado << endl;
        }
}

