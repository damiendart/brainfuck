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

brainfuck_tape *brainfuck_createTape(unsigned int number_of_cells,
    void *(*allocator_function)(size_t))
{
  brainfuck_tape *tape = (*allocator_function)(sizeof(brainfuck_tape));
  tape->data = (*allocator_function)(number_of_cells * sizeof(int8_t));
  for (unsigned int i = 0; i < number_of_cells; i++) {
    tape->data[i] = 0;
  }
  tape->data_pointer = tape->data;
  tape->cell_count = number_of_cells;
  return tape;
}

brainfuck_evaluate_status brainfuck_evaluate(brainfuck_tape *tape,
    const char *commands, int (*input_function)(void),
    int (*output_function)(int))
{
  brainfuck_evaluate_status status = { BRAINFUCK_EVALUATE_SUCCESS, NULL, 0 };
  for (unsigned int index = 0; commands[index] != '\0'; index++) {
    switch (commands[index]) {
      case BRAINFUCK_COMMAND_POINTER_DECREMENT:
      case BRAINFUCK_COMMAND_POINTER_INCREMENT:
        tape->data_pointer +=
            commands[index] == BRAINFUCK_COMMAND_POINTER_INCREMENT ? 1 : -1;
        if ((tape->data_pointer < tape->data) ||
            (tape->data_pointer) > (tape->data + tape->cell_count)) {
          status.return_code = BRAINFUCK_EVALUATE_FAILURE;
          status.error_message =
              "Data cell pointer no longer points to a valid data cell.";
          status.offending_command_position = index;
          return status;
        }
        break;
      case BRAINFUCK_COMMAND_VALUE_DECREMENT:
      case BRAINFUCK_COMMAND_VALUE_INCREMENT:
        *tape->data_pointer +=
            commands[index] == BRAINFUCK_COMMAND_VALUE_INCREMENT ? 1 : -1;
        break;
      case BRAINFUCK_COMMAND_OUTPUT:
        (*output_function)((int)*(tape->data_pointer));
        break;
      case BRAINFUCK_COMMAND_INPUT:
        *(tape->data_pointer) = (int8_t)(*input_function)();
        break;
      case BRAINFUCK_COMMAND_LOOP_BEGIN:
      case BRAINFUCK_COMMAND_LOOP_END:
        if ((*(tape->data_pointer) == 0 &&
              commands[index] == BRAINFUCK_COMMAND_LOOP_BEGIN) ||
              (*(tape->data_pointer) != 0 &&
              commands[index] == BRAINFUCK_COMMAND_LOOP_END)) {
          unsigned int loop_depth = 1;
          unsigned int loop_start_index = index;
          while (loop_depth > 0) {
            if (commands[commands[loop_start_index]
                  == BRAINFUCK_COMMAND_LOOP_BEGIN ? ++index : --index]
                  == BRAINFUCK_COMMAND_LOOP_BEGIN) {
              commands[loop_start_index] == BRAINFUCK_COMMAND_LOOP_BEGIN ?
                  loop_depth++ : loop_depth--;
            } else if (commands[index] == BRAINFUCK_COMMAND_LOOP_END) {
              commands[loop_start_index] == BRAINFUCK_COMMAND_LOOP_BEGIN ?
                  loop_depth-- : loop_depth++;
            } else if (commands[index] == '\0' || index == 0) {
              status.return_code = BRAINFUCK_EVALUATE_FAILURE;
              /* TODO: Update error message to use symbolic constants. */
              status.error_message = "Unmatched \"[\" or \"]\".";
              status.offending_command_position = loop_start_index;
              return status;
            }
          }
        }
        break;
    }
  }
  return status;
}

void brainfuck_freeTape(brainfuck_tape *tape,
    void (deallocator_function)(void *))
{
  (*deallocator_function)(tape->data);
  (*deallocator_function)(tape);
}
