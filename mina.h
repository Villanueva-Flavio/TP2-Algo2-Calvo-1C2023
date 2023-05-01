class Mina{

    private:

        char estado;    //mina (c)olocada - casilla (i)nactiva - mina - (e)liminada


    public:

        // Constructor
        Mina();

        // Getter del estado
        char obtenerEstado() const;

        // Setter del estado
        void cambiarEstado(char nuevoEstado);

}