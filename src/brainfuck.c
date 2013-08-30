/*
 * A simple brainfuck library.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#include <stddef.h>
#include <stdint.h>

#include "brainfuck.h"

brainfuck_tape *brainfuck_createTape(unsigned int number_of_cells,
    void *(*allocator_function)(size_t))
{
  brainfuck_tape *tape = (*allocator_function)(sizeof(brainfuck_tape));
  tape->data = (*allocator_function)(number_of_cells * sizeof(int8_t));
  for (unsigned int i = 0; i < number_of_cells; i++) {
    tape->data[i] = 0;
  }
  tape->data_pointer = tape->data;
  tape->cell_count = number_of_cells;
  return tape;
}

brainfuck_evaluate_status brainfuck_evaluate(brainfuck_tape *tape,
    const char *commands, int (*input_function)(void),
    int (*output_function)(int))
{
  brainfuck_evaluate_status status = { BRAINFUCK_EVALUATE_SUCCESS, NULL, 0 };
  for (unsigned int index = 0; commands[index] != '\0'; index++) {
    switch (commands[index]) {
      case '>':
      case '<':
        tape->data_pointer += (commands[index] == '>' ? 1 : -1);
        if ((tape->data_pointer < tape->data) ||
            (tape->data_pointer) > (tape->data + tape->cell_count)) {
          status.return_code = BRAINFUCK_EVALUATE_FAILURE;
          status.error_message =
              "Data cell pointer no longer points to a valid data cell.";
          status.offending_command_position = index;
          return status;
        }
        break;
      case '+':
      case '-':
        *tape->data_pointer += commands[index] == '+' ? 1 : -1;
        break;
      case '.':
        (*output_function)((int)*(tape->data_pointer));
        break;
      case ',':
        *(tape->data_pointer) = (int8_t)(*input_function)();
        break;
      case '[':
        if (*(tape->data_pointer) == 0) {
          uint32_t loop_depth = 1;
          while (loop_depth > 0) {
            if (commands[++index] == '[') {
              loop_depth++;
            } else if (commands[index] == ']') {
              loop_depth--;
            /* TODO: Open loops should be checked for beforehand. */
            } else if (commands[index] == '\0') {
              status.return_code = BRAINFUCK_EVALUATE_FAILURE;
              status.error_message = "Unmatched \"[\".";
              status.offending_command_position = index;
              return status;
            }
          }
        }
        break;
      case ']':
        if (*(tape->data_pointer) != 0) {
          uint32_t loop_depth = 1;
          while (loop_depth > 0) {
            if (commands[--index] == '[') {
              loop_depth--;
            } else if (commands[index] == ']') {
              loop_depth++;
            /* TODO: Open loops should be checked for beforehand. */
            } else if (index == 0) {
              status.return_code = BRAINFUCK_EVALUATE_FAILURE;
              status.error_message = "Unmatched \"]\".";
              status.offending_command_position = index;
              return status;
            }
          }
        }
        break;
    }
  }
  return status;
}

void brainfuck_freeTape(brainfuck_tape *tape,
    void (deallocator_function)(void *)) {
  (*deallocator_function)(tape->data);
  (*deallocator_function)(tape);
}
