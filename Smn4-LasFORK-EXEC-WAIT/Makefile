CFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS= ex2Aa ex2Ab ex2Ac

ALL: $(PROGS)

ex2Aa: ex2Aa.o
	gcc $(CFLAGS) -o ex2Aa ex2Aa.o

ex2Aa.o: ex2Aa.c
	gcc $(CFLAGS) -c ex2Aa.c

ex2Ab: ex2Ab.o
	gcc $(CFLAGS) -o ex2Ab ex2Ab.o

ex2Ab.o: ex2Ab.c
	gcc $(CFLAGS) -c ex2Ab.c

ex2Aa: ex2Ac.o
	gcc $(CFLAGS) -o ex2Ac ex2Ac.o

ex2Aa.o: ex2Ac.c
	gcc $(CFLAGS) -c ex2Ac.c

# utils_v1.o: ../../utils_v1.h ../../utils_v1.c
#         gcc $(CFLAGS) -c ../../utils_v1.c

c:
	rm ._*
	rm -f *.o