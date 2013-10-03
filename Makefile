# This file was written by Damien Dart, <damiendart@pobox.com>. This is free
# and unencumbered software released into the public domain. For more
# information, please refer to the accompanying "UNLICENCE" file.

CFLAGS = -O2 -pedantic -std=c99 -Wall -Wextra -Werror

.PHONY: all clean
all: brainfuck
brainfuck: src/interpreter.c src/brainfuck.c
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -f brainfuck
