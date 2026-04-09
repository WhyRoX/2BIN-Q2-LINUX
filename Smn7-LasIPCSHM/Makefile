CFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL=radar dashboard famille1 famille2 locks

all: $(ALL)

radar: radar.o utils.o
	cc $(CFLAGS) -o radar radar.o utils.o

dashboard: dashboard.o utils.o
	cc $(CFLAGS) -o dashboard dashboard.o utils.o

radar.o: utils.h radar.c
	cc $(CFLAGS) -c radar.c

dashboard.o: utils.h dashboard.c
	cc $(CFLAGS) -c dashboard.c




famille1: famille1.o utils.o
	cc $(CFLAGS) -o famille1 famille1.o utils.o

famille1.o: utils.h famille1.c
	cc $(CFLAGS) -c famille1.c




famille2: famille2.o utils.o
	cc $(CFLAGS) -o famille2 famille2.o utils.o

famille2.o: utils.h famille2.c
	cc $(CFLAGS) -c famille2.c




locks: locks.o utils.o
	cc $(CFLAGS) -o locks locks.o utils.o

locks.o: utils.h locks.c
	cc $(CFLAGS) -c locks.c




utils.o: utils.c utils.h
	cc $(CFLAGS) -c utils.c 

# for dev purposess
clear:
	clear
	
clean:
	rm -f ._*
	rm -f *.o
	rm -f $(ALL)
	ipcrm -a

dev3: all
	$ ./radar & ./dashboard
	ipcs

