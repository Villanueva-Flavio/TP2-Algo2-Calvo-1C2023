#ifndef __COORDENADAS_H__
#define __COORDENADAS_H__

class Coordenada{
    private:
        int coordX,coordY,coordZ;

    public:
        //post: inicializa las coordenadas en el origen
        Coordenada();

        //pre: 'x' debe estar inicializado
        //post: asigna el valor recibido a 'coordX'
        void setCoordenadaX(int x);

        //pre: 'y' debe estar inicializado
        //post: asigna el valor recibido a 'coordY'
        void setCoordenadaY(int y);

        //pre: 'z' debe estar inicializado
        //post: asigna el valor recibido a 'coordZ'
        void setCoordenadaZ(int z);

        //pre: 'x', 'y' y 'z' deben estar inicializados
        //post: asigna los valores recibidos a 'coordX', 'coordY' y 'coordZ'
        void setCoordenadas(int x, int y, int z);

        //post: devuelve coordX
        int getCoordenadaX();
        
        //post: devuelve coordX
        int getCoordenadaY();

        //post: devuelve coordX
        int getCoordenadaZ();
};

#endif