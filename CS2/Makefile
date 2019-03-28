#
# Makefile for ArrayDeque
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

ArrayDeque: ArrayDeque.o memcheck.o
	$(CC) ArrayDeque.o memcheck.o -o ArrayDeque

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

test_deq:
	./ArrayDeque

check_deq:
	c_style_check ArrayDeque.c

clean:
	rm -f *.o ArrayDeque



