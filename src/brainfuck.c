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

brainfuck_state *brainfuck_createState(unsigned int number_of_cells,
    void *(*allocator_function)(size_t))
{
  brainfuck_state *state = (*allocator_function)(sizeof(brainfuck_state));
  state->data = (*allocator_function)(number_of_cells * sizeof(int8_t));
  for (unsigned int i = 0; i < number_of_cells; i++) {
    state->data[i] = 0;
  }
  state->data_pointer = state->data;
  state->cell_count = number_of_cells;
  return state;
}

brainfuck_evaluate_status brainfuck_evaluate(brainfuck_state *state,
    const char *commands, int (*input_function)(void),
    int (*output_function)(int))
{
  brainfuck_evaluate_status status = { BRAINFUCK_EVALUATE_SUCCESS, NULL, 0 };
  for (unsigned int index = 0; commands[index] != '\0'; index++) {
    switch (commands[index]) {
      case '>':
      case '<':
        state->data_pointer += (commands[index] == '>' ? 1 : -1);
        if ((state->data_pointer < state->data) ||
            (state->data_pointer) > (state->data + state->cell_count)) {
          status.return_code = BRAINFUCK_EVALUATE_FAILURE;
          status.error_message =
              "Data pointer no longer points to any brainfuck data.";
          status.offending_command_position = index;
          return status;
        }
        break;
      case '+':
      case '-':
        *state->data_pointer += commands[index] == '+' ? 1 : -1;
        break;
      case '.':
        (*output_function)((int)*(state->data_pointer));
        break;
      case ',':
        *(state->data_pointer) = (int8_t)(*input_function)();
        break;
      case '[':
        if (*(state->data_pointer) == 0) {
          uint32_t loop_depth = 1;
          char temp = 0;
          while (loop_depth > 0) {
            temp = commands[++index];
            if (temp == '[') {
              loop_depth++;
            } else if (temp == ']') {
              loop_depth--;
            }
          }
        }
        break;
      case ']':
        if (*(state->data_pointer) != 0) {
          uint32_t loop_depth = 1;
          char temp = 0;
          while (loop_depth > 0) {
            temp = commands[--index];
            if (temp == '[') {
              loop_depth--;
            } else if (temp == ']') {
              loop_depth++;
            }
          }
        }
        break;
    }
  }
  return status;
}

void brainfuck_freeState(brainfuck_state *state,
    void (deallocator_function)(void *)) {
  (*deallocator_function)(state->data);
  (*deallocator_function)(state);
}
