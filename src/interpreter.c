/*
 * A simple brainfuck interpreter.
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

#define NUMBER_OF_CELLS 30000

int main(int argc, char **argv)
{
  char *commands = NULL;
  unsigned int number_of_commands = 0;
  brainfuck_evaluate_status status;
  brainfuck_tape *tape = NULL;
  FILE *brainfuck_stream = stdin;
  if (argc != 1 && strcmp(argv[1], "-") != 0) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      printf("\"%s\" is a nice brainfuck interpreter.\n\n", argv[0]);
      printf("  - brainfuck programs have access to %d %d-bit cells.\n",
          NUMBER_OF_CELLS, (int)sizeof(tape->data[0]) * 8);
      puts("  - Integer overflow results in wrap-around.");
      printf("  - When accepting input, EOF is equal to %d.\n\n", EOF);
      printf("Usage: %s [options] [- | programfile]\n", argv[0]);
      puts("Options:\n  -h, --help    Print this message.");
      exit(EXIT_SUCCESS);
    } else if (argv[1][0] == '-') {
      fprintf(stderr, "Unrecognised option: %s\n", argv[1]);
      fprintf(stderr, "Try \"%s -h\" for more information.\n", argv[0]);
      exit(EXIT_FAILURE);
    } else if ((brainfuck_stream = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "Cannot open \"%s\": %s\n", argv[1], strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  while (1) {
    char character = fgetc(brainfuck_stream);
    char *new_commands = realloc(commands, ++number_of_commands * sizeof(char));
    if (new_commands == NULL) {
      free(commands);
      perror("Unable to create command list");
      exit(EXIT_FAILURE);
    } else {
      commands = new_commands;
    }
    if (character == EOF) {
      commands[number_of_commands - 1] = '\0';
      if (brainfuck_stream == stdin) {
        clearerr(stdin);
      } else {
        fclose(brainfuck_stream);
      }
      break;
    } else {
      commands[number_of_commands - 1] = character;
    }
  }
  if ((tape = brainfuck_createTape(NUMBER_OF_CELLS, malloc, free)) == NULL) {
    free(commands);
    perror("Unable to create brainfuck memory tape");
    exit(EXIT_FAILURE);
  }
  status = brainfuck_evaluate(tape, commands, getchar, putchar);
  if (status.return_code == BRAINFUCK_EVALUATE_FAILURE) {
    unsigned int line_number = 1;
    unsigned int character_offset = 1;
    for (unsigned int i = 0; i != status.offending_command_position; i++) {
      line_number += commands[i] == '\n' ? 1 : 0;
      character_offset = commands[i] == '\n' ? 0 : character_offset + 1;
    }
    fprintf(stderr, "%s:%d:%d: ERROR: %s\n",
        brainfuck_stream == stdin ? "-" : argv[1], line_number,
        character_offset, status.error_message);
  }
  brainfuck_freeTape(tape, free);
  free(commands);
  return status.return_code == BRAINFUCK_EVALUATE_SUCCESS ?
      EXIT_SUCCESS : EXIT_FAILURE;
}
