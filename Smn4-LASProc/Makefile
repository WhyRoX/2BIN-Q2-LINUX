CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS=exemple2 exemple3 exemple4 exemple5 ex2A.a ex2A.b

all: $(PROGS)

exemple2: exemple2.o utils.o
	gcc $(CFLAGS) -o exemple2 exemple2.o utils.o

exemple2.o: exemple2.c utils.h
	gcc $(CFLAGS) -c exemple2.c

exemple3: exemple3.o utils.o
	gcc $(CFLAGS) -o exemple3 exemple3.o utils.o

exemple3.o: exemple3.c utils.h
	gcc $(CFLAGS) -c exemple3.c

exemple4: exemple4.o utils.o
	gcc $(CFLAGS) -o exemple4 exemple4.o utils.o

exemple4.o: exemple4.c utils.h
	gcc $(CFLAGS) -c exemple4.c

exemple5: exemple5.o utils.o
	gcc $(CFLAGS) -o exemple5 exemple5.o utils.o

exemple5.o: exemple5.c utils.h
	gcc $(CFLAGS) -c exemple5.c




ex2A.b: ex2A.b.o utils.o
	gcc $(CFLAGS) -o ex2A.b ex2A.b.o utils.o

ex2A.b.o: ex2A.b.c utils.h
	gcc $(CFLAGS) -c ex2A.b.c

ex2A.a: ex2A.a.o utils.o
	gcc $(CFLAGS) -o ex2A.a ex2A.a.o utils.o

ex2A.a.o: ex2A.a.c utils.h
	gcc $(CFLAGS) -c ex2A.a.c

utils.o: utils.c utils.h
	gcc $(CFLAGS) -c utils.c

clean:
	rm *.o
	rm ._*
	rm $(PROGS)
