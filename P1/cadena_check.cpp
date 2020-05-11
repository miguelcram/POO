#include "caclibrary.h"

#include <vector>
#include <iostream>

using namespace std;

int main(int argc, const char **argv){

	checkCode c(argc, argv, "cadena.cpp", "Orden: ./cadena_check cadena.cpp -- -std=c++11");
	c.setCorrectMessage("Verificación correcta de la clase Cadena.");
	c.setIncorrectMessage("REVISA LOS ERRORES DE CADENA.");

	if(c.findClass({"Cadena"})){

		c.defaultConstructor("Cadena", "Revisa el enunciado respecto a la construcción de objetos.");

		vector<string> params = {"unsigned long", "char"};
		c.explicitSpecifiedConstructor("Cadena", params, "Revisa el enunciado respecto a conversiones implícitas.");

		vector<string> initializationList = {"?"};
		vector<string> parameters = {"?"};
		c.listInitializerConstructor("Cadena", parameters, initializationList, "Revisa la inicialización de los atributos.");

	        c.numberOfConstructors("Cadena", 3, true, "Número de constructores incorrecto.");

		vector<string> memoryFunctionNames = {"malloc","calloc", "realloc", "free"};
		string memoryHeaderName = "stdlib";
		c.invocationsFromHeaders(memoryFunctionNames, memoryHeaderName, false, "Revisa la asignación y destrucción de memoria de variables.");

		c.takeException({"out_of_range"}, "Revisa las excepciones que se han de lanzar en el programa.");
		c.fileIncludedHeader("stdexcept", {"cadena.cpp", "cadena.hpp"}, "Comprueba haber incluido las cabeceras adecuadas en tus ficheros.");

		vector<string> standardFunctionNames = {"strlen","strcat", "memset", "strcpy"};
		string standardHeaderName = "cstring";
		c.invocationsFromHeaders(standardFunctionNames, standardHeaderName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");

		c.destructorDeleteMember("Cadena", {"s_"}, "Revisa el destructor de la clase.");

		c.releaseVariable("Revisa la asignación y liberación de memoria de variables.");

		vector<string> methodNames = {"length"};
		vector<vector<string> > parametersMethods = {{"?"}};
		c.inlineMethod(methodNames, parametersMethods, "Cadena", {"?"}, "Sugerencia: incluir marca 'inline' a aquellos métodos con pocas instrucciones, como 'length()'.");

		c.noExceptMethod(methodNames, parametersMethods, "Cadena", {"?"}, "Sugerencia: incluir marca 'noexcept' a aquellos métodos que no lancen excepciones, como 'length()'");

		c.guardClauses("cadena.hpp", "Recuerda incluir las guardas de inclusión.");

                c.moveConstructor("Cadena", "Revisa el enunciado respecto a los constructores.");

                c.notFriendMember("Cadena", "Revisa por qué es necesario incluir 'friend'.");

                c.function({"operator<<", "operator>>", "operator>", "operator<", "operator>=", "operator<=", "operator==", "operator!=", "operator+"}, {{"?"}, {"?"}, {"?"}, {"?"}, {"?"}, {"?"}, {"?"}, {"?"}, {"?"}}, "Revisa el lugar de la declaración de los operadores.");

                vector<vector<string> > parametros = {{"?"}, {"?"}, {"?"}, {"?"} };
                c.methodWithReferencedMethod({"rbegin", "crbegin", "rend", "crend"}, parametros, "Cadena", {"?", "?", "?", "?"},
                                             {"end", "end", "begin", "begin"}, parametros, "Cadena", {"?", "?", "?", "?"},
                                             "Emplea la reutilización en las funciones sobre iteradores.");

		c.check();

	}else{
		llvm::outs()<<"No se ha encontrado la clase 'Cadena'"<<"\n";
	}

	return 0;
}
