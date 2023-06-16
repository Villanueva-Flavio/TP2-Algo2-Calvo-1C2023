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
#include "Headers/Structs/Coordenadas.h"

using namespace std;

#define CAPA_MAXIMA 5

typedef map<string, Coordenada> MapaCoordenadas;
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
    bool nombreValido = false;
    string nombre;
    for (int i = 0; i < this->cantidadJugadores; i++) {
        while (!nombreValido) {
            cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombre;
            this->jugadores->getLData(i)->setNombre(nombre);
            nombreValido = (this->jugadores->getLData(i)->getNombre() != "");
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

bool BatallaDigital::esOrilla(int tipo, Coordenada pos){
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
                Coordenada pos = {x, y, z};
                (!esOrilla(tipo, pos))? this->mapa->getTData(x, y, z)->setTipo(CAPA_AGUA) : this->mapa->getTData(x, y, CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
            }
            mapa->getTData(x, y, 0)->setTipo(CAPA_ARENA);
        }
    }
}

void BatallaDigital::cargarMapaEspecificado(int aux){
    if (aux == M_TIERRA || aux == M_DESIERTO || aux == M_MAR) {
        this->cargarTerrenoPlano(aux);
    } else if (aux == M_PLAYA) {
        this->cargarPlaya(aux);
    } else if (aux == M_RIO || aux == M_LAGO) {
        this->cargarRioLago(aux);
    }
}

void BatallaDigital::cargarMapas() {
    string tipo = this->consultarTipoDeMapa();
    MapaTipos mapa = getMapaTipos();
    TipoMapa aux;

    while (mapa.count(tipo) == 0) {
        cout << "Tipo inválido, reingrese el tipo.\n";
        tipo = this->consultarTipoDeMapa();
    }
    aux = mapa[tipo];
    this->cargarMapaEspecificado(aux);
}

void BatallaDigital::cargarCantidadesDeFichasAJugadores(){
    for(int i = 0; i < this->jugadores->getSize(); i++) {
        this->jugadores->getLData(i)->setArmamentos(1), jugadores->getLData(i)->setSoldados(5);
    }    
}

bool BatallaDigital::validarCeldaAInsertarFicha(Coordenada* cordenada, TipoContenido tipoDeFicha) {
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
    Coordenada cordenada;
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
        resultado = (esArmamento(fichaDeJugador))? validacionArmamento(celdaJugador,celdaElegida) : validacionSoldado(celdaJugador,celdaElegida);
    }
    return resultado;
}

string BatallaDigital::validacionArmamento(Celda* celdaJugador, Celda* celdaElegida){
    TipoContenido tipoCeldaElegida = celdaElegida->getFicha()->getTipo();
    return (tipoCeldaElegida == SOLDADO || esArmamento(tipoCeldaElegida))? 
            esFichaDelJugadorActual(celdaJugador, celdaElegida)? "fichaJugador" : 
            "armamentoJugadorContrario" : tipoCeldaElegida == MINA_FICHA ? "destruir" : 
            "vacia";
}

string BatallaDigital::validacionSoldado(Celda* celdaJugador, Celda* celdaElegida){
    string resultado= "vacia"; 
    TipoContenido tipoCeldaElegida = celdaElegida->getFicha()->getTipo();
    bool confirmacion = esFichaDelJugadorActual(celdaJugador, celdaElegida);    
    return (esArmamento(tipoCeldaElegida))?
             confirmacion? "fichaJugador" : "destruir" : 
             (tipoCeldaElegida == SOLDADO)? 
             confirmacion? "fichaJugador" : "soldadoJugadorContrario" : 
             (tipoCeldaElegida == MINA_FICHA)? 
             "destruir" : "vacia";
}

bool BatallaDigital::esArmamento(TipoContenido contenidoFicha){
    return (contenidoFicha !=  CARTA && contenidoFicha != VACIO && contenidoFicha !=  SOLDADO && contenidoFicha !=  MINA_FICHA);
}

bool BatallaDigital::esFichaDelJugadorActual(Celda* celdaJugador, Celda* celdaElegida){
    return (celdaJugador->getFicha()->getJugadorOwner() == celdaElegida->getFicha()->getJugadorOwner());
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

Coordenada BatallaDigital::obtenerCoordenadaCelda(){
    Coordenada aux;
    cout << "Ingrese coordenada en formato 'x y z': ";
    cin >> aux.x >> aux.y >> aux.z;

    return aux;
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

Carta* BatallaDigital::generarCarta(){
    srand(time(NULL));
    int indiceDeCarta = rand() % 5;
    mapaIndiceDeCartas mapaIndiceCartas = this->getMapaIndiceDeCartas();
    Carta* cartaGenerada= new Carta(mapaIndiceCartas[indiceDeCarta]);
    return cartaGenerada;
}

void BatallaDigital::ejecutarCartaElegida(Carta* carta, Jugador* jugador,Coordenada coordenada){
    
    switch(carta->getTipoCarta()){
        case OMITIR_TURNO:
            this->omitirTurno = true;
            break;
        case ESCUDO:
            jugador->activarEscudo();
            break;
        case BARCO:
            Coordenada coordenadaBomba = obtenerCoordenadaCelda();
            carta->usarCarta(this->mapa, coordenadaBomba);
            break;
        default:
            carta->usarCarta(this->mapa, coordenada);
    }
}

void BatallaDigital::insertarMina(Coordenada coordenada){
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
    indice = (indice == this->jugadores->getSize()) ? 0 : indice;
}

bool BatallaDigital::mensajeValido(std::string mensaje){
    return (mensaje == "Y" || mensaje == "N");
}

void BatallaDigital::tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada){
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
            Coordenada coordendaMina=this->obtenerCoordenadaCelda();
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