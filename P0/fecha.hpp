#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Fecha{
public:
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;
    //Constructores
    Fecha(const Fecha&)=default;    //Constructro por defecto
    explicit Fecha(int d=0, int m=0, int a=0);
    Fecha(const char* );
    
    class Invalida{
        public:
            explicit Invalida(const char* inv):cad(inv){}
            const char* por_que() const{return info_;}
        private:
            const char* info_;
    }

    //Observadores
    int dia() const;
    int mes() const;
    int anno() const;
    //Operadores
    Fecha& operator=(const Fecha&) = default;
    Fecha& operator+=(int );
    Fecha& operator-=(int );
    Fecha operator+(int );
    Fecha operator-(int );
    Fecha operator++(int );
    Fecha& operator++();
    Fecha operator--(int );
    Fecha& operator--();
    operator const char*() const;
    //Destructor(por defecto)
    ~Fecha() = default;

private:
    int dia_, mes_, anno_;
    void Correcto() const;
};
    bool operator==(const Fecha&, const Fecha&);
    bool operator<(const Fecha&, const Fecha&);
    bool operator<=(const Fecha&, const Fecha&);
    bool operator>(const Fecha&, const Fecha&);
    bool operator>=(const Fecha&, const Fecha&);
    bool operator!=(const Fecha&, const Fecha&);
#endif