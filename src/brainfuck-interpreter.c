/*
 * A simple Brainfuck interpreter.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brainfuck.h"

void *realloc2(void *, size_t);

int main(void)
{
  char character = 0;
  char *commands = NULL;
  uint32_t number_of_commands = 0;
  while((character = getchar()) != EOF) {
    commands = realloc2(commands, ++number_of_commands * sizeof(char));
    commands[number_of_commands - 1] = character;
  }
  commands = realloc2(commands, ++number_of_commands * sizeof(char));
  commands[number_of_commands - 1] = '\0';
  brainfuck_state *state = brainfuck_createState(30000);
  brainfuck_evaluate(state, commands);
  brainfuck_freeState(state);
  free(commands);
  return EXIT_SUCCESS;
}

void *realloc2(void *ptr, size_t size)
{
  char *new_obj = realloc(ptr, size);
  if (new_obj == NULL) {
    free(ptr);
    strerror(errno);
    exit(EXIT_FAILURE);
  }
  return new_obj;
}
