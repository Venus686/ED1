#include "comun.h"
#include "GestorClientes.h"
#include <iomanip>

void esteticaClientes(){
cout<<"DNI        NOMBRE                             PROVINCIA     ACUMU KM       ACUMU $   VEHICULO"<<endl;
cout<<"*********************************************************************************************"<<endl;
}

GestorClientes::GestorClientes(cadena NomFile){
    fichero.open("ClientesSin.dat", ios::in | ios::out | ios::binary);
    if (fichero.fail()){
        fichero.close();
        fichero.clear();
        fichero.open("ClientesSin.dat", ios::out | ios::binary);
        numclientes=0;
        fichero.seekp(0,ios::beg);
        fichero.write((char*)&numclientes, sizeof(int));
        fichero.close();
        fichero.open("ClientesSin.dat", ios::in | ios::out | ios::binary);

    }else{
        fichero.seekg(0,ios::beg);
        fichero.read((char*)&numclientes, sizeof(int));
    }
}

GestorClientes::~GestorClientes(){
    fichero.close();
}

int GestorClientes::getNumClientes(){
    return numclientes;
}

bool GestorClientes::mostrar (cadena Dni){
    bool mostrado=false;
    cadena vehiculo;
    TCliente cliente;
        if(strcmp(Dni,"*")==0){
            fichero.seekg(sizeof(int), ios::beg);
            esteticaClientes();
            for(int i=0; i<numclientes;i++){
             fichero.read((char*)&cliente, sizeof(TCliente));
                cout<<setw(11)<<left<<cliente.Dni;
                cout<<setw(35)<<left<<cliente.Nombre;
                cout<<setw(14)<<left<<cliente.Provincia;
                cout<<setw(15)<<left<<cliente.AcumuKm;
                cout<<setw(10)<<left<<cliente.AcumuEuros;
                if(cliente.VEnAlquiler){
                    strcpy(vehiculo,"Si");
                }else{
                    strcpy(vehiculo,"No");
                }
                cout<<setw(8)<<left<<vehiculo<<endl;
                mostrado=true;
            }

            fichero.clear();
        }else{
            fichero.seekg(sizeof(int), ios::beg);
            esteticaClientes();
            for(int i=0; i<numclientes;i++){
                fichero.read((char*)&cliente, sizeof(TCliente));
                if(strcmp(cliente.Dni,Dni)==0){
                cout<<setw(11)<<left<<cliente.Dni;
                cout<<setw(35)<<left<<cliente.Nombre;
                cout<<setw(14)<<left<<cliente.Provincia;
                cout<<setw(15)<<left<<cliente.AcumuKm;
                cout<<setw(10)<<left<<cliente.AcumuEuros;
                if(cliente.VEnAlquiler){
                    strcpy(vehiculo,"Si");
                }else{
                    strcpy(vehiculo,"No");
                }
                cout<<setw(8)<<left<<vehiculo<<endl;
                mostrado=true;
                break;
                }
            }
            fichero.clear();

        }
        return mostrado;
    }


int GestorClientes::buscar(cadena Dni){
    TCliente cliente;
    int posicion=-1;
    fichero.seekg(sizeof(int), ios:: beg);
    while (!fichero.eof()){
        if(strcmp (cliente.Dni, Dni)==0){
            posicion=(fichero.tellg()-sizeof(int))/sizeof(TCliente);
            break;
        }
        fichero.read((char*)&cliente, sizeof(TCliente));
    }
    if (posicion !=-1){
        fichero.clear();
    }
    /*for(int i=0;i<numclientes;i++){
        if(strcmp (cliente.Dni, Dni)==0){
            posicion=i;
            break;
        }
    }*/

    return posicion;
}


TCliente GestorClientes::consultar(int Posicion){
    TCliente cliente;

    if (Posicion ==-1){
        strcpy(cliente.Dni, "*");
        strcpy(cliente.Nombre, "*");
        strcpy(cliente.Provincia, "*");
        cliente.AcumuKm = 0.00;
        cliente.AcumuEuros = 0.00;
        cliente.VEnAlquiler = false;
    }else {
        fichero.seekg((Posicion-1) * sizeof (TCliente)+ sizeof(int), ios::beg);
        fichero.read((char*)&cliente, sizeof (TCliente));
    }
    return cliente;

}



void GestorClientes::insertar (TCliente C)
{
        fichero.clear();
        fichero.seekg(0,ios::beg);
        numclientes++;
        TCliente cliente;
        int posIns = -1;
        fichero.write((char*)&numclientes,sizeof(numclientes));
        if(numclientes==1)
        {
            fichero.write((char*)&C,sizeof(TCliente));
            return;
        }
        while(fichero.read((char*)&cliente,sizeof(TCliente)))
        {
            if(strcmp(cliente.Dni,C.Dni)>0)
            {
                posIns = fichero.tellg()-sizeof(TCliente);
                break;
            }
        }
        fichero.clear();
        if(posIns != -1)
        {
            streampos currentPos = fichero.tellp();
            fichero.seekp(0,ios::end);
            streampos endPos = fichero.tellp();

            for(streampos i = endPos;i>posIns;i-= sizeof(TCliente))
            {
                fichero.seekg(i-sizeof(TCliente));
                fichero.read((char*)&cliente,sizeof(TCliente));
                fichero.seekp(i);
                fichero.write((char*)&cliente,sizeof(TCliente));
            }
            fichero.seekp(posIns);
            fichero.write((char*)&C, sizeof(TCliente));
        }
        else
        {
            fichero.seekp(0,ios::end);
            fichero.write((char*)&C,sizeof(TCliente));
        }
}




bool GestorClientes:: modificar (TCliente C, int Posicion){
    bool modificar=false;

    if (Posicion>=0 || Posicion<numclientes){
        fichero.seekp((Posicion-1)*sizeof(TCliente)+sizeof(int), ios::beg);
        fichero.write((char*)&C, sizeof(TCliente));

        modificar=true;

    }
    return modificar;
}


bool GestorClientes::eliminar (int Posicion){
    bool eliminado= false;
    TCliente cliente;
    if (Posicion>=0 || Posicion<numclientes){
        if (numclientes==0){
            cout<< "No hay clientes para eliminar. "<<endl;
        }
        for (int i=Posicion-1;i<numclientes;i++){
            fichero.seekg((i + 1) * sizeof(TCliente) + sizeof(numclientes), ios::beg);
            fichero.read((char*)&cliente, sizeof(TCliente));
            fichero.seekp(i*sizeof(TCliente)+sizeof(numclientes), ios:: beg);
            fichero.write((char*)&cliente, sizeof(TCliente));
        }
        fichero.clear();
        eliminado =true;
        numclientes --;
        fichero.seekp(0,ios::beg);
        fichero.write((char*)&numclientes, sizeof(int));


        }else{
            cout<< "Introduce de nuevo una posicion: ";
            cin>> Posicion;
        }
        return eliminado;
    }


