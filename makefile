CC = gcc
STANDARD = c99
INCLUDES = -I ./headers -I ./includes/**
LIBS = -L ./libraries -l SDL2
SRC_PATH = ./sources/
IN = $(SRC_PATH)main.c $(SRC_PATH)sdl_config.c $(SRC_PATH)graph.c
OUT = build.exe
CFLAGS = -std=$(STANDARD) -Wall -Werror $(INCLUDES) $(LIBS) 

# gcc main.c sdl_config.c -std=c99 -Wall -Werror -I .\includes\SDL2 -L .\libraries -l SDL2 -o gameszko.exe
build:
	$(CC) $(IN) $(CFLAGS) -o $(OUT)

run:
	$(OUT)