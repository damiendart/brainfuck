# This file was written by Damien Dart, <damiendart@pobox.com>. This is free
# and unencumbered software released into the public domain. For more
# information, please refer to the accompanying "UNLICENCE" file.

.PHONY: all clean
all: brainfuck
brainfuck: src/interpreter.c src/brainfuck.c src/brainfuck.h
	$(CC) $(CFLAGS) -pedantic -std=c99 -Wall -Wextra -Werror $^ -o $@
clean:
	rm -f brainfuck
