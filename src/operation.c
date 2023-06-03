#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

operation_S *create_new_operation(uint8_t opcode)
{
  operation_S *operation = malloc(sizeof(struct OPERATION_STRUCT));
  operation->opcode = opcode;
  uint8_t operands_count = get_operands_count(opcode);

  switch (operands_count)
  {
  case 0:
    break;
  case 1:
    operation->operands = malloc(sizeof(int8_t));
    operation->operands[0] = 0;
    break;
  case 2:
    operation->operands = malloc(sizeof(int8_t) * 2);
    operation->operands[0] = 0;
    operation->operands[1] = 0;
    break;
  default:
    printf("Error: Operation cannot have %d operands", operands_count);
    exit(1);
    break;
  }

  return operation;
}

void modify_operation_operand(operation_S *operation, uint8_t index, int8_t value)
{
  if ((index + 1) > get_operands_count(operation->opcode) || index > 1)
  {
    printf("Error: Operation \"%x\" cannot have %d operands\n", operation->opcode, index + 1);
    exit(1);
  }

  operation->operands[index] = value;
}

uint8_t get_operands_count(uint8_t opcode)
{
  switch (opcode)
  {
  case 1:
    return 2;
    break;

  default:
    printf("Error: Operation \"%x\" could not be found", opcode);
    exit(1);
    break;
  }
}

void handle_move_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 3)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  modify_register_value(registers[operands[1]], operands[0]);
}

// add two registers and save the result on the second register (operands[1])
void handle_add_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 3 || operands[1] > 3)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0]];
  register_S *reg_two = registers[operands[1]];
  modify_register_value(reg_two, get_register_value(reg_one) + get_register_value(reg_two));
}

// increase a register value
void handle_add_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 3)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1]];
  modify_register_value(reg, get_register_value(reg) + operands[0]);
}

// substract two registers and save the result on the second register (operands[1])
void handle_sub_operation_r(register_S **registers, int8_t *operands)
{

  if (operands[0] > 3 || operands[1] > 3)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0]];
  register_S *reg_two = registers[operands[1]];
  modify_register_value(reg_two, get_register_value(reg_one) - get_register_value(reg_two));
}

// decrease a register value
void handle_sub_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 3)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1]];
  modify_register_value(reg, get_register_value(reg) - operands[0]);
}

// random but useful operators
void handle_print_num_operation(register_S **registers, int8_t *operands)
{
  if (operands[0] > 3)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  printf("%d\n", registers[operands[0]]);
}

void handle_print_char_operation(register_S **registers, int8_t *operands)
{
  if (operands[0] > 3)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  printf("%c", registers[operands[0]]);
}
