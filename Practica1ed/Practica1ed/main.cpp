#include "comun.h"

using namespace std;

void mostrarMenu(){
    //system("cls");
    cout<< "\n ------MENU PRINCIPAL------"<<endl;
    cout<< "1. Gestion de Clientes"<<endl;
    cout<< "2. Gestion de Vehiculos"<<endl;
    cout<< "3. Gestion de Alquileres"<<endl;
    cout<< "0. Salir"<<endl;
}


void menuClientes(){
    //system("cls");
    cout<< "\n ------MENU GESTION DE CLIENTES------"<<endl;
    cout<< "1. Consulta de clientes"<<endl;
    cout<< "2. Buscar un cliente"<<endl;
    cout<< "3. Nuevo cliente"<<endl;
    cout<< "4. Modificar cliente"<<endl;
    cout<< "5. Eliminar un cliente"<<endl;
    cout<< "0. Salir"<<endl;
}

void menuVehiculos(){
   //system("cls");
    cout<< "\n ------MENU GESTION DE VEHICULOS------"<<endl;
    cout<< "1. Consulta de vehiculos"<<endl;
    cout<< "2. Buscar un vehiculo"<<endl;
    cout<< "3. Nuevo vehiculo"<<endl;
    cout<< "4. Modificar vehiculo"<<endl;
    cout<< "5. Eliminar un vehiculo"<<endl;
    cout<< "6. Ocultar Vehiculos"<<endl;
    cout<< "7. Recuperar Vehiculos"<<endl;
    cout<< "0. Salir"<<endl;

}

void menuGestiondeAlquileres(){
    //system("cls");
    cout<< "\n ------MENU GESTION DE ALQUILERES------"<<endl;
    cout<< "1. Mostrar vehiculos alquilados"<<endl;
    cout<< "2. Alquilar un vehiculo"<<endl;
    cout<< "3. Devolver un vehiculo"<<endl;
    cout<< "0.Salir"<<endl;

}

int main()
{
    int opc;
    cadena Dni;
    GestorClientes clientes ("ClientesSin.dat");
    TCliente cli;
    char respuesta;
    int pos;
    cadena provincia;
    cadena vehiculo;
    GestorVehiculos veh("vehiculos.bin");
    Vehiculo vehi;
    GestorAlquiler alqui("Alquileres.dat");
    TAlquiler alq;
    cadena matricula;
    int posicion_v, posicion_c, posicion_v2;
    float max_km, n_dias, km_recorridos, precio_km, precio_dias, precio_total;
    int dias_circulados;
    int numAlquiler;
    int pos_m;

    bool funciona;

    mostrarMenu();
    do{
        cout<< "Elija una opcion: ";
        cin>>opc;
        if (opc<0 ||opc>3){
            cout<< "La opcion es incorrecta. "<<endl;
        }
    }while(opc<0 || opc>3);


    do{
        switch(opc){
            case 1:
                menuClientes();
                do{
                    do{
                        cout<< "Elija una opcion: ";
                        cin>>opc;
                        if(opc<0 || opc>5){
                            cout<< "Error. Introduce otra opcion.";
                        }

                    }while (opc<0 || opc>5);

                    switch(opc){
                        case 1:
                            cout<< "Introduce el Dni a mostrar:"<<endl;
                            cin>>Dni;
                            funciona=clientes.mostrar(Dni);
                            if(!funciona){
                                cout<< "No se ha podido encontrar el DNI"<<endl;
                            }
                            break;

                        case 2:
                            cout<< "Indroduce el Dni a buscar: ";
                            cin>> Dni;
                            pos=clientes.buscar(Dni);
                            if (pos !=-1){
                               cli= clientes.consultar(pos);

                                esteticaClientes();
                                cout<<setw(11)<<left<<cli.Dni;
                                cout<<setw(35)<<left<<cli.Nombre;
                                cout<<setw(14)<<left<<cli.Provincia;
                                cout<<setw(15)<<left<<cli.AcumuKm;
                                cout<<setw(10)<<left<<cli.AcumuEuros;
                               if(cli.VEnAlquiler){
                                    strcpy(vehiculo,"Si");
                                }else{
                                    strcpy(vehiculo,"No");
                                }
                                cout<<setw(8)<<left<<vehiculo<<endl;
                            }else{
                                cout<< "No se ha podido encontrar el DNI"<<endl;
                            }

                            break;

                        case 3:
                            cout<< "Introduce el Dni: ";
                            cin>>cli.Dni;
                            if (clientes.buscar(cli.Dni)==-1){
                                cout<< "Introduce el Nombre: ";
                                cin.ignore();
                                cin.getline(cli.Nombre, 150);
                                cout<< "Introduce la provincia del cliente: ";
                                cin.getline(cli.Provincia, 150);
                                cli.AcumuEuros=0;
                                cli.AcumuKm=0;
                                cli.VEnAlquiler=false;
                                clientes.insertar(cli);
                                cout<< "Se ha insertado el cliente."<<endl;
                            }else{
                                cout<< "El DNI ya se encuentra entre los clientes actuales. "<<endl;
                            }
                            break;

                        case 4:

                            cout<< "Indroduce el Dni a buscar: ";
                            cin>> Dni;
                            pos =clientes.buscar(Dni);
                            if (pos==-1 ){
                                cout<< "El DNI no se encuentra entre los clientes"<<endl;
                                break;

                            }else {
                                TCliente c= clientes.consultar(pos);
                                esteticaClientes();
                                cout<<setw(11)<<left<<c.Dni;
                                cout<<setw(35)<<left<<c.Nombre;
                                cout<<setw(14)<<left<<c.Provincia;
                                cout<<setw(15)<<left<<c.AcumuKm;
                                cout<<setw(10)<<left<<c.AcumuEuros;
                                if(c.VEnAlquiler){
                                    strcpy(vehiculo,"Si");
                                }else{
                                    strcpy(vehiculo,"No");
                                }
                                cout<<setw(8)<<left<<vehiculo<<endl;

                                cout<< "¿Desea modificar el nombre (s/n)?";
                                cin>> respuesta;
                                respuesta=toupper(respuesta);
                                if (respuesta== 'S'){
                                    cout<< "Introduce el Nombre: ";
                                    cin.ignore();
                                    cin.getline(c.Nombre,150);
                                }
                                cout<< "¿Desea modificar la provincia (s/n)?";
                                cin>> respuesta;
                                respuesta=toupper(respuesta);
                                if (respuesta== 'S'){
                                    cout<< "Introduce la provincia del cliente: ";
                                    cin.ignore();
                                    cin.getline(c.Provincia,150);
                                }
                                funciona=clientes.modificar(c,pos);
                                if(funciona && respuesta == 'S'){
                                   cout<< "El cliente ha sido modificado"<<endl;
                                }
                            }

                            break;

                        case 5:
                            cout<< "Introduce el Dni a buscar: ";
                            cin>> Dni;
                            pos = clientes.buscar(Dni);
                            cli=clientes.consultar(pos);
                            if (!cli.VEnAlquiler){
                                cout<< "¿Desea eliminar al cliente (s/n)?";
                                cin>> respuesta;
                                respuesta=toupper(respuesta);
                                if (respuesta == 'S'){
                                    funciona=clientes.eliminar(pos);
                                    if (funciona){
                                        cout<< "El cliente ha sido eliminado. "<<endl;
                                    }else{
                                        cout<< "No se ha podido eliminar."<<endl;
                                    }
                                }
                            }else{
                                cout<< "El cliente no puede ser eliminado al tener un vehículo alquilado. "<<endl;
                            }
                            break;
                        }

                }while (opc !=0);

                break;

            case 2:
                menuVehiculos();
                do{
                    do{
                        cout<< "\nElija una opcion: ";
                        cin>>opc;

                    }while (opc<0 || opc>7);
                    if(opc<0 && opc>7){
                            cout<< "Error. Introduce otra opcion.";
                    }


                    switch (opc){
                        case 1:
                            cout<< "Introduce una provincia: ";
                            cin.ignore();
                            cin.getline(provincia,150);
                            veh.mostrar(provincia);
                            break;

                        case 2:
                            do{
                                cout<< "Introduce campo de busqueda (P: posición, M: matricula): ";
                                cin>> respuesta;
                                if (respuesta != 'p' && respuesta != 'P' && respuesta != 'M' && respuesta != 'm'){
                                    cout<< "Error. "<<endl;
                                }
                            }while (respuesta != 'p' && respuesta != 'P' && respuesta != 'M' && respuesta != 'm');

                            Vehiculo v;
                            respuesta=toupper(respuesta);
                            if (respuesta == 'P'){
                                cout<< "Introduce la posicion a buscar: ";
                                cin>> pos;
                                vehi=veh.consultar(pos);
                                esteticaVehiculos();
                                cout<<setw(17)<<left<<vehi.modelo;
                                cout<<setw(14)<<left<<vehi.matricula;
                                cout<<setw(13)<<left<<vehi.provincia;
                                cout<<setw(14)<<left<<vehi.kilometros;
                                cout<<setw(15)<<left<<vehi.precio_km;
                                cout<<setw(20)<<left<<vehi.estado<<endl;

                            }else {
                                cadena m;
                                cout<< "Introduce el texto a buscar: ";
                                cin>> m;
                                pos=veh.consultar(m);
                                if (pos !=-1){
                                    v=veh.consultar(pos);
                                    cout<<setw(17)<<left<<v.modelo;
                                    cout<<setw(14)<<left<<v.matricula;
                                    cout<<setw(13)<<left<<v.provincia;
                                    cout<<setw(14)<<left<<v.kilometros;
                                    cout<<setw(15)<<left<<v.precio_km;
                                    cout<<setw(20)<<left<<v.estado<<endl;

                                }else{
                                    cout<< "No se ha encontrado un coche con dicha matricula"<<endl;
                                }

                            }
                            break;
                        case 3:
                            cout << "Introduce la matricula: ";
                            cin>> vehi.matricula;
                            pos=veh.consultar(vehi.matricula);

                            if (pos ==-1){
                                cout<< "Introduce el modelo: ";
                                cin.ignore();
                                cin.getline(vehi.modelo, 150);
                                cout<< "Introduce la provincia: ";
                                cin.ignore();
                                cin.getline(vehi.provincia,150);
                                cout<< "Introduce el kilometraje: ";
                                cin>>vehi.kilometros;
                                cout<< "Introduce el precio por kilometro: ";
                                cin>>vehi.precio_km;
                                strcpy (vehi.estado, "libre");

                                veh.insertar(vehi);


                            }else{
                                cout<< "Error, se ha encontrado un vehiculo con esa matricula. "<<endl;
                            }

                            break;

                        case 4:
                            Vehiculo x;
                            int y;
                            cout<< "Introduce la posicion: "<<endl;
                            cin>>pos;
                            x = veh.consultar(pos);
                            y=veh.consultar(x.matricula);
                            if (y!=-1){
                                cout<< "Introduce la nueva provincia: ";
                                cin>> vehi.provincia;
                                cout<< "Introduce el precio por kilometro: ";
                                cin>> vehi.precio_km;
                                veh.modificar(vehi, pos);
                            }else{
                                cout<< "No se ha encontrado la matricula. "<<endl;
                            }

                            break;

                        case 5:
                            bool estado;
                            cout<< "Introduce la posicion: "<<endl;
                            cin>>pos;
                            vehi=veh.consultar(pos);
                            estado=vehi.estado;
                            if (vehi.estado){
                                veh.eliminarPorPosicion(pos);
                            }else{
                                cout<< "El vehiculo no se ha podido eliminar, ya que esta ocupado. "<<endl;
                            }

                            break;
                        case 6:
                            cout<< "Introduce la provincia de los vehiculos a ocultar: ";
                            cin >> provincia;
                            veh.OcultarVehiculos(provincia);
                            break;
                        case 7:
                            cout<< "Introduce la provincia de los vehiculos a recuperar: ";
                            cin>> provincia;
                            veh.RecuperarVehiculos(provincia);
                            break;


                    }


                }while (opc !=0);
                break;

            case 3:
                menuGestiondeAlquileres();
                do{
                    do{
                        cout<< "\nElija una opcion: ";
                        cin>>opc;
                        if(opc<0 || opc>3){
                            cout<< "Error. Introduce otra opcion.";
                        }

                    }while (opc<0 || opc>3);


                    switch (opc){
                        case 1:
                            numAlquiler=alqui.getNumAlquiler();

                            cout<<"MATRICULA   KILOM.  DNI         NOMBRE                              CIR KM  CIR DIAS"<<endl;
                            cout<<"************************************************************************************"<<endl;

                            for (int i=0; i<numAlquiler;i++){
                                alq=alqui.consultar(i); //consulto el alquiler en la posicion i
                                posicion_c=clientes.buscar(alq.Dni); //Obtengo la posicion del Dni
                                pos=veh.consultar(alq.Matricula);
                                if(posicion_c ==-1 && pos ==-1){
                                    cout<< "Error.";
                                }else{
                                    vehi=veh.consultar(pos);
                                    cli=clientes.consultar(posicion_c);//obtengo el dni
                                    cout<<setw(12)<<left<<alq.Matricula;
                                    cout<<setw(8)<<left<<vehi.kilometros;
                                    cout<<setw(12)<<left<< alq.Dni;
                                    cout<<setw(36)<<left<< cli.Nombre;
                                    cout<<setw(8)<<left<< alq.KmsCir;
                                    cout<<setw(8)<<left<< alq.NDiasCir<<endl;

                                }
                            }

                            break;
                        case 2:
                            {
                            pos=0;
                            cout<< "Introduce el dni del cliente: ";
                            cin>> Dni;
                            cout<< "Introduce la Matricula del coche:";
                            cin>> matricula;

                            pos=clientes.buscar(Dni);
                            if(pos==-1){
                                cout<< "El dni no se ha encontrado"<<endl;
                                break;
                            }
                            posicion_v=veh.consultar(matricula);
                            if(posicion_v==-1){
                                cout<< "No se ha encontrado la matricula del coche"<<endl;
                                break;
                            }


                            if (alqui.Buscar(Dni, 'D')!=-1 || alqui.Buscar(matricula,'M')!=-1){
                                cout<< "El Dni del cliente o la matricula ya tiene un alquiler"<<endl;
                                break;
                            }

                            clientes.mostrar(Dni);
                            vehi=veh.consultar(posicion_v);

                            if (strcmp (vehi.estado, "Libre")!=0){
                                cout<< "El coche ya está ocupado, por lo que no podras alquilarlo."<<endl;

                            }

                            esteticaVehiculos();
                            cout<<setw(17)<<left<<vehi.modelo;
                            cout<<setw(14)<<left<<vehi.matricula;
                            cout<<setw(13)<<left<<vehi.provincia;
                            cout<<setw(14)<<left<<vehi.kilometros;
                            cout<<setw(15)<<left<<vehi.precio_km;
                            cout<<setw(20)<<left<<vehi.estado<<endl;

                            cout<< "¿Son los datos correctos?(s/n)";
                            cin>>respuesta;
                            respuesta=toupper(respuesta);
                            if (respuesta == 'S'){
                                cout<< "Introduce el maximo de km a circular: ";
                                cin>> max_km;
                                cout<< "Introduce el numero de dias a circular: ";
                                cin>> n_dias;
                                strcpy (alq.Matricula,matricula);
                                strcpy (alq.Dni,Dni);
                                alq.KmsCir=max_km;
                                alq.NDiasCir=n_dias;
                                cout<< "El coche ha sido alquilado"<<endl;

                                strcpy (vehi.estado,"Ocupado");
                                veh.modificar(vehi, posicion_v);
                                alqui.nuevo(alq);


                            }else {
                                cout<< "No desea modificar nada";
                            }
                            }

                            break;
                        case 3:

                            cout<< "Introduce la matricula del vehiculo: ";
                            cin>>matricula;
                            pos=alqui.Buscar(matricula, 'M');
                            if (pos==-1){
                                cout<< "El vehiculo no se encuentra alquilado";
                                break;
                            }

                                vehi= veh.consultar(pos);

                                cout<<"MATRICULA   KILOM.  DNI         NOMBRE                              CIR KM  CIR DIAS"<<endl;
                                cout<<"************************************************************************************"<<endl;
                                cout<<setw(17)<<left<<vehi.modelo;
                                cout<<setw(14)<<left<<vehi.matricula;
                                cout<<setw(13)<<left<<vehi.provincia;
                                cout<<setw(14)<<left<<vehi.kilometros;
                                cout<<setw(15)<<left<<vehi.precio_km;
                                cout<<setw(20)<<left<<vehi.estado<<endl;

                            cout<< "¿Son los datos correctos? (s/n): ";
                            cin>>respuesta;
                            respuesta=toupper(respuesta);

                            strcpy(matricula, alq.Matricula);


                            if (respuesta == 'S'){
                                pos_m=veh.consultar(matricula);

                                km_recorridos= rand()%alq.KmsCir +1;
                                dias_circulados= rand()%alq.NDiasCir+1;
                                precio_km=(km_recorridos*veh.consultar(pos_m).precio_km)/100;
                                precio_dias=dias_circulados*50;
                                precio_total=precio_km+precio_dias;

                                cout<< "Kilometros recorridos : "<< km_recorridos<<endl;
                                cout<< "Dias circulados: "<< dias_circulados<<endl;
                                cout<< "Precio Km Recorridos"<<precio_km<<endl;
                                cout<< "Precio Dias Alquiler: "<<precio_dias<<endl;
                                cout<< "Precio Total: "<<precio_total<<endl;

                            }
                            alq=alqui.consultar(pos);
                            strcpy(vehi.estado, "Libre");

                            Vehiculo v;
                            posicion_v2= veh.consultar(matricula);
                            v=veh.consultar(posicion_v2);
                            veh.modificar(v, posicion_v2);

                            posicion_c= clientes.buscar(alq.Dni);
                            cli=clientes.consultar(posicion_c);

                            cli.AcumuKm+=km_recorridos;
                            cli.AcumuEuros+=precio_total;
                            vehi.kilometros+=km_recorridos;


                            clientes.modificar(cli, posicion_c);

                            alqui.eliminarPorPosicion(pos);

                            break;
                    }


                }while (opc !=0);
                break;
        }
    }while(opc!=0);

    return 0;
}
