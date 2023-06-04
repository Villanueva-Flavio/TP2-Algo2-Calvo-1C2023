#include "./Headers/Interacciones.h"
#include <string>
#include <iostream>
using namespace std;

string validarContenidoFicha(Celda* celdaJugador, Celda* celdaElegida){
    
    // soldadoJugadorContrario - armamentoJugadorContrario - inactiva- vacia - fichaJugador - destruir
    string resultado= "inactiva"; 
    if(celdaElegida->getEstado()){

        TipoContenido fichaDeJugador = celdaJugador->getFicha()->getTipo();

        if(esArmamento(fichaDeJugador)){
            resultado = validacionArmamento(celdaJugador,celdaElegida);
        }else {
            resultado = validacionSoldado(celdaJugador,celdaElegida);
        }

    }

    return resultado;
}

string validacionArmamento(Celda* celdaJugador, Celda* celdaElegida){
    string resultado = "vacia";
    TipoContenido tipoCeldaElegida = celdaElegida->getFicha()->getTipo();
    if(tipoCeldaElegida == SOLDADO || esArmamento(tipoCeldaElegida)){
        resultado=  esFichaDelJugadorActual(celdaJugador,celdaElegida) ? "fichaJugador" : "armamentoJugadorContrario";;
    }else if(tipoCeldaElegida == MINA_FICHA){
        resultado= "destruir";
    }

    return resultado;
}

string validacionSoldado(Celda* celdaJugador, Celda* celdaElegida){
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

bool esArmamento(TipoContenido contenidoFicha){
    bool resultado= false;
    if(contenidoFicha !=  CARTA && contenidoFicha != VACIO && contenidoFicha !=  SOLDADO && contenidoFicha !=  MINA_FICHA){
        resultado = true;
    }
    return resultado;
}

bool esFichaDelJugadorActual(Celda* celdaJugador, Celda* celdaElegida){
    bool resultado = false;
    if(celdaJugador->getFicha()->getJugadorOwner() == celdaElegida->getFicha()->getJugadorOwner() ){
        resultado = true;
    }
    return resultado;
}

void errorEnCeldaElegida(string resultado){

    string mensaje = resultado == "inactiva" ? "ocupada por otra de sus fichas" : resultado;
    cout << "La celda seleccionada se encuentra " << resultado << " elija otra celda"<< endl;
}
