CC = gcc
STANDARD = c99
INCLUDES = -I ./headers -I ./includes/**
LIBS = -L ./libraries/** -l SDL2
IN = ./sources/main.c
OUT = main.exe
CFLAGS = -std $(STANDARD) -Wall -Werror $(INCLUDES) $(LIBS) -o $(OUT)

build:
	$(CC) $(IN) $(CFLAGS)

run:
	$(OUT)