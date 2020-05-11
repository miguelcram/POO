CXX = clang++	# Compilador
STD = c++17
CXXFLAGS = -std=${STD} -g -Wall -pedantic -Wextra	# Opciones del compilador
CPPFLAGS = -DP0 -I../Tests-auto -I.
VPATH = ../Tests-auto:.
SRC = fecha.cpp test-auto.cpp test-caso0-fecha-auto.cpp test-PO-consola.cpp

RMV = rm -f
OBJ := $(SRC:.cpp=.o)
EXE = test-PO-consola
AUTO = test-auto

all: ${EXE} ${AUTO}

run-auto: ${AUTO}
		./$<

run-console: ${EXE}
		./$<

run-dsl: fecha_check
		./fecha_check fecha.cpp -- -std=${STD}

fecha_check: fecha_check.cpp
		$(MAKE) -f Make_check.mk

${EXE}: fecha.o test-PO-consola.o
		$(CXX) $(CXXFLAGS) $^ -o $@

${AUTO}: test-caso0-fecha-auto.o test-auto.o fecha.o
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ): $(SRC)

cadena_check: cadena_check.cpp
		${MAKE} -f Make_check.mk

limpia:
		$(RMV) *.o
		$(MAKE) -f Make_check.mk clean