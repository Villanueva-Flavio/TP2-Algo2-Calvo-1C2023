// #include <string>
// using namespace std;

// Carta::Carta(TipoCarta carta) {
    
//     this->activa = true;
//     this->radioAccion = NULL;
//     this->cantidadBombas = NULL;

//     switch(carta){
//         //case AVION:
//         //    this->carta = AVION;
//         //    break;
//         case ATAQUE_QUIMICO:
//             this->carta = ATAQUE_QUIMICO;
//             break;
//         case BOMBARDEO:
//             this->carta = BOMBARDEO;
//             break;
//         case BARCO:
//             this->carta = BARCO;
//             break;
//         case OMITIR_TURNO:
//             this->carta = OMITIR_TURNO;
//             break;
//         case ESCUDO:
//             this->carta = ESCUDO;
//             break;
//     }
// }

//  void Carta::usarCarta(bool &atributoJugador){
    
//     this->activa = false;

//     switch(this->carta){
//         case OMITIR_TURNO:
//             //se pasa por parametros jugador continuo
//             activarAtributosJugador(atributoJugador);
//             break;
//         case ESCUDO:
//             activarAtributosJugador(atributoJugador);
//             break;
//     }
// } 
// template <class T> 
//  void Carta::usarCarta(Tablero<T> &tablero,  int x, int y, int z){

//     this->activa = false;

//     /* switch(this->carta){
//         case AVION:
//             this->radioAccion = 8;
//             obtenerReporte(tablero,celda);
//             break;
//         case ATAQUE_QUIMICO:
//             this->radioAccion = 5;
//             inactivarCeldas(tablero,celda);
//             break;
//         case BOMBARDEO:
//             this->radioAccion = 5;
//             this->cantidadBombas = 4;
//             bombardearZona(tablero,celda);
//             break;
//         case BARCO:
//             lanzarMisil(tablero,celda);
//             break;
//     } */
// }

// TipoCarta Carta::obteneterTipoCarta() {
//     return this->carta;
// }

// bool Carta::cartaActiva() {
//     return this->activa;
// }
// template <class Celda> 
// void Carta::inactivarCeldas(Tablero<Celda> &tablero, int x, int y, int z){

//     int &radio = this->radioAccion; 

//     Celda celdaCentral = new Celda();
//     celdaCentral = tablero->getTData(x,y,z);
    
//     /* for (x=-radio; x < radio ; x++){

//         for (y=-radio; y < radio ; y++){

//             for (z=-radio; z < radio ; z++){

//                 if(tablero->inRange(x,y,z)){

//                     if(){

//                     }
//                 }
        
//             }
        
//         }

//     } */
//   /*   
//     1.accedo a la celda que central
//     2.Itero sobre las celdas dentro del rango de la explosion
//     3.una vez accedo al contenido de las celdas verifico su contenido 
//         Si la celda esta vacia-> la inactivo
//         Si la celda tenia una Ficha-> guardo la ubicacion y agrego la linea en un archivo txt reporte -> la inactivo
//         (X,Y,Z) - Tipo de Ficha - Owner /
//     4. Imprimo un reporte en un txt 
//  */

// }
// template <class Celda> 
// void Carta::bombardearCeldas(Tablero<Celda> &tablero,  int x, int y, int z){

// /*   
//     1.accedo a la celda central
//     2. Elijo 4 ubicaciones de forma aleatoria
//     3.una vez accedo al contenido de las celdas verifico su contenido 
//         Si la celda esta vacia-> la inactivo
//         Si la celda tenia una Ficha-> guardo la ubicacion y agrego la linea en un archivo txt reporte -> la inactivo
//         (X,Y,Z) - Tipo de Ficha - Owner /
//     4. Imprimo un reporte en un txt 
//  */
// }
// template <class Celda> 
// void Carta::obtenerReporte(Tablero<Celda> &tablero, int x, int y, int z){
//  /*   
//     1.accedo a la celda central
//     2.Itero sobre las celdas dentro del rango de la explosion
//     3.una vez accedo al contenido de las celdas verifico su contenido 
//         Si la celda tenia una Ficha-> tomo la ubicacion y agrego la linea en un archivo txt reporte
//         (X,Y,Z) - Tipo de Ficha - Owner - Estado/
//     4. Imprimo un reporte en un txt 
//  */
// }
// template <class Celda> 
// void Carta::lanzarMisil(Tablero<Celda> &tablero,  int x, int y, int z){
//     /*   Hacer que devuelva un string con 
//     1.accedo a la celda
//     2.una vez accedo al contenido de las celdas verifico su contenido 
//         Si la celda tenia una Ficha-> tomo la ubicacion y agrego la linea en un archivo txt reporte- la inactivo
//         (X,Y,Z) - Tipo de Ficha - Owner - Estado/
//     4. Imprimo un reporte en un txt 
//  */
// }

// void Carta::activarAtributosJugador(bool &atributoJugador){
//     if(!atributoJugador){
//         atributoJugador = true;
//     }
// } 