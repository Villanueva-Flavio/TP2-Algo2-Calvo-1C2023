#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include <map>
#include "celda.h"
#include "./rendererSrc/EasyBMP.h"
enum Lado {IZQUIERDA, DERECHA, ATRAS};
enum Capa {CAPA_ARENA, CAPA_AGUA, CAPA_TIERRA, CAPA_PASTO, CAPA_BORDE, CAPA_MINA, CAPA_FUEGO};
struct Coordenada{int x; int y; int z;};
struct CoordenadaDouble{double x; double y; double z;};

typedef std::map<int, RGBApixel> MapaColores;
typedef Tablero<Celda> Mapa;

MapaColores getMap();

double gradosARadianes(double grados);

void getAngulos(double angulos[6], Lado lado);

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, Lado lado);

bool coloresSonIguales(RGBApixel color1, RGBApixel color2);

bool colorEnRango(RGBApixel color);

bool pixelEnRango(int px, int py, Coordenada imgSize);

bool colorDisponible(RGBApixel color, MapaColores mapa);

void setPlayerColor(RGBApixel* color, int jugador, MapaColores& mapa);

int pixelSizeGet(RGBApixel color);

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize);

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize);

Coordenada getPixelOffset(Lado lado, int size);

RGBApixel getColor(Celda celda, MapaColores colores);

void imprimirAngulo(Lado lado, Coordenada imgSize, BMP* image, Mapa tablero, MapaColores colores);

#endif