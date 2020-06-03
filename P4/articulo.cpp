#include <iomanip>
#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

Articulo::Articulo(Autores autr, const Cadena &ref, const Cadena &til, const Fecha &publi, double precio)
    : autor_(autr),
      referencia_(ref),
      titulo_(til),
      f_publi_(publi),
      precio_(precio) {
  if (autor_.empty()) throw Autores_vacios();
}

const Cadena &Articulo::referencia() const{ return referencia_; }

const Cadena &Articulo::titulo() const{ return titulo_; }

const Fecha &Articulo::f_publi() const{ return f_publi_; }

const Articulo::Autores &Articulo::autores() const{ return autor_; }

std::ostream &operator<<(std::ostream &os, const Articulo &art){
    os << "[" << art.referencia() << "] \"" << art.titulo() << "\", de ";
    auto autor = art.autores().begin();
    for(++autor; autor != art.autores().end(); ++autor){
        os << ", " << (*autor)->apellidos();
    }
    os << ". ";
    os << art.f_publi().anno() << ". " << std::fixed << std::setprecision(2)
       << art.precio() << " €\n\t";
    art.impresion_especifica(os);
    return os;
}