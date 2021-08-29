# Makefile for ACOTSP-MPI-OMP
# To be adapted to the testbed used

VERSION=MPI-OMP

OPTIM_FLAGS=-O
WARN_FLAGS=-parallel -qopenmp  
CFLAGS=$(WARN_FLAGS) $(OPTIM_FLAGS)
CC=mpiicc
# To change the default timer implementation, uncomment the line below
#TIMER=dos
TIMER=unix
LDLIBS=-lm -parallel -qopenmp

all: clean acotsp

clean:
	@$(RM) *.o acotsp

acotsp: acotsp.o parallel.o TSP.o utilities.o ants.o InOut.o $(TIMER)_timer.o ls.o parse.o

acotsp.o: acotsp.c

TSP.o: TSP.c TSP.h

ants.o: ants.c ants.h

InOut.o: InOut.c InOut.h

utilities.o: utilities.c utilities.h

ls.o: ls.c ls.h

parse.o: parse.c parse.h

parallel.o: parallel.c parallel.h

$(TIMER)_timer.o: $(TIMER)_timer.c timer.h

dist : DIST_SRC_FILES=*.c *.h README *.tsp Makefile gpl.txt
dist : all
	@(mkdir -p ../ACOTSP-$(VERSION)			\
	&& rsync -rlpC --exclude=.svn $(DIST_SRC_FILES) ../ACOTSP-$(VERSION)/ \
        && cd .. 	\
	&& tar cf - ACOTSP-$(VERSION) | gzip -f9 > ACOTSP-$(VERSION).tar.gz \
	&& rm -rf ./ACOTSP-$(VERSION)					\
	&& echo "ACOTSP-$(VERSION).tar.gz created." && cd $(CWD) )
