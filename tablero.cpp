#include "tablero.h"

template <class T> Tablero<T>::Tablero(int n, int m, int l) {
    this->x = n, this->y = m, this->z = l;
    cubo = new Lista<Lista<Lista<T>*>*>();
    for (int i = 0; i < n; i++) {
        Lista<Lista<T>*>* plano = new Lista<Lista<T>*>();
        for (int j = 0; j < m; j++) {
            Lista<T>* fila = new Lista<T>();
            for (int k = 0; k < l; k++) {
                fila->add(T());
            }
            plano->add(fila);
        }
        cubo->add(plano);
    }
}

template <class T> Tablero<T>::~Tablero() {
    cubo->resetIter();
    int a = this->y, b = this->z;
    for (int i = 0; i < a; i++) {
        cubo->getLData(i)->resetIter();
        for (int j = 0; j < b; j++) {
            cubo->getLData(i)->getLData(j)->resetIter();
            delete cubo->getLData(i)->getLData(j);
        }
        delete cubo->getLData(i);
    }
    this->x = 0, this->y = 0, this->z = 0;
    delete cubo;
}

template <class T> int Tablero<T>::getTamanioX() {
    return this->x;
}

template <class T> int Tablero<T>::getTamanioY() {
    return this->y;
}

template <class T> int Tablero<T>::getTamanioZ() {
    return this->z;
}

template <class T> void Tablero<T>::setTData(int n, int m, int l, T data){
    setCoordenada(n, m, l);
    this->cubo->getLData(n)->getLData(m)->getLData(l)->setNData(data);
}

template <class T> T Tablero<T>::getTData(int n, int m, int l){
    setCoordenada(n, m, l);
    return this->cubo->getLData(n)->getLData(m)->getLData(l);
}

template <class T> void Tablero<T>::setCoordenada(int n, int m, int l){
    this->cubo->irANodo(n);
    this->cubo->getLData(m)->irANodo(m);
    this->cubo->getLData(m)->getLData(m)->irANodo(l);
}

template <class T> bool Tablero<T>::inRange(int n, int m, int l) {
    return (n >= 0 && n < this->x && m >= 0 && m < this->y && l >= 0 && l < this->z);
}