CFLAGS=-Wall -O2 -std=c++11 -fPIC
LDFLAGS=-lpthread -shared

SRC = ./src/destruirProcesoPar.cpp ./src/enviarMensajeProcesoPar.cpp ./src/establecerFuncionDeEscucha.cpp ./src/lanzarProcesoPar.cpp

OBJ = $(SRC:.cpp=.o)

OUT = ./lib/libproyectopar.so

all: $(OUT)

./lib:
	mkdir ./lib

${OUT}: $(OBJ) ./lib
	ar rcs $@ $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) 