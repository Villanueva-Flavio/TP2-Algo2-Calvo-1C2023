#include "CoordenadasDoubleNew.h"

CoordenadaDoubleNew::CoordenadaDoubleNew(){
    this->coordX = 0;
    this->coordY = 0;
    this->coordZ = 0;
}

void CoordenadaDoubleNew::setCoordenadaX(double x){
    this->coordX = x;
}

void CoordenadaDoubleNew::setCoordenadaY(double y){
    this->coordY = y;
}

void CoordenadaDoubleNew::setCoordenadaZ(double z){
    this->coordZ = z;
}

double CoordenadaDoubleNew::getCoordenadaX(){
    return this->coordX;
}

double CoordenadaDoubleNew::getCoordenadaY(){
    return this->coordY;
}

double CoordenadaDoubleNew::getCoordenadaZ(){
    return this->coordZ;
}