#include <iostream>
#include "Torneo.h"

using namespace std;
const int max_torneo=50;

void MENU(){
cout<< "Elija un MENU: "<<endl;
cout<< "Menu Club de Golf"<<endl;
cout<< "Menu Torneo"<<endl;
}
void MenuClubGolf(){
cout<<"CLUB DE GOLF"<<endl;
cout<<"-----------------------------------------"<<endl;
cout<<"Torneos: "<<endl;
cout<< "        1.Listado Torneos Abiertos"<<endl;
cout<< "        2.Alta Torneo"<<endl;
cout<< "        3.Elegir Torneo"<<endl;
cout<< "        4.Salir"<<endl;
}

void MenuTorneo(){
cout<< "Torneo: "<<endl;
cout<<"-----------------------------------------"<<endl;
cout<<"Golfistas: "<<endl;
cout<< "        1.Consulta de inscripciones"<<endl;
cout<< "        2.Inscripción al torneo"<<endl;
cout<<"         3.Busqueda de una inscripción"<<endl;
cout<< "        4.Modificar datos de una inscripción"<<endl;
cout<< "        5.Eliminar una inscripcion"<<endl;
cout<< "        6.Mostrar Resultados del Torneo"<<endl;
cout<< "        7.Salir"<<endl;
}

int main(){

    Torneo torneos[max_torneo];
    fstream f;
    int numTorneos=0;
    f.open("Torneos.dat",ios::binary | ios::in | ios::out);
    if(f.fail()){
        cout<< "Error en la apertura del archivo."<<endl;
        f.close();
        f.clear();
        f.open("Torneos.dat", ios::binary| ios::out);
        f.seekp(0,ios::beg);
        f.write((char*)&numTorneos,sizeof(int));
        f.close();
       // f.open("Torneos.dat",ios::binary, ios::in, ios::out);
    }else{
        f.read((char*)&numTorneos,sizeof(int));
        if(numTorneos>0){
                for (int i = 0; i < numTorneos; i++) {
                    cadena nombreFichero;
                    f.read((char*)&nombreFichero, sizeof(cadena)); // Leer nombre del archivo de torneo
                    torneos[i].crearFichero(nombreFichero); // Cargar datos del torneo
                    torneos[i].putNomFichero(nombreFichero); // Guardar el nombre en el objeto Torneo
                }

        }
        f.close();
    }

  Torneo torneo;
   // char nombreFichero[] = "SONY.dat";
    torneo.crearFichero("IBM.dat");


    float hdcp;
    cout << "Introduzca un handicap (-1 para mostrar todos): ";
    cin >> hdcp;

    torneo.mostrar(hdcp);

    return 0;
}


