CC = gcc
STANDARD = c99
INCLUDES = -I ./includes
#LIBS = -L ./libraries -l SDL2
SRC_DIR = ./sources
C_SOURCES = $(addprefix $(SRC_DIR)/, main.c linked_list.c dynamic_array.c)
OBJ_DIR = ./objects
C_OBJECTS = $(addprefix $(OBJ_DIR)/, main.o linked_list.o dynamic_array.o)
BIN = ./build.exe
C_FLAGS = -std=$(STANDARD) $(INCLUDES)

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