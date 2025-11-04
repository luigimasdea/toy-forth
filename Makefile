TARGET = toyforth
SRC = main.c memory.c tfobj.c list.c stack.c parser.c exec.c
CC = gcc

CFLAGS = -Wall -Wextra

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	rm $(TARGET)
