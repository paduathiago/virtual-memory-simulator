TARGET = tp2virtual

# Compilador C
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -pedantic

BUILD_DIR    = ./build
SRC_DIR    = ./src
INCLUDE_DIR  = ./include

clean:
	rm -rf $(BUILD_DIR)