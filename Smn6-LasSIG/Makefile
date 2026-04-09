CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE
ALL = ex4.1a ex4.1b ex4.1c timer ex4.3

all: $(ALL)

ex4.1a: utils.o ex4.1a.o
	cc $(CFLAGS) -o ex4.1a utils.o ex4.1a.o

ex4.1a.o: utils.h ex4.1a.c
	cc $(CFLAGS) -c ex4.1a.c

ex4.1b: utils.o ex4.1b.o
	cc $(CFLAGS) -o ex4.1b utils.o ex4.1b.o

ex4.1b.o: utils.h ex4.1b.c
	cc $(CFLAGS) -c ex4.1b.c

ex4.1c: utils.o ex4.1c.o
	cc $(CFLAGS) -o ex4.1c utils.o ex4.1c.o

ex4.1c.o: utils.h ex4.1c.c
	cc $(CFLAGS) -c ex4.1c.c

timer: utils.o timer.o
	cc $(CFLAGS) -o timer utils.o timer.o

timer.o: utils.h timer.c
	cc $(CFLAGS) -c timer.c

ex4.3: utils.o ex4.3.o
	cc $(CFLAGS) -o ex4.3 utils.o ex4.3.o

ex4.3.o: utils.h ex4.3.c
	cc $(CFLAGS) -c ex4.3.c

utils.o: utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean:
	rm *.o
	rm ._*
	rm -f $(ALL)