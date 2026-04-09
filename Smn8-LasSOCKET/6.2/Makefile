CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= client

all: $(ALL)

client : client.o utils.o
	$(CC) $(CCFLAGS) -o client client.o utils.o
client.o: client.c
	$(CC) $(CCFLAGS) -c client.c

utils.o: utils.c utils.h
	$(CC) $(CCFLAGS) -c utils.c

clean:
	rm -f *.o
	rm -f $(ALL)
	rm -f *.html