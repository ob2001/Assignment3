CC = gcc

CFLAGS = -ansi -Wall

all: babyQuery.o funcs.o removeCommas.o
	$(CC) $(CFLAGS) -o babyQuery babyQuery.o funcs.o removeCommas.o

babyQuery.o: babyQuery.c
	$(CC) $(CFLAGS) -c babyQuery.c

funcs.o: funcs.c
	$(CC) $(CFLAGS) -c funcs.c

clean:
	-rm babyQuery.o funcs.o babyQuery
