CC=clang++
CFLAGS=-Wall -O3 -pedantic -fsanitize=address --std=c++14
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfgui

# TODO make it better

all:
	$(CC) $(CFLAGS) $(SFMLFLAGS) -o build/main src/main.cc src/fractals/julia/keyboard.cc
