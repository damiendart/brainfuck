/*
 * A simple Brainfuck interpreter.
 *
 * This file was written by Damien Dart, <damiendart@pobox.com>. This is free
 * and unencumbered software released into the public domain. For more
 * information, please refer to the accompanying "UNLICENCE" file.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char character = 0;
  char *commands = NULL;
  uint32_t number_of_commands = 0;
  while((character = getchar()) != EOF) {
    if ((character == '>') || (character == '<') || (character == '+') ||
        (character == '-') || (character == '.') || (character == ',') ||
        (character == '[') || (character == ']')) { 
      commands = realloc(commands, ++number_of_commands * sizeof(char)); 
      commands[number_of_commands - 1] = character;
    }
  }
  commands = realloc(commands, ++number_of_commands * sizeof(char)); 
  commands[number_of_commands - 1] = '\0';
  char data[30000] = { 0 };
  char *data_pointer = data;
  uint32_t current_command = 0;
  while (current_command < strlen(commands)) {
    switch (commands[current_command]) {
      case '>':
        data_pointer++;
        break;
      case '<':
        data_pointer--;
        break;
      case '+':
        ++*data_pointer;
        break;
      case '-':
        --*data_pointer;
        break;
      case '.':
        putchar(*data_pointer);
        break;
      case ',':
        *data_pointer = getchar();
        break;
      case '[':
        if (*data_pointer == 0) {
          uint32_t loop_depth = 1;
          char temp = 0;
          while (loop_depth > 0) {
            temp = commands[++current_command];
            if (temp == '[') {
              loop_depth++;
            } else if (temp == ']') {
              loop_depth--;
            }
          }
        }
        break;
      case ']':
        if (*data_pointer != 0) {
          uint32_t loop_depth = 1;
          char temp = 0;
          while (loop_depth > 0) {
            temp = commands[--current_command];
            if (temp == '[') {
              loop_depth--;
            } else if (temp == ']') {
              loop_depth++;
            }
          }
        }
        break;
    }
    current_command++;
  }
  return EXIT_SUCCESS;
}
