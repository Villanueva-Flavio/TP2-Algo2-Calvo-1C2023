#ifndef __COORDENADAS_DOUBLE_NEW_H__
#define __COORDENADAS_DOUBLE_NEW_H__

class CoordenadaDouble{
    private:
        double coordX, coordY, coordZ;

    public:
        //post: inicializa las coordenadas en el origen
        CoordenadaDouble();

        //pre: 'x' debe esta inicializado
        //post: asigna el valor recibido a 'coordX'
        void setCoordenadaX(double x);

        //pre: 'y' debe esta inicializado
        //post:asigna el valor recibido a 'coordY'
        void setCoordenadaY(double y);

        //pre: 'z' debe esta inicializado
        //post: asigna el valor recibido a 'coordZ'
        void setCoordenadaZ(double z);

        //post: devuelve coordX
        double getCoordenadaX();

        //post: devuelve coordX
        double getCoordenadaY();

        //post: devuelve coordX
        double getCoordenadaZ();
};



#endif 