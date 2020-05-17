#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

class Articulo{
    public:
        Articulo(const Cadena, const Cadena, const Fecha, double , unsigned );

        const Cadena referencia() const;
        const Cadena titulo() const;
        const Fecha f_publi() const;
        
        double precio() const;
        double& precio();
        unsigned stock() const;
        unsigned& stock();

    private:
        Cadena referencia_, titulo_;
        Fecha f_publi_;
        double precio_;
        unsigned stock_;
};

std::ostream &operator<<(std::ostream &, const Articulo &);

#endif