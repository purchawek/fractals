CC=clang++
CFLAGS=-Wall -pedantic -fsanitize=address --std=c++14
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) $(CFLAGS) $(SFMLFLAGS) -o build/main src/main.cc
