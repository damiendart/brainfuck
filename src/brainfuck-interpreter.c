/*
 * A simple Brainfuck interpreter.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brainfuck.h"

int main(int argc, char **argv)
{
  uint8_t *commands = NULL;
  uint32_t number_of_commands = 0;
  FILE *brainfuck_stream = stdin;
  if ((argc != 1) && (strcmp(argv[1], "-") != 0)) {
    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
      printf("\"%s\" is a simple Brainfuck interpreter.\n", argv[0]);
      printf("Usage: %s [options] [- | programfile]\n", argv[0]);
      puts("Options:\n  -h, --help    Print this message.");
      exit(EXIT_SUCCESS);
    } else if (argv[1][0] == '-') {
      fprintf(stderr, "Unrecognised option: %s\n", argv[1]);
      fprintf(stderr, "Try \"%s -h\" for more information.\n", argv[0]);
      exit(EXIT_SUCCESS);
    } else if ((brainfuck_stream = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "Cannot open \"%s\": %s\n", argv[1], strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  while(true) {
    int8_t character = getc(brainfuck_stream);
    uint8_t *new_commands = realloc(commands,
        ++number_of_commands * sizeof(uint8_t));
    if (new_commands == NULL) {
      free(commands);
      perror("Unable to create command list");
      exit(EXIT_FAILURE);
    } else {
      commands = new_commands;
    }
    if (character == EOF) {
      commands[number_of_commands - 1] = '\0';
      break;
    } else {
      commands[number_of_commands - 1] = character;
    }
  }
  if (brainfuck_stream == stdin) {
    clearerr(stdin);
  } else {
    fclose(brainfuck_stream);
  }
  brainfuck_state *state = brainfuck_createState(30000);
  brainfuck_evaluate(state, commands);
  brainfuck_freeState(state);
  free(commands);
  return EXIT_SUCCESS;
}
