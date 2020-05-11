#include "fecha.hpp"
#include <cstdio>
#define BISIESTO (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) && mes_ == 2
// CONSTRUCTORES
Fecha::Fecha(const char* f) : dia_(-1), mes_(-1), anno_(-1)
{
    if(std::sscanf(f, "%d/%d/%d", &dia_, &mes_, &anno_) != 3){
        throw Invalida("Error de conversion");
    }
    if(dia_ == 0 || mes_ == 0 || anno_ == 0){
        Hrsys hrsys;
        if(dia_ == 0) dia_ = hrsys.dia();
        if(mes_ == 0) mes_ = hrsys.mes();
        if(anno_ == 0) anno_ = hrsys.anio();
    }
    Correcto();
}

Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    if(dia_ == 0 || mes_ == 0 || anno_ == 0){
        Hrsys hrsys;
        if(dia_ == 0) dia_ = hrsys.dia();
        if(mes_ == 0) mes_ = hrsys.mes();
        if(anno_ == 0) anno_ = hrsys.anio();
    }
    Correcto();
}
// PRIVADO
void Fecha::Correcto() const
{
    if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo){
        throw Invalida("Error: Año invalido");
    }
    if(mes_ < 1 || mes_ > 12){ 
        throw Invalida("Error: Mes incorrecto");
    }
    static const int DiaMes[] = {0,  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(dia_ < 1 || dia_ > (DiaMes[mes_] + static_cast<int>(BISIESTO))){
        throw Invalida("Error: Dia Incorrecto");
    }
}
// PUBLICO
inline int Fecha::dia() const noexcept{ return dia_; }
inline int Fecha::mes() const noexcept{ return mes_; }
inline int Fecha::anno() const noexcept{ return anno_; }

const char *Fecha::cadena() const{
    return Hrsys(this->dia(), this->mes(), this->anno()).toString();
}

Fecha &Fecha::operator+=(int n) {
  if (n != 0) {
    // Objeto con la suma de n-dias a una fecha
    Hrsys nhrsys(this->dia_, this->mes_, this->anno_, n);
    this->dia_ = nhrsys.dia();
    this->mes_ = nhrsys.mes();
    this->anno_ = nhrsys.anio();
    Correcto();
  }
  return *this;
}

Fecha& Fecha::operator-=(int n){ return *this += (-n); }

Fecha Fecha::operator+(int n) const{ return Fecha(*this) += n; }

Fecha Fecha::operator-(int n) const{ return Fecha(*this) += -n; }

Fecha& Fecha::operator++(){ return *this += 1; }

Fecha Fecha::operator++(int){
    Fecha t = *this;
    *this += 1;
    return t;
}

Fecha &Fecha::operator--() { return *this += -1; }

Fecha Fecha::operator--(int) {
  Fecha t = *this;
  *this += -1;
  return t;
}

bool operator==(const Fecha &f1, const Fecha &f2) noexcept{
    return (f1.dia() == f2.dia()) && (f1.mes() == f2.mes()) && (f1.anno() == f2.anno());    
}

bool operator<(const Fecha&f1, const Fecha &f2) noexcept{
    if(f1.anno() < f2.anno())
        return true;
    else if(f1.anno() > f2.anno())
        return false;
    else if(f1.mes() < f2.mes())
        return true;
    else if(f1.mes() > f2.mes())
        return false;
    else
        return f1.dia() < f2.dia();
}

bool operator!= (const Fecha &f1, const Fecha &f2) noexcept{
    return !(f1 == f2);
}

bool operator>(const Fecha &f1, const Fecha &f2) noexcept{
    return f2 < f1;
}

bool operator<=(const Fecha&f1, const Fecha &f2) noexcept{
    return ((f1 < f2) || (f1 == f2));
}

bool operator>=(const Fecha &f1, const Fecha &f2) noexcept{
    return !(f1 < f2);
}

std::istream &operator>>(std::istream &is, Fecha &fecha){
    char tmp[11];
    is.getline(tmp, 11);
    try{
        fecha = Fecha(tmp);
    }catch(const Fecha::Invalida &e){
        //FAIL
        is.setstate(std::ios_base::failbit);
        throw;
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Fecha &fecha) noexcept{
    os << fecha.cadena();
    return os;
}