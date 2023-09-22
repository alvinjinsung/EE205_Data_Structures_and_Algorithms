CC = gcc
CFLAGS = -W -Wall

all: quick minfine

quick: quick.o
	$(CC) $(CFLAGS) -o quick quick.o

minfine: minfine.o
	$(CC) $(CFLAGS) -o minfine minfine.o

%.o: %.c
	$(CC) $(CFLAGS) $< -c

quick.0: quick.c

minfine: minfine.c

clean:
	@rm *.o quick minfine