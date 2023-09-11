#include <stdio.h>
#include <stdlib.h>
#include "interpret.h"
#include "lexer.h"

void interpret(char *source, register_S **registers, uint8_t* memory)
{
  lexer_S *lexer = init_lexer(source);

  while (1)
  {
    operation_S *curr_operation = lexer_advance(lexer);
    if (curr_operation == NULL)
      break;


    switch (curr_operation->opcode)
    {
    case 0x01:
      handle_move_operation(registers, curr_operation->operands);
      break;
    case 0x02:
      handle_move_to_memory_operation(registers, curr_operation->operands, memory);
      break;
    case 0x03:
      handle_move_from_memory_operation(registers, curr_operation->operands, memory);
      break;
    case 0x04:
      handle_add_operation_r(registers, curr_operation->operands);
      break;
    case 0x05:
      handle_add_operation(registers, curr_operation->operands);
      break;
    case 0x06:
      handle_sub_operation_r(registers, curr_operation->operands);
      break;
    case 0x07:
      handle_sub_operation(registers, curr_operation->operands);
      break;
    case 0x08:
      handle_mul_operation_r(registers, curr_operation->operands);
      break;
    case 0x09:
      handle_mul_operation(registers, curr_operation->operands);
      break;
    case 0x0a:
      handle_div_operation_r(registers, curr_operation->operands);
      break;
    case 0x0b:
      handle_div_operation(registers, curr_operation->operands);
      break;
    case 0x0c:
      handle_print_num_operation(registers, curr_operation->operands);
      break;
    case 0x0d:
      handle_print_char_operation(registers, curr_operation->operands);
      break;

    default:
      printf("Error: operation \"%x\" not found!\n", curr_operation->opcode);
      exit(1);
      break;
    }

    free(curr_operation);
  }
}
