#ifndef __LISTA_H__
#define __LISTA_H__
#include <iostream>
#include "nodo.h"

enum Iteracion {SIGUIENTE, FINAL, ANTERIOR};

template <class T> class Lista {
private:
	Nodo<T>* primero;
	Nodo<T>* iterador;
	int size;
	int iteracion;
public: 

	// Constructor de lista vacia.
	Lista();

	// Destructor de ultimo elemento de lista
	~Lista();

	// Recibe un dato
	// Y lo asigna al nodo del iterador
	void assign(T data);

	// Recibe el tipo de iteracion
	// Itera la lista una vez, o hasta el final
	void iterar(Iteracion iteracion);

	// Reinicia el iterador en la primer posicion
	void resetIter();

	// Obtiene el dato del nodo del iterador
	T getLData(int x);

	// Crea un nuevo nodo al final de la lista
	void add(T data);

	// Obtiene la posicion del iterador
	int getIter();

	// Obtiene el tamaño de la lista
	int getSize();

	void irANodo(int x);
};
#include "./tpps/lista.tpp"
#endif