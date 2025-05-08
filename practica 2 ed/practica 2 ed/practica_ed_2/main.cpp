
#include "comun.h"

void menu(){
    cout<< "\n*********GESTION FESTIVAL*********"<<endl;
    cout<< "  1. Mostrar informacion general"<<endl;
    cout<< "  2. Mostrar informacion conciertos"<<endl;
    cout<< "  3. Anadir concierto"<<endl;
    cout<< "  4. Cargar fichero concierto"<<endl;
    cout<< "  5. Eliminar concierto"<<endl;
    cout<< "  6. Mostrar entradas concierto"<<endl;
    cout<< "  7. Registrar compra de entrada"<<endl;
    cout<< "  8. Devolucion entrada"<<endl;
    cout<< "  9. Mostrar reservas concierto"<<endl;
    cout<< "  10. Eliminacion reserva"<<endl;
    cout<< "  0. Salir"<<endl;
}

int main(){
    srand(time(NULL));
    int opc;
    cadena banda;
    cadena nomfes,fechaIn, fechaFn;

    strcpy(nomfes, "butterfly");
    strcpy(fechaIn, "2024/09/09");
    strcpy(fechaFn, "2024/09/26");

    Festival fes(nomfes, fechaIn, fechaFn);

    int pos, codID, ID_entrada;
    cadena res, fecha;
    char respuesta;
    bool existe;
    cadena dni, nomfichero;
    int num=0;
    do{
    if(num>0){
        cls;
    }
    num++;
        menu();
        do{
            cout<< "Introduce una opcion: ";
            cin>> opc;
            pause;
            if (opc<0 || opc>10){
            cout<< "Error"<<endl;
            }
        }while(opc<0 || opc>10);

            switch(opc){
                case 1:
                    fes.getNombre(nomfes);
                    fes.getFechaInicio(fechaIn);
                    fes.getFechaFin(fechaFn);

                    cout<< "El nombre del festival es: "<< nomfes<<endl;
                    cout<< "Fecha de inicio: "<< fechaIn<<endl;
                    cout<< "Fecha de clausura: "<<fechaFn<<endl;
                    cout<< "Numero de conciertos:"<<fes.getNumConciertos()<<endl;
                    pause;
                    break;

                case 2:
                    cout<< "Introduce el nombre del artista/banda que actua o (*) para mostrarlos todos:  ";
                    cin.ignore();
                    cin.getline(banda, 100);
                    num=fes.getNumConciertos();
                    if (num>0){
                        if (strcmp(banda,"*")==0){
                                fes.esteticaconcierto();
                                for (int i=1; i<=num;i++){
                                    fes.mostrarInfoConcierto(i);
                                }
                            }else{
                                pos=fes.existeConcierto(banda);
                                if (pos ==-1){
                                    cout<< "Error. El nombre o banda del artista, no se encuentra entre los conciertos."<<endl;
                                }else{
                                    fes.esteticaconcierto();
                                    fes.mostrarInfoConcierto(pos);
                                }
                        }
                    }else{
                        cout<< "No se han encontrado conciertos."<<endl;
                    }

                        pause;
                    break;

                case 3:
                    cout<< "Introduce el nombre del artista/banda que actua: ";
                    cin.ignore();
                    cin.getline(banda, 100);
                    pos=fes.existeConcierto(banda);
                    if (pos !=-1){
                        cout<< "Error. El nombre del artista, ya se encuentra en un concierto. "<<endl;
                    }else{
                        do{
                            cout<< "Introduce la fecha del concierto: ";
                            cin.ignore();
                            cin.getline(fecha, 100);
                            if (strcmp(fecha,fechaIn)<0 && strcmp(fecha, fechaFn)>0){
                                cout<< "Error. La fecha debe de encontrarse entre la fecha del festival."<<endl;
                            }

                        }while(strcmp(fecha,fechaIn)<0 && strcmp(fecha, fechaFn)>0);

                        cout<< "Introduce el numero de entradas que se pondran a la venta: ";
                        cin>> num;
                        do{
                            codID=9000+rand()%10000;
                            pos=fes.existeConcierto(codID);
                        }while (pos !=-1);

                        fes.programarConcierto(codID, banda, fecha, num);
                    }
                    pause;

                    break;
                case 4:
                    cin.ignore();
                    cout<< "Introduce el nombre del fichero: ";
                    gets(nomfichero);
                    existe=fes.cargarConciertoDesdeFichero(nomfichero);

                    if (existe){
                        cout<< "El fichero se ha abierto correctamente."<<endl;
                    }else{
                        cout<< "Error al cargar el fichero."<<endl;
                    }
                    pause;
                    break;
                case 5:
                cin.ignore();
                cout<<"Introduzca el nombre del artista/grupo a eliminar: ";
                gets(banda);
                pos = fes.existeConcierto(banda);
                if (pos==-1){
                    cout << "No esta programado ningun concierto de ese artista\n";
                }else
                {
                    cout << setw(35)<< left << "ARTISTA" << setw(15) << "ID CONCIERTO" << setw(15) << "FECHA" << setw(15) << "ENTRADAS DISP\n";
                    cout << "*************************************************************************"<<endl;
                    fes.mostrarInfoConcierto(pos);

                    cout << "Desea eliminar el concierto (s/n)? ";
                    cin>>respuesta;
                    respuesta= toupper(respuesta);

                    if (respuesta=='S')
                    {
                        codID=fes.getCodIdConcierto(pos);
                        cout<<"codid: "<<codID<<endl;
                        bool eliminado = fes.cancelarConcierto(codID);
                        if (eliminado){
                             cout << "Se ha cancelado el concierto"<<endl;
                        }

                        else{
                            cout << "Error en la cancelacion del concierto"<<endl;
                        }

                    }else{
                    cout<< "No se cancelara el concierto."<<endl;
                    }

                }
                        pause;
                    break;

                case 6:
                    cout<< "Introduce la posicion del concierto que quiere consultar: "<<endl;
                    cin>> pos;
                    fes.mostrarEntradasVendidas(pos);
                    pause;
                    break;
                case 7:
                    cout<< "Introduce el nombre del artista o grupo:"<<endl;
                    cin.ignore();
                    cin.getline(banda,100);
                    pos=fes.existeConcierto(banda);
                    if(pos==-1){
                        cout<< "No hay concierto con ese artista";
                    }else{
                        SolicitudCompra s;
                        cout<< "Introduce el dni:";
                        gets(s.dni);
                        codID=fes.getCodIdConcierto(pos);
                        pos=fes.comprarEntrada(codID, s.dni);
                        if (pos ==-2){
                            cout<< "No quedan entradas disponibles en el concierto, le pondremos en cola de espera"<<endl;
                            cout<<"Introduzca su nombre: ";
                            gets(s.nombre);
                            cout<<"Introduzca su mail: ";
                            gets(s.mail);
                            cout<<"Introduzca su número de teléfono: ";
                            cin>>s.numTlfn;
                            existe = fes.registrarReserva(codID, s);
                            if(existe){
                                cout<<"Se ha puesto en la cola de espera "<<endl;

                            }else{
                                cout<<"No hemos podido ingresarle en la lista de espera "<<endl;
                            }
                        }else if(pos==-1){
                            cout<< "Error en el procedimiento de compra."<<endl;
                        }else{
                            cout<<"Su entrada fue comprada correctamente "<<endl;
                        }

                    }

                    pause;
                    break;
                case 8:
                    cout<< "Introduce el id del artista/banda que realiza el concierto.";
                    cin>> codID;
                     pos = fes.existeConcierto(codID);
                    if(pos != -1){
                        cout<< "Introduce el codigo identificador de la entrada.";
                        cin>> ID_entrada;
                        bool existe= fes.eliminarEntrada(codID, ID_entrada);
                    if (existe){
                        cout<< "La entrada ha sido eliminada"<<endl;
                    }else{
                        cout<< "No se ha podido encontrar la entrada."<<endl;
                    }
                    }else{
                        cout<< "No se ha podido encontrar el concierto";
                    }
                    pause;
                    break;

                case 9:
                    cout<< "Introduce la posicion del artista/grupo responsable del concierto para el que quiere realizar la consulta: ";
                    cin>> pos;
                    fes.mostrarSolicitudesDeCompra(pos);
                    pause;
                    break;

                case 10:
                    cout<< "Introduce el id del concierto: ";
                    cin>> codID;
                    cout<< "Introduce el DNI de la persona a eliminar de la cola: ";
                    cin>> dni;
                    existe= fes.eliminarReserva(codID, dni);
                    if (existe){
                        cout<< "Se ha eliminado la reserva."<<endl;
                    }else{
                        cout<< "Error al eliminar la reserva."<<endl;
                    }
                    pause;
                    break;

            }
    }while(opc !=0);
    return 0;
}
