CC=gcc
CFLAGS=-Wall -g

SRC=src
OBJ=obj
OUTPUT=output
LFLAGS=-lm

all: criar_pastas main

criar_pastas:
	@mkdir -p ${OBJ} ${OUTPUT}

${OBJ}/espquadrada.o: ${SRC}/espquadrada.c
	${CC} ${CFLAGS} -c ${SRC}/espquadrada.c -o ${OBJ}/espquadrada.o

${OBJ}/esptriangular.o: ${SRC}/esptriangular.c
	${CC} ${CFLAGS} -c ${SRC}/esptriangular.c -o ${OBJ}/esptriangular.o

main: ${OBJ}/espquadrada.o ${OBJ}/esptriangular.o
	${CC} ${CFLAGS} ${OBJ}/espquadrada.o \
	-o ${OUTPUT}/espquadrada ${LFLAGS}

	${CC} ${CFLAGS} ${OBJ}/esptriangular.o \
	-o ${OUTPUT}/esptriangular

clean:
	rm -r ${OBJ} ${OUTPUT}