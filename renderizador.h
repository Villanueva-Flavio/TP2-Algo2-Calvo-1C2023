#include <sstream>
#include <string>
#include <iostream>
#include "./rendererSrc/EasyBMP.h"
#include <map>
#include "tablero.h"
#include "celda.h"

enum Capa {CAPA_ARENA, CAPA_AGUA, CAPA_TIERRA, CAPA_PASTO, CAPA_BORDE, CAPA_MINA, CAPA_FUEGO};
enum Lado {IZQUIERDA, DERECHA, ATRAS};

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
const RGBApixel MINA = {0, 0, 0, 0};
const RGBApixel FUEGO = {12, 92, 232, 0};

struct Coordenada{int x; int y; int z;};
struct CoordenadaDouble{double x; double y; double z;};

typedef std::map<int, RGBApixel> mapaColores;

mapaColores getMap(){
    mapaColores mapa;
    mapa[CAPA_ARENA] = ARENA;
    mapa[CAPA_AGUA] = AGUA;
    mapa[CAPA_PASTO] = PASTO;
    mapa[CAPA_TIERRA] = TIERRA;
    mapa[CAPA_BORDE] = BORDE;
    mapa[CAPA_MINA] = MINA;
    mapa[CAPA_FUEGO] = FUEGO;
    return mapa;
}

double gradosARadianes(double grados){
    return grados * 3.14159 / 180.0;
}

void getAngulos(double angulos[6], Lado lado){
    switch(lado){
        case IZQUIERDA:
            angulos[0] = 40; angulos[1] = 20; angulos[2] = 0; angulos[3] = 30; angulos[4] = -30; angulos[5] = 30;
            break;
        case DERECHA:
            angulos[0] = -40; angulos[1] = 20; angulos[2] = 0; angulos[3] = -30; angulos[4] = 30; angulos[5] = 30;
            break;
        case ATRAS:
            angulos[0] = 40; angulos[1] = 20; angulos[2] = 0; angulos[3] = -30; angulos[4] = 30; angulos[5] = 30;
            break;
    }
}

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, Lado lado){
    double angulos[6];
    getAngulos(angulos, lado);
    pixel->x = gradosARadianes(angulos[0]) * pixel->x + gradosARadianes(angulos[1]) * pixel->y + gradosARadianes(angulos[2]) * pixel->z;
    pixel->y = gradosARadianes(angulos[3]) * pixel->x + gradosARadianes(angulos[4]) * pixel->y + gradosARadianes(angulos[5]) * pixel->z;
}

bool coloresSonIguales(RGBApixel color1, RGBApixel color2){
    return color1.Red == color2.Red && color1.Green == color2.Green && color1.Blue == color2.Blue;
}

bool colorEnRango(RGBApixel color){
    return color.Red >= 0 && color.Red <= 255 && color.Green >= 0 && color.Green <= 255 && color.Blue >= 0 && color.Blue <= 255;
}

bool pixelEnRango(int px, int py, Coordenada imgSize){
    return px >= 0 && px < imgSize.x && py >= 0 && py < imgSize.y;
}

bool colorDisponible(RGBApixel color, mapaColores mapa){
    for(mapaColores::iterator it = mapa.begin(); it != mapa.end(); ++it){
        if(coloresSonIguales(it->second, color)){
            return false;
        }
    }
    return true;
}

void setPlayerColor(RGBApixel* color, int jugador, mapaColores& mapa){
    std::cout << "Ingrese el color del jugador en formato R G B (0 a 255): " << std::endl;
    std::cin >> color->Red >> color->Green >> color->Blue;
    while(!colorEnRango(*color) || !colorDisponible(*color, mapa)){
        std::cout << (colorEnRango(*color)? "Color no disponible" : "Color fuera de rango") << std::endl;
        std::cout << "Ingrese el color del jugador R G B (0 a 255): " << std::endl;
        std::cin >> color->Red >> color->Green >> color->Blue;
    }
    mapa[static_cast<Capa>(jugador)] = *color;
}

int pixelSizeGet(RGBApixel color){
    int resultado = (coloresSonIguales(color, AGUA))? 2:8;
    resultado = (coloresSonIguales(color, FUEGO))? 7:resultado;
    resultado = (coloresSonIguales(color, AGUA_OSCURA) || coloresSonIguales(color, BORDE) || coloresSonIguales(color, MINA))? 3:resultado;
    resultado = (coloresSonIguales(color, ARENA) || coloresSonIguales(color, ARENA_OSCURA) || coloresSonIguales(color, TIERRA) || coloresSonIguales(color, TIERRA_OSCURA) || coloresSonIguales(color, PASTO))? 6:resultado;
    return resultado;
}

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize){
    bool resultado = false;
    if(pixelEnRango(pixelPos.x + 1, pixelPos.y, imgSize) && 
        pixelEnRango(pixelPos.x - 1, pixelPos.y, imgSize) && 
        pixelEnRango(pixelPos.x, pixelPos.y + 1, imgSize) && 
        pixelEnRango(pixelPos.x, pixelPos.y - 1, imgSize)){
        resultado = true;
    }
    return resultado;
}

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize){
    int pixelSize = pixelSizeGet(color);
    for(int i = 0; i < pixelSize; i++){
        for(int j = 0; j < pixelSize; j++){
            if(pixelSizeEnRango(pixelPos, imgSize) && !rgbaIg(color, BLANCO)){
                    image->SetPixel(pixelPos.x + i, pixelPos.y + j, color);
                    image->SetPixel(pixelPos.x - i, pixelPos.y + j, color);
                    image->SetPixel(pixelPos.x + i, pixelPos.y - j, color);
                    image->SetPixel(pixelPos.x - i, pixelPos.y - j, color);
            }
        }
    }
}

Coordenada getPixelOffset(Lado lado, int size){
    Coordenada pixelOffset;
    pixelOffset.x = (lado == IZQUIERDA)? size*5 : (lado == DERECHA)? size*45 : size*55;
    pixelOffset.y = (lado == IZQUIERDA)? size*37 : (lado == DERECHA)? size*30 : size*37;
    return pixelOffset;
}

void imprimirAngulo(Lado lado, Coordenada imgSize, BMP* image, Tablero<Celda> tablero){
    
    RGBApixel color;
    Coordenada pixelOffset = getPixelOffset(lado, size), matrixPos;

    for (matrixPos.x = size; matrixPos.x > 0; matrixPos.x--) {
        for (matrixPos.y = size; matrixPos.y > 0; matrixPos.y--) {
            for (matrixPos.z = size; matrixPos.z > 0; matrixPos.z--){
                CoordenadaDouble pixel = {matrixPos.x, matrixPos.y, matrixPos.z};
                aplicarProyeccionIsometrica(&pixel, lado);
                Coordenada pixelPos = {static_cast<int>(pixel.x * 20 + pixelOffset.x), static_cast<int>(pixel.y * 20 + pixelOffset.y)};
                getColor(matrixPos, &color, capa);
                pintarEntidad(image, pixelPos, color, imgSize);
            }
        }
    }

}