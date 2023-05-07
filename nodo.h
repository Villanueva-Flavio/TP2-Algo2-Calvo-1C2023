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

template <class T> Nodo<T>::Nodo(T data){
    this->data = data;
    this->sig = NULL;
    this->ant = NULL;
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

template <class T> Nodo<T>* Nodo<T>::prev(){
    return this->ant;
}

template <class T> void Nodo<T>::setSig(Nodo<T>* sig) {
    this->sig = sig;
}

template <class T> void Nodo<T>::setAnt(Nodo<T>* ant) {
    this->ant = ant;
}

#endif