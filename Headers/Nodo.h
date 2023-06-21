#ifndef __NODO_H__
#define __NODO_H__

template <class T> class Nodo{
private:
    T data;
    Nodo<T>* sig;
    Nodo<T>* ant;

public:

    // PRE: Recibe un dato generico
    // POST: Construye un nodo con el dato recibido
    Nodo(T data);
    
    // PRE: Devuelve el dato guardado en el nodo
    T getNData();
    
    // PRE: Recibe un dato generico
    // POST: Setea el dato del nodo
    void setNData(T data);
    
    // POST: Devuelve el nodo siguiente
    Nodo<T>* next();

    // POST: Devuelve el nodo anterior
    Nodo<T>* prev();

    // POST: Linkea el nodo siguiente al puntero
    void setSig(Nodo<T>* sig);

    // POST: Linkea el nodo anterior al puntero
    void setAnt(Nodo<T>* ant);
};
#include "../TPPs/Nodo.tpp"
#endif