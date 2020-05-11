# $Id: Makefile 414 2018-04-16 10:13:23Z gerardo $
# Makefile para la práctica 2, casos de uso 1 y 2 de la librería electrónica
# ©2009-2020 Los profesores de POO
#
# --- Parte configurable ---

# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, P2, P3 y P4. En esta práctica, P2.
# NOMBREALUMNO debe ser de la forma: Apellido1_Apellido2_Nombre_de_pila.
# Ejemplo: Para Pánfilo Pancracio Povedilla Putiérrez sería:
# Povedilla_Putierrez_PanfiloPancracio, y debajo de ese directorio estarían
# P1, P4 y los directorios Tests-auto y dsl-comprobaciones (y P0, P2 y P3).
# Véanse las instrucciones de entrega en el enunciado.
NA = $(shell dirname ${PWD})
NOMBREALUMNO = $(notdir ${NA})

# DIRFECHACADENA es el directorio donde están las cabeceras, fuentes o módulos
# objeto de las clases Cadena y Fecha de P1, y su Makefile.
# NOTA IMPORTANTE: Este Makefile supone que ya Cadena y Fecha están hechos y
# no se modifican. Si se cambiara algo en ellos, habría que recompilar.
DFC = P1
DIRFECHACADENA = ../${DFC}

# Esto debe dejarse así para que funcionen los tests automáticos.
# DIRTESTS es el directorio donde están los ficheros del programa de pruebas
# unitarias automáticas.
DIRTESTS = ../Tests-auto
NOMBREPRACTICA := P2
INCLUDES  = -I${DIRFECHACADENA} -I${DIRTESTS} -I.

# DIRLUHN es el directorio donde está el fichero luhn.cpp con la función luhn
DIRLUHN = ..

# Compilador de C++ preferido: el de LLVM (clang++), el de GNU (g++),
# el de GNU en la versión N (g++-N), el de Intel (icpc)...
CXX = clang++

# ¿Qué estándar seguir?
# c++98 o c++03 (-ansi): estándar de 1998, corregido en 2003. NO USAR YA.
# c++11: estándar de 2011 - Versión mínima necesaria.
# c++14: estándar de 2014 - Recomendado si su compilador lo admite.
# c++17: estándar de 2017 - Se puede usar si su compilador lo admite.
# c++20: estándar previsto para 2020. Experimental, no recomendado.
STD = c++17

# Opciones para el compilador. Añada o quite las que prefiera pero deje
# al menos la primera. Recomendado: no quite ninguna.
# -std=${STD}: el estándar de C++ a utilizar, en $(STD)
# -g         : para poder depurar, si hay que hacerlo
# -pedantic  : para que se ajuste sin desvíos del estándar empleado
# -Wall      : para que dé todo tipo de avisos, no solo los normales
CXXFLAGS = -std=${STD} -g -pedantic -Wall -Wextra -Wfloat-equal -Wundef\
			-Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls\
			-Wshadow -Woverloaded-virtual

# Opciones del preprocesador. No las quite.
# -I : directorio donde buscar cabeceras adicionales (#include "...")
# -D : define una macro del preprocesador, como #define
CPPFLAGS = ${INCLUDES} -D${NOMBREPRACTICA}

# --- Fin parte configurable

LOCALLIBS = cadena.o fecha.o luhn.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${DIRTESTS}:${DIRFECHACADENA}:${DIRLUHN}

# Estos son los ficheros que tiene que hacer el alumno. El resto se le da.
OWN_SRCS  = usuario.cpp tarjeta.cpp articulo.cpp
OWN_HDRS  = $(OWN_SRCS:.cpp=.hpp)

OWN_OBJS  = $(OWN_SRCS:.cpp=.o)

MAIN_SRCS = test-caso1-consola.cpp
MAIN_OBJS = ${MAIN_SRCS:.cpp=.o}
MAIN_EXE  = ${MAIN_SRCS:.cpp=}

TEST_SRCS = test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
            test-caso1-2-auto.cpp test-auto.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-P2-auto
TEST_HDRS = test-auto.hpp fct.h

CHECK_SRC = compra_check.cpp
CHECK_OBJ = ${CHECK_SRC:.cpp=.o}
CHECK_EXE = ${CHECK_SRC:.cpp=}

SRCS      = ${OWN_SRCS} $(MAIN_SRCS) ${TEST_SRCS} $(CHECK_SRC) \
            Makefile Make_check.mk
HDRS      = $(OWN_HDRS) $(TEST_HDRS)

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

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

# Hace comprobaciones en el código fuente
check:
	${MAKE} --file=Make_check.mk $@

# Ejecuta los tests comprobando que no haya fugas de memoria
valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind ./${TEST_EXE} --logger=minimal -v --leak-check=full
	valgrind ./${MAIN_EXE} -v --leak-check=full

# Construye el programa de prueba de consola
${MAIN_EXE}: ${MAIN_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de pruebas automáticas
${TEST_EXE}: ${TEST_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de comprobaciones del código fuente
${CHECK_EXE}:
	${MAKE} --makefile=Make_check.mk $@

# Dependencias y compilación
${MAIN_OBJS} ${TEST_OBJS} ${OWN_OBJS}: ${OWN_HDRS}
cadena.o: ${DIRFECHACADENA}/cadena.hpp
fecha.o : ${DIRFECHACADENA}/fecha.hpp

# Por si se cambia algo en los tests automáticos
${TESTS_OBJS}: ${TESTS_SRCS} ${TESTS_HDRS}

# Limpieza
clean:
	${RM} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
	      ${LOCALLIBS} ${OWN_OBJS} *.{aux,log,dvi,toc} *~ \#* core
	${MAKE} --makefile=Make_check.mk clean
	${MAKE} --directory=${DIRFECHACADENA} clean

# Esto lo deberían usar los alumnos a la hora de la entrega:
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
		${NOMBREDIR}/usuario.cpp  ${NOMBREDIR}/tarjeta.cpp  \
		${NOMBREDIR}/articulo.cpp ${NOMBREDIR}/usuario.hpp  \
		${NOMBREDIR}/tarjeta.hpp  ${NOMBREDIR}/articulo.hpp \
		${NOMBREALUMNO}/${DFC}/cadena.hpp \
		${NOMBREALUMNO}/${DFC}/cadena.cpp \
		${NOMBREALUMNO}/${DFC}/fecha.hpp  \
		${NOMBREALUMNO}/${DFC}/fecha.cpp  \
		${NOMBREALUMNO}/${DFC}/Makefile
endif

# Limpieza general del directorio y del archivo de distribución
distclean: clean
	${RM} ${NOMBRETAR}

# Objetivos falsos
.PHONY: all tests test-consola test-auto check valgrind clean dist distclean
