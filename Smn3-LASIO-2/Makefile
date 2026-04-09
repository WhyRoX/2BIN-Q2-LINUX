CFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS=lire lireEtEcrire Maj maj min

all: lire lireEtEcrire

lireEtEcrire : lireEtEcrire.o utils.o
	gcc $(CFLAGS) -o lireEtEcrire lireEtEcrire.o utils.o

lire: lire.o utils.o
	gcc $(CFLAGS) -o lire lire.o utils.o

lireEtEcrire.o : lireEtEcrire.c utils.h
	gcc $(CFLAGS) -c lireEtEcrire.c

lire.o: lire.c utils.h
	gcc $(CFLAGS) -c lire.c

utils.o: utils.c utils.h
	gcc $(CFLAGS) -c utils.c

clean:
	rm *.o
	rm ._*
	rm $(PROGS)

LEE: lireEtEcrire
	./lireEtEcrire maj min