CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= exemple15_Serveur exemple15_Client

all: $(ALL)

exemple15_Serveur: exemple15_Serveur.o utils_v2.o
	$(CC) $(CCFLAGS) -o exemple15_Serveur exemple15_Serveur.o utils_v2.o
						
exemple15_Serveur.o: exemple15_Serveur.c 
	$(CC) $(CCFLAGS) -c exemple15_Serveur.c

exemple15_Client: exemple15_Client.o utils_v2.o
	$(CC) $(CCFLAGS) -o exemple15_Client exemple15_Client.o utils_v2.o

exemple15_Client.o: exemple15_Client.c
	$(CC) $(CCFLAGS) -c exemple15_Client.c

utils_v2.o: utils_v2.c utils_v2.h
	$(CC) $(CCFLAGS) -c utils_v2.c

clean: 
	rm -f $(ALL) *.o