CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE
ALL = child_3A

all: $(ALL)

child_3A: child_3A.o utils_v2.o
	cc $(CFLAGS) -o child_3A child_3A.o utils_v2.o

child_3A.o: child_3A.c utils_v2.h
	cc $(CFLAGS) -c child_3A.c

utils_v2.o: utils_v2.c utils_v2.h
	cc $(CFLAGS) -c utils_v2.c

clean:
	rm ._*
	rm -f *.o
	rm -f $(ALL)