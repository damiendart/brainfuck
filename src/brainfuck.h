/*
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <stdint.h>

struct brainfuck_state {
  int8_t *data;
  int8_t *data_pointer;
};

typedef struct brainfuck_state brainfuck_state;

brainfuck_state *brainfuck_createState(unsigned int);
void brainfuck_evaluate(brainfuck_state *, const char *);
void brainfuck_freeState(brainfuck_state *);

#endif
