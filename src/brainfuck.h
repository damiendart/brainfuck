/*
 * A simple brainfuck interpreter library.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is
 * free and unencumbered software released into the public domain. For
 * more information, please refer to the accompanying "UNLICENCE" file.
*/

#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <stddef.h>
#include <stdint.h>

typedef enum brainfuck_commands {
  BRAINFUCK_COMMAND_INPUT = ',',
  BRAINFUCK_COMMAND_LOOP_BEGIN = '[',
  BRAINFUCK_COMMAND_LOOP_END = ']',
  BRAINFUCK_COMMAND_OUTPUT = '.',
  BRAINFUCK_COMMAND_POINTER_DECREMENT = '<',
  BRAINFUCK_COMMAND_POINTER_INCREMENT = '>',
  BRAINFUCK_COMMAND_VALUE_DECREMENT = '-',
  BRAINFUCK_COMMAND_VALUE_INCREMENT = '+'
} brainfuck_commands;

typedef enum brainfuck_evaluate_return_code {
  BRAINFUCK_EVALUATE_SUCCESS,
  BRAINFUCK_EVALUATE_FAILURE
} brainfuck_evaluate_return_code;

typedef struct brainfuck_evaluate_status {
  brainfuck_evaluate_return_code return_code;
  const char *error_message; /* Will be "NULL" if successful. */
  unsigned int offending_command_position; /* Will be 0 if successful. */
} brainfuck_evaluate_status;

typedef struct brainfuck_tape {
  int8_t *data;
  int8_t *data_pointer;
  unsigned int cell_count;
} brainfuck_tape;

brainfuck_tape *brainfuck_createTape(unsigned int number_of_cells,
    void *(*memory_allocator_function)(size_t),
    void (memory_deallocator_function)(void *));
brainfuck_evaluate_status brainfuck_evaluate(brainfuck_tape *tape,
    const char *commands, int (*input_handler_function)(void),
    int (*output_handler_function)(int));
void brainfuck_freeTape(brainfuck_tape *tape,
    void (memory_deallocator_function)(void *));

#endif
