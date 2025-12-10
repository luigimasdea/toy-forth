CC = gcc
TARGET = toyforth

SRC_FILES = memory.c tfobj.c list.c stack.c parser.c exec.c primitives.c symbol.c interpreter.c compiler.c
SRC = $(addprefix src/, $(SRC_FILES))

CFLAGS = -Wall -Wextra -g

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) main.c $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	rm $(TARGET)
