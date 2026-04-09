CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE

all : encryptROT13 decryptROT13 encryptPolybe decryptPolybe

decryptPolybe : decryptPolybe.o utils.o cryptPolybe.o
	cc $(CFLAGS) -o decryptPolybe decryptPolybe.o utils.o cryptPolybe.o

encryptPolybe : encryptPolybe.o utils.o
	cc $(CFLAGS) -o encryptPolybe encryptPolybe.o utils.o

cryptPolybe : cryptPolybe.o utils.o
	cc $(CFLAGS) -o cryptPolybe cryptPolybe.o utils.o

decryptROT13 : decryptROT13.o utils.o cryptROT13.o
	cc $(CFLAGS) -o decryptROT13 decryptROT13.o utils.o cryptROT13.o

encryptROT13 : encryptROT13.o utils.o cryptROT13.o
	cc $(CFLAGS) -o encryptROT13 encryptROT13.o utils.o cryptROT13.o

decryptPolybe.o : decryptPolybe.c utils.h cryptPolybe.h
	cc $(CFLAGS) -c decryptPolybe.c

encryptPolybe.o : encryptPolybe.c utils.h cryptPolybe.h
	cc $(CFLAGS) -c encryptPolybe.c

cryptPolybe.o : cryptPolybe.c utils.h cryptPolybe.h
	cc $(CFLAGS) -c cryptPolybe.c

decryptROT13.o : decryptROT13.c utils.h cryptROT13.h
	cc $(CFLAGS) -c decryptROT13.c

encryptROT13.o : encryptROT13.c utils.h cryptROT13.h
	cc $(CFLAGS) -c encryptROT13.c

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c
cryptROT13.o : cryptROT13.c cryptROT13.h
	cc $(CFLAGS) -c cryptROT13.c

clean :
	rm *.o
	rm encryptROT13
	rm decryptROT13
	rm cryptPolybe
	rm ._*