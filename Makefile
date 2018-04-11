CC=clang++
CFLAGS=-Wall -O3 -pedantic -fsanitize=address --std=c++14
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfgui

all:
	$(CC) $(CFLAGS) $(SFMLFLAGS) -o build/main src/main.cc
