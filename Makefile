# This file was written by Damien Dart, <damiendart@pobox.com>. This is free
# and unencumbered software released into the public domain. For more
# information, please refer to the accompanying "UNLICENCE" file.

INTERPRETER_SOURCES = src/brainfuck-interpreter.c src/brainfuck.c
CFLAGS = -pedantic -std=c99 -Wall -Wextra -Werror

.PHONY: all clean
all: brainfuck brainfuck-debug
brainfuck: CFLAGS += -O2
brainfuck: $(INTERPRETER_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
brainfuck-debug: CFLAGS += -g -O0
brainfuck-debug: $(INTERPRETER_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -f brainfuck brainfuck-debug
