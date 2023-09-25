CC=gcc
CFLAGS=-lncurses -Wall -Wextra -pedantic
TARGET=Show

all: $(TARGET)

$(TARGET): Show.c
	$(CC) -o $(TARGET) Show.c $(CFLAGS)

clean:
	rm -f $(TARGET)
