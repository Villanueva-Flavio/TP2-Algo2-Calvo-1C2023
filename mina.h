#ifndef MINA_H
#define MINA_H

enum EstadoMina { COLOCADA, CASILLA_INACTIVA, ELIMINADA };

class Mina{

    private:

        EstadoMina estado;


    public:

        // Constructor
        Mina();

        // Devuelve el estado
        char getEstado() const;

        // Cambia el estado
        void setEstado(EstadoMina nuevoEstado);


        // Cambia el estado a 'colocar'
        void colocar();


        // Cambia el estado a 'casilla_inactiva'
        void explotar();


        // Cambia el estado a 'eliminada'
        void eliminar();
};

#endif // MINA_H