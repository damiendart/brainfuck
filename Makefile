# This file was written by Damien Dart, <damiendart@pobox.com>. This is free
# and unencumbered software released into the public domain. For more
# information, please refer to the accompanying "UNLICENCE" file.

.PHONY: clean
all: brainfuck brainfuck-debug
brainfuck: src/brainfuck.c
	$(CC) -O2 -pendantic -std=c99 -Wall -Wextra -Werror $< -o $@
brainfuck-debug: src/brainfuck.c
	$(CC) -g -O -pendantic -std=c99 -Wall -Wextra -Werror $< -o $@
clean:
	rm -f brainfuck brainfuck-debug
