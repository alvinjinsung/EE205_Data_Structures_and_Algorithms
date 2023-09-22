CC = gcc
CFLAGS = -W -Wall

all: test dist

test: msort.o test.o 
	$(CC) $(CFLAGS) -o test msort.o test.o

dist: dist.o msort.o
	$(CC) $(CFLAGS) -o dist dist.o msort.o 

%.o: %.c
	$(CC) $(CFLAGS) $< -c

msort.o: msort.c msort.h

test.o: test.c

clean:
	@rm *.o test dist