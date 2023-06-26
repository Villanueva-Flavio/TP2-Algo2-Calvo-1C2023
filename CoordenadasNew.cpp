#include "CoordenadasNew.h"

CoordenadaNew::CoordenadaNew(){
    this->coordX = 0;
    this->coordY = 0;
    this->coordZ = 0;
}

void CoordenadaNew::setCoordenadaX(int x){
    this->coordX = x;
}

void CoordenadaNew::setCoordenadaY(int y){
    this->coordY = y;
}

void CoordenadaNew::setCoordenadaZ(int z){
    this->coordZ = z;
}

int CoordenadaNew::getCoordenadaX(){
    return this->coordX;
}

int CoordenadaNew::getCoordenadaY(){
    return this->coordY;
}

int CoordenadaNew::getCoordenadaZ(){
    return this->coordZ;
}