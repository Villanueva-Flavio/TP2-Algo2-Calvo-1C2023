#ifndef __TABLERO_H__
#define __TABLERO_H__
#include "Lista.h"

template <class T> class Tablero {
    private:
        Lista<Lista<Lista<T>*>*>* cubo;
        int x, y, z;
        
    public:

        // PRE: Recibe 3 enteros positivos
        // POST: Construye un Tablero con las dimensiones especificadas
        Tablero(int n, int m, int l);

        ~Tablero();

        // PRE: Recibe 3 enteros positivos como Coordenada y el dato
        // POST: Setea el dato en la celda especificada
        void setTData(int n, int m, int l, T data);

        // PRE: Recibe 3 enteros positivos como Coordenada
        // POST: Devuelve el dato de la celda especificada
        T getTData(int n, int m, int l);

        //PRE: Devuelve el tamanio del tablero en X
        int getTamanioX();

        //PRE: Devuelve el tamanio del tablero en Y
        int getTamanioY();

        //PRE: Devuelve el tamanio del tablero en Z
        int getTamanioZ();
        
        //PRE: Recibe 3 enteros positivos como Coordenada
        //POST: Devuelve true si la coordenada esta dentro del tablero
        bool inRange(int n, int m, int l);
        
    private:

        //PRE: Recibe 3 enteros positivos como Coordenada
        //POST: Setea la coordenada
        void setCoordenada(int n, int m, int l);
};
#include "../TPPs/Tablero.tpp"
#endif