# $Id: Makefile 398 2017-05-17 15:24:34Z gerardo $
# Makefile para el caso 3 de la LIBRERÍA
# ©2010-2020 Los profesores de POO
#
# --- Parte configurable ---
#
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, P2, P3, P4. En esta práctica, P3.
# NOMBREALUMNO debería ser de la forma: Ap1_Ap2_NP
# (Véanse las instrucciones de entrega).
NA = $(shell dirname ${PWD})
NOMBREALUMNO = $(notdir ${NA})

# DIRFECHACADENA es el directorio donde están las cabeceras, fuentes o módulos
# objeto de Cadena y Fecha, y su Makefile.
DFC = P1
DIRFECHACADENA = ../${DFC}

# DIRLUHN es el directorio donde está el fichero luhn.cpp con la función luhn
DIRLUHN = ..

# Esto debe dejarse así para que funcionen los tests
# DIRTESTS es el directorio donde están los ficheros del programa de pruebas
# unitarias automáticas.
DIRTESTS = ../Tests-auto
NOMBREPRACTICA := P3
INCLUDES  = -I${DIRFECHACADENA} -I${DIRTESTS} -I.

# Compilador de C++ preferido: el de LLVM (clang++), el de GNU (g++),
# el de GNU en la versión 6, 7 u 8 (g++-8), el de Intel (icpc)...
CXX = clang++

# ¿Qué estándar seguir?
# ansi o c++98 o c++03: estándar de 1998, corregido en 2003. NO USAR YA.
# c++0x: borrador del estándar de 2011. Solo si el compilador es antiguo.
# c++11: estándar de 2011 - Versión mínima necesaria.
# c++14: estándar de 2014 - Recomendado si su compilador lo admite.
# c++17: estándar de 2017 - Recomendado si su compilador lo admite.
# c++2a: estándar previsto para 2020. Experimental, no recomendado.
STD = c++17

# Opciones para el compilador. Añada o quite las que prefiera pero deje
# la primera. Recomendado: no quite ninguna.
CXXFLAGS = -std=${STD} -g -pedantic -Wall
# Opciones del preprocesador. No quite estas.
CPPFLAGS = ${INCLUDES} -D${NOMBREPRACTICA}

# --- Fin parte configurable

LOCALLIBS = cadena.o fecha.o luhn.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${DIRFECHACADENA}:${DIRLUHN}:${DIRTESTS}

# Estos son los ficheros que tiene que hacer el alumno. El resto se le da.
# NOTA IMPORTANTE: usuario-pedido.cpp no hace falta si se hacen los métodos
# de Usuario_Pedido inline, pero si se definen normales en usuario-pedido.cpp, 
# añádase a OWN_SRCS y quítese usuario-pedido.hpp de OWN_HDRS.
OWN_SRCS  = usuario.cpp tarjeta.cpp articulo.cpp \
	pedido-articulo.cpp pedido.cpp usuario-pedido.cpp
OWN_HDRS  = $(OWN_SRCS:.cpp=.hpp)
OWN_OBJS  = $(OWN_SRCS:.cpp=.o)

MAIN_SRCS = test-caso3-consola.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = ${MAIN_SRCS:.cpp=}

TEST_SRCS = test-caso0-cadena-auto.cpp test-caso0-fecha-auto.cpp \
  test-caso1-2-auto.cpp test-caso3-auto.cpp test-auto.cpp
TEST_HDRS = test-auto.hpp fct.h
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-P3-auto

CHECK_SRC = pedido_check.cpp
CHECK_OBJ = ${CHECK_SRC:.cpp=.o}
CHECK_EXE = ${CHECK_SRC:.cpp=}

SRCS      = ${OWN_SRCS} $(MAIN_SRCS) ${TEST_SRCS} $(CHECK_SRC) \
            Makefile Make_check.mk
HDRS      = $(OWN_HDRS)

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
D = ${NOMBREALUMNO}/${NOMBREPRACTICA}

## OBJETIVOS PRINCIPALES

# Construye los programas de prueba
all: ${MAIN_EXE} ${TEST_EXE}

# Ejecuta los programas de prueba
tests: test-consola test-auto

# Ejecuta el test de consola
test-consola: ${MAIN_EXE}
	./$<

# Ejecuta los tests unitarios
test-auto: ${TEST_EXE}
	./$<

# Hace comprobaciones del código fuente
check:  ${OWN_SRCS}
	${MAKE} --file=Make_check.mk $@

# Ejecuta los tests comprobando que no haya fugas de memoria
valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind --quiet ./${TEST_EXE} --logger=minimal
	valgrind --quiet ./${MAIN_EXE}

# Construye el programa de prueba de consola
${MAIN_EXE}: ${MAIN_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de pruebas automáticas
${TEST_EXE}: ${TEST_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de comprobaciones sobre el código fuente
${CHECK_EXE}: ${CHECK_SRC}
	${MAKE} --file=Make_check.mk $@

# Detección automática de dependencias en código fuente C++ #
%.d: %.cpp
	@$(CXX) -MM ${CPPFLAGS} $(CXXFLAGS) $< > $@
	@sed --regexp-extended --in-place 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d) $(OWN_SRCS:.cpp=.d)

# Por si acaso aún hay cambios en Fecha y Cadena...
cadena.o: ${DIRFECHACADENA}/cadena.hpp
fecha.o : ${DIRFECHACADENA}/fecha.hpp

# Limpieza
clean:
	${RM} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
	      ${OWN_OBJS} ${LOCALLIBS} *.d *.{aux,log,dvi,toc} *~ \#* core
	${MAKE} --directory=${DIRFECHACADENA} clean
	${MAKE} --file=Make_check.mk clean

distclean: clean
	${RM} ${NOMBRETAR}


## Empaquetado

# Esto lo deben usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: distclean ${NOMBRETAR}

${NOMBRETAR}: ${OWN_SRCS} ${OWN_HDRS}
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: debe definir en el Makefile la variable NOMBREALUMNO"
	@echo "con el nombre del directorio superior a este."
	@echo " Vea las instrucciones de entrega de las prácticas."
else
	@echo "Creando archivo en ${NOMBRETAR} con el siguiente contenido:"
	@tar --create --verbose --gzip --file=${NOMBRETAR} --directory=../.. \
		$D/usuario.cpp  $D/usuario.hpp  \
		$D/articulo.cpp $D/articulo.hpp \
		$D/tarjeta.cpp  $D/tarjeta.hpp  \
		$D/pedido.cpp   $D/pedido.hpp   \
		$D/pedido-articulo.cpp $D/pedido-articulo.hpp \
		$D/usuario-pedido.cpp  $D/usuario-pedido.hpp  \
		${NOMBREALUMNO}/${DFC}/cadena.hpp \
		${NOMBREALUMNO}/${DFC}/cadena.cpp \
		${NOMBREALUMNO}/${DFC}/fecha.hpp  \
		${NOMBREALUMNO}/${DFC}/fecha.cpp  \
		${NOMBREALUMNO}/${DFC}/Makefile
endif

# Objetivos falsos
.PHONY: all tests test-consola test-auto check valgrind clean dist distclean
