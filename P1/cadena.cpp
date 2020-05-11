#include "cadena.hpp"
#include <cstring>
#include <stdexcept>

Cadena::Cadena(size_t tam, const char c) : s_(new char[tam + 1]), tam_(tam) {
  std::memset(s_, c, tam_);
  s_[tam_] = '\0';
}

Cadena::Cadena(const char *cc)
    : s_(new char[std::strlen(cc) + 1]), tam_(std::strlen(cc)) {
  std::strcpy(s_, cc);
}

Cadena::Cadena(const Cadena &cad) : s_(new char[cad.tam_ + 1]), tam_(cad.tam_) {
  std::strcpy(s_, cad.s_);
}

Cadena::Cadena(Cadena &&cad) : s_(cad.s_), tam_(cad.tam_) {
  cad.tam_ = 0;
  cad.s_ = nullptr;
}

//Método subcadena
Cadena Cadena::substr(size_t begindex, size_t len) const {
  if (begindex >= tam_ || begindex + len > tam_ || begindex + len < begindex)
    throw std::out_of_range("Error de rango");

  Cadena ctmp(len);
  std::strncpy(ctmp.s_, s_ + begindex, len);
  ctmp.s_[len] = '\0';
  return ctmp;
}

//OPERADORES DE ACCESO
char Cadena::operator[](size_t i) const noexcept { return s_[i]; }
char &Cadena::operator[](size_t i) noexcept { return s_[i]; }

char Cadena::at(size_t i) const {
  if (i >= tam_) throw std::out_of_range("Fuera de rango");
  return s_[i];
}

char &Cadena::at(size_t i) {
  if (i >= tam_) throw std::out_of_range("Fuera de rango");
  return s_[i];
}

//OPERADORES DE ASIGNACION
Cadena &Cadena::operator+=(const Cadena &cad){
    Cadena t = *this;
    tam_ = t.tam_ + cad.tam_;
    delete[] s_;
    s_ = new char[tam_+1];
    std::strcpy(s_, t.s_);
    std::strcat(s_, cad.s_);
    return *this;
}
Cadena &Cadena::operator=(const Cadena &cad){
    if(this != &cad){
        delete[] s_;
        tam_ = cad.tam_;
        s_ = new char[tam_+1];
        std::strcpy(s_, cad.s_);
    }
    return *this;
}
Cadena &Cadena::operator=(const char *cad){
    delete[] s_;
    tam_ = std::strlen(cad);
    s_ = new char[tam_+1];
    std::strcpy(s_, cad);
    return *this;
}
Cadena &Cadena::operator=(Cadena &&cad){
    if(this != &cad){
        delete[] s_;
        tam_ = cad.tam_;
        s_ = cad.s_;
        cad.s_ = nullptr;
        cad.tam_ = 0;
    }
    return *this;
}

//OPERADOR ARITMETICO
Cadena operator+(const Cadena &cad1, const Cadena &cad2) {
  return Cadena(cad1) += cad2;
}

//OPERADORES DE COMPARACION
bool operator==(const Cadena &cad1, const Cadena &cad2) noexcept {
  return (std::strcmp(cad1.c_str(), cad2.c_str()) == 0);
}

bool operator!=(const Cadena &cad1, const Cadena &cad2) noexcept {
  return !(cad1 == cad2);
}

bool operator>(const Cadena &cad1, const Cadena &cad2) noexcept {
  return (std::strcmp(cad1.c_str(), cad2.c_str()) > 0);
}

bool operator<(const Cadena &cad1, const Cadena &cad2) noexcept {
  return !(cad1 == cad2) && !(cad1 > cad2);
}

bool operator<=(const Cadena &cad1, const Cadena &cad2) noexcept {
  return !(cad1 > cad2);
}

bool operator>=(const Cadena &cad1, const Cadena &cad2) noexcept {
  return (cad1 == cad2) || (cad1 > cad2);
}

//OPERADORES DE FLUJO

std::istream &operator>>(std::istream &is, Cadena &cad) noexcept {
  char *tmp = new char[33];
  int i = 0;
  char aux;
  while (isspace(is.get()) && is.good()) {
  }
  is.unget();
  while (i < 32 && !isspace(is.peek()) && is.good() && is.peek() != '\n' &&
         is.peek() != '\0') {
    aux = is.get();
    if (is.good()) tmp[i++] = aux;
  }
  tmp[i] = '\0';
  cad = tmp;
  delete[] tmp;
  return is;
}

std::ostream &operator<<(std::ostream &os, const Cadena &cad) noexcept {
  os << cad.c_str();
  return os;
}