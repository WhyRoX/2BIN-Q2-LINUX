CFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

ALL= exemple9 exemple10 exemple11 exemple12 chat4.1a

all: $(ALL)

chat4.1a: chat4.1a.o utils_v2.o
	gcc $(CFLAGS) -o chat4.1a chat4.1a.o utils_v2.o

chat4.1a.o: chat4.1a.c utils_v2.h
	gcc $(CFLAGS) -c chat4.1a.c

exemple9: exemple9.o utils_v2.o
	gcc $(CFLAGS) -o exemple9 exemple9.o utils_v2.o

exemple9.o: exemple9.c utils_v2.h
	gcc $(CFLAGS) -c exemple9.c

exemple10: exemple10.o utils_v2.o
	gcc $(CFLAGS) -o exemple10 exemple10.o utils_v2.o

exemple10.o: exemple10.c utils_v2.h
	gcc $(CFLAGS) -c exemple10.c

exemple11: exemple11.o utils_v2.o
	gcc $(CFLAGS) -o exemple11 exemple11.o utils_v2.o

exemple11.o: exemple11.c utils_v2.h
	gcc $(CFLAGS) -c exemple11.c

exemple12: exemple12.o utils_v2.o
	gcc $(CFLAGS) -o exemple12 exemple12.o utils_v2.o

exemple12.o: exemple12.c utils_v2.h
	gcc $(CFLAGS) -c exemple12.c

utils_v2.o: utils_v2.c utils_v2.h
	gcc $(CFLAGS) -c utils_v2.c

clean:
	rm ._*
	rm -f *.o
	rm -f $(ALL)

cl:
	rm ._*