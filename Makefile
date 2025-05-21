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
	${CC} ${CFLAGS} -c ${SRC}/espquadrada.c -o ${OBJ}/espquadrada.o ${LFLAGS}

${OBJ}/esptriangular.o: ${SRC}/esptriangular.c
	${CC} ${CFLAGS} -c ${SRC}/esptriangular.c -o ${OBJ}/esptriangular.o ${LFLAGS}

${OBJ}/minhaesp.o: ${SRC}/minhaesp.c
	${CC} ${CFLAGS} -c ${SRC}/minhaesp.c -o ${OBJ}/minhaesp.o ${LFLAGS}

main: ${OBJ}/espquadrada.o ${OBJ}/esptriangular.o ${OBJ}/minhaesp.o
	${CC} ${CFLAGS} ${OBJ}/espquadrada.o \
	-o ${OUTPUT}/espquadrada ${LFLAGS}

	${CC} ${CFLAGS} ${OBJ}/esptriangular.o \
	-o ${OUTPUT}/esptriangular ${LFLAGS}

	${CC} ${CFLAGS} ${OBJ}/minhaesp.o \
	-o ${OUTPUT}/minhaesp ${LFLAGS}

clean:
	rm -r ${OBJ} ${OUTPUT}