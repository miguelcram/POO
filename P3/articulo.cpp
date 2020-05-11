#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

Articulo::Articulo(const Cadena ref,const Cadena tit,const Fecha fpubli,double precio, unsigned stock):referencia_(ref),
        titulo_(tit),f_publi_(fpubli),precio_(precio),stock_(stock){}

const Cadena Articulo::referencia() const{
    return referencia_;
}

const Cadena Articulo::titulo() const{
    return titulo_;
}

const Fecha Articulo::f_publi() const{
    return f_publi_;
}

double Articulo::precio() const{
    return precio_;
}

double& Articulo::precio(){
    return precio_;
}
unsigned Articulo::stock() const{
    return stock_;
}

unsigned& Articulo::stock(){
    return stock_;
}

std::ostream &operator<<(std::ostream &os, const Articulo &art){
    os << "[" << art.referencia() << "] " << art.titulo() << ", "
        << art.f_publi() << ". " << art.precio() << " €";
    return os;
}