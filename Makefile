# This file was written by Damien Dart, <damiendart@pobox.com>. This is free
# and unencumbered software released into the public domain. For more
# information, please refer to the accompanying "UNLICENCE" file.

brainfuck: src/brainfuck.c
	gcc -O2 -pendantic -std=c99 -Wall -Wextra -Werror $< -o $@
.PHONY: clean
clean:
	rm -f brainfuck 
