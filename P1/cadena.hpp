#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <functional>
#include <iostream>
#include <iterator>

class Cadena{
    public:
        /* CONSTRUCTORES */
        explicit Cadena(size_t t = 0, char c = ' ');
        Cadena(const char *cad);
        //Constructor de copia
        Cadena(const Cadena &cad);
        //Constructor de movimiento
        Cadena(Cadena &&cad);

        /* METODOS */
        //Obtener una subacadena
        Cadena substr(size_t begindex, size_t len) const;
        //Obtnener la longitud de la cadena
        size_t length() const noexcept{ return tam_; }
        //Convertir de Cadena a const char*
        const char *c_str() const noexcept{ return s_; }

        //OPERADORES
        char operator[](size_t j) const noexcept;
        char &operator[](size_t j) noexcept;
        char at(size_t i) const;
        char &at(size_t i);

        Cadena& operator+=(const Cadena &cad);
        Cadena& operator=(const Cadena &cad);
        Cadena& operator=(const char *cad);
        Cadena& operator=(Cadena &&cad);

        //DESTRUCTOR
        ~Cadena(){ delete[] s_; }
        //ITERADORES
        using iterator = char *;
        using const_iterator = char const *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator begin() noexcept{ return s_; }
        const_iterator begin() const noexcept{ return s_; }
        const_iterator cbegin() const noexcept{ return s_; }
        reverse_iterator rbegin() noexcept{ return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const noexcept{
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const noexcept{
            return const_reverse_iterator(end());
        }

        iterator end() noexcept{ return s_+tam_; }
        const_iterator end() const noexcept{ return s_+tam_; }
        const_iterator cend() const noexcept{ return s_+tam_; }
        reverse_iterator rend() noexcept{ return reverse_iterator(begin()); }
        const_reverse_iterator rend() const noexcept{
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const noexcept{
            return const_reverse_iterator(begin());
        }

    private:
        char *s_;
        size_t tam_;
};
    //Concatenación con el operator +
    Cadena operator+(const Cadena &, const Cadena &);
    //OPERADORES DE COMPARACION
    bool operator>(const Cadena &cad1, const Cadena &cad2) noexcept;
    bool operator<(const Cadena &cad1, const Cadena &cad2) noexcept;
    bool operator==(const Cadena &cad1, const Cadena &cad2) noexcept;
    bool operator!=(const Cadena &cad1, const Cadena &cad2) noexcept;
    bool operator<=(const Cadena &cad1, const Cadena &cad2) noexcept;
    bool operator>=(const Cadena &cad1, const Cadena &cad2) noexcept;

    std::istream &operator>>(std::istream &is, Cadena &cad) noexcept;
    std::ostream &operator<<(std::ostream &os, const Cadena &cad) noexcept;

//Para P2 y ss.
//Especializaciond e la plantilla hash<T> para definir la
//funcion hash a utilizar con contenedores desordenados de
//Cadena, unordered_[set|map|multiset|multimap]
namespace std{
    template <>
    struct hash<Cadena>{    //conversion const char* a string
        size_t operator()(const Cadena &cad) const{
            return hash<string>{}(cad.c_str());
        }
    };
}

#endif