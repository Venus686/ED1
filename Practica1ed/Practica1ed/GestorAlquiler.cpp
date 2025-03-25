#include "GestorAlquiler.h"
#include "comun.h"


GestorAlquiler::GestorAlquiler(cadena nomPpal)
{
    fichero.open(nomPpal,ios::in | ios::out | ios::binary);
    if(fichero.fail()){
        fichero.close();
        fichero.clear();
        strcpy(nomFichero,nomPpal);
        fichero.open(nomPpal, ios::binary |ios::out);
        fichero.close();
        fichero.open(nomPpal, ios::binary |ios::in |ios::out);
        fichero.close();
        numAlquiler=0;
        Alquileres=new TAlquiler[0];
        tam=0;
    }else{
    fichero.seekg(0,ios::beg);
    fichero.read((char*) &numAlquiler,sizeof(numAlquiler));
    tam=numAlquiler;
    Alquileres = new TAlquiler[tam];
    for(int i=0; i<numAlquiler;i++){
        fichero.read((char*)&Alquileres[i], sizeof(TAlquiler));
    }
    fichero.clear();
    fichero.close();
    strcpy(nomFichero,nomPpal);
    }

}

GestorAlquiler::~GestorAlquiler()
{
fichero.open(nomFichero,ios::binary | ios::in | ios::out);
    if(!fichero.is_open()){
        cout<<"Error al guardar datos en el fichero\n";
        exit(1);
    }
    fichero.seekp(0,ios::beg);
    fichero.write((char*)&numAlquiler,sizeof(numAlquiler));
    for(int i = 0; i<numAlquiler;i++){
        fichero.write((char*)&Alquileres[i],sizeof(TAlquiler));
    }
    fichero.clear();
    fichero.close();
    delete[] Alquileres;
}


void GestorAlquiler::aumentarArray(){
    tam+=INCREMENTO;
    TAlquiler *nuevoAlq =new TAlquiler[tam];
    for (int i=0; i<numAlquiler;i++){
        nuevoAlq[i]=Alquileres[i];
    }
    delete[] Alquileres;
    Alquileres=nuevoAlq;
   // delete[] nuevoVeh;
}


int GestorAlquiler::getNumAlquiler(){
    return numAlquiler;
}


void GestorAlquiler:: nuevo(TAlquiler A){
     if (numAlquiler==tam){
        aumentarArray();
    }

    Alquileres[numAlquiler]=A;
    numAlquiler++;
}


int GestorAlquiler:: Buscar (cadena Datos,char DM){
    int pos=-1;
    if (DM== 'D'){
        for(int i=0; i<numAlquiler;i++){
            if (strcmp(Datos, Alquileres[i].Dni)==0){
                pos=i;
                break;
            }
        }
    }else{
        for(int i=0; i<numAlquiler;i++){
            if (strcmp(Datos, Alquileres[i].Matricula)==0){
                pos=i;
                break;
            }
        }
    }return pos;
}

TAlquiler GestorAlquiler:: consultar(int posicion){
    TAlquiler alq;
    if (posicion<0 || posicion>=numAlquiler){
        alq.NDiasCir=0;
        alq.KmsCir=0;
        strcpy (alq.Dni, "*");
        strcpy (alq.Matricula, "*");
        return alq;
    }return Alquileres[posicion];
}


bool GestorAlquiler:: modificar(TAlquiler A, int posicion){
    bool modificado=false;
     if (posicion>0 || posicion<=numAlquiler){
        Alquileres[posicion]=A;
       modificado =true;
    }return modificado;
}

bool GestorAlquiler:: eliminarPorPosicion (int posicion){
    bool eliminar=false;
    if (posicion>0 || posicion<=numAlquiler){
        for (int i= posicion;i<=numAlquiler;i++){
            Alquileres[i]=Alquileres[i+1];
        }
            numAlquiler--;
            eliminar =true;
    }return eliminar;
}


