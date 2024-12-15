CC = gcc
CFLAGS = -Wall -Wextra -g

all: test_system test_custom

test_system: test.o
	$(CC) $(CFLAGS) -o test test.o -lm

test_custom: test.o memory.o
	$(CC) $(CFLAGS) -o test_custom test.o memory.o -lm

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

system_test: test_system
	./test

custom_test: test_custom
	./test_custom

clean:
	rm -f *.o test test_custom
