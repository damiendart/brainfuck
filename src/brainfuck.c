#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "brainfuck.h"

brainfuck_state *brainfuck_createState(uint32_t number_of_cells)
{
  brainfuck_state *state = malloc(sizeof(brainfuck_state));
  state->data = malloc(number_of_cells * sizeof(char));
  for (uint32_t i = 0; i < number_of_cells; i++) {
    state->data[i] = 0;
  }
  state->data_pointer = state->data;
  return state;
}

void brainfuck_evaluate(brainfuck_state *state, uint8_t *commands)
{
  uint32_t current_command_index = 0;
  while (current_command_index < strlen((const char *)commands)) {
    switch (commands[current_command_index]) {
      case '>':
        state->data_pointer++;
        break;
      case '<':
        state->data_pointer--;
        break;
      case '+':
        ++*state->data_pointer;
        break;
      case '-':
        --*state->data_pointer;
        break;
      case '.':
        putchar(*(state->data_pointer));
        break;
      case ',':
        *(state->data_pointer) = getchar();
        break;
      case '[':
        if (*(state->data_pointer) == 0) {
          uint32_t loop_depth = 1;
          char temp = 0;
          while (loop_depth > 0) {
            temp = commands[++current_command_index];
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
            temp = commands[--current_command_index];
            if (temp == '[') {
              loop_depth--;
            } else if (temp == ']') {
              loop_depth++;
            }
          }
        }
        break;
    }
    current_command_index++;
  }
}

void brainfuck_freeState(brainfuck_state *state)
{
  free(state->data);
  free(state);
}
