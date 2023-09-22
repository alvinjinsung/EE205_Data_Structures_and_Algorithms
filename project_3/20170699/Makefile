CC = gcc
CFLAGS = -W -Wall

all: count

count: count.o
	$(CC) $(CFLAGS) -o count count.o

%.o: %.c
	$(CC) $(CFLAGS) $< -c

count.0: count.c

clean:
	@rm *.o count