#ifndef FESTIVAL_H
#define FESTIVAL_H
#include "comun.h"

class Festival{
     Concierto *conciertos; //puntero inicial de la estructura de nodos enlazados de tipo Concierto
     //correspondiente al conjunto de conciertos que integran el festival
     int numConciertos; //número de conciertos registrados en el festival
     cadena nombre; //nombre del festival
     cadena fechaInicio; //fecha de comienzo del festival, con formato AAAAMMDD
     cadena fechaFin; //fecha en la que finaliza el festival, con formato AAAAMMDD

public:

     //Método constructor de la clase. Inicializara los atributos nombre, fechaInicio y fechaFin
     //respectivamente con los valores contenidos en los parámetros nombreConcierto, fIni y fFin.
     //El nuevo festival inicialmente no tendrá ningún concierto registrado, siendo necesario
     //inicializar el atributo numConciertos de acuerdo con esta circunstancia.
     Festival(cadena nomFestival, cadena fIni, cadena fFin);

     //Método destructor de la clase, que liberará convenientemente la memoria reservada para almacenar
    //cada uno de los nodos tipo Concierto, generados de forma dinámica.
    ~Festival();

     //Método para devolver el nombre del festival a través del parámetro de E/S nomFestival.
     void getNombre(cadena nomFestival);

     //Método para devolver la fecha de comienzo del festival a través del parámetro de E/S fIni.
     void getFechaInicio(cadena fIni);

     //Método para devolver la fecha de clausura del festival a través del parámetro de E/S fFin.
     void getFechaFin(cadena fFin);

     //Método para devolver el número de conciertos registrados en el festival
     int getNumConciertos();

     //Método para registrar un nuevo concierto en el festival. Insertara un nuevo registro tipo
     //Concierto en la estructura enlazada accesible a través del atributo conciertos. Dicho
     //registro será previamente inicializado a partir de los parámetros reales recibidos por el
     //método. El identificador codId de un Concierto es único en el sistema, por lo que será
     //necesario garantizar que no existe almacenado previamente ningún concierto con el mismo
     //valor para dicho campo que el indicado por el parámetro idConcierto. Igualmente, se asume
     //que en un mismo festival no ocurrirá en más de una ocasión la actuación de un mismo artista.
     //Por tanto también será necesario garantizar que no se añada el concierto si ya hay otro
     //registro para el artista/grupo indicado. El método devolverá true en caso de que se haya
     //podido realizar la inserción del nuevo concierto; false evidentemente en caso contrario.
     bool programarConcierto(int idConcierto, cadena nomGrupo, cadena fecha, int numEntradasMax);

     //Método para registrar un nuevo concierto en el festival, a partir de la información
     //contenida en el fichero binario con nombre el indicado por el parámetro nomFichero. El
     //método devolverá true en caso de realizarse correctamente la apertura del fichero indicado;
     //false en caso contrario.
     bool cargarConciertoDesdeFichero(cadena nomFichero);

     //Método para eliminar el concierto con identificador el indicado por el parámetro idConcierto.
     //Si no existe ningún concierto con el identificador indicado el método devolverá false; true
     //en caso contrario, confirmando que dicho concierto ha sido eliminado de la estructura
     //enlazada.
     bool cancelarConcierto(int idConcierto);

     //Método que permite conocer si existe en el festival un concierto con código identificador
     //coincidente con el pasado como parámetro. Devolverá su posición dentro de la secuencia de
     //nodos enlazados, donde el primer elemento es el 1, en caso de existir; -1 en caso contrario.
     int existeConcierto(int idConcierto);

     //Método que permite conocer si existe en el festival un concierto del artista/grupo de nombre
     //coincidente con el indicado por el parámetro nomGrupo. Devolverá su posición dentro de la
     //secuencia de nodos enlazados, donde el primer elemento es el 1, en caso de existir; -1 en
     //caso contrario.
     int existeConcierto(cadena nomGrupo);

     //Método para mostrar por pantalla la información del concierto que se encuentra en la
     //posición indicada por el parámetro posicion dentro de la secuencia enlazada accesible a
     //partir de conciertos, donde el primer elemento está en la posición 1. Se mostrará el nombre
     //del artista, el código identificativo del concierto, la fecha de celebración y el número de
     //entradas disponibles.
     void mostrarInfoConcierto(int posicion);

     //Método para obtener el código identificador único (codId) del concierto almacenado en la
     //posición indicada por el parámetro posicion dentro de la secuencia de nodos enlazados tipo
     //Concierto accesible a través del atributo conciertos. Si el valor de posicion está fuera del
     //rango efectivo, el método devolverá un -1.
     int getCodIdConcierto(int posicion);

     //Método para registrar la compra de una entrada en el concierto de código identificador único
     //idConcierto. Si hay entradas disponibles, y no hay ninguna otra ya registrada con el mismo dni
     //que el indicado por parámetro, se generará un registro Entrada, y será almacenado en la
     //lista entradasVendidas del Concierto. El campo codIdEntrada será generado de forma aleatoria,
     //dentro del rango [10000, 50000], garantizando además que para un mismo concierto no existan
     //dos entradas distintas con el mismo código. El método devolverá dicho valor aleatorio. Si no
     //hay entradas disponibles, o bien ya existe otra entrada con el mismo dni que el indicado por el
     //parámetro correspondiente, el método devolverá un -1.
     int comprarEntrada(int idConcierto, cadena dni);

     //Método para registrar una reserva en el concierto de código identificador único idConcierto.
     //La instancia de tipo SolicitudCompra será añadida al final de la cola colaEspera del concierto
     //correspondiente. El método devolverá true cuando el registro es encolado correctamente; false
     //en caso contrario, esto es, cuando se dé alguna de las siguientes circunstancias: 1. no exista
     //ningún concierto en el festival con el identificador indicado por el parámetro idConcierto; 2.
     //cuando aún haya entradas disponibles para dicho concierto, y por tanto no tenga sentido registrar
     //una solicitud de compra en espera; 3. cuando exista ya una solicitud previa para el dni contenido
     //en el parámetro s; 4. cuando exista una entrada registrada para el dni contenido en el parámetro
     //s.
     bool registrarReserva(int idConcierto, SolicitudCompra s);

     //Método para eliminar de la lista entradasVendidas la entrada de código identificativo idEntrada,
     //correspondiente al concierto de código idConcierto. Al liberarse una entrada, será necesario
     //comprobar si había solicitudes de compra en espera. En caso positivo, habrá que registrar una
     //nueva entrada para la solicitud a la cabeza de la cola, y evidentemente eliminar este elemento
     //de la misma. Esta nueva entrada deberá conservar el idEntrada de la entrada eliminada. El método
     //devolverá true en caso de eliminar correctamente la entrada de la lista; false en caso contrario,
     //cuando no exista un concierto, o bien una entrada para el mismo, con el identificador indicado.
     bool eliminarEntrada(int idConcierto, int idEntrada);
     //Método para eliminar una solicitud de compra registrada para el concierto de identificador
     //idConcierto. Eliminará de la cola colaEspera dicho registro. Devolverá true en caso de eliminarse
     //el registro correctamente; false en caso contrario, cuando no exista el concierto con
     //identificador idConcierto, o bien una reserva para una persona con el dni indicado por el parámetro
     //correspondiente.
     bool eliminarReserva(int idConcierto, cadena dni);

     //Método para mostrar la información de cada entrada vendida para el concierto que se encuentra en
     //la posición indicada por el parámetro posicion, dentro de la secuencia de nodos enlazados
     //accesibles a partir del atributo conciertos. Si no hay concierto alguno en la posición indicada,
     //el método mostrará un mensaje de error. Se considera que el primer elemento es el situado en la
     //posicion 1.
     void mostrarEntradasVendidas(int posicion);

     //Método para mostrar la información de cada reserva en la cola colaEspera del concierto que se
     //encuentra en la posición indicada por el parámetro posición, dentro de la secuencia de nodos
     //enlazados accesibles a partir del atributo conciertos. Si no hay concierto alguno en la posición
     //indicada, el método mostrará un mensaje de error. Se considera que el primer elemento es el
     //situado en la posición 1.
     void mostrarSolicitudesDeCompra(int posicion);
     bool comprobarid(Entrada e);
     void esteticasolicitudes();
     void esteticaconcierto();

};

#endif // FESTIVAL_H
