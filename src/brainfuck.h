/*
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <stdint.h>

struct brainfuck_state {
  char *data;
  char *data_pointer;
};

typedef struct brainfuck_state brainfuck_state;

brainfuck_state *brainfuck_createState(uint32_t);
void brainfuck_evaluate(brainfuck_state *, char *);
void brainfuck_freeState(brainfuck_state *);

#endif
