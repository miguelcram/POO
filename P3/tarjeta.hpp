#ifndef TARJETA_HPP
#define TARJETA_HPP
#include <ostream>
#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"

class Usuario;  //declaracion anticipada
struct EsDigito:public std::unary_function<char, bool>{
    bool operator()(char c) const{ return isdigit(c); }
}
struct EsBlanco:public std::unary_function<char, bool>{
    bool operator()(char c) const{ return isspace(c); }
};

class Numero{
    public:
        Numero(const Cadena &cad);
        operator const char *() const;
        enum Razon{
            LONGITUD,
            DIGITOS,
            NO_VALIDO
        };

        friend bool operator<(const Numero &A, const Numero &B);
        
        class Incorrecto{
            public:
                Incorrecto(Razon r) : r_(r) {}
                const Razon &razon() const { return r_; }
            private:
                Razon r_;
        };
    private:
        Cadena numero_;
};

class Tarjeta{
    public:
        Tarjeta(Numero, Usuario &, Fecha);
        Tarjeta(const Tarjeta &) = delete;
        Tarjeta &operator=(const Tarjeta &) = delete;
        
        enum Tipo{
            Otro,
            VISA,
            Mastercard,
            Maestro,
            JCB,
            AmericanExpress
        };
        
        class Caducada{
            public:
                Caducada(const Fecha &f) : f_(f) {}
                Fecha cuando() const { return f_; }
            private:
                Fecha f_;
        };

        class Num_duplicado{
            public:
                explicit Num_duplicado(const Numero &num) : n_(num) {}
                Numero que() const { return n_; }
            private:
                Numero n_;
        };

        class Desactivada{};

        Tipo tipo() const{ return t_; }
        Numero numero() const{ return num_; }
        const Usuario *titular() const{ return user_; }
        Fecha caducidad() const{ return caducidad_; }
        
        bool activa() const { return estado_; }
        bool activa(bool est = true){
            estado_ = est;
            return estado_;
        }
        void anula_titular();
        Cadena titular_facial() const;

        ~Tarjeta();
    private:
        Tipo t_;
        Numero num_;
        const Usuario *user_;
        Fecha caducidad_;
        bool estado_;
};

std::ostream &operator<<(std::ostream &os, const Tarjeta &T);
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &t);
bool operator<(const Tarjeta &A, const Tarjeta &B);

#endif