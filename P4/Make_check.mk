# $Id: Make_check.mk 416 2018-04-23 08:38:49Z u44965478 $
# Comprobaciones de código para P4
# ©2015 Pedro Delgado, para POO
# 2017 - Simplificación - Gerardo
# 2020 - usuario-pedido.cpp (no hpp) - Gerardo

# Directorio donde está el código compartido del DSL
DIR=../dsl-comprobaciones/

# Obligatorio Clang, versión 3.9 al menos.
CXX         := clang++
CPPFLAGS    := -I${DIR} $(shell llvm-config --cppflags)
CXXFLAGS    := -std=c++14
# Descomentar la siguiente línea para obtener un ejecutable enlazado 
# estáticamente muy grande y pesado pero que se puede distribuir al 
# alumnado para que no tengan que instalarse todos los paquetes de 
# desarrollo de LLVM/CLang.
LDFLAGS     := # -static
LLVMLDFLAGS := $(shell llvm-config --libs) $(LDFLAGS)
COMMONSRCS  := $(DIR)caclibrary.cpp $(DIR)execute.cpp $(DIR)matchers.cpp
SOURCES     := catalogo_check.cpp ${COMMONSRCS}
COMMONHDRS  := $(COMMONSRCS:.cpp=.h) $(DIR)info.h
COMMONOBJS  := $(COMMONSRCS:.cpp=.o)
OBJECTS     := $(SOURCES:.cpp=.o)
EXES        := catalogo_check
CLANGLIBS   := -lclangFrontend -lclangSerialization -lclangDriver \
		-lclangTooling -lclangParse -lclangSema -lclangAnalysis \
		-lclangEdit -lclangAST -lclangASTMatchers -lclangLex \
		-lclangBasic -lclangRewrite

.PHONY: clean all check check_pedido
all: $(EXES)

${EXES}: $(OBJECTS)
	@echo "(LINK) catalogo_check.o"
	$(CXX) -o $@ $^ $(CLANGLIBS) $(LLVMLDFLAGS)

catalogo_check.o: $(COMMONHDRS)

check check_catalogo: ${EXES}
	@echo Verificando los fuentes ...
	./${EXES} -extra-arg-before="-I../P1" -extra-arg="-std=c++14" \
		articulo.cpp usuario.cpp tarjeta.cpp pedido.cpp \
		pedido-articulo.cpp usuario-pedido.cpp -- 2> /dev/null

clean:
	@echo "Limpiando."
	@${RM} ${RMFLAGS} $(EXES) $(OBJECTS)
