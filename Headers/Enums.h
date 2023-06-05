#ifndef __ENUMS_H__
#define __ENUMS_H__

//fichas
enum TipoContenido {
    SOLDADO, 
    TANQUE, 
    BARCO, 
    SUBMARINO, 
    AVION, 
    MINA_FICHA, 
    CARTA, 
    VACIO
};

//cartas
enum TipoCarta {
    AVION_RADAR,
    BARCO_MISIL, 
    ATAQUE_QUIMICO, 
    BOMBARDEO, 
    OMITIR_TURNO, 
    ESCUDO
};

//celdas
enum Capa {
    CAPA_ARENA,
    CAPA_AGUA, 
    CAPA_TIERRA, 
    CAPA_PASTO, 
    CAPA_BORDE, 
    CAPA_MINA, 
    CAPA_FUEGO, 
    CAPA_AIRE
};

//lista
enum Iteracion {
    SIGUIENTE, 
    FINAL, 
    ANTERIOR
};



#endif