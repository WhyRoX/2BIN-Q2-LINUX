CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE
ALL = pipe pipeB pipeC pipeD

all: $(ALL)

pipe: utils.o pipe.o
	cc $(CFLAGS) -o pipe utils.o pipe.o

pipe.o: utils.h pipe.c
	cc $(CFLAGS) -c pipe.c

pipeB: utils.o pipeB.o
	cc $(CFLAGS) -o pipeB utils.o pipeB.o

pipeB.o: utils.h pipeB.c
	cc $(CFLAGS) -c pipeB.c

pipeC: utils.o pipeC.o
	cc $(CFLAGS) -o pipeC utils.o pipeC.o 

pipeC.o: utils.h pipeC.c
	cc $(CFLAGS) -c pipeC.c

pipeD: utils.o pipeD.o
	cc $(CFLAGS) -o pipeD utils.o pipeD.o

pipeD.o: utils.h pipeD.c
	cc $(CFLAGS) -c pipeD.c

utils.o: utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean:
	rm *.o
	rm ._*
	rm -f $(ALL)

test: pipeD 
	./pipeD ls grep "\.c"