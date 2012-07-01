#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "brainfuck.h"

void brainfuck_evaluate(char *commands)
{
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
}
