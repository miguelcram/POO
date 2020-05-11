CXX = clang++
STD = c++17
CXXFLAGS = -std=${STD} -g -Wall -pedantic -Wextra -Wfloat-equal -Wundef\
			-Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls\
			-Wshadow -Woverloaded-virtual
CPPFLAGS = -DP1 -I../Tests-auto -I.
VPATH = ../Tests-auto:.
SRC = fecha.cpp cadena.cpp test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp test-auto.cpp test-P1-consola.cpp

RMV = rm -f
OBJ := $(SRC:.cpp=.o)
MAIN_EXE = test-P1-consola
TEST_AUTO = test-P1-auto

CHECK_SRC = fecha_check.cpp cadena_check.cpp
CHECK_EXE = ${CHECK_SRC:.cpp=}

all: ${MAIN_EXE} ${TEST_AUTO}

run-auto: ${TEST_AUTO}
		@./$<

run-console: ${MAIN_EXE}
		@./$<

valgrind: ${MAIN_EXE} ${TEST_AUTO}
		valgrind ./${TEST_AUTO} --logger=minimal
		valgrind ./${MAIN_EXE}

${MAIN_EXE}: fecha.o cadena.o test-P1-consola.o
		@echo "Enlazando Objetos test-P1-consola"
		@$(CXX) $(CXXFLAGS) $^ -o $@

${TEST_AUTO}: fecha.o cadena.o test-auto.o test-caso0-fecha-auto.o test-caso0-cadena-auto.o
		@echo "Enlazando Objetos test-P1-auto"
		@$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ): $(SRC)

$(CHECK_EXE): $(CHECK_SRC)
		@$(MAKE) -f Make_check.mk

check: $(CHECK_EXE)
		./fecha_check fecha.cpp -- -std=${STD}
		./cadena_check cadena.cpp -- -std=${STD}

clean:
		@echo "Procediendo a limpieza..."
		@$(MAKE) -f Make_check.mk clean
		@$(RM) $(OBJ) $(MAIN_EXE) $(TEST_AUTO)