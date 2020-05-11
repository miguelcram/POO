/* -*- mode: c++; compile-command: "g++ -std=c++17 -Wall -o ejemplo_algoSTL ejemplo_algoSTL.cpp" -*-
 * $Id: ejemplo_algoSTL.cpp 418 2018-04-27 19:12:54Z gerardo $
 *
 * Ejemplo de uso de un algoritmo que recibe un predicado unario (count_if),
 * donde se muestran las alternativas que hay para pasarle algo que se comporte
 * como un predicado.
 * También se ven otras cosas interesantes: contenedor y cómo inicializarlo,
 * iterador de flujo de salida, otros algoritmos, etc.
 * ©2014-2020 Gerardo
 */

#include <vector>		// vector
#include <algorithm>		// copy, count_if
#include <utility>		// bind2nd, binary_function
#include <iostream>		// cout, operator <<, endl
#include <iterator>		// ostream_iterator, begin, end
#include <functional>		// bind, placeholders
using namespace std;

// Mínima versión de GNU C++: 4.7
#if !defined(__clang__)
#  if (__GNUC__<4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7))
#   error Su compilador GNU C++ es muy antiguo; actualícelo a la última versión.
#  endif
#endif

#define cuantos_hay_mayores_que(c) cout <<"Hay " << (n) << " elemento" \
  << ((n) == 1 ? "  " : "s ") << ((n) == 1 ? "mayor  " : "mayores")    \
  << " que " << (c) << endl

inline bool mayor_q_7(int x) { return x > 7; } // Función para el 1er. caso

/***
 * Dado un vector de enteros, imprimirlo de varias formas y contar
 * cuántos elementos son mayores que cierto valor dado,
 * usando el algoritmo count_if de varias maneras.
 */

int main()
{
#ifndef __clang__
  cout << "Versión de GNU C++: " << __GNUC__ << '.' << __GNUC_MINOR__ << endl;
#else
  cout << "Versión de CLang C++:" << __clang_major__ << '.' << __clang_minor__
       << '.' << __clang_patchlevel__ << endl;
#endif
  // Definición del contenedor y su inicialización
  // C++11: con lista de inicialización (initializer_list) (GNU C++ 4.4+)
  vector<int> v { -32, 2, 1, 5, 7, 9, 3, 0, 4, 2, -32 };
#if 0
  // Alternativa 1: constructor de rango a partir de otro contenedor,
  // que en este simple caso puede ser una simple ristra
  int vv[] = { -32, 2, 1, 5, 7, 9, 3, 0, 4, 2, -32 };
  vector<int> v(vv, vv + sizeof vv / sizeof(int));
  // Alternativa 2: contenedor vacío + inserciones, en este caso con push_back
  vector<int> v(9); v.push_back(-32); v.push_back(2); /*...*/; v.push_back(-32);
#endif

  // Impresión del vector: 4 formas
  // 1- Con un bucle for «tradicional» que funciona en C++98
  cout << "Impresión con for tradicional........: v = {";
  for (vector<int>::const_iterator i = v.begin(); i != v.end(); ++i) {
    if (i != v.begin()) cout << ',';
    cout << ' ' << *i;
  }
  cout << " };\n";
  // "{ x0, x1, x2 }\n" 

  // 2- Con el bucle for de rango y con "auto" [C++11] (GNU C++ 4.6+)
  cout << "Impresión con for de rango y auto....: v = { ";
  bool p = true;
  for (auto x : v)
    cout << (p ? (p = false, "") : ", ") << x;
  cout << " };\n";

  // 3- Con el algoritmo copy y un iterador de flujo de salida.
  // Usamos las funciones de contenedor cbegin/cend que devuelven const_iterator
  cout << "Impresión con copy + ostream_iterator: v = { ";
  copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, ", "));
  cout << "\b\b };\n";

  // 4- Con el algoritmo for_each y una función anónima
  cout << "Impresión con for_each + lambda......: v = { ";
  for_each(v.cbegin(), v.cend(), [](int x) { cout << x << ", "; });
  cout << "\b\b };\n";

  //---------------------------------------------------------------------------
  // 1er. caso: con una función, o puntero a función.
  // Usamos las funciones genéricas globales begin/end que devuelven
  // (const_)iterator (GNU C++ 4.7+). El & antes de mayor_q_7 es opcional.

  cout << "1- (Puntero a) función......................: ";
  // El tipo de n es seguramente int, pero de forma ortodoxa sería
  // iterator_traits<vector<int>::const_iterator>::difference_type
  // Un gran invento, la redefinición de auto en C++11...
  // Bueno, en realidad también se podría poner vector<int>::difference_type
  auto n = count_if(begin(v), end(v), &mayor_q_7);
  cuantos_hay_mayores_que(7);

  // 2.º caso: con un objeto función, cuya clase se crea expresamente
  struct mayor_q_7 {
    bool operator() (int x) const { return x > 7; }
  };
  cout << "2- Objeto función simple....................: ";
  // Se llama al ctor. explícitamente, creándose un objeto anónimo y temporal
  // que se pasa a count_if y se destruye inmediatamente; esto es mejor que
  // crear un objeto y pasárselo a la función, porque no se destruiría hasta
  // salir de ámbito.
  n = count_if(begin(v), end(v), mayor_q_7());
  cuantos_hay_mayores_que(7);

  // 3er. caso: con un objeto función de una clase más perfeccionada
  struct mayor_q {
    mayor_q(int y): y_(y) {}
    bool operator() (int x) const { return x > y_; }
  private:
    int y_;
  };
  cout << "3- Objeto función con atributo y constructor: ";
  n = count_if(begin(v), end(v), mayor_q(3));
  cuantos_hay_mayores_que(3);

  // 4.º caso: con un objeto función de una clase adaptable, y usando
  // un adaptador de función binaria a monaria con el 2.º parámetro fijado.
  // [Desaconsejado a partir de C++11, quitado a partir de C++17]
  struct mayor_que: binary_function<int, int, bool> {
    bool operator()(int x, int y) const { return x > y; }
  };
  cout << "4- Objeto función adaptable + bind2nd.......: ";
  n = count_if(begin(v), end(v), bind2nd(mayor_que(), 4));
  cuantos_hay_mayores_que(4);

  // 5.º caso: como el 4.º pero usando un objeto función de una clase
  // predefinida en la Biblioteca estándar.
  cout << "5- Objetos función y adaptadores de la STL..: ";
  n = count_if(begin(v), end(v), bind2nd(greater<int>(), 5));
  cuantos_hay_mayores_que(5);

  // 6.º caso: con bind, greater y marcadores de posición (C++11)
  using namespace placeholders;
  cout << "6- bind + greater + placeholder.............: ";
  n = count_if(begin(v), end(v), bind(greater<int>(), _1, 6));
  cuantos_hay_mayores_que(6);

  // 7.º caso: usando una función anónima (lambda) [C++11] (GNU C++ 4.5+)
  auto f = [](int x) { return x > 0; };
  cout << "7- Función anónima (lambda).................: ";
  n = count_if(begin(v), end(v),f);
  cuantos_hay_mayores_que(0);
}
