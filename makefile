# This is a makefile for the ADT project

CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = 
OBJS= main.o list.o person.o point.o cluster.o
RM = rm -f

ADT: $(OBJS)
	$(CCLINK) -o ADT $(OBJS) $(LIBS)

main.o: main.c defs.h list.h point.h cluster.h person.h
list.o: list.c list.h defs.h
point.o: point.c point.h list.h defs.h
cluster.o: cluster.c cluster.h point.h list.h defs.h
person.o: person.c person.h list.h defs.h

clean:
	$(RM) ADT *.o