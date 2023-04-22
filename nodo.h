#ifndef __NODO_H__
#define __NODO_H__

template <class T> class Nodo{
private:
    T data;
    Nodo<T>* sig;

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

    // Linkea el nodo siguiente al puntero
    void setSig(Nodo<T>* sig);
};

template <class T> Nodo<T>::Nodo(T data){
    this->data = data;
    this->sig = NULL;
}

template <class T> T Nodo<T>::getNData(){
    return this->data;
}

template <class T> void Nodo<T>::setNData(T data){
    this->data = data;
}

template <class T> Nodo<T>* Nodo<T>::next(){
    return this->sig;
}

template <class T> void Nodo<T>::setSig(Nodo<T>* sig) {
    this->sig = sig;
}

#endif