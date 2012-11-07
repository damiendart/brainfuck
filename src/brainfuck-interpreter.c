/*
 * A simple Brainfuck interpreter.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brainfuck.h"

void *realloc2(void *, size_t);

int main(void)
{
  uint8_t *commands = NULL;
  uint32_t number_of_commands = 0;
  while(true) {
    int8_t character = getchar();
    uint8_t *new_commands = realloc(commands,
        ++number_of_commands * sizeof(uint8_t));
    if (new_commands == NULL) {
      free(commands);
      perror("Unable to create command list");
      exit(EXIT_FAILURE);
    } else {
      commands = new_commands;
    }
    commands[number_of_commands - 1] = (character == EOF) ? '\0' : character;
    if (character == EOF) {
      break;
    }
  }
  brainfuck_state *state = brainfuck_createState(30000);
  brainfuck_evaluate(state, commands);
  brainfuck_freeState(state);
  free(commands);
  return EXIT_SUCCESS;
}
