/** $Id: test-caso3-consola.cpp 395 2017-04-28 18:34:41Z gerardo $
 * Pruebas del caso 3 de la SGL
 *
 * LIBRERÍA
 * ©2009-2020 Inma, Juanma, Fidel, Gerardo
 */

#include <cstdlib>
#include <exception>
#include <iostream>
#include <locale>
#include "fecha.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#define AZUL  "\033[0m\033[01;34m"
#define NORMAL "\033[0m"

int main()
{
  std::cout.imbue(std::locale(""));
    // Constructor de usuario: id, nombre, apellidos, dirección, clave
  Usuario
    oliver("oliver", "Oliverio", "Tejada Navas",
	  "Caño, 89 (Alcafrán)", "vaeg0Quo"),
    angelines("angelines", "Angelines", "Franco Portillo",
	    "Plazuela del Puerto, 77 (Icod de los Vinos)", "Pheaj9li"),
    yeni("yeni", "Jennifer", "Mingladilla Romegosa",
	   "Carrer de Colom (Cerdanyola del Vallès)", "ahxo2Aht"),
    vane("vane", "Vanessa", "Toro Rojas",
	 "S. Pedro, 97 (Pedrosillo de Alba)", "Roh9aa5v");
  // Constructor de Tarjeta: Tipo, Numero, Usuario, fecha de caducidad
  // Para evitar problemas con las fechas y sus caducidades, ponemos año 0
  // (el actual) y sumamos uno o más años.

 Tarjeta
    visa1(Numero("4539 4512 0398 7356"),
          oliver, Fecha(31,12,0) + 3*365),
    american_express(Numero("378282246310005"),
                     yeni, Fecha(30,11,0) + 4*365),
    dinners_club(Numero("30569309025904"),
                 vane, Fecha(31,7) + 5*365),
    mastercard(Numero("555555555555 4444  "),
               angelines, Fecha(31,1) + 3*365),
    australian_bank_card(Numero("5610591081018250"),
               angelines, Fecha(28,2)+ 365),
    jcb(Numero("3530111333300000"), vane, Fecha("31/7/0") + 2*365),
    visa2(Numero(" 4222222222222"), oliver, Fecha("28/2/0") + 365);

  // Constructor de Articulo: referencia, título, fecha de publicación,
  // precio, stock
  Articulo
    poo("100", "Programación Orientada a Objetos", "1/8/2000", 32.50, 5),
    cpp("110", "Fundamentos de C++", "20/6/1998", 35.95, 10),
    stl("111", "The Standard Template Library", "5/10/2002", 42.10, 3),
    ada("103", "Análisis y Diseño de Algoritmos", "1/2/2001", 39.95, 2);

  // Añadir y quitar artículos al carrito y ver el carrito
  // Comprar: Articulo, Cantidad (1 por omisión, 0 elimina el artículo)
  // Factura: Usuario_Pedido, Pedido_Articulo, Usuario, Tarjeta, Fecha [hoy]
  Usuario_Pedido usuario_ped;
  Pedido_Articulo pedido_art;

  std::cout << "\n\nCARRITOS VACÍOS\n\n";
  mostrar_carro(std::cout, oliver);
  mostrar_carro(std::cout, angelines);
  mostrar_carro(std::cout, yeni);
  mostrar_carro(std::cout, vane);
  std::cout << std::endl;

  oliver.compra(cpp, 3);
  oliver.compra(stl, 1);
  std::cout << "Oliverio compra 3 \"Fundamentos de C++\" y 1 \"The STL\"\n";
  mostrar_carro(std::cout, oliver);
  Pedido p1(usuario_ped, pedido_art, oliver, visa1, Fecha(10, 3));

  std::cout << "*** Cambio de precio de CPP y STL\n\n";
  cpp.precio() = 29.95;	// cambiar precios
  stl.precio() = 44.50;
  std::cout << "Angelines compra 2 de CPP y otros 2 de STL\n";
  angelines.compra(cpp, 2);
  angelines.compra(stl, 2);
  mostrar_carro(std::cout, angelines);
  std::cout << "\n*** Angelines devuelve STL y compra 1 POO\n";
  angelines.compra(stl, 0); // quita STL del carrito
  angelines.compra(poo);    // un ejemplar
  mostrar_carro(std::cout, angelines);
  std::cout << "\n*** No se comprueba stock\n"
	    << "*** stock de ADA = " << ada.stock()
	    << "\nLa Yeni compra 6 ADA\n";
  yeni.compra(ada, 6);	// no se comprueban las existencias
  mostrar_carro(std::cout, yeni);
  std::cout << "\n*** La Yeni devuelve 4 ADA\n";
  yeni.compra(ada, 6 - 4);	// quita 4 del carrito
  mostrar_carro(std::cout, yeni);
  Pedido p3(usuario_ped, pedido_art, yeni, american_express,
	    Fecha() - 1);	// pedido ayer
  Pedido p2(usuario_ped, pedido_art, angelines, mastercard, "5/4/2010");
  std::cout << "*** Cambio de precio de POO y ADA\n\n";
  poo.precio() = 35.20;	// cambiar precios
  ada.precio() = 34.90;
  std::cout << "La Vane compra 2 de POO, 3 de CPP y 1 STL\n";
  vane.compra(poo, 2);
  vane.compra(cpp, 3);
  vane.compra(stl);
  vane.compra(ada, 0); // no hace nada, ada no está en el carro
  mostrar_carro(std::cout, vane);
  Pedido p4(usuario_ped, pedido_art, vane, jcb, "5/4/2010");

  std::cout << "\n --- PEDIDOS ---\n"
	    << p1 << std::endl << p2 << std::endl
	    << p3 << std::endl << p4
	    << "\nRecibimos mercancías: 5 más de POO, "
    "4 de CPP y 2 de STL y ADA\n";

  // Recepción de mercancías
  poo.stock() += 5; 
  cpp.stock() *= 4; 
  stl.stock() += 2; 
  ada.stock() += 2;

  std::cout << "La Vane compra 1 STL, 1 ADA y 3 CPP\n";
  vane.compra(stl); vane.compra(ada);
  Pedido p5(usuario_ped, pedido_art, vane, jcb); // pedido hoy
  vane.compra(cpp, 3);
  Pedido p6(usuario_ped, pedido_art, vane, dinners_club); // pedido hoy
  std::cout << "Angelines compra 1 ADA, 1 STL y 3 POO\n";
  angelines.compra(ada); angelines.compra(stl); angelines.compra(poo, 3);
  Pedido p7(usuario_ped, pedido_art, angelines, australian_bank_card,
	    "5/4/2010");
  std::cout << "La Yeni compra 2 POO y 1 CPP\n";
  yeni.compra(poo, 2); yeni.compra(cpp);
  Pedido p8(usuario_ped, pedido_art, yeni, american_express, "5/4/2010");

  std::cout << "\n --- NUEVOS PEDIDOS ---\n"
	    << p5 << std::endl << p6 << std::endl
	    << p7 << std::endl << p8

	    << "\n\n" AZUL "-------------------DETALLE DE PEDIDOS--------------"
    NORMAL  << std::endl;
  pedido_art.mostrarDetallePedidos(std::cout);
  std::cout << "\n" AZUL "------------------VENTAS DE ARTÍCULOS--------------"
    NORMAL << std::endl;
  pedido_art.mostrarVentasArticulos(std::cout);

  // Pruebas de excepciones
  try {
    Pedido nulo(usuario_ped, pedido_art, oliver, visa2);
  }
  catch(const Pedido::Vacio& e) {
    std::cerr << "Error de pedido: el carrito de " << e.usuario().id()
	      << " está vacío. " << std::endl;
  }
  try {
    angelines.compra(cpp);
    Pedido farsante(usuario_ped, pedido_art, angelines, visa2);
  }
  catch(const Pedido::Impostor& e) {
    std::cerr << "Error de pedido: la tarjeta de pago no es de "
	      << e.usuario().id() << std::endl;
  }
  try {
    vane.compra(poo, 2); vane.compra(stl, 4); vane.compra(ada, 5);
    Pedido no_disponible(usuario_ped, pedido_art, vane, dinners_club);
  }
  catch(const Pedido::SinStock& e) {
    std::cerr << "Error de pedido: no hay existencias del artículo ["
	      << e.articulo().referencia() << "]" << std::endl;
  }
  try {
    // Creamos una tarjeta que caducó ayer. ¿Qué pasa? ¡No somos un
    // maldito banco, esto es solo una simulación, una prueba!
    Tarjeta caduca(Numero("4222222222222"), oliver, Fecha() - 1);
    oliver.compra(poo, 2);
    Pedido no_pagado(usuario_ped, pedido_art, oliver, caduca); // pedido hoy
  }
  catch(const Tarjeta::Caducada& e) {
    std::cerr << "Error de pedido: tarjeta caducada el " << e.cuando()
	      << std::endl;
  }
  std::cout << "\nNúmero total de pedidos: "
	    << Pedido::n_total_pedidos() << std::endl;
}
