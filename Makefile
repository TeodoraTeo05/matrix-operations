CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb

TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c matrix.c case.c -o my_octave

clean:
	rm -f $(TARGETS)
	
PHONY: pack clean