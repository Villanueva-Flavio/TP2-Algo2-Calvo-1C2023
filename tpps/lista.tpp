template <class T> Lista<T>::Lista() {
	this->primero = NULL;
	this->iterador = this->primero;
	this->iteracion = 0;
	this->size = 0;
}

template <class T> Lista<T>::~Lista() {
	Nodo<T>* destructor = this->primero;
	while(this->getSize()>0){
		this->primero = this->primero->next();
		delete destructor;
		destructor = this->primero;
		this->size --;
	}
}

template <class T> void Lista<T>::assign(T data){
	this->iterador->setNData(data);
}

template <class T> void Lista<T>::iterar(Iteracion iteracion){
	if(this->getSize() > 0){
		if(iteracion == SIGUIENTE){
			this->iterador = this->iterador->next();
			this->iteracion++;
		} else if (iteracion == ANTERIOR) {
			this->iterador = this->iterador->prev();
			this->iteracion--;
		} else {
			while (this->iteracion < this->getSize() -1){
				this->iterador = this->iterador->next();
				this->iteracion++;
			}
		}
	}
}

template <class T> void Lista<T>::resetIter() {
	this->iterador = this->primero;
	this->iteracion = 0;
}

template <class T> T Lista<T>::getLData(int x) {
	irANodo(x);
	return this->iterador->getNData();
}

template <class T> void Lista<T>::add(T data) {
	Nodo<T>* nuevo = new Nodo<T>(data);
	iterar(FINAL);
	if(this->getSize() == 0){
		this->primero = nuevo;
		this->iterador = this->primero;
	}else{
		nuevo->setAnt(this->iterador);
		this->iterador->setSig(nuevo);
	}
	this->size++;
}

template <class T> int Lista<T>::getIter() {
	return this->iteracion;
}

template <class T> int Lista<T>::getSize() {
	return this->size;
}

// EDITAR esta aberracion
template <class T> void Lista<T>::irANodo(int x){
	bool inicioMasCerca = (this->getIter() / 2 < x);
    if(x < this->getIter()){
		if(inicioMasCerca){
        	this->resetIter();
			for(int i = this->getIter(); i < x; i++){
				this->iterar(SIGUIENTE);
			}
		} else {
			for(int i = this->getIter(); i > x; i--){
				this->iterar(ANTERIOR);
			}
		}
    } else {
		for(int i = this->getIter(); i < x; i++){
				this->iterar(SIGUIENTE);
		}
	}
}