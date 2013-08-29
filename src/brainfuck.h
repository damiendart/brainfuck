/*
 * A simple brainfuck library.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <stddef.h>
#include <stdint.h>

#define BRAINFUCK_EVALUATE_SUCCESS 0
#define BRAINFUCK_EVALUATE_FAILURE 1

typedef struct brainfuck_evaluate_status {
  int return_code;
  const char *error_message;
  unsigned int offending_command_position;
} brainfuck_evaluate_status;

typedef struct brainfuck_tape {
  int8_t *data;
  int8_t *data_pointer;
  unsigned int cell_count;
} brainfuck_tape;

brainfuck_tape *brainfuck_createTape(unsigned int, void *(size_t));
brainfuck_evaluate_status brainfuck_evaluate(brainfuck_tape *, const char *,
    int(void), int(int));
void brainfuck_freeTape(brainfuck_tape *, void(void *));

#endif
