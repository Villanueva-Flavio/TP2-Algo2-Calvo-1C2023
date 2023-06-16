#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>

#include "Headers/Tablero.h"
#include "Headers/Celda.h"
#include "Headers/carta.h"
#include "Headers/Renderizador.h"
#include "Headers/BatallaDigital.h"
#include "Headers/Enums.h"


using namespace std;

#define CAPA_MAXIMA 5

typedef map<string, coordenadas> MapaCoordenadas;
typedef map<string, TipoMapa> MapaTipos;

MapaCoordenadas getMapaCoordenadas(){
    MapaCoordenadas mapa;
    mapa["w"] = {0,0,1};
    mapa["a"] = {-1,0,0};
    mapa["s"] = {0,0,-1};
    mapa["d"] = {1,0,0};
    mapa["W"] = {0,0,1};
    mapa["A"] = {-1,0,0};
    mapa["S"] = {0,0,-1};
    mapa["D"] = {1,0,0};
    return mapa;
};

MapaTipos getMapaTipos(){
    MapaTipos mapa;
    mapa["playa"] = M_PLAYA;
    mapa["mar"] = M_MAR;
    mapa["tierra"] = M_TIERRA;
    mapa["desierto"] = M_DESIERTO;
    mapa["rio"] = M_RIO;
    mapa["lago"] = M_LAGO;
    return mapa;
};

BatallaDigital::BatallaDigital(int cantidad){
    this->mapa = new Mapa(cantidad*4, cantidad*4, cantidad*4);
    this->jugadores = new Jugadores();
    this->omitirTurno=false;
    for(int i = 0; i < cantidad; i++){
        Jugador* jugador = new Jugador();
        this->jugadores->add(jugador);
    }
    this->cantidadJugadores = cantidad;
    this->turno = 0;
}

BatallaDigital::~BatallaDigital(){
    delete this->mapa;
    delete this->jugadores;
}

void BatallaDigital::consultarNombres(){
    for (int i = 0; i < this->cantidadJugadores; i++) {
        bool nombreValido = false;
        while (!nombreValido) {
            string nombre;
            cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombre;
            this->jugadores->getLData(i)->setNombre(nombre);

            if (this->jugadores->getLData(i)->getNombre() != "") {
                nombreValido = true;
            }
        }
    }
}

std::string BatallaDigital::consultarTipoDeMapa(){
    cout << "\nSeleccione un tipo de mapa:\n";
    cout << "+------------------------------------+\n";
    cout << "|    Playa    -   Mar   -   Tierra   |\n";
    cout << "|  Desierto   -   Rio   -   Lago     |\n";
    cout << "+------------------------------------+\n";
    cout << "(Escriba su respuesta): ";
    return this->tipoMapa;
}

void BatallaDigital::cargarTerrenoPlano(int tipo) {
    for(int i = 0; i < this->mapa->getTamanioX(); i ++){
        for(int j = 0; i < this->mapa->getTamanioY(); j ++){
            for(int k = 0; i < this->mapa->getTamanioZ(); k ++){
                this->mapa->getTData(i, j, k)->setTipo((k>5)? CAPA_AIRE : (i<k+4)? CAPA_ARENA : CAPA_AGUA);
            }    
        }    
    }    
}

void BatallaDigital::cargarPlaya(int tipo) {
    for(int i = 0; i < this->mapa->getTamanioX(); i ++){
        for(int j = 0; i < this->mapa->getTamanioY(); j ++){
            for(int k = 0; i < this->mapa->getTamanioZ(); k ++){
                this->mapa->getTData(i, j, k)->setTipo((k>5)? CAPA_AIRE : (i<k+4)? CAPA_ARENA : CAPA_AGUA);
            }    
        }    
    }    
}

bool BatallaDigital::esOrilla(int tipo, coordenadas pos){
    CoordenadaDouble r;
    double p = (tipo == M_LAGO)? 0.285:0.227;
    double radioAjustado = 1+(p*(pow(this->mapa->getTamanioX()/4, 1/2.5)));
    r.x = (tipo == M_LAGO)? pow(pos.x - mapa->getTamanioX()/2, 2) : 0;
    r.y = pow(pos.y - mapa->getTamanioY()/2, 2);
    r.z = pow(pos.y - mapa->getTamanioZ()/2, 2);
    return ((double)(r.x + r.y + r.z) <= pow(this->mapa->getTamanioX(), radioAjustado));
}

void BatallaDigital::cargarRioLago(int tipo){
    for(int x = 0; x < mapa->getTamanioX(); x++){
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < mapa->getTamanioZ(); z++){
                coordenadas pos = {x, y, z};
                (!esOrilla(tipo, pos))? this->mapa->getTData(x, y, z)->setTipo(CAPA_AGUA) : this->mapa->getTData(x, y, CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
            }
            mapa->getTData(x, y, 0)->setTipo(CAPA_ARENA);
        }
    }
}

// Carga el mapa elegido por el jugador
void BatallaDigital::cargarMapas() {
    string tipo = ""; 
    tipo = this->consultarTipoDeMapa();
    MapaTipos mapita = getMapaTipos();
    int enumeradorcito = 0;
    while (mapita.count(tipo) == 0) {
        cout << "Tipo inválido, reingrese el tipo.\n";
        tipo = this->consultarTipoDeMapa();
        tipo = "lago";
    }
    enumeradorcito = mapita[tipo];
    if (enumeradorcito == M_TIERRA || enumeradorcito == M_DESIERTO || enumeradorcito == M_MAR) {
        this->cargarTerrenoPlano(enumeradorcito);
    } else if (enumeradorcito == M_PLAYA) {
        this->cargarPlaya(enumeradorcito);
    } else if (enumeradorcito == M_RIO || enumeradorcito == M_LAGO) {
        this->cargarRioLago(enumeradorcito);
    }
}

// Carga las cantidades de fichas que contiene cada jugador
void BatallaDigital::cargarCantidadesDeFichasAJugadores(){
    for(int i = 0; i < this->jugadores->getSize(); i++) {
        this->jugadores->getLData(i)->setArmamentos(1), jugadores->getLData(i)->setSoldados(5);
    }    
}

bool BatallaDigital::validarCeldaAInsertarFicha(coordenadas* cordenada, TipoContenido tipoDeFicha) {
    TipoContenido tipo = this->mapa->getTData(cordenada->x,cordenada->y,cordenada->z)->getFicha()->getTipo();
    Capa capa = this->mapa->getTData(cordenada->x,cordenada->y,cordenada->z)->getTipo();

    return (tipo == VACIO 
    && ((tipoDeFicha == BARCO && this->mapa->getTData(cordenada->x,cordenada->y,CAPA_MAXIMA-1)->getTipo() == CAPA_AGUA) 
        || (tipoDeFicha == SUBMARINO && capa == CAPA_AGUA) 
        || (tipoDeFicha == AVION && capa == CAPA_AIRE)  
        || (tipoDeFicha == SOLDADO && capa == CAPA_AIRE))
    );
}

void BatallaDigital::cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    coordenadas cordenada;
    for (int i = 0; i <= cantidadDeCarga; i++){
        do{
            cordenada.x = std::rand()%(this->mapa->getTamanioX()-1);
            cordenada.y = std::rand()%(this->mapa->getTamanioY()-1);
            cordenada.z = (tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? CAPA_MAXIMA : std::rand()%(this->mapa->getTamanioZ()-1);
        } while (validarCeldaAInsertarFicha(&cordenada,tipoDeFicha));
    }
}

void BatallaDigital::cargarFichas(){
    for (int i = 0; i < jugadores->getSize(); i++){
        if (this->tipoMapa != "mar"){
            this->cargarFichaDelTipo(jugadores->getLData(i)->getSoldados(),SOLDADO,i+1);
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),TANQUE,i+1);
        }
        if (this->tipoMapa != "tierra" && this->tipoMapa != "desierto"){
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),SUBMARINO,i+1);
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),BARCO,i+1);

        }
        this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos() + 1,AVION,i+1);
    }
}

void BatallaDigital::cargarJuego() {
    this->cargarMapas();
    this->cargarCantidadesDeFichasAJugadores();
    this->cargarFichas();
}

// ---------------- Interacciones entre fichas ------------------

string BatallaDigital::validarContenidoFicha(Celda* celdaJugador, Celda* celdaElegida){
    // soldadoJugadorContrario - armamentoJugadorContrario - inactiva- vacia - fichaJugador - destruir
    string resultado= "inactiva"; 

    if(celdaElegida->getEstado()!=false){

        TipoContenido fichaDeJugador = celdaJugador->getFicha()->getTipo();

        if(esArmamento(fichaDeJugador)){
            resultado = validacionArmamento(celdaJugador,celdaElegida);
        }else {
            resultado = validacionSoldado(celdaJugador,celdaElegida);
        }

    }

    return resultado;
}

string BatallaDigital::validacionArmamento(Celda* celdaJugador, Celda* celdaElegida){
    string resultado = "vacia";
    TipoContenido tipoCeldaElegida = celdaElegida->getFicha()->getTipo();
    if(tipoCeldaElegida == SOLDADO || esArmamento(tipoCeldaElegida)){
        resultado=  esFichaDelJugadorActual(celdaJugador,celdaElegida) ? "fichaJugador" : "armamentoJugadorContrario";;
    }else if(tipoCeldaElegida == MINA_FICHA){
        resultado= "destruir";
    }

    return resultado;
}

string BatallaDigital::validacionSoldado(Celda* celdaJugador, Celda* celdaElegida){
    string resultado= "vacia"; 
    TipoContenido tipoCeldaElegida = celdaElegida->getFicha()->getTipo();
    if(esArmamento(tipoCeldaElegida)){
        resultado= esFichaDelJugadorActual(celdaJugador,celdaElegida) ? "fichaJugador" : "destruir";
    }else if (tipoCeldaElegida == SOLDADO){
        resultado= esFichaDelJugadorActual(celdaJugador,celdaElegida) ?  "fichaJugador" : "soldadoJugadorContrario";
    }else if (tipoCeldaElegida == MINA_FICHA){
        resultado= "destruir";
    }

    return resultado;
}

bool BatallaDigital::esArmamento(TipoContenido contenidoFicha){
    bool resultado= false;
    if(contenidoFicha !=  CARTA && contenidoFicha != VACIO && contenidoFicha !=  SOLDADO && contenidoFicha !=  MINA_FICHA){
        resultado = true;
    }
    return resultado;
}

bool BatallaDigital::esFichaDelJugadorActual(Celda* celdaJugador, Celda* celdaElegida){
    bool resultado = false;

    if(celdaJugador->getFicha()->getJugadorOwner() == celdaElegida->getFicha()->getJugadorOwner() ){
        resultado = true;
    }
    return resultado;
}

void BatallaDigital::errorEnCeldaElegida(string resultado){
    cout << "La celda seleccionada se encuentra ocupada por otra de sus fichas elija otra celda"<< endl;
}

void BatallaDigital::destruirFicha(Ficha* ficha){
    ficha->setTipo(VACIO);
    ficha->setJugadorOwner(-1);
    ficha->setNumFicha(-1);

}

void BatallaDigital::inactivarCelda(Celda* celda){
    celda->setEstado(false);
}

//------------------- ---------------------- 

coordenadas BatallaDigital::obtenerCoordenadaCelda(){
    cout<<"Elija las coordenadas de la bomba"<<endl;
    int x,y,z;
    cout<<"Ingrese la coordenada X: "<<endl;
    cin>>x;
    cout<<"Ingrese la coordenada Y: "<<endl;
    cin>>y;
    cout<<"Ingrese la coordenada Z: "<<endl;
    cin>>z;

    coordenadas coordenada = {x,y,z};

    return coordenada;
}

mapaIndiceDeCartas BatallaDigital::getMapaIndiceDeCartas(){
    mapaIndiceDeCartas mapa;
    mapa[AVION_RADAR]=AVION_RADAR;
    mapa[BARCO_MISIL]=BARCO_MISIL;
    mapa[ATAQUE_QUIMICO]=ATAQUE_QUIMICO;
    mapa[BOMBARDEO]=BOMBARDEO;
    mapa[OMITIR_TURNO]=OMITIR_TURNO;
    mapa[ESCUDO]=ESCUDO;
    return mapa;
}

Carta*  BatallaDigital::generarCarta(){
    srand(time(NULL));
    int indiceDeCarta = rand() % 5;
    mapaIndiceDeCartas mapaIndiceCartas = this->getMapaIndiceDeCartas();
    Carta* cartaGenerada= new Carta(mapaIndiceCartas[indiceDeCarta]);
    return cartaGenerada;
}

void BatallaDigital::ejecutarCartaElegida(Carta* carta, Jugador* jugador,coordenadas coordenada){
    
    switch(carta->getTipoCarta()){
        case OMITIR_TURNO:
            this->omitirTurno = true;
            break;
        case ESCUDO:
            jugador->activarEscudo();
            break;
        case BARCO:
            coordenadas coordenadaBomba = obtenerCoordenadaCelda();
            carta->usarCarta(this->mapa, coordenadaBomba);
            break;
        default:
            carta->usarCarta(this->mapa, coordenada);
    }
}

void BatallaDigital::insertarMina(coordenadas coordenada){
    Celda* celdaSelecionada = this->mapa->getTData(coordenada.x,coordenada.y,coordenada.z);
    if(celdaSelecionada->getEstado()){
        if(celdaSelecionada->getFicha()->getJugadorOwner() != -1 || celdaSelecionada->getFicha()->getTipo() == MINA_FICHA){
            //Missing informar al usuario
            destruirFicha(celdaSelecionada->getFicha());
            inactivarCelda(celdaSelecionada);
        }else{
            celdaSelecionada->getFicha()->setTipo(MINA_FICHA);
        }
    }
}

void BatallaDigital::mantenerIndiceEnRango(int &indice){
    if(indice == this->jugadores->getSize()){
        indice= 0;
    }
}

bool BatallaDigital::mensajeValido(std::string mensaje){
    bool valido= false;
    if(mensaje =="Y" || mensaje == "N"){
        valido = true;
    }
    return valido;
}

void BatallaDigital::tomarCartaDeMazo(Jugador* jugador, coordenadas coordenada){
    Carta*  carta = generarCarta();
    jugador->agregarCarta(carta);
    cout<<"Acaba de selecionar una carta del tipo: " << carta->getStringTipoCarta()<<endl;
    string respuesta = "";
    
    while(!mensajeValido(respuesta)){
        
        cout<<"¿Desea usar alguna Carta? Y/N: "<<endl;
        cin>>respuesta;
    }  

    if(respuesta == "Y"){
        jugador->imprimirCartas();
        int indiceDeCarta;
        //Agregar validacion
        cout<<"Ingrese el indice de la carta que quiere usar: "<<endl;
        cin >> indiceDeCarta;
        insertarMina(coordenada);
        this->ejecutarCartaElegida(jugador->seleccionarCarta(indiceDeCarta),jugador,coordenada);
    }else {
        insertarMina(coordenada);
    }
    

 }

void BatallaDigital::cambiarTurno(){
    string estadoPartida= "activa";
    int i= 0;
    while(estadoPartida == "activa"){ // agregar condicion de fin de partida para parar buclue infinito
        
        mantenerIndiceEnRango(i);

        if(!this->omitirTurno){
            Jugador* jugadorActual = this->jugadores->getLData(i);
            coordenadas coordendaMina=this->obtenerCoordenadaCelda();
             string respuesta = "";
            
            while(!mensajeValido(respuesta)){
                cout<<"Desea tomar una carta del mazo? Y/N: "<<endl;
                cin>>respuesta;
            }  
           
            if(respuesta == "Y"){
                tomarCartaDeMazo(jugadorActual, coordendaMina);
            }


        }else{
            this->omitirTurno= false;
        }
        
        i++;
    }  
}