#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>

#include "Headers/Tablero.h"
#include "Headers/Celda.h"
#include "Headers/Carta.h"
#include "Headers/Renderizador.h"
#include "Headers/BatallaDigital.h"
#include "Headers/Enums.h"
#include "Headers/Structs/Coordenadas.h"

using namespace std;

#define CAPA_MAXIMA 5

typedef map<string, Coordenada> MapaCoordenadas;

MapaCoordenadas getMapaCoordenadas(){
    MapaCoordenadas mapa;
    
    Coordenada coordW = {0, 0, 1};
    Coordenada coordA = {-1, 0, 0};
    Coordenada coordS = {0, 0, -1};
    Coordenada coordD = {1, 0, 0};
    
    mapa["w"] = coordW;
    mapa["a"] = coordA;
    mapa["s"] = coordS;
    mapa["d"] = coordD;
    mapa["W"] = coordW;
    mapa["A"] = coordA;
    mapa["S"] = coordS;
    mapa["D"] = coordD;
    
    return mapa;
}

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
    TipoContenido tipo = this->mapa->getTData(cordenada.x,cordenada.y,cordenada.z)->getFicha()->getTipo();
    Capa capa = this->mapa->getTData(cordenada.x,cordenada.y,cordenada.z)->getTipo();

    return (tipo == VACIO 
    && ((tipoDeFicha == BARCO && this->mapa->getTData(cordenada.x,cordenada.y,CAPA_MAXIMA-1)->getTipo() == CAPA_AGUA) 
        || (tipoDeFicha == SUBMARINO && capa == CAPA_AGUA) 
        || (tipoDeFicha == AVION && capa == CAPA_AIRE)  
        || (tipoDeFicha == SOLDADO && capa == CAPA_AIRE))
    );
}

void BatallaDigital::cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    Coordenada cordenada;
    for (int i = 0; i <= cantidadDeCarga; i++){
        do{
            cordenada.x = rand()% this->mapa->getTamanioX();
            cordenada.y = rand()% this->mapa->getTamanioY();
            cordenada.z = (tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? CAPA_MAXIMA : rand()% this->mapa->getTamanioZ();
        } while (validarCeldaAInsertarFicha(cordenada,tipoDeFicha));
        this->mapa->getTData(cordenada.x,cordenada.y,cordenada.z)->getFicha()->setJugadorOwner(jugadorOwner);
        this->mapa->getTData(cordenada.x,cordenada.y,cordenada.z)->getFicha()->setTipo(tipoDeFicha);
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
    do{ 
        cout << "Ingrese coordenada en formato 'x y z': ";
        cin >> aux.x >> aux.y >> aux.z;
    }while(!coordenadaEnRango(aux)); 

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
    int indiceDeCarta = rand() % 5;
    mapaIndiceDeCartas mapaIndiceCartas = this->getMapaIndiceDeCartas();
    Carta* cartaGenerada= new Carta(mapaIndiceCartas[indiceDeCarta]);
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
    Celda* celdaSelecionada = this->mapa->getTData(coordenada.x,coordenada.y,coordenada.z);
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

void BatallaDigital::pedirMovimiento(){
    bool movimientoValido = false;
    string movimiento = "";
    MapaCoordenadas mapa = getMapaCoordenadas();

    cout << "\nIngrese un movimiento (w-a-s-d): ";
    cin >> movimiento;

    this->mapa->getTData();

    while((mapa.find(movimiento) == mapa.end())){
        cout << "No se ingrese un movimiento valido.\nIngrese un movimiento (w-a-s-d): ";
        cin >> movimiento;
    }
    Coordenada coordenada = mapa[movimiento];
}

void BatallaDigital::procesarDireccion(Coordenada* coordenada){
    if (!this->coordenadaEnRango(*coordenada)){
        cout << "La direccion a la que desea moverse esta fuera de rango" << endl;
        seleccionarDireccion(coordenada);
    }
}

void BatallaDigital::seleccionarDireccion(Coordenada* coordenada){
    string direccion;
    MapaCoordenadas mapaCoordenadas = getMapaCoordenadas();
    cout << "Ingrese la direccion en la que desea mover la ficha (W - A - S - D | R - F): " << endl;
    cin >> direccion;
    while(mapaCoordenadas.find(direccion) == mapaCoordenadas.end()){
        cout << "Ingrese una direccion valida: " << endl ;
        cin >> direccion;
    }
    coordenada->x += mapaCoordenadas[direccion].x;
    coordenada->y += mapaCoordenadas[direccion].y;
    coordenada->z += mapaCoordenadas[direccion].z;

    procesarDireccion(coordenada);
    
}

bool BatallaDigital::sePuedeMover(Coordenada coordenada, int jugador){
    TipoContenido tipo = this->mapa->getTData(coordenada.x, coordenada.y, coordenada.z)->getFicha()->getTipo();
    
    return(coordenada.x < 0 || 
            coordenada.x >= this->mapa->getTamanioX() || 
            coordenada.y < 0 || 
            coordenada.y >= this->mapa->getTamanioY() || 
            coordenada.z < 0 || 
            coordenada.z >= this->mapa->getTamanioZ() ||
            !this->mapa->getTData(coordenada.x, coordenada.y, coordenada.z)->getEstado() ||
            this->mapa->getTData(coordenada.x, coordenada.y, coordenada.z)->getFicha()->getJugadorOwner() == jugador)?
            false : true;
}

void BatallaDigital::aplicarGravedad(Coordenada* coordenada){
    while(coordenada->z > 0 && this->mapa->getTData(coordenada->x, coordenada->y, coordenada->z - 1)->getTipo() == CAPA_AIRE){
        coordenada->z -= 1;
    }
}

void BatallaDigital::contarEscalado(Coordenada* coordenada){
    int difAltura = 0;
    Capa capa = this->mapa->getTData(coordenada->x, coordenada->y, coordenada->z)->getTipo();
    difAltura = (capa == CAPA_PASTO || CAPA_AGUA == CAPA_TIERRA) ? 1 : 0;
    coordenada->z += difAltura;
}

void BatallaDigital::removerAmbasFichas(Coordenada c1, Coordenada c2){
    int j1 = this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha()->getJugadorOwner();
    int j2 = this->mapa->getTData(c2.x, c2.y, c2.z)->getFicha()->getJugadorOwner();
    TipoContenido tipoj1 = this->mapa->getTData(c2.x, c2.y, c2.z)->getFicha()->getTipo();
    TipoContenido tipoj2 = this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha()->getTipo();

    (tipoj1 == SOLDADO)?
        this->jugadores->getLData(j1)->setSoldados(this->jugadores->getLData(j1)->getSoldados() - 1):
        this->jugadores->getLData(j1)->setArmamentos(this->jugadores->getLData(j1)->getArmamentos() - 1);
    (tipoj2 == SOLDADO)?
        this->jugadores->getLData(j2)->setSoldados(this->jugadores->getLData(j2)->getSoldados() - 1):
        this->jugadores->getLData(j2)->setArmamentos(this->jugadores->getLData(j2)->getArmamentos() - 1);
}

void BatallaDigital::aplicarMovimiento(int jugador, Coordenada* coordenada){
    int i = coordenada->x;
    int j = coordenada->y;
    int k = coordenada->z;
    this->seleccionarDireccion(coordenada);
    this->contarEscalado(coordenada);
    this->aplicarGravedad(coordenada);
    while(!this->sePuedeMover(*coordenada, jugador)){
        cout << "No se puede mover a esa posicion, ingrese otra direccion: " << endl;
        coordenada->x = i;
        coordenada->y = j;
        coordenada->z = k;
        this->seleccionarDireccion(coordenada);
        this->contarEscalado(coordenada);
        this->aplicarGravedad(coordenada);
    }
}

void BatallaDigital::eventoColisionMortal(string evento, Coordenada c1, Coordenada c2){
    this->removerAmbasFichas(c1, c2);
    this->destruirFicha(this->mapa->getTData(c2.x, c2.y, c2.z)->getFicha());
    this->destruirFicha(this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha());
    if(evento == "destruir"){
        this->inactivarCelda(this->mapa->getTData(c2.x, c2.y, c2.z));
    }
}

void BatallaDigital::eventoDesplazamiento(Coordenada c1, Coordenada c2){
    int ownerAux = this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha()->getJugadorOwner();
    TipoContenido tipoAux = this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha()->getTipo();
    this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha()->setJugadorOwner(-1);
    this->mapa->getTData(c1.x, c1.y, c1.z)->getFicha()->setTipo(VACIO);
    this->mapa->getTData(c2.x, c2.y, c2.z)->getFicha()->setJugadorOwner(ownerAux);
    this->mapa->getTData(c2.x, c2.y, c2.z)->getFicha()->setTipo(tipoAux);
}

void BatallaDigital::procesarEventos(Coordenada coordenada, int jugador){
    Coordenada aux = coordenada;
    this->aplicarMovimiento(jugador, &coordenada);
    Ficha* fichaSrc = this->mapa->getTData(aux.x,aux.y,aux.z)->getFicha();
    Ficha* fichaDest = this->mapa->getTData(coordenada.x, coordenada.y, coordenada.z)->getFicha();
    string evento = this->validarContenidoFicha(this->mapa->getTData(aux.x, aux.y, aux.z), this->mapa->getTData(coordenada.x, coordenada.y, coordenada.z));
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
                    coordenada.x = i;
                    coordenada.y = j;
                    coordenada.z = k;
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
    imgSize.x = this->mapa->getTamanioX() * 100;
    imgSize.y = this->mapa->getTamanioY() * 70;
    BMP *image = new BMP();
    image->SetSize(imgSize.x, imgSize.y);
    imprimirBMP(imgSize, image, this->mapa, getMap(), jugador);
    image->WriteToFile("Partida.bmp");
    delete image;
}

bool BatallaDigital::coordenadaEnRango(Coordenada coordenada){
    return (coordenada.x >= 0 && coordenada.x < this->mapa->getTamanioX() && coordenada.y >= 0 && coordenada.y < this->mapa->getTamanioY() && coordenada.z >= 0 && coordenada.z < this->mapa->getTamanioZ());
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
