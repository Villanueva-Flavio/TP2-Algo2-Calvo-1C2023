#include "CoordenadasDouble.h"

CoordenadaDouble::CoordenadaDouble(){
    this->coordX = 0;
    this->coordY = 0;
    this->coordZ = 0;
}

void CoordenadaDouble::setCoordenadaX(double x){
    this->coordX = x;
}

void CoordenadaDouble::setCoordenadaY(double y){
    this->coordY = y;
}

void CoordenadaDouble::setCoordenadaZ(double z){
    this->coordZ = z;
}

double CoordenadaDouble::getCoordenadaX(){
    return this->coordX;
}

double CoordenadaDouble::getCoordenadaY(){
    return this->coordY;
}

double CoordenadaDouble::getCoordenadaZ(){
    return this->coordZ;
}