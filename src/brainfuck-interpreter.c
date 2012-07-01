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

int main(void)
{
  char character = 0;
  char *commands = NULL;
  uint32_t number_of_commands = 0;
  while((character = getchar()) != EOF) {
    if ((character == '>') || (character == '<') || (character == '+') ||
        (character == '-') || (character == '.') || (character == ',') ||
        (character == '[') || (character == ']')) {
      char *temp = realloc(commands, ++number_of_commands * sizeof(char));
      if (temp == NULL) {
        free(commands);
        perror("Unable to create command list");
        exit(EXIT_FAILURE);
      }
      commands = temp;
      commands[number_of_commands - 1] = character;
    }
  }
  commands = realloc(commands, ++number_of_commands * sizeof(char));
  commands[number_of_commands - 1] = '\0';
  brainfuck_evaluate(commands);
  free(commands);
  return EXIT_SUCCESS;
}
