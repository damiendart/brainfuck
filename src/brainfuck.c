#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "brainfuck.h"

brainfuck_state *brainfuck_createState(unsigned int number_of_cells)
{
  brainfuck_state *state = malloc(sizeof(brainfuck_state));
  state->data = malloc(number_of_cells * sizeof(int8_t));
  for (unsigned int i = 0; i < number_of_cells; i++) {
    state->data[i] = 0;
  }
  state->data_pointer = state->data;
  return state;
}

void brainfuck_evaluate(brainfuck_state *state, const char *commands)
{
  for (unsigned int index = 0; commands[index] != '\0'; index++) {
    switch (commands[index]) {
      case '>':
      case '<':
        state->data_pointer += commands[index] == '>' ? 1 : -1;
        break;
      case '+':
      case '-':
        *state->data_pointer += commands[index] == '+' ? 1 : -1;
        break;
      case '.':
        putchar((int)*(state->data_pointer));
        break;
      case ',':
        *(state->data_pointer) = (int8_t)getchar();
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
}

void brainfuck_freeState(brainfuck_state *state)
{
  free(state->data);
  free(state);
}
