#include <iostream>
#include "./Nodo.h"
#include "./Enums.h"

#ifndef __LISTA_H__
#define __LISTA_H__

template <class T> class Lista {
private:
	Nodo<T>* primero;
	Nodo<T>* iterador;
	int size;
	int iteracion;
	
public: 

	Lista();

	~Lista();

	// PRE: Recibe un entero positivo
	// POST: Itera el cursor de la lista hasta el entero recibido
	void irANodo(int x);	

	// PRE: Recibe el tipo de iteracion
	// POST: Itera la lista una vez, o hasta el final
	void iterar(Iteracion iteracion);

	// POST: Reinicia el iterador en la primer posicion
	void resetIter();

	// PRE: Recibe un dato generico
	// POST: Y lo asigna al nodo del iterador
	void assign(T data);

	// POST: Devuelve el nodo del iterador
	Nodo<T>* getNodo();

	// PRE: Recibe un entero positivo
	// POST: Obtiene el dato del nodo del iterador
	T getLData(int x);

	// PRE: Recibe un dato generico
	// POST: Crea un nuevo nodo al final de la lista
	void add(T data);

	// POST: Obtiene la posicion del iterador
	int getIter();

	// POST: Obtiene el tamaño de la lista
	int getSize();

};
#include "../TPPs/Lista.tpp"
#endif