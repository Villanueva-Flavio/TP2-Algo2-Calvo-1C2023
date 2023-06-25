#include "Coordenadas.h"

Coordenada::Coordenada(){
    this->coordX = 0;
    this->coordY = 0;
    this->coordZ = 0;
    this->coordXDouble = 0;
    this->coordYDouble = 0;
    this->coordZDouble = 0;
}

void Coordenada::setCoordenadaX(int x){
    this->coordX = x;
}

void Coordenada::setCoordenadaY(int y){
    this->coordY = y;
}

void Coordenada::setCoordenadaZ(int z){
    this->coordZ = z;
}

void Coordenada::setCoordenadaXDouble(double x){
    this->coordXDouble = x;
}

void Coordenada::setCoordenadaYDouble(double y){
    this->coordYDouble = y;
}

void Coordenada::setCoordenadaZDouble(double z){
    this->coordZDouble = z;
}

int Coordenada::getCoordenadaX(){
    return this->coordX;
}

int Coordenada::getCoordenadaY(){
    return this->coordY;
}

int Coordenada::getCoordenadaZ(){
    return this->coordZ;
}

double Coordenada::getCoordenadaXDouble(){
    return this->coordXDouble;
}

double Coordenada::getCoordenadaYDouble(){
    return this->coordYDouble;
}

double Coordenada::getCoordenadaZDouble(){
    return this->coordZDouble;
}