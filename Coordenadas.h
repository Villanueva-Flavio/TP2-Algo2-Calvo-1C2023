#ifndef __COORDENADAS_H__
#define __COORDENADAS_H__

class Coordenada{
    private:
        int coordX,coordY,coordZ;
        double coordXDouble, coordYDouble, coordZDouble;

    public:
        //post: inicializa las coordenadas en el origen
        Coordenada();

        //pre: 'x' debe esta inicializado
        //post: asigna el valor recibido a 'coordX'
        void setCoordenadaX(int x);

        //pre: 'y' debe esta inicializado
        //post: asigna el valor recibido a 'coordY'
        void setCoordenadaY(int y);

        //pre: 'z' debe esta inicializado
        //post: asigna el valor recibido a 'coordZ'
        void setCoordenadaZ(int z);

        //pre: 'x' debe esta inicializado
        //post: asigna el valor recibido a 'coordXDouble'
        void setCoordenadaXDouble(double xDouble);

        //pre: 'y' debe esta inicializado
        //post:asigna el valor recibido a 'coordYDouble'
        void setCoordenadaYDouble(double yDouble);

        //pre: 'z' debe esta inicializado
        //post: asigna el valor recibido a 'coordZDouble'
        void setCoordenadaZDouble(double zDouble);

        //post: devuelve coordX
        int getCoordenadaX();
        
        //post: devuelve coordX
        int getCoordenadaY();

        //post: devuelve coordX
        int getCoordenadaZ();

        //post: devuelve coordX
        double getCoordenadaXDouble();

        //post: devuelve coordX
        double getCoordenadaYDouble();

        //post: devuelve coordX
        double getCoordenadaZDouble();
};

#endif  //__Coordenadas_h__