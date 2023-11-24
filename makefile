CC = gcc
STANDARD = c99
INCLUDES = -I ./includes/ -I ./includes/SDL2 -I ./includes/SDL2_gfx
LIBS = -L ./libraries -l SDL2
SRC_DIR = ./sources
C_SOURCES = $(addprefix $(SRC_DIR)/, main.c SDL2_gfxPrimitives.c SDL2_rotozoom.c lists.c graphics.c saves.c)
OBJ_DIR = ./objects
C_OBJECTS = $(addprefix $(OBJ_DIR)/, main.o SDL2_gfxPrimitives.o SDL2_rotozoom.o lists.o graphics.o saves.o)
BIN = ./build.exe
C_FLAGS = -std=$(STANDARD) $(INCLUDES) $(LIBS) -g3

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

$(C_OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# gcc main.c sdl_config.c -std=c99 -Wall -Werror -I .\includes\SDL2 -L .\libraries -l SDL2 -o gameszko.exe
build: $(C_OBJECTS)
	$(CC) $(C_FLAGS) $(C_OBJECTS) -o $(BIN)

run:
	$(BIN)