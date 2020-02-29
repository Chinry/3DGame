NAME = game
DEBUGFLAGS = -g
CFLAGS = -Wall
CC = gcc
LIBS = -lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp

all: main.o
	gcc -o $(NAME) $(LIBS) main.o

main.o: main.c
	$(CC) -c -o main.o main.c
