#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "tarjeta.hpp"
#include "fecha.hpp"
#include <ostream>

class Pedido_Articulo;
class Usuario_Pedido;

class Pedido{
    public:
        Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha &f = Fecha());

        class Vacio{
            public:
                Vacio(Usuario &u):user(&u){};
                Usuario &usuario() const{ return *user; }
            private:
                Usuario *user;
        };

        class Impostor{
            public:
                Impostor(Usuario &u):user(&u){};
                Usuario &usuario() const{ return *user; }
            private:
                Usuario *user;
        };

        class SinStock{
            public:
                SinStock(Articulo &art):art_(art){};
                Articulo &articulo() const{ return *art_; }
            private:
                Articulo *art_;
        };

    //OBSERVADORES
    int numero() const noexcept{ return num_; };
    Tarjeta tarjeta() const noexcept{ return tarjeta_; };
    Fecha fecha() const noexcept{ return fecha_; };
    double total() const noexcept{ return total_; };
    static int n_total_pedidos() noexcept{ return cant_; };

    private:
        int num_;
        const Tarjeta tarjeta_;
        Fecha fecha_;
        double total_;
        inline static int cant_ = 0;
};

std::ostream &operator<<(std::ostream &os, const Pedido &P);

#endif





















#endif