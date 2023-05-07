CC = g++
CGLAGS = -g -Wall -Werror -Wconversion -lm

all: juego

test.o: lista.h nodo.h tablero.h test.cpp
	$(CC) -g -c -Wall -Werror -Wconversion -lm test.cpp

juego: test.o
	$(CC) -g  -Wall -Werror -Wconversion -lm test.o -o juego

clean:
	rm *.o