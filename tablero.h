#ifndef __TABLERO_H__
#define __TABLERO_H__
#include "lista.h"

template <class T> class Tablero {
    private:
        Lista<Lista<Lista<T>*>*>* cubo;
        int x, y, z;
        void setCoordenada(int n, int m, int l);
        
    public:

        // Constructor de tablero vacio de nxmxl celdas
        Tablero(int n, int m, int l);

        // Destructor que elimina todo el tablero
        ~Tablero();

        // Recibe un dato y lo carga en la celda especificada
        void setTData(int n, int m, int l, T data);

        // Obtiene el dato de la celda especificada
        T getTData(int n, int m, int l);

        int getTamanioX();

        int getTamanioY();

        int getTamanioZ();
        
        bool inRange(int n, int m, int l);
};
#include "./tpps/tablero.tpp"
#endif