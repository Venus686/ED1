#include "comun.h"

cola::cola(){
    elementos=new SolicitudCompra[INCREMENTO];
     if (elementos!=NULL) {
         ne=fin=inicio=0;
         Tama=INCREMENTO;
     }else {
         ne=fin=inicio=-1;
         Tama=-1;
    }
}

cola::~cola(){
    if (elementos!=NULL)
        delete [] elementos;
     elementos=NULL;
     ne=fin=inicio=-1;
     Tama=0;
}

SolicitudCompra cola::primero(){
    return elementos[inicio];

}

bool cola::esvacia(){
    return (ne==0);
}

int cola::longitud(){
    return ne;
}

void cola::encolar(SolicitudCompra e){
     if (ne==Tama) {
        SolicitudCompra *NuevaZona=new SolicitudCompra[Tama+INCREMENTO];
        if (NuevaZona!=NULL) {
            for (int i=0;i<ne; i++) {
                NuevaZona[i]=elementos[inicio];
                inicio++;
                if (inicio==Tama) // inicio=(inicio+1)%Tama
                    inicio=0;
            }
             inicio=0;
             fin=ne;
             Tama+=INCREMENTO;
             delete [] elementos;
             elementos=NuevaZona;
        }
     }
     if (ne<Tama) {
         elementos[fin]=e;
         fin=(fin+1)%Tama;
         ne++;
     }
}

void cola::desencolar(){
     inicio++; // inicio=(inicio+1)%Tama;
     if (inicio==Tama)
        inicio=0;
     ne--;

        if (Tama-ne>=INCREMENTO && Tama>INCREMENTO) {
            SolicitudCompra *NuevaZona=new SolicitudCompra[Tama-INCREMENTO];
            if (NuevaZona!=NULL) {
                for (int i=0;i<ne; i++) {
                    NuevaZona[i]=elementos[inicio++];
                     if (inicio==Tama)
                        inicio=0;
                }
                 Tama-=INCREMENTO;
                 inicio=0;
                 fin=Tama;
                 delete [] elementos;
                 elementos=NuevaZona;
            }
        }
}
