CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= server client

all: $(ALL)

server : server.o utils_v2.o
	$(CC) $(CCFLAGS) -o server server.o utils_v2.o
server.o: server.c messages.h
	$(CC) $(CCFLAGS) -c server.c

client : client.o utils_v2.o
	$(CC) $(CCFLAGS) -o client client.o utils_v2.o
client.o: client.c messages.h
	$(CC) $(CCFLAGS) -c client.c

utils_v2.o: utils_v2.c utils_v2.h
	$(CC) $(CCFLAGS) -c utils_v2.c

clean:
	rm ._*
	rm -f *.o
	rm -f $(ALL)		