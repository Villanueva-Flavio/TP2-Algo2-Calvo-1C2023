#include <sstream>
#include <string>
#include <iostream>
#include "EasyBMP.h"
#include <map>
#include <cmath>
#define SIZE 30
int matrix[SIZE][SIZE][SIZE];

// BLUE - GREEN - RED - ALPHA -------- BLUE Y RED ESTAN AL REVES
enum Modo {MATRIZ, LISTA_ENLAZADA, LISTA_DOBLEMENTE_ENLAZADA};
enum Capa {CAPA_ARENA, CAPA_AGUA, CAPA_TIERRA, CAPA_PASTO, CAPA_BORDE, CAPA_MINA, CAPA_FUEGO};

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

struct Coordenada{
    int x;
    int y;
    int z;
};

struct pixelCoord{
    double x;
    double y;
    double z;
};

typedef std::map<Capa, RGBApixel> mapaColores;

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

void aplicarProyeccionIsometrica(pixelCoord* pixel, int angulo){
    int a, b, c, d, e, f;
    switch(angulo){
        case 1:
            a = 40; b = 20; c = 0; d = 30; e = -30; f = 30;
            break;
        case 2:
            a = -40; b = 20; c = 0; d = -30; e = 30; f = 30;
            break;
        case 3:
            a = 40; b = 20; c = 0; d = -30; e = 30; f = 30;
            break;
    }
    pixel->x = gradosARadianes(a) * pixel->x + gradosARadianes(b) * pixel->y + gradosARadianes(c) * pixel->z;
    pixel->y = gradosARadianes(d) * pixel->x + gradosARadianes(e) * pixel->y + gradosARadianes(f) * pixel->z;
}

bool rgbaIg(RGBApixel color1, RGBApixel color2){
    return color1.Red == color2.Red && color1.Green == color2.Green && color1.Blue == color2.Blue;
}

bool colorEnRango(RGBApixel rgba){
    return (rgba.Red >= 0 && rgba.Red <= 255) && (rgba.Green >= 0 && rgba.Green <= 255) && (rgba.Blue >= 0 && rgba.Blue <= 255);
}

bool pixelEnRango(int x, int y, Coordenada imgSize){
    return (x >= 0 && x < imgSize.x) && (y >= 0 && y < imgSize.y);
}

bool colorDisponible(RGBApixel rgba, mapaColores& mapa){
    bool resultado = true;
    for(mapaColores::iterator it = mapa.begin(); it != mapa.end(); ++it){
        if(rgbaIg(rgba, it->second)){
            resultado = false;
            break;
        }
    }       
    return resultado;
}

void setPlayerColor(RGBApixel* rgba, int jugador, mapaColores& mapa){ // requiere mapa de colores
    std::cout << "Ingrese el color del jugador R G B (0 a 255): " << std::endl;
    std::cin >> rgba->Red >> rgba->Green >> rgba->Blue;   
    while(!colorEnRango(*rgba) || !colorDisponible(*rgba, mapa)){
        std::cout << (colorEnRango(*rgba) ? "Color no disponible" : "Color fuera de rango") << std::endl;
        std::cout << "Ingrese el color del jugador R G B (0 a 255): " << std::endl;
        std::cin >> rgba->Red >> rgba->Green >> rgba->Blue;
    }
    mapa[static_cast<Capa>(jugador)] = *rgba;
}

bool esBorde(int x, int y, int z, bool frente){
    bool esBorde;
    bool a = (x == 1 || x == SIZE ); // FRENTE IZQ || FONDO DER
    bool b = (y == 1 || y == SIZE ); // FONDO IZQ || FRENTE DER
    bool c = (z == 1 || z == SIZE ); // TOP || BOT

    esBorde = ((a && b && c) || (a && b) || (a && c) || (b && c) );
    if(frente){
        esBorde = (y == 1 && z == SIZE)? false : esBorde;
        esBorde = (x == SIZE && z == SIZE)? false : esBorde;
        esBorde = (x == SIZE && y == 1)? false : esBorde;
    }
    return esBorde;
}

void setColor(Coordenada pos, RGBApixel* rgba, Capa capa){ // PLAYA
    *rgba = BLANCO;
    if(capa == CAPA_ARENA){
        *rgba = (pos.x < pos.z - 4) ? ARENA : BLANCO;
        if (pos.z == (SIZE/2)+1 && rgbaIg(*rgba, ARENA)) {
            *rgba = ARENA_OSCURA;
        }
    }
    if(rgbaIg(*rgba, BLANCO) && capa == CAPA_AGUA){
        *rgba = (pos.x >= pos.z - 4) ? AGUA : BLANCO;
        *rgba = (esBorde(pos.x, pos.y, pos.z, false) && rgbaIg(*rgba, AGUA))? AGUA_OSCURA : *rgba;
    }
    *rgba = (pos.z > (SIZE / 2))? *rgba : BLANCO;
    if(capa == CAPA_BORDE){
        *rgba = (esBorde(pos.x, pos.y, pos.z, true) && capa == CAPA_BORDE)? BORDE : *rgba;
    }
}

int pixelSizeGet(RGBApixel color){
    int resultado = (rgbaIg(color, AGUA))? 2:8;
    resultado = (rgbaIg(color, FUEGO))? 7:resultado;
    resultado = (rgbaIg(color, AGUA_OSCURA) || rgbaIg(color, BORDE) || rgbaIg(color, MINA))? 3:resultado;
    resultado = (rgbaIg(color, ARENA) || rgbaIg(color, ARENA_OSCURA) || rgbaIg(color, TIERRA) || rgbaIg(color, TIERRA_OSCURA) || rgbaIg(color, PASTO))? 6:resultado;
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

bool validarCapa(Capa capa, RGBApixel color){
    mapaColores mapa = getMap();
    for(mapaColores::iterator it = mapa.begin(); it != mapa.end(); ++it){
        if(it->first == capa){
            return true;
        }
    }
    return false;
}

Coordenada getPixelOffset(int angulo){
    Coordenada pixelOffset;
    pixelOffset.x = (angulo == 1)? SIZE*5 : (angulo == 2)? SIZE*45 : SIZE*55;
    pixelOffset.y = (angulo == 1)? SIZE*37 : (angulo == 2)? SIZE*30 : SIZE*37;
    return pixelOffset;
}

void imprimirAngulo(int angulo, Coordenada imgSize, BMP* image, Capa capa){
    
    RGBApixel color;
    Coordenada pixelOffset = getPixelOffset(angulo), matrixPos;

    for (matrixPos.x = SIZE; matrixPos.x > 0; matrixPos.x--) {
        for (matrixPos.y = SIZE; matrixPos.y > 0; matrixPos.y--) {
            for (matrixPos.z = SIZE; matrixPos.z > 0; matrixPos.z--){
                pixelCoord pixel = {matrixPos.x, matrixPos.y, matrixPos.z};
                aplicarProyeccionIsometrica(&pixel, angulo);
                Coordenada pixelPos = {static_cast<int>(pixel.x * 20 + pixelOffset.x), static_cast<int>(pixel.y * 20 + pixelOffset.y)};
                setColor(matrixPos, &color, capa);
                pintarEntidad(image, pixelPos, color, imgSize);
            }
        }
    }

}

void pintarBMP(Coordenada imgSize){
    BMP image;
    image.SetSize(SIZE*100, SIZE*70);
    for(int angulo = 1; angulo <= 3; angulo ++){
        imprimirAngulo(angulo, imgSize, &image, CAPA_ARENA);
        imprimirAngulo(angulo, imgSize, &image, CAPA_AGUA);
        imprimirAngulo(angulo, imgSize, &image, CAPA_BORDE);
    }
    image.WriteToFile("Mapa-3-perspectivas.bmp");
    
}

int main(){
    srand(time(NULL));
    Coordenada imgSize = {SIZE*100, SIZE*70};
    pintarBMP(imgSize);

    return 0;
}

