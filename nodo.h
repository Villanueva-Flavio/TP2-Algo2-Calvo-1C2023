#ifndef __NODO_H__
#define __NODO_H__

template <class T> class Nodo{
private:
    T data;
    Nodo<T>* sig;
    Nodo<T>* ant;

public:

    // Constructor de nodo:
    // Crea el nodo con el dato del parametro
    Nodo(T data);
    
    // Devuelve el dato guardado en el nodo
    T getNData();
    
    // Cambia el dato guardado en el nodo por el del parametro
    void setNData(T data);
    
    // Devuelve el nodo siguiente
    Nodo<T>* next();

    // Devuelve el nodo anterior
    Nodo<T>* prev();

    // Linkea el nodo siguiente al puntero
    void setSig(Nodo<T>* sig);

    void setAnt(Nodo<T>* ant);
};

#endif