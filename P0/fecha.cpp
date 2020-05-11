#include <iostream>
#include <cstring>
#include <time.h>
#include "fecha.hpp"
#define BISIESTO (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) && mes_ == 2

Fecha::Fecha(const char* f) : dia_(0), mes_(0), anno_(0)
{
    std::time tiempo_descompuesto = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_descompuesto);

    if((sscanf(f, "%d%d%d", &dia_, &mes_, &anno_)) != 3)
        throw Invalida("error de formato en la fecha");
    
    if(dia_ == 0)
        dia_ = tiempo_descompuesto->tm_mday;
    if(mes_ == 0)
        mes_ = tiempo_descompuesto->tm_mon+1;
    if(anno_ == 0)
        anno_ = tiempo_descompuesto->tm_year+1900;
    
    correcto();
}

Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    std::time tiempo_descompuesto = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_descompuesto);
    if(d == 0)
        dia_ = tiempo_descompuesto->tm_mday;
    if(m == 0)
        mes_ = tiempo_descompuesto->tm_mon+1;
    if(a == 0)
        anno_ = tiempo_descompuesto->tm_year+1900;
    
    correcto();
}

void Fecha::correcto() const
{
    if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo){
        throw Invalida("error por el año");
    }
    if(mes_ < 1 || mes_ > 12){
        throw Invalida("error por el mes");
    }

    static const int DiaMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30, 31};
    if(dia_ < 1 || dia_ > (DiaMes[mes_] + static_cast<int>(BISIESTO)))
        throw Invalida("error: Dia Incorrecto");
}

int Fecha::dia() const{
    return dia_;
}

int Fecha::mes() const{
    return mes_;
}

int Fecha::anno() const{
    return anno_;
}

Fecha& Fecha::operator+=(int n){
    if(n != 0){
        std::tm* time_tm = new std::tm{
            0, 0, 0, (dia_ + n), (mes_ - 1), (anno_ - 1900), 0, 0, 0, 0, 0
        }

        std::mktime(time_tm);

        dia_ = time_tm->tm_mday;
        mes_ = time_tm->tm_mon+1;
        anno_ = time_tm->tm_year+1900;

        correcto();
    }
    return *this;
}

Fecha& Fecha::operator-=(int n){
    return *this += (-n);
}

Fecha Fecha::operator+(int n){
    return Fecha(*this) += n;
}

Fecha Fecha::operator-(int n){
    return Fecha(*this) -= n;
}

Fecha Fecha::operator++(int){
    Fecha tmp = *this;
    *this += 1;
    return tmp;
}

Fecha& Fecha::operator++(){
    return *this += 1;
}

Fecha Fecha::operator--(int){
    Fecha tmp = *this;
    *this -= 1;
    return tmp;
}

Fecha& Fecha::operator--(){
    return *this -= 1;
}

bool operator==(const Fecha &f1, const Fecha &f2){
    if(f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.dia() == f2.dia())
        return true;
    else
        return false;    
}

bool operator<(const Fecha&f1, const Fecha &f2){
    if(f1.anno() < f2.anno())
        return true;
    if(f1.anno() == f2.anno() && f1.mes() < f2.mes())
        return true;
    if(f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() < f2.dia())
        return true;
    else
        return false; 
}

bool operator>(const Fecha &f1, const Fecha &f2){
    return f2 < f1;
}

bool operator<=(const Fecha&f1, const Fecha &f2){
    return !(f2 < f1);
}

bool operator>=(const Fecha &f1, const Fecha &f2){
    return !(f1 < f2);
}

bool operator!= (const Fecha &f1, const Fecha &f2){
    return !(f1 == f2);
}
