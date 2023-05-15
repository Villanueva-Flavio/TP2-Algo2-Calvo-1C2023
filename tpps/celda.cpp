Celda::Celda() {
    this->tipo = AIRE;
    this->estado = true;
    this->ficha = Ficha();
}

bool Celda::getEstado() {
    return this->estado;
}

void Celda::setEstado(bool estado) {
    this->estado = estado;
}

TipoCelda Celda::getTipo() {
    return this->tipo;
}

void Celda::setTipo(TipoCelda elemento) {
    this->tipo = elemento;
}

Ficha Celda::getFicha() {
    return this->ficha;
}