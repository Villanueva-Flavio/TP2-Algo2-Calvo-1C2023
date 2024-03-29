#include <sstream>
#include <string>
#include <iostream>
#include "Tablero.h"
#include "Renderizador.h"
#include "Enums.h"


const RGBApixel BLANCO = {255, 255, 255, 0};
const RGBApixel ARENA = {0, 215, 215, 0};
const RGBApixel ARENA_OSCURA = {0, 150, 150, 0};
const RGBApixel AGUA = {255, 0, 0, 0};
const RGBApixel AGUA_OSCURA = {150, 0, 0, 0};
const RGBApixel PASTO = {89, 130, 65, 0};
const RGBApixel PASTO_OSCURO = {50, 70, 35, 0};
const RGBApixel TIERRA = {14, 48, 94, 0};
const RGBApixel TIERRA_OSCURA = {9, 32, 64, 0};
const RGBApixel BORDE = {0, 0, 0, 0};
const RGBApixel MINA = {50, 50, 50, 0};
const RGBApixel FUEGO = {12, 92, 232, 0};
const RGBApixel JUGADOR = {0, 0, 0, 0};


double gradosARadianes(double grados){
    return grados * 3.14159 / 180.0;
}

void getAngulos(double angulos[6], int lado){
    switch(lado){
        case IZQUIERDA:
            angulos[0] = 40; angulos[1] = 20; angulos[2] = 0; angulos[3] = 30; angulos[4] = -30; angulos[5] = -30;
            break;
        case DERECHA:
            angulos[0] = -40; angulos[1] = 20; angulos[2] = 0; angulos[3] = -30; angulos[4] = 30; angulos[5] = -30;
            break;
        case ATRAS:
            angulos[0] = 40; angulos[1] = 20; angulos[2] = 0; angulos[3] = -30; angulos[4] = 30; angulos[5] = -30;
            break;
    }
}

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, int lado){
    double angulos[6];
    getAngulos(angulos, lado);
    pixel->setCoordenadaX((double)(gradosARadianes(angulos[0]) * pixel->getCoordenadaX() + gradosARadianes(angulos[1]) * pixel->getCoordenadaY() + gradosARadianes(angulos[2]) * pixel->getCoordenadaZ()));
    pixel->setCoordenadaY((double)(gradosARadianes(angulos[3]) * pixel->getCoordenadaX() + gradosARadianes(angulos[4]) * pixel->getCoordenadaY() + gradosARadianes(angulos[5]) * pixel->getCoordenadaZ()));
}

bool coloresSonIguales(RGBApixel color1, RGBApixel color2){
    return color1.Red == color2.Red && color1.Green == color2.Green && color1.Blue == color2.Blue;
}

bool colorEnRango(RGBApixel color){
    return color.Red >= 0 && color.Red <= 255 && color.Green >= 0 && color.Green <= 255 && color.Blue >= 0 && color.Blue <= 255;
}

bool pixelEnRango(int px, int py, Coordenada imgSize){
    return px >= 0 && px < imgSize.getCoordenadaX() && py >= 0 && py < imgSize.getCoordenadaY();
}

// bool colorDisponible(RGBApixel color, MapaColores mapa){
//     for(MapaColores::iterator it = mapa.begin(); it != mapa.end(); ++it){
//         if(coloresSonIguales(it->second, color)){
//             return false;
//         }
//     }
//     return true;
// }


int pixelSizeGet(RGBApixel color){
    int resultado = (coloresSonIguales(color, AGUA))? 2:8;
    resultado = (coloresSonIguales(color, FUEGO))? 7:resultado;
    resultado = (coloresSonIguales(color, AGUA_OSCURA) || coloresSonIguales(color, BORDE) || coloresSonIguales(color, MINA))? 3:resultado;
    resultado = (coloresSonIguales(color, ARENA) || coloresSonIguales(color, ARENA_OSCURA) || coloresSonIguales(color, TIERRA) || coloresSonIguales(color, TIERRA_OSCURA) || coloresSonIguales(color, PASTO))? 6:resultado;
    return resultado;
}

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize, int pixelSize){
    bool resultado = false;
    if(pixelEnRango(pixelPos.getCoordenadaX() + pixelSize, pixelPos.getCoordenadaY() + pixelSize, imgSize) && 
        pixelEnRango(pixelPos.getCoordenadaX() - pixelSize, pixelPos.getCoordenadaY() - pixelSize, imgSize) && 
        pixelEnRango(pixelPos.getCoordenadaX() + pixelSize, pixelPos.getCoordenadaY() + pixelSize, imgSize) && 
        pixelEnRango(pixelPos.getCoordenadaX() - pixelSize, pixelPos.getCoordenadaY() - pixelSize, imgSize)){
        resultado = true;
    }
    return resultado;
}

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize){
    /*Coordenada pixelPos;
    pixelPos.x = pixelPosBB.getCoordenadaX();
    pixelPos.y = pixelPosBB.getCoordenadaY();
    pixelPos.z = pixelPosBB.getCoordenadaZ();*/
    

    int pixelSize = pixelSizeGet(color);
    for(int i = 0; i < pixelSize; i++){
        for(int j = 0; j < pixelSize; j++){
            if(pixelSizeEnRango(pixelPos, imgSize, pixelSize) && !coloresSonIguales(color, BLANCO)){
                    image->SetPixel(pixelPos.getCoordenadaX() + i, pixelPos.getCoordenadaY() + j, color);
                    image->SetPixel(pixelPos.getCoordenadaX() - i, pixelPos.getCoordenadaY() + j, color);
                    image->SetPixel(pixelPos.getCoordenadaX() + i, pixelPos.getCoordenadaY() - j, color);
                    image->SetPixel(pixelPos.getCoordenadaX() - i, pixelPos.getCoordenadaY() - j, color);
            }
        }
    }
}

Coordenada getPixelOffset(int lado, int size){
    Coordenada pixelOffset;
    pixelOffset.setCoordenadaX((lado == IZQUIERDA)? size*5 : (lado == DERECHA)? size*43 : size*55);
    pixelOffset.setCoordenadaY((lado == IZQUIERDA)? size*37 : (lado == DERECHA)? size*31 : size*38);
    return pixelOffset;
}

RGBApixel codigoColorSegunCelda(Capa capaCelda){
    RGBApixel codigoColor;
    switch (capaCelda)
    {
    case CAPA_ARENA:
        codigoColor=ARENA;
        break;
    case CAPA_AGUA:
        codigoColor=AGUA;
        break;
    case CAPA_PASTO:
        codigoColor=PASTO;
        break;
    case CAPA_TIERRA:
        codigoColor=TIERRA;
        break;
    case CAPA_BORDE:
        codigoColor=BORDE;
        break;
    case CAPA_MINA:
        codigoColor=MINA;
        break;
    case CAPA_FUEGO:
        codigoColor=FUEGO;
        break;
    case FICHA_JUGADOR:
        codigoColor=JUGADOR;
        break;
    default:
        codigoColor=MINA;
        break;
    }
    return codigoColor;
}

bool capaExiste(Capa capaCelda){
    if(capaCelda == CAPA_ARENA || capaCelda == CAPA_AGUA || capaCelda == CAPA_PASTO || capaCelda == CAPA_TIERRA ||capaCelda == FICHA_MINA 
       || capaCelda == CAPA_BORDE || capaCelda == CAPA_MINA || capaCelda == CAPA_FUEGO || capaCelda == FICHA_JUGADOR){
        return true;
    }
    return false;
}

RGBApixel getColor(Celda celda, bool esFicha){
    RGBApixel colorAux = (esFicha)? JUGADOR : BLANCO;
    if(coloresSonIguales(colorAux, BLANCO)){
        colorAux = (capaExiste(celda.getTipo()))? codigoColorSegunCelda(celda.getTipo()) : colorAux;
    }
    return colorAux;
}

void getAux(int lado, Coordenada* aux){
    int valor = (lado == ATRAS) ? -1 : 1;
    aux->setCoordenadaX(valor);
    aux->setCoordenadaY(valor);
    aux->setCoordenadaZ(valor);
}

void getPixel(CoordenadaDouble* pixel, Coordenada matrixPos){



    pixel->setCoordenadaX((double)matrixPos.getCoordenadaX());
    pixel->setCoordenadaY((double)matrixPos.getCoordenadaY());
    pixel->setCoordenadaZ((double)matrixPos.getCoordenadaZ());
}

int matrixPosStarter(int lado, int size){
    return (lado == IZQUIERDA)? 0 : (lado == DERECHA)? 0 : size-1;
}

void imprimirBMP(Coordenada imgSize, BMP* image, Tablero<Celda*>* tablero, int jugador){
    RGBApixel color;
    int i = 0;
    Coordenada pixelPos, matrixPos, aux, pixelOffset;
    CoordenadaDouble pixel;
    bool esFicha = false;
    for(int lado = 0; lado < 3; lado ++){
        getAux(lado, &aux);
        pixelOffset = getPixelOffset(lado, tablero->getTamanioX());

        matrixPos.setCoordenadaX(matrixPosStarter(lado, tablero->getTamanioX()));
        matrixPos.setCoordenadaY(matrixPosStarter(lado, tablero->getTamanioY()));
        matrixPos.setCoordenadaZ(matrixPosStarter(lado, tablero->getTamanioZ()));

        while (matrixPos.getCoordenadaX() < tablero->getTamanioX() && matrixPos.getCoordenadaX() >= 0) {
            while (matrixPos.getCoordenadaY() < tablero->getTamanioY() && matrixPos.getCoordenadaY() >= 0) {
                while (matrixPos.getCoordenadaZ() < tablero->getTamanioZ() && matrixPos.getCoordenadaZ() >= 0) {
                    getPixel(&pixel, matrixPos);
                    aplicarProyeccionIsometrica(&pixel, lado);
                    pixelPos.setCoordenadaX(static_cast<int>((pixel.getCoordenadaX()) * 20 + pixelOffset.getCoordenadaX())); 
                    pixelPos.setCoordenadaY(static_cast<int>((pixel.getCoordenadaY()) * 20 + pixelOffset.getCoordenadaY()));
                    esFicha = (tablero->getTData(matrixPos.getCoordenadaX(), matrixPos.getCoordenadaY(), matrixPos.getCoordenadaZ())->getFicha()->getJugadorOwner() == jugador && tablero->getTData(matrixPos.getCoordenadaX(), matrixPos.getCoordenadaY(), matrixPos.getCoordenadaZ())->getFicha()->getTipo() != MINA_FICHA);
                    color = getColor(*tablero->getTData(matrixPos.getCoordenadaX(), matrixPos.getCoordenadaY(), matrixPos.getCoordenadaZ()), esFicha);
                    pintarEntidad(image, pixelPos, color, imgSize);
                    matrixPos.setCoordenadaZ(matrixPos.getCoordenadaZ() + aux.getCoordenadaZ());
                }
                matrixPos.setCoordenadaZ(matrixPosStarter(lado, tablero->getTamanioZ()));
                matrixPos.setCoordenadaY(matrixPos.getCoordenadaY() + aux.getCoordenadaY());
            }
            matrixPos.setCoordenadaY(matrixPosStarter(lado, tablero->getTamanioY()));
            matrixPos.setCoordenadaX(matrixPos.getCoordenadaX() + aux.getCoordenadaX());
        }
    }
}