#ifndef __MINA_H__
#define __MINA_H__
enum tipoMina {MINA_TERRESTRE, MINA_AEREA, MINA_MARITIMA, INEXISTENTE};

class Mina {
    private:
        bool activa;
        tipoMina tipo;
    public:
        Mina();
        bool getMinaActiva();
        tipoMina getTipoMina();
        void setMinaActiva(bool estado);
        void setTipoMina(tipoMina tipo);
};

#endif