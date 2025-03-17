#include "Torneo.h"
#include <cstring>

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
    fichero.open(nombreFichero, ios::in | ios::out | ios::binary);
    if(fichero.fail()){
        fichero.close();
        fichero.clear();
        fichero.open(nombreFichero, ios::out| ios::binary);
        numGolfistas=0;
        fichero.seekp(0,ios::beg);
        fichero.write((char*)&numGolfistas, sizeof(int));
        fichero.close();
        fichero.open(nombreFichero, ios::in |ios::out |ios::binary);
        if(fichero.fail()){
            cout<<"Error al abrir el fichero. "<<endl;
            return;
        }
    }else{
        fichero.seekg(0,ios::beg);
        fichero.read((char*)&numGolfistas,sizeof(int));
    }
}

void Torneo::mostrar(float hdcp){
    Golfista golf;
    fichero.seekg(0, ios::beg);
    fichero.read((char*)&numGolfistas, sizeof(int));
    if (numGolfistas <= 0) {
        cout << "No hay golfistas registrados en el fichero." << endl;
        return;
    }

    fichero.seekg(sizeof(int), ios::beg);
    bool mostrado=false;
    if (hdcp !=-1){
        int i=0;
        while(fichero.read((char*)&golf,sizeof(Golfista))){
            if(hdcp==golf.handicap){
                cout<< "Golfista: "<<i+1;
                cout<<"Nombre: "<<golf.nombre<<endl;
                cout<<"Apellidos: "<<golf.apellidos<<endl;
                cout<< "Licencia: "<<golf.licencia<<endl;
                cout<< "Golpes: "<<golf.golpes<<endl;
                cout<< "Resultado: "<<golf.resultado<<endl;
                mostrado=true;
            }i++;
        }
    }else{
        fichero.seekg(sizeof(int), ios::beg);
       for (int i=0; i<numGolfistas;i++){
            if(fichero.read((char*)&golf, sizeof(Golfista))){
                cout<< "Golfista: "<<i+1<<endl;
                cout<<"Nombre: "<<golf.nombre<<endl;
                cout<<"Apellidos: "<<golf.apellidos<<endl;
                cout<< "Licencia: "<<golf.licencia<<endl;
                cout<< "Golpes: "<<golf.golpes<<endl;
                cout<< "Resultado: "<<golf.resultado<<endl;
                mostrado=true;
            }else{
                cout<< "Error al leer el fichero."<<endl;
                break;
            }

       }
    }
    if(!mostrado){
        cout<< "Error en la busqueda del handicap"<<endl;
    }fichero.clear();
}

Golfista Torneo::consultar(int posicion){
    Golfista golf;
    bool encontrado=false;
    Golfista g;
    fichero.seekg(sizeof(int),ios::beg);
    int i=0;
    while(i<numGolfistas && !encontrado){
        fichero.read((char*)&golf, sizeof(Golfista));
        if(i==posicion-1){
            encontrado=true;
            g=golf;
        }
        i++;
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

}
