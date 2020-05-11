#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <ostream>
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

class Clave{
    public:
        Clave(const char *);
        enum Razon{
            CORTA,
            ERROR_CRYPT
        };

        class Incorrecta{
            public:
                Incorrecta(Razon r) : r_(r) {}
                Razon razon() const{ return r_; }
            private:
                Razon r_;
        };

        const Cadena &clave() const;
        bool verifica(const char *) const;
    private:
        Cadena clave_;
};

class Tarjeta;  //declaracion anticipada
class Numero;  //declaracion anticipada

class Usuario{
    public:
        Usuario(const Cadena &, const Cadena &, const Cadena &, const Cadena &, const Clave &);
        Usuario(const Usuario &) = delete;
        Usuario &operator=(const Usuario &) = delete;

        class Id_duplicado{
            public:
                Id_duplicado(const Cadena &cad) : id_(cad) {}
                const Cadena idd() const{ return id_; };
            private:
                Cadena id_;
        };

        typedef std::map<Numero, Tarjeta *> Tarjetas;
        typedef std::unordered_map<Articulo *, unsigned> Articulos;
        typedef std::unordered_set<Cadena> Usuarios ;
        
        void es_titular_de(Tarjeta &);
        void no_es_titular_de(Tarjeta &);
        Cadena id() const{ return identificador_; }
        Cadena nombre() const{ return nombre_; }
        Cadena apellidos() const{ return apellidos_; }
        Cadena direccion() const{ return direccion_; }
        void compra(Articulo &, unsigned cant = 1);

        const Tarjetas &tarjetas() const { return t_; }
        const Articulos &compra() const{ return art_; };
        size_t n_articulos() const{ return art_.size(); }

        friend std::ostream &operator << (std::ostream &os, const Usuario &user);
        
        ~Usuario();
    private:
        Cadena identificador_, nombre_, apellidos_, direccion_;
        Clave clave_;
        static Usuarios user_ ;
        Tarjetas t_;
        Articulos art_;
};

std::ostream &mostrar_carro(std::ostream &os, const Usuario &user);

#endif