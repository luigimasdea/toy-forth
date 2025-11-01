TARGET = toyforth
SRC = main.c memory.c tfobj.c stack.c
CC = gcc

CFLAGS = -O3 -Wall -Wextra

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	rm $(TARGET)
