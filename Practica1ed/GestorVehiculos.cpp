#include "GestorVehiculos.h"
#include "comun.h"
#include <iomanip>

void  esteticaVehiculos(){
cout<<"MODELO           MATRICULA     PROVINCIA    KILOMETROS    PRECIO POR KM  ESTADO"<<endl;
cout<<"*********************************************************************************************"<<endl;
}

GestorVehiculos::GestorVehiculos(cadena NomPpal){
    ficheroPrincipal.open(NomPpal, ios::binary | ios::in | ios:: out);
    if (ficheroPrincipal.fail()){
        ficheroPrincipal.close();
        ficheroPrincipal.clear();
        ficheroPrincipal.open(NomPpal, ios::binary |ios::out);
        ficheroPrincipal.close();
        ficheroPrincipal.open(NomPpal, ios::binary |ios::in |ios::out);
        ficheroPrincipal.close();
        numVehiculos=0;
        strcpy(nomFichero,NomPpal);
        tam=INCREMENTO;
        vehiculos=new Vehiculo [tam];

    }else{
        numVehiculos=0;
        tam=INCREMENTO;
        strcpy(nomFichero,NomPpal);
        vehiculos=new Vehiculo[tam];

        ficheroPrincipal.read((char*)&vehiculos[numVehiculos],sizeof(Vehiculo));
        while (!ficheroPrincipal.eof()){
            numVehiculos++;
            if(numVehiculos==tam){
                aumentarArray();
            }
            ficheroPrincipal.read((char*)&vehiculos[numVehiculos],sizeof(Vehiculo));

        }
        ficheroPrincipal.close();

    }
}


GestorVehiculos::~GestorVehiculos(){
    ficheroPrincipal.open(nomFichero,  ios::binary | ios::out);
    for (int i=0; i<numVehiculos;i++){
        ficheroPrincipal.write((char*)&vehiculos[i], sizeof(Vehiculo));
   }
    delete[] vehiculos;
   ficheroPrincipal.close();
   ficheroPrincipal.clear();

}

int GestorVehiculos::getNumVehiculos(){
    return numVehiculos;
}

void GestorVehiculos::aumentarArray(){
    tam+=INCREMENTO;
    Vehiculo *nuevoVeh =new Vehiculo [tam];
    for (int i=0; i<numVehiculos;i++){
        nuevoVeh[i]=vehiculos[i];
    }
    delete[] vehiculos;
    vehiculos=nuevoVeh;
   // delete[] nuevoVeh;
}

void GestorVehiculos::mostrar(cadena provincia){
    if(strcmp(provincia,"*")!=0){
        esteticaVehiculos();
        for (int i=0; i<numVehiculos;i++){

            if (strcmp(vehiculos[i].provincia, provincia)==0){
                cout<<setw(17)<<left<<vehiculos[i].modelo;
                cout<<setw(14)<<left<<vehiculos[i].matricula;
                cout<<setw(13)<<left<<vehiculos[i].provincia;
                cout<<setw(14)<<left<<vehiculos[i].kilometros;
                cout<<setw(15)<<left<<vehiculos[i].precio_km;
                cout<<setw(20)<<left<<vehiculos[i].estado<<endl;
            }
        }
    }else{
        esteticaVehiculos();
        for (int i=0; i<numVehiculos;i++){
                cout<<setw(17)<<left<<vehiculos[i].modelo;
                cout<<setw(14)<<left<<vehiculos[i].matricula;
                cout<<setw(13)<<left<<vehiculos[i].provincia;
                cout<<setw(14)<<left<<vehiculos[i].kilometros;
                cout<<setw(15)<<left<<vehiculos[i].precio_km;
                cout<<setw(20)<<left<<vehiculos[i].estado<<endl;
        }
    }

}


Vehiculo GestorVehiculos:: consultar (int posicion){
    if (posicion<0 ||posicion>numVehiculos){
        Vehiculo veh;
       // aumentarArray();
            esteticaVehiculos();
            strcpy(veh.modelo, " ");
            strcpy(veh.matricula,"0");
            strcpy (veh.provincia, " ");
            veh.kilometros=0;
            veh.precio_km=0;
            strcpy(veh.estado, " ");
        return veh;

    }else{
        return vehiculos[posicion];
    }

}

int GestorVehiculos::consultar(cadena matricula){
    int con_pos=-1;
    for (int i=0; i<numVehiculos;i++){
        if (strcmp(vehiculos[i].matricula,matricula)==0){
            con_pos=i;
            break;
        }
    }

    return con_pos;
}


void GestorVehiculos::insertar(Vehiculo v){
    int pos=-1;
    if (numVehiculos==tam){
        aumentarArray();
    }
    if (numVehiculos==0){
        vehiculos[0]=v;
        numVehiculos++;
        return;
    }

    for (int i=0; i<numVehiculos;i++){
                if (strcmp(v.provincia,vehiculos[i].provincia)==0){
            pos =i;

            break;
        }
    }

    if (pos !=-1){
         for (int j=numVehiculos; j>=pos;j--){
            vehiculos[j]=vehiculos[j-1];

         }
    }else{
        pos=numVehiculos;
    }


    vehiculos[pos]=v;
    numVehiculos++;

}


void GestorVehiculos::modificar (Vehiculo v,int posicion){
    if (posicion>0 || posicion<= numVehiculos){
        vehiculos[posicion]=v;

    }else{
        cout<< "La posicion es incorrecta. "<<endl;
    }

}
void GestorVehiculos::eliminarPorPosicion(int posicion){
    if (posicion>0 || posicion<= numVehiculos){
        for (int i=posicion-1;i<numVehiculos;i++){
            vehiculos[i]=vehiculos[i+1];
        }
        numVehiculos--;

    }else{
        cout<< "La posicion es incorrecta. "<<endl;
    }
}

int GestorVehiculos::OcultarVehiculos(cadena provincia){
    ficheroSecundario.open(provincia, ios::trunc | ios::binary | ios::in | ios:: out);
    if (ficheroSecundario.fail()){
     /*   ficheroSecundario.close();
        ficheroSecundario.clear();
        ficheroSecundario.open(provincia, ios::binary |ios::out);
        ficheroSecundario.close();
        ficheroSecundario.open(provincia, ios::binary |ios::in |ios::out);
        ficheroSecundario.close();
        numVehiculos=0;
        strcpy(nomFichero,provincia);
        tam=INCREMENTO;
        vehiculos=new Vehiculo [tam];
        Vehiculo *vehiculos2;
        vehiculos2= new Vehiculo[tam];
*/
    return -1;
    }else{
        numVehiculos=0;
        tam=INCREMENTO;
        strcpy(nomFichero,provincia);
        vehiculos=new Vehiculo[tam];
        Vehiculo *vehiculos2;
        vehiculos2= new Vehiculo[tam];
        ficheroSecundario.read((char*)&vehiculos2[numVehiculos],sizeof(Vehiculo));
        while (!ficheroSecundario.eof()){
            numVehiculos++;
            if(numVehiculos==tam){
                aumentarArray();
            }
            ficheroSecundario.read((char*)&vehiculos[numVehiculos],sizeof(Vehiculo));

        }
    }

        Vehiculo *vehiculos2;
       vehiculos2= new Vehiculo[tam];
        ficheroPrincipal.seekg(0,ios::beg);
        for (int i=0; i<numVehiculos;i++){
            ficheroPrincipal.read((char*)&vehiculos, sizeof(Vehiculo));
            if ((strcmp(vehiculos[i].provincia,provincia)==0)&& (strcmp (vehiculos[i].estado, "Ocupado")!=0)){
                vehiculos2[i]=vehiculos[i];
                ficheroSecundario.write((char*)&vehiculos2[i], sizeof(Vehiculo));
            }
    }
        delete[] vehiculos2;
        ficheroSecundario.close();
        ficheroSecundario.clear();

        ficheroSecundario.open(provincia, ios::trunc | ios::binary | ios::in | ios:: out);
        if (!ficheroSecundario.fail()){
            ficheroSecundario.read((char*)&vehiculos[numVehiculos],sizeof(int));

        }

        ficheroSecundario.close();
        ficheroSecundario.clear();
}

int GestorVehiculos::RecuperarVehiculos(cadena provincia){
    ficheroSecundario.open(provincia, ios::trunc | ios::binary | ios::in | ios:: out);
    if (ficheroSecundario.fail()){
       /* ficheroSecundario.close();
        ficheroSecundario.clear();
        ficheroSecundario.open(provincia, ios::binary |ios::out);
        ficheroSecundario.close();
        ficheroSecundario.open(provincia, ios::binary |ios::in |ios::out);
        ficheroSecundario.close();
        numVehiculos=0;
        strcpy(nomFichero,provincia);
        tam=INCREMENTO;
        vehiculos=new Vehiculo [tam];
        Vehiculo *vehiculos2;
        vehiculos2= new Vehiculo[tam];
*/
    return -1;
    }else{
        numVehiculos=0;
        tam=INCREMENTO;
        strcpy(nomFichero,provincia);
        vehiculos=new Vehiculo[tam];

        ficheroSecundario.read((char*)&vehiculos[numVehiculos],sizeof(Vehiculo));
        while (!ficheroSecundario.eof()){
            numVehiculos++;
            if(numVehiculos==tam){
                aumentarArray();
            }
            ficheroSecundario.read((char*)&vehiculos[numVehiculos],sizeof(Vehiculo));

        }
        esteticaVehiculos();
        for (int i=0; i<numVehiculos;i++){
                ficheroSecundario.read((char*)&vehiculos, sizeof(Vehiculo));
                cout<<setw(17)<<left<<vehiculos[i].modelo;
                cout<<setw(14)<<left<<vehiculos[i].matricula;
                cout<<setw(13)<<left<<vehiculos[i].provincia;
                cout<<setw(14)<<left<<vehiculos[i].kilometros;
                cout<<setw(15)<<left<<vehiculos[i].precio_km;
                cout<<setw(20)<<left<<vehiculos[i].estado<<endl;
        }
    }
        ficheroSecundario.close();
}


