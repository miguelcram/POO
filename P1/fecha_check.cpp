#include "caclibrary.h"

#include <vector>
#include <iostream>

using namespace std;

  
int main(int argc, const char **argv){

	checkCode c(argc, argv, "fecha.cpp", "Orden: ./fecha_check fecha.cpp -- -std=c++11");

	c.setCorrectMessage("Verificación correcta de la clase Fecha.");
	c.setIncorrectMessage("REVISA LOS ERRORES DE FECHA.");

	if(c.findClass({"Fecha"})){
		
		c.staticVariable("Fecha", {"AnnoMaximo", "AnnoMinimo"}, {"const", "const"}, "Revisa el enunciado respecto a AnnoMinimo y AnnoMaximo.");

		c.defaultConstructor("Fecha", true, "Revisa el enunciado respecto a la construcción de objetos.");

                vector<string> parameters= {"int", "int", "int"};
		c.explicitSpecifiedConstructor("Fecha", parameters, "Revisa el enunciado respecto a conversiones implícitas.");

		vector<string> initializationList = {"int", "int", "int"};
		c.listInitializerConstructor("Fecha", initializationList, initializationList, "Revisa la inicialización de los atributos.");

		c.copyConstructor("Fecha", false, "Revisa el enunciado respecto al constructor de copia.");

		vector<string> consts = {"?", "?", "?", "?", "?"};
		vector<vector<string> > params = {{"?"}, {"?"}, {"?"}, {"?"}, {"?"}};
		c.methodWithReferencedMethod({"operator-=", "operator+", "operator-", "operator++", "operator--"}, params, "Fecha", consts,
					     {"operator+=", "operator+=", "operator+=", "operator+=", "operator+="}, params, "Fecha", consts,
					     "Revisa los consejos sobre los operadores aritméticos.");

		params = {{"?"}, {"?"}, {"?"}, {"?"} };
		c.functionWithReferencedFunction({"operator!=", "operator>", "operator<=", "operator>="}, params,   
						 {"operator==", "operator<", "operator<", "operator<"}, params,
						 "Revisa los consejos sobre los operadores de comparación.");


		params = {{"?"}};
		c.inlineMethod({"dia"}, params, "Fecha", {"const"}, 
			"Sugerencia: incluir marca 'inline' a aquellos métodos con pocas instrucciones, como 'dia()'."); 
		
		c.noExceptMethod({"dia"}, params, "Fecha", {"const"}, 
			"Sugerencia: incluir marca 'noexcept' a aquellos métodos que no lancen excepciones."); 		

		vector<string> functionNames = {"ssprintf", "sscanf"};
		string headerName = "cstdio";
		c.fileIncludedHeader(headerName, {"fecha.cpp", "fecha.hpp"}, "Revisa de dónde son tomadas las funciones ssprintf y sscanf.");

  		c.check();

	}else{
		llvm::outs()<<"No se ha encontrado la clase 'Fecha'"<<"\n";
	}

  	return 0;
}

