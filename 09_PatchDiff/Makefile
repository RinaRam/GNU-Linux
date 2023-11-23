CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O0 -g
TARGET = labirint labirint_1 labirint_2 labirint_3
TRASH = labirint_1* labirint_2* labirint_3* *.o

all:	$(TARGET) run

labirint_1.c:	labirint.c 0001_Size_indication.patch
	patch labirint.c -i 0001_Size_indication.patch -o labirint_1.c

labirint_2.c:	labirint.c 0002_PathAndWallSymbols_and_Size_indication.patch
	patch labirint.c -i 0002_PathAndWallSymbols_and_Size_indication.patch -o labirint_2.c

labirint_3.c:	labirint.c 0003_RandomSeed_PathAndWallSymbols_and_Size_indication.patch
	patch labirint.c -i 0003_RandomSeed_PathAndWallSymbols_and_Size_indication.patch -o labirint_3.c

labirint: labirint.c
	$(CC) -o $@ $^ 

labirint_1:	labirint_1.c
	$(CC) -o $@ $^

labirint_2:	labirint_2.c
	$(CC) -o $@ $^

labirint_3:	labirint_3.c
	$(CC) -o $@ $^

run:	$(TARGET)
	./labirint 
	./labirint_1 10
	./labirint_2 '*B' 7
	./labirint_3 42 ' x' 5

clean:
	rm -f $(TARGET) $(TRASH)