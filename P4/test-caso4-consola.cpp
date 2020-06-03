/* $Id: test-caso4-consola.cpp 396 2017-05-12 18:54:19Z gerardo $
 * Prueba del SGL, caso de uso 4
 *
 * LIBRERÍA
 * ©2009-20 los profesores de POO
 */

#include <cstdlib>
#include <exception>
#include <iostream>
#include <locale>
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#define AZUL  "\033[0m\033[01;34m"
#define VERDE "\033[0m\033[01;32m"
#define NORMAL "\033[0m"

using std::cout;
using std::cerr;
using std::endl;

int main()
{
  cout.imbue(std::locale(""));
  // Constructor de usuario: id, nombre, apellidos, dirección, clave
  Usuario 
    lucas("lucas", "Lucas", "Grijánder", 
	  "Avda. del Atún, 654 (Barbate)", "vaeg0Quo"),
    krispin("krispin", "Crispín", "Klánder", 
	    "Calle del Jurel, 876 (Cerdanyola del Vallès)", "Pheaj9li"),
    yoshua("yoshua", "Yoshua", "Romegosa", 
	   "Callejón del Algarrobo, s/n (Mondragón)", "ahxo2Aht"),
    yessi("yessi", "Yésica", "Minglaníllez",
	  "Calle del Almendro, 345 (Corrubedo)", "Roh9aa5v");
  
  // Constructor de Tarjeta: Numero, Usuario, fecha de caducidad
  // Para evitar problemas con las fechas y sus caducidades, ponemos año 0
  // (el actual) y sumamos uno o más años.
  Tarjeta
    visa1(Numero("4539 4512 0398 7356"), lucas, Fecha(31,12,0) + 3*365),
    american_express(Numero("378282246310005"), yoshua, Fecha(30,11,0) + 4*365),
    dinners_club(Numero("30569309025904"), yessi, Fecha(31,7) + 5*365),
    mastercard(Numero("555555555555 4444  "), krispin, Fecha(31,1) + 3*365),
    australian_bank_card(Numero("5610591081018250"), krispin, Fecha(28,2)+ 365),
    jcb(Numero("3530111333300000"), yessi, Fecha("31/7/0") + 2*365),
    visa2(Numero(" 4222222222222"), lucas, Fecha("28/2/0") + 365);
   
  // Constructor de Autor: nombre, apellidos, dirección
  Autor 
    Esteban("Esteban", "Rey", "Portland, Maine (US)"),
    Rolling("JK", "Rolling", "Yate, Gloucestershire (UK)"),
    Humberto("Humberto", "Echo", "Alessandria, Piamonte (Italia)"),
    Goria("Goria", "Fuertes", "Madriz (Españia)");
  
  Articulo::Autores autores { &Rolling };
  
  // Constructor de Libro: autores, referencia, título, fecha publicación,
  //                       precio, páginas, stock
  Libro enrique_alfarero(autores, "100",
			 "Enrique Alfarero y el fistro de fuego",
			 "1/8/2000", 32.50, 245, 5); // autor = Rolling
  
  autores.insert(&Goria);
  Libro manualidades1(autores, "110", "Mi primer libro de manualidades",
	    "20/6/1998)", 35.95, 650, 100); // autores = Rolling y Goria
  autores.clear();
  
  autores.insert(&Esteban);
  Libro salem(autores, "111", "Las brujas de Salem",
	    "17/10/1975", 42.10, 150, 300); // autor = Esteban
  
  autores.insert(&Humberto);
  Libro bracula(autores, "103", "Brácula, el no vivo",
	    "1/1/1902", 39.95, 455, 4); // autores = Esteban y Humberto
  
  // Constructor de LibroDigital: autores, referencia, título,
  //                              fecha publicación, precio, fecha expiración
  LibroDigital  // autores = Esteban y Humberto
    nombre(autores, "034", "El nombre de La Cosa", "15/1/2009", 6., "1/7/2009");
  autores.clear();
  
  autores.insert(&Goria);
  LibroDigital // autor = Goria
    tonto(autores, "035", "Eres mu tonto", "20/3/2009)", 
	   9., Fecha("20/6/00") + 365 * 4),
    pasquin(autores, "036", "55 días en Pasquín", "1/10/2007",
	    12., "30/9/2008"); // expdo.
  
  // Constructor de Cederron: autores, referencia, título, fecha publicación,
  //                          precio, megas, stock
  Cederron // autor = Goria
    camela(autores, "210", "Biografía de Camela", "1/8/2000", 32.50, 245, 40);
  
  autores.insert(&Rolling);
  Cederron  // autores = Goria y Rolling
    adenda(autores, "211", "Adenda a las asignaturas del GII",
	   "20/6/1998", 35.95, 650, 50);
  
  autores.insert(&Esteban);
  Cederron  // autores = Goria, Rolling y Esteban
    cppref(autores, "220", "Referencia de C++", 
	"9/9/2020", 12.90, 547, 30);
  
  cout << "\n" AZUL "---------------INVENTARIO DE EXISTENCIAS-----------"
    NORMAL "\nLIBROS: \n" 
       << enrique_alfarero << '\n' << manualidades1 << '\n' 
       << salem << '\n' << bracula
       << "\nLIBROS DIGITALES: \n" 
       << nombre << '\n' << tonto << '\n' << pasquin
       << "\nCEDERRONES: \n" 
       << camela << '\n' << adenda << '\n' << cppref << endl;
  
  // Añadir y quitar artículos al carrito y ver el carrito
  // Comprar: Articulo, Cantidad (1 por omisión, 0 elimina el artículo)
  // Factura: Usuario_Pedido, Pedido_Articulo, Usuario, Tarjeta, Fecha [hoy]
  Usuario_Pedido usuario_ped;
  Pedido_Articulo pedido_art;
  
  cout << "\n\nCARRITOS VACÍOS\n\n";
  mostrar_carro(cout, lucas);
  mostrar_carro(cout, krispin);
  mostrar_carro(cout, yoshua);
  mostrar_carro(cout, yessi);
  cout << VERDE "\n*** Lucas compra 4 artículos.\n" NORMAL;
  
  lucas.compra(manualidades1, 3);
  lucas.compra(salem, 1);
  lucas.compra(nombre, 2);
  lucas.compra(adenda, 1);
  mostrar_carro(cout, lucas);
  Pedido p1(usuario_ped, pedido_art, lucas, visa1, Fecha(10, 3));
  
  cout << VERDE "*** Cambio de precio de \"Mi primer libro de manualidades\", "
    "\"Las brujas de Salem\", \"El nombre de la Cosa\" y"
    " \"Biografía de Camela\".\n\n" NORMAL;
  manualidades1.precio() = 29.95;	// cambiar precios
  salem.precio() = 44.50; 
  nombre.precio() = 5.50;
  camela.precio() = 24.05;

  cout << VERDE "*** Krispín compra 2 artículos.\n" NORMAL;
  krispin.compra(manualidades1, 2);
  krispin.compra(salem, 2);
  mostrar_carro(cout, krispin);
  cout << VERDE "\n*** Krispín devuelve \"Las brujas de Salem\" y compra"
    " \"Enrique Alfarero y el fistro de fuego\" y \"Referencia de C++\".\n"
    NORMAL;
  krispin.compra(salem, 0); // quita salem del carrito
  krispin.compra(enrique_alfarero);    // un ejemplar
  krispin.compra(cppref);
  mostrar_carro(cout, krispin);
  cout << VERDE "\n*** No se comprueban existencias\n"
    "*** existencias de \"Brácula, el no vivo\" = " << bracula.stock()
       << NORMAL << endl;
  yoshua.compra(bracula, 6);	// no se comprueban las existencias
  cout << VERDE "\n*** No se comprueba la fecha de expiración\n"
    "*** fecha expir. \"55 días en Pasquín\" = " << pasquin.f_expir()
       << NORMAL "\n\n";
  yoshua.compra(pasquin, 2); // no se comprueba la fecha de expiración
  mostrar_carro(cout, yoshua);
  cout << VERDE "\n*** Yoshua devuelve 4 ejemplares de \"Brácula\"\n" NORMAL;
  yoshua.compra(bracula, 2);	// quita 4 del carrito
  mostrar_carro(cout, yoshua);
  Pedido p2(usuario_ped, pedido_art, yoshua, american_express, 
	    --Fecha());	// pedido ayer
  Pedido p3(usuario_ped, pedido_art, krispin, mastercard, "5/4/2010");
  
  cout << VERDE "*** Cambio de precios de "
    "\"Enrique Alfarero y el fistro de fuego\","
    " \"Brácula el no vivo\" y \"Eres mu tonto\"\n\n" NORMAL;
  enrique_alfarero.precio() = 35.20;	// cambiar precios
  bracula.precio() = 34.9; 
  tonto.precio() -= 6.; // 6 € menos

  cout << VERDE "*** Yessi compra 3 artículos.\n" NORMAL;
  yessi.compra(cppref, 2);
  yessi.compra(tonto, 3);
  yessi.compra(salem);
  yessi.compra(adenda, 0); // no hace nada, adenda no está en el carro
  mostrar_carro(cout, yessi);
  Pedido p4(usuario_ped, pedido_art, yessi, jcb, "5/4/2010");
  
  cout << AZUL "\n---------------------PEDIDOS-----------------------\n"
    NORMAL << p1 << endl << p2 << endl << p3 << endl << p4

       << VERDE "\nSe reciben más cantidades de los artículos existentes.\n\n"
    NORMAL;
  // Recepción de mercancías
  enrique_alfarero.stock() += 5; 
  manualidades1.stock() *= 4; 
  salem.stock() += 2; 
  bracula.stock() += 2;

  cout << VERDE "*** Yessi compra 2 libros más y hace un pedido.\n" NORMAL;
  yessi.compra(salem);
  yessi.compra(bracula);
  Pedido p5(usuario_ped, pedido_art, yessi, jcb); // pedido hoy
  cout << VERDE "*** Yessi compra 3 ejemplares de "
    "\"Mi primer libro de manualidades\" y hace otro pedido.\n" NORMAL;
  yessi.compra(manualidades1, 3);
  Pedido p6(usuario_ped, pedido_art, yessi, dinners_club); // pedido hoy
  cout << VERDE "*** Krispín compra 3 artículos y hace su pedido.\n" NORMAL;
  krispin.compra(bracula); 
  krispin.compra(salem); 
  krispin.compra(enrique_alfarero, 3);
  Pedido p7(usuario_ped, pedido_art, krispin, australian_bank_card, "5/4/2010");
  cout << VERDE "*** Yoshua compra 2 artículos y hace su pedido.\n" NORMAL;
  yoshua.compra(enrique_alfarero, 2); 
  yoshua.compra(manualidades1);
  Pedido p8(usuario_ped, pedido_art, yoshua, american_express, "5/4/2010");
  
  cout << p5 << endl << p6 << endl << p7 << endl << p8 << endl
    
       << "\n" AZUL "-------------------DETALLE DE PEDIDOS--------------"
    NORMAL "\n";
  pedido_art.mostrarDetallePedidos(cout);
  cout << "\n" AZUL "------------------VENTAS DE ARTÍCULOS--------------"
    NORMAL "\n";
  pedido_art.mostrarVentasArticulos(cout);
  
  cerr << "\n" AZUL "-----------------PRUEBAS DE EXCEPCIONES------------"
    NORMAL "\n";
  try {
    Pedido nulo(usuario_ped, pedido_art, lucas, visa2);
  }
  catch(Pedido::Vacio& e) {
    cerr << "Error de pedido: el carrito de " << e.usuario().id() 
	      << " está vacío. " << endl;
  }
  try {
    krispin.compra(manualidades1);
    Pedido farsante(usuario_ped, pedido_art, krispin, visa2);
  }
  catch(Pedido::Impostor& e) {
    cerr << "Error de pedido: la tarjeta de pago no es de " 
	      << e.usuario().id() << endl;
  }
  try {
    yessi.compra(enrique_alfarero, 2); 
    yessi.compra(salem, 4); 
    yessi.compra(bracula, 5);
    Pedido no_disponible(usuario_ped, pedido_art, yessi, dinners_club);
  }
  catch(Pedido::SinStock& e) {
    cerr << "Error de pedido: no hay existencias del artículo [" 
	      << e.articulo().referencia() << "]" << endl;
  }
  try {
    // Creamos una tarjeta que caducó ayer. ¿Qué pasa? ¡No somos un
    // maldito banco, esto es una prueba!
    Tarjeta caduca(Numero("4222222222222"), lucas, Fecha() - 1); 
    lucas.compra(enrique_alfarero, 2);
    Pedido no_pagado(usuario_ped, pedido_art, lucas, caduca); // pedido hoy
  }
  catch(Tarjeta::Caducada& e) {
    cerr << "Error de pedido: tarjeta caducada el " << e.cuando()
	      << endl;
  }
  try {
    Articulo::Autores a;
    Libro anonimo(a, "133", "El Necronomicón", 
		  "10/3/2009", 35.00, 210, 4);
  }
  catch(Articulo::Autores_vacios) {
    cerr << "Error de artículo: No se puede crear uno anónimo.\n";
  }
  // Por último: impresión del número total de pedidos.
  cout << "\nNúmero total de pedidos: " 
       << Pedido::n_total_pedidos() << '\n' << endl;
}

