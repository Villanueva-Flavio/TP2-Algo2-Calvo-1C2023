#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>

#include "Tablero.h"
#include "Celda.h"
#include "Carta.h"
#include "Renderizador.h"
#include "BatallaDigital.h"
#include "Enums.h"
#include "Coordenadas.h"

using namespace std;

#define CAPA_MAXIMA 5

BatallaDigital::BatallaDigital(int cantidad){
    this->mapa = new Tablero<Celda*>(cantidad*4, cantidad*4, cantidad*4);
    this->jugadores = new Lista<Jugador*>();
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

std::string BatallaDigital::consultarTipoDeMapa(){
    cout << "\nSeleccione un tipo de mapa:\n";
    cout << "+------------------------------------+\n";
    cout << "|    Playa    -   Mar   -   Tierra   |\n";
    cout << "|  Desierto   -   Rio   -   Lago     |\n";
    cout << "+------------------------------------+\n";
    cout << "Version Beta: Sin Rio y Lago" << endl;
    cout << "(Escriba su respuesta): ";
    cin >> this->tipoMapa;
    return this->tipoMapa;
}

void BatallaDigital::cargarTerrenoPlano(string tipo) {
    for(int i = 0; i < this->mapa->getTamanioX(); i ++){
        for(int j = 0; j < this->mapa->getTamanioY(); j ++){
            for(int k = 0; k < this->mapa->getTamanioZ(); k ++){
                this->mapa->getTData(i, j, k)->setTipo((k>5)? CAPA_AIRE : (tipo == "Mar")? CAPA_AGUA : (tipo == "Desierto")? CAPA_ARENA : CAPA_TIERRA);
            }    
        }    
    }    
}

void BatallaDigital::cargarPlaya(string tipo) {
    for(int i = 0; i < this->mapa->getTamanioX(); i ++){
        for(int j = 0; j < this->mapa->getTamanioY(); j ++){
            for(int k = 0; k < this->mapa->getTamanioZ(); k ++){
                this->mapa->getTData(i, j, k)->setTipo((k>5)? CAPA_AIRE : (k<i)? CAPA_ARENA : CAPA_AGUA);
            }    
        }    
    }    
}

/* bool BatallaDigital::esOrilla(string tipo, Coordenada pos){
    CoordenadaDouble r;
    double p = (tipo == "Lago")? 0.285:0.227;
    double radioAjustado = 1+(p*(pow(this->mapa->getTamanioX()/4, 1/2.5)));
    r.x = (tipo == "Lago")? pow(pos.x - mapa->getTamanioX()/2, 2) : 0;
    r.y = pow(pos.y - mapa->getTamanioY()/2, 2);
    r.z = pow(pos.y - mapa->getTamanioZ()/2, 2);
    return ((double)(r.x + r.y + r.z) <= pow(this->mapa->getTamanioX(), radioAjustado));
}

void BatallaDigital::cargarRioLago(string tipo){
    for(int x = 0; x < mapa->getTamanioX(); x++){
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < mapa->getTamanioZ(); z++){
                Coordenada pos = {x, y, z};
                (z >= 5)? this->mapa->getTData(x, y, z)->setTipo(CAPA_AIRE) : this->mapa->getTData(x, y, z)->setTipo(CAPA_AGUA);
                if(esOrilla(tipo, pos)){
                    this->mapa->getTData(x, y, CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
            }
            mapa->getTData(x, y, 0)->setTipo(CAPA_ARENA);
        }
    }
} */

void BatallaDigital::cargarMapaEspecificado(string aux){
    if(aux == "Playa"){
        this->cargarPlaya(aux);
    }else if(aux == "Mar" || aux == "Tierra" || aux == "Desierto"){
        this->cargarTerrenoPlano(aux);
    }else if(aux == "Rio" || aux == "Lago"){
        /* this->cargarRioLago(aux); */
        // A IMPLEMENTAR
    }
}

void BatallaDigital::cargarMapas() {
    string mapa = this->consultarTipoDeMapa();
    while (mapa != "Playa" && mapa != "Mar" && mapa != "Tierra" && mapa != "Desierto" && mapa != "Rio" && mapa != "Lago") {
        cout << "Tipo inválido, reingrese el tipo.\n";
        mapa = this->consultarTipoDeMapa();
    }
    this->cargarMapaEspecificado(mapa);
}

void BatallaDigital::cargarCantidadesDeFichasAJugadores(){
    for(int i = 0; i < this->jugadores->getSize(); i++) {
        this->jugadores->getLData(i)->setArmamentos(1), jugadores->getLData(i)->setSoldados(5);
    }    
}

bool BatallaDigital::validarCeldaAInsertarFicha(Coordenada cordenada, TipoContenido tipoDeFicha) {
    TipoContenido tipo = this->mapa->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getFicha()->getTipo();
    Capa capa = this->mapa->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getTipo();

    return (tipo == VACIO 
    && ((tipoDeFicha == BARCO && this->mapa->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),CAPA_MAXIMA-1)->getTipo() == CAPA_AGUA) 
        || (tipoDeFicha == SUBMARINO && capa == CAPA_AGUA) 
        || (tipoDeFicha == AVION && capa == CAPA_AIRE)  
        || (tipoDeFicha == SOLDADO && capa == CAPA_AIRE))
    );
}

void BatallaDigital::cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    Coordenada cordenada;
    for (int i = 0; i <= cantidadDeCarga; i++){
        do{
            cordenada.setCoordenadaX(rand()% this->mapa->getTamanioX());
            cordenada.setCoordenadaY(rand()% this->mapa->getTamanioY());
            cordenada.setCoordenadaZ((tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? CAPA_MAXIMA : rand()% this->mapa->getTamanioZ());
        } while (validarCeldaAInsertarFicha(cordenada,tipoDeFicha));
        this->mapa->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getFicha()->setJugadorOwner(jugadorOwner);
        this->mapa->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getFicha()->setTipo(tipoDeFicha);
    }
}

void BatallaDigital::cargarFichas(){
    for (int i = 0; i < jugadores->getSize(); i++){
        if (this->tipoMapa != "mar"){
            this->cargarFichaDelTipo(jugadores->getLData(i)->getSoldados(),SOLDADO,i);
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),TANQUE,i);
        }

        if (this->tipoMapa != "tierra" && this->tipoMapa != "desierto"){
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),SUBMARINO,i);
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),BARCO,i);
        }

        this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos() + 1,AVION,i);
    }
    
}

void BatallaDigital::cargarJuego() {
    this->cargarMapas();
    this->cargarCantidadesDeFichasAJugadores();
    this->cargarFichas();
}

// ---------------- Interacciones entre fichas ------------------

string BatallaDigital::validarContenidoFicha(Celda* celdaJugador, Celda* celdaElegida){
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
    int x=0, y=0, z=0;
    do{ 
        cout << "Ingrese coordenada en formato 'x y z': ";
        cin >> x >> y >> z;
        aux.setCoordenadaX(x);
        aux.setCoordenadaY(y);
        aux.setCoordenadaZ(z);
    }while(!coordenadaEnRango(aux)); 

    return aux;
}

TipoCarta BatallaDigital::obtenerTipoDeCarta(int indiceDeCarta){
    TipoCarta tipo;
    switch (indiceDeCarta)
    {
    case AVION_RADAR:
        tipo = AVION_RADAR;
        break;
    case BARCO_MISIL:
        tipo = BARCO_MISIL;
        break;
    case ATAQUE_QUIMICO:
        tipo = ATAQUE_QUIMICO;
        break;
    case BOMBARDEO:
        tipo = BOMBARDEO;
        break;
    case OMITIR_TURNO:
        tipo = OMITIR_TURNO;
        break;
    default:
        tipo = ESCUDO;
        break;
    }
    return tipo;
}

Carta* BatallaDigital::generarCarta(){
    int indiceDeCarta = rand() % 5;
    TipoCarta tipo = obtenerTipoDeCarta(indiceDeCarta);
    Carta* cartaGenerada= new Carta(tipo);
    return cartaGenerada;
}

void BatallaDigital::ejecutarCartaElegida(Carta* carta, Jugador* jugador,Coordenada coordenada){
    Coordenada coordenadaMisil;
    switch(carta->getTipoCarta()){
        case OMITIR_TURNO:
            this->omitirTurno = true;
            break;
        case ESCUDO:
            jugador->activarEscudo();
        break;
        case BARCO:
            cout << "Ingrese la posicion del misil"<<endl;
            coordenadaMisil = this-> obtenerCoordenadaCelda();
            carta->usarCarta(this->mapa, coordenadaMisil);
            break;
        default:
            carta->usarCarta(this->mapa, coordenada);
    }
}

void BatallaDigital::insertarMina(Coordenada coordenada){
    Celda* celdaSelecionada = this->mapa->getTData(coordenada.getCoordenadaX(),coordenada.getCoordenadaY(),coordenada.getCoordenadaZ());
    if(celdaSelecionada->getEstado()){
        if(celdaSelecionada->getFicha()->getJugadorOwner() != -1 || celdaSelecionada->getFicha()->getTipo() == MINA_FICHA){
            cout<<"Haz destruido una Ficha" << endl;
            this->destruirFicha(celdaSelecionada->getFicha());
            this->inactivarCelda(celdaSelecionada);
            
        }else{
            celdaSelecionada->getFicha()->setTipo(MINA_FICHA);
            cout<<"Mina insertada"<<endl;
        }
    }
}

void BatallaDigital::mantenerIndiceEnRango(int &indice){
    if(! (indice < this->jugadores->getSize())){
        indice = 0;
    }
}

bool BatallaDigital::mensajeValido(std::string mensaje){
    return (mensaje == "Y" || mensaje == "N");
}

int BatallaDigital::obtenerIndiceDeCarta(Jugador* jugador){
    int i = 0;
    int indiceDeCarta;
    while(i !=-1){
        cout<<"Ingrese el indice de la carta que quiere usar: "<<endl;
        cin >> indiceDeCarta;
        if( (indiceDeCarta -1 >= 0) && (indiceDeCarta -1  < jugador->getCantidadDeCartas()) ){
            i= -1;
        }else{
            cout<<"Ingrese un indice valido"<<endl;
        }
    }
    return indiceDeCarta-1;
}

void BatallaDigital::tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada){
    Carta*  carta = this->generarCarta();
    jugador->agregarCarta(carta);
    cout<<"Acaba de selecionar una carta del tipo: " << carta->getStringTipoCarta()<<endl;
    string respuesta = "";
    
    while(!mensajeValido(respuesta)){
        cout<<"¿Desea usar alguna Carta? Y/N: "<<endl;
        cin>>respuesta;
    }  

    if(respuesta == "Y"){
        jugador->imprimirCartas();
        int indiceDeCarta = this->obtenerIndiceDeCarta(jugador);
        this->ejecutarCartaElegida(jugador->seleccionarCarta(indiceDeCarta),jugador,coordenada);
        jugador->removerCarta(indiceDeCarta);
        cout<<"Carta ejecutada correctamente"<<endl;
    }
}

void BatallaDigital::mostrarFichasActuales(int jugador){
    system("clear");
    cout << "Fichas actuales: " << endl;
    int contador = 0;
    for(int i = 0; i < this->mapa->getTamanioX(); i++){
        for(int j = 0; j < this->mapa->getTamanioY(); j++){
            for(int k = 0; k < this->mapa->getTamanioZ(); k++){
                if(this->mapa->getTData(i,j,k)->getFicha()->getJugadorOwner() == jugador){
                    string tipo = (this->esArmamento(this->mapa->getTData(i,j,k)->getFicha()->getTipo())) ? "Armamento" : "Soldado";
                    cout << contador + 1  << " " << tipo << ". En (" << i << ", " << j << ", " << k << ")" << endl;
                    contador++;
                }

                if(contador == this->jugadores->getLData(jugador)->getArmamentos() + this->jugadores->getLData(jugador)->getSoldados()){
                    return;
                }
            }
        }
    }
    cout << endl << endl;
}

void BatallaDigital::solicitarFichaAMover(int* indice, int jugador){
    cout << "Ingrese el numero de la ficha que desea mover: ";
    cin >> *indice;
    while(*indice < 1 || *indice > this->jugadores->getLData(jugador)->getArmamentos() + this->jugadores->getLData(jugador)->getSoldados()){
        cout << endl << "Ingrese un numero valido: ";
        cin >> *indice;
    }
    *indice -= 1;
}

void BatallaDigital::procesarDireccion(Coordenada* coordenada){
    if (!this->coordenadaEnRango(*coordenada)){
        cout << "La direccion a la que desea moverse esta fuera de rango" << endl;
        seleccionarDireccion(coordenada);
    }
}

Coordenada BatallaDigital::obtenerCoordenadaDireccion(std::string direccion){
    Coordenada coordenada;
    coordenada.setCoordenadaX(0);
    coordenada.setCoordenadaY(0);
    coordenada.setCoordenadaZ(0);

    if(direccion == "w" || direccion == "W"){
        coordenada.setCoordenadaY(1);
    }else if(direccion == "a" || direccion == "A"){
        coordenada.setCoordenadaX(-1);
    }else if(direccion == "s" || direccion == "S"){
        coordenada.setCoordenadaY(-1);
    }else if(direccion == "d" || direccion == "D"){
        coordenada.setCoordenadaX(1);
    }else if(direccion == "r" || direccion == "R"){
        coordenada.setCoordenadaZ(1);
    }else{
        coordenada.setCoordenadaZ(-1);
    }
    
    return coordenada;
}

bool BatallaDigital::direccionValida(std::string direccion){
    bool valido = false;

    if( direccion == "w" || direccion == "W" ||
        direccion == "a" || direccion == "A" || 
        direccion == "s" || direccion == "S" || 
        direccion == "d" || direccion == "D" || 
        direccion == "r" || direccion == "R" ||
        direccion == "f" || direccion == "F"){
            valido = true;
    }

    return valido;
}

void BatallaDigital::seleccionarDireccion(Coordenada* coordenada){
    string direccion;
    cout << "Ingrese la direccion en la que desea mover la ficha (W - A - S - D | R - F): " << endl;
    cin >> direccion;
    while(!this->direccionValida(direccion)){
        cout << "Ingrese una direccion valida: " << endl ;
        cin >> direccion;
    }
    Coordenada coordenadaDireccion = this->obtenerCoordenadaDireccion(direccion);

    coordenada->setCoordenadaX(coordenada->getCoordenadaX() + coordenadaDireccion.getCoordenadaX());
    coordenada->setCoordenadaY(coordenada->getCoordenadaY() + coordenadaDireccion.getCoordenadaY());
    coordenada->setCoordenadaZ(coordenada->getCoordenadaZ() + coordenadaDireccion.getCoordenadaZ());
    
    this->procesarDireccion(coordenada);
    
}

bool BatallaDigital::sePuedeMover(Coordenada coordenada, int jugador){
    TipoContenido tipo = this->mapa->getTData(coordenada.getCoordenadaX(), coordenada.getCoordenadaY(), coordenada.getCoordenadaZ())->getFicha()->getTipo();
    
    return(coordenada.getCoordenadaX() < 0 || 
            coordenada.getCoordenadaX() >= this->mapa->getTamanioX() || 
            coordenada.getCoordenadaY() < 0 || 
            coordenada.getCoordenadaY() >= this->mapa->getTamanioY() || 
            coordenada.getCoordenadaZ() < 0 || 
            coordenada.getCoordenadaZ() >= this->mapa->getTamanioZ() ||
            !this->mapa->getTData(coordenada.getCoordenadaX(), coordenada.getCoordenadaY(), coordenada.getCoordenadaZ())->getEstado() ||
            this->mapa->getTData(coordenada.getCoordenadaX(), coordenada.getCoordenadaY(), coordenada.getCoordenadaZ())->getFicha()->getJugadorOwner() == jugador)?
            false : true;
}

void BatallaDigital::aplicarGravedad(Coordenada* coordenada){
    while(coordenada->getCoordenadaZ() > 0 && this->mapa->getTData(coordenada->getCoordenadaX(), coordenada->getCoordenadaY(), coordenada->getCoordenadaZ() - 1)->getTipo() == CAPA_AIRE){
        coordenada->setCoordenadaZ(coordenada->getCoordenadaZ() -1);
    }
}

void BatallaDigital::contarEscalado(Coordenada* coordenada){
    int difAltura = 0;
    Capa capa = this->mapa->getTData(coordenada->getCoordenadaX(), coordenada->getCoordenadaY(), coordenada->getCoordenadaZ())->getTipo();
    difAltura = (capa == CAPA_PASTO || CAPA_AGUA == CAPA_TIERRA) ? 1 : 0;
    coordenada->setCoordenadaZ(coordenada->getCoordenadaZ() + difAltura);
}

void BatallaDigital::removerAmbasFichas(Coordenada c1, Coordenada c2){
    int j1 = this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha()->getJugadorOwner();
    int j2 = this->mapa->getTData(c2.getCoordenadaX(), c2.getCoordenadaY(), c2.getCoordenadaZ())->getFicha()->getJugadorOwner();
    TipoContenido tipoj1 = this->mapa->getTData(c2.getCoordenadaX(), c2.getCoordenadaY(), c2.getCoordenadaZ())->getFicha()->getTipo();
    TipoContenido tipoj2 = this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha()->getTipo();

    (tipoj1 == SOLDADO)?
        this->jugadores->getLData(j1)->setSoldados(this->jugadores->getLData(j1)->getSoldados() - 1):
        this->jugadores->getLData(j1)->setArmamentos(this->jugadores->getLData(j1)->getArmamentos() - 1);
    (tipoj2 == SOLDADO)?
        this->jugadores->getLData(j2)->setSoldados(this->jugadores->getLData(j2)->getSoldados() - 1):
        this->jugadores->getLData(j2)->setArmamentos(this->jugadores->getLData(j2)->getArmamentos() - 1);
}

void BatallaDigital::aplicarMovimiento(int jugador, Coordenada* coordenada){
    int i = coordenada->getCoordenadaX();
    int j = coordenada->getCoordenadaY();
    int k = coordenada->getCoordenadaZ();
    this->seleccionarDireccion(coordenada);
    this->contarEscalado(coordenada);
    this->aplicarGravedad(coordenada);
    while(!this->sePuedeMover(*coordenada, jugador)){
        cout << "No se puede mover a esa posicion, ingrese otra direccion: " << endl;
        coordenada->setCoordenadaX(i);
        coordenada->setCoordenadaY(j);
        coordenada->setCoordenadaZ(k);
        this->seleccionarDireccion(coordenada);
        this->contarEscalado(coordenada);
        this->aplicarGravedad(coordenada);
    }
}

void BatallaDigital::eventoColisionMortal(string evento, Coordenada c1, Coordenada c2){
    this->removerAmbasFichas(c1, c2);
    this->destruirFicha(this->mapa->getTData(c2.getCoordenadaX(), c2.getCoordenadaY(), c2.getCoordenadaZ())->getFicha());
    this->destruirFicha(this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha());
    if(evento == "destruir"){
        this->inactivarCelda(this->mapa->getTData(c2.getCoordenadaX(), c2.getCoordenadaY(), c2.getCoordenadaZ()));
    }
}

void BatallaDigital::eventoDesplazamiento(Coordenada c1, Coordenada c2){
    int ownerAux = this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha()->getJugadorOwner();
    TipoContenido tipoAux = this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha()->getTipo();
    this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha()->setJugadorOwner(-1);
    this->mapa->getTData(c1.getCoordenadaX(), c1.getCoordenadaY(), c1.getCoordenadaZ())->getFicha()->setTipo(VACIO);
    this->mapa->getTData(c2.getCoordenadaX(), c2.getCoordenadaY(), c2.getCoordenadaZ())->getFicha()->setJugadorOwner(ownerAux);
    this->mapa->getTData(c2.getCoordenadaX(), c2.getCoordenadaY(), c2.getCoordenadaZ())->getFicha()->setTipo(tipoAux);
}

void BatallaDigital::procesarEventos(Coordenada coordenada, int jugador){
    Coordenada aux = coordenada;
    this->aplicarMovimiento(jugador, &coordenada);
    Ficha* fichaSrc = this->mapa->getTData(aux.getCoordenadaX(),aux.getCoordenadaY(),aux.getCoordenadaZ())->getFicha();
    Ficha* fichaDest = this->mapa->getTData(coordenada.getCoordenadaX(), coordenada.getCoordenadaY(), coordenada.getCoordenadaZ())->getFicha();
    string evento = this->validarContenidoFicha(this->mapa->getTData(aux.getCoordenadaX(), aux.getCoordenadaY(), aux.getCoordenadaZ()), this->mapa->getTData(coordenada.getCoordenadaX(), coordenada.getCoordenadaY(), coordenada.getCoordenadaZ()));
    if(evento == "soldadoJugadorContrario" || evento == "armamentoJugadorContrario" || evento == "destruir"){
        this->eventoColisionMortal(evento, aux, coordenada);
    } else if(evento == "inactiva"){
        cout << "No se puede mover a esa posicion, la ficha quedara esperando en el mismo lugar" << endl;
    } else if(evento == "fichaJugador"){
        cout << "Dos soldados propios casi se matan, al finalizar el conflicto, las fichas se quedaron en el mismo lugar" << endl;
    } else if(evento == "vacia"){
        this->eventoDesplazamiento(aux, coordenada);
    }
}

void BatallaDigital::moverFicha(int indice, int jugador){
    int contador = 0;
    Coordenada coordenada;
    for(int i = 0; i < this->mapa->getTamanioX(); i++){
        for(int j = 0; j < this->mapa->getTamanioY(); j++){
            for(int k = 0; k < this->mapa->getTamanioZ(); k++){
                if(this->mapa->getTData(i,j,k)->getFicha()->getJugadorOwner() == jugador){
                    contador++;
                }
                if(contador == indice){
                    coordenada.setCoordenadaX(i);
                    coordenada.setCoordenadaY(j);
                    coordenada.setCoordenadaZ(k);
                    i = j = k = this->mapa->getTamanioX();
                }
            }
        }
    }
    this->procesarEventos(coordenada, jugador);
}

void BatallaDigital::jugarFicha(int jugador){
    int indice = 0;
    this->mostrarFichasActuales(jugador);
    this->solicitarFichaAMover(&indice, jugador);
    this->moverFicha(indice, jugador);
}

bool BatallaDigital::jugadorConFichasVivas(int jugador){
    return this->jugadores->getLData(jugador)->getArmamentos() + this->jugadores->getLData(jugador)->getSoldados() > 0;
}

int BatallaDigital::jugadoresConFichasVivas(){
    int contador = 0;
    for(int i = 0; i < this->jugadores->getSize(); i++){
        if(jugadorConFichasVivas(i)){
            contador++;
        }
    }
    return contador;
}

void BatallaDigital::procesarInactivas(){
    for(int i = 0; i < this->mapa->getTamanioX(); i++){
        for(int j = 0; j < this->mapa->getTamanioY(); j++){
            for(int k = 0; k < this->mapa->getTamanioZ(); k++){
                if(this->mapa->getTData(i, j, k)->getTurnosInactiva() > 0){
                    this->mapa->getTData(i, j, k)->setTurnosInactiva(this->mapa->getTData(i, j, k)->getTurnosInactiva() - 1);
                }
            }
        }
    }
}

void BatallaDigital::mensajeEmpate(){
    cout << "Empate!" << endl;
}

void BatallaDigital::sacarFoto(int jugador){
    Coordenada imgSize;
    imgSize.setCoordenadaX(this->mapa->getTamanioX() * 100);
    imgSize.setCoordenadaY(this->mapa->getTamanioY() * 70);

    BMP *image = new BMP();
    image->SetSize(imgSize.getCoordenadaX(), imgSize.getCoordenadaY());
    imprimirBMP(imgSize, image, this->mapa, getMap(), jugador);
    image->WriteToFile("Partida.bmp");
    delete image;
}

bool BatallaDigital::coordenadaEnRango(Coordenada coordenada){
    return (coordenada.getCoordenadaX() >= 0 && coordenada.getCoordenadaX() < this->mapa->getTamanioX() && coordenada.getCoordenadaY() >= 0 && coordenada.getCoordenadaY() < this->mapa->getTamanioY() && coordenada.getCoordenadaZ() >= 0 && coordenada.getCoordenadaZ() < this->mapa->getTamanioZ());
}

void BatallaDigital::moverFicha(int indiceDeJugador){
    string respuesta = "";
    do{
        cout << "Desea mover una ficha? Y/N: " << endl;
        cin >> respuesta;
    }while(!mensajeValido(respuesta)); 

    if(respuesta== "Y"){
        this->jugarFicha(indiceDeJugador);
    }
}

void BatallaDigital::jugar(){
    int indiceDeJugador = 0;
    while(this->jugadoresConFichasVivas() > 1){
        system("clear");
        this->mantenerIndiceEnRango(indiceDeJugador);
        this->sacarFoto(indiceDeJugador);
        cout << "Turno Jugador " << indiceDeJugador +1 << endl;
        
        if(this->omitirTurno){ 
            this->omitirTurno = false;
        } else if(this->jugadorConFichasVivas(indiceDeJugador)){
            
            cout << "Elija la posicion para la mina " << endl;
            Coordenada coordenada = this-> obtenerCoordenadaCelda();

            this->insertarMina(coordenada);
            this->tomarCartaDeMazo(this->jugadores->getLData(indiceDeJugador), coordenada); 
            this->moverFicha(indiceDeJugador);
            
        }
        
        indiceDeJugador++;
        
        if(indiceDeJugador == this->jugadores->getSize()){
            this->procesarInactivas();
        }
    }
    if(this->jugadoresConFichasVivas() == 0){
        this->mensajeEmpate();
    }
}
