CFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL=exemple13 exemple14 radar dashboard

all: $(ALL)

radar: radar.o utils_v2.o
	cc $(CFLAGS) -o radar radar.o utils_v2.o

dashboard: dashboard.o utils_v2.o
	cc $(CFLAGS) -o dashboard dashboard.o utils_v2.o

exemple13: utils_v2.o exemple13.o
	cc $(CFLAGS) -o exemple13 exemple13.o utils_v2.o  

exemple14: utils_v2.o exemple14.o
	cc $(CFLAGS) -o exemple14 exemple14.o utils_v2.o  

radar.o: utils_v2.h radar.c
	cc $(CFLAGS) -c radar.c

dashboard.o: utils_v2.h dashboard.c
	cc $(CFLAGS) -c dashboard.c

exemple13.o: utils_v2.h exemple13.c
	cc $(CFLAGS) -c exemple13.c  

exemple14.o: utils_v2.h exemple14.c
	cc $(CFLAGS) -c exemple14.c  

utils_v2.o: utils_v2.c utils_v2.h
	cc $(CFLAGS) -c utils_v2.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f ._*
	rm -f *.o
	rm -f $(ALL)
	ipcrm -a

dev1: all
	./exemple13
	ipcs
	
dev2: all
	./exemple14
	ipcs

dev3: all
	$ ./radar & ./dashboard
	ipcs
