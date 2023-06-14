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
  case 0x01:
    return 2;
    break;
  case 0x02:
    return 2;
    break;
  case 0x03:
    return 2;
    break;
  case 0x04:
    return 2;
    break;
  case 0x05:
    return 2;
    break;
  case 0x06:
    return 2;
    break;
  case 0x07:
    return 2;
    break;
  case 0x08:
    return 2;
    break;
  case 0x09:
    return 2;
    break;
  case 0x0a:
    return 1;
    break;
  case 0x0b:
    return 1;
    break;

  default:
    printf("Error: Operation \"%x\" could not be found", opcode);
    exit(1);
    break;
  }
}

void handle_move_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  modify_register_value(registers[operands[1] - 1], operands[0]);
}

// add two registers and save the result on the second register (operands[1])
void handle_add_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  modify_register_value(reg_two, get_register_value(reg_one) + get_register_value(reg_two));
}

// increase the value of a register
void handle_add_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  modify_register_value(reg, get_register_value(reg) + operands[0]);
}

// substract two registers and save the result on the second register (operands[1])
void handle_sub_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  modify_register_value(reg_two, get_register_value(reg_one) - get_register_value(reg_two));
}

// decrease the value of a register
void handle_sub_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  modify_register_value(reg, get_register_value(reg) - operands[0]);
}

// multiply the value of a register by another register
void handle_mul_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  modify_register_value(reg_two, get_register_value(reg_one) * get_register_value(reg_two));
}

// multiply the value of a register
void handle_mul_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  modify_register_value(reg, get_register_value(reg) * operands[0]);
}

// divide the value of a register by another register
void handle_div_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  modify_register_value(reg_two, get_register_value(reg_one) / get_register_value(reg_two));
}
// divide the value of a register
void handle_div_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  modify_register_value(reg, get_register_value(reg) / operands[0]);
}

// random but useful operators
void handle_print_num_operation(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  printf("%d\n", get_register_value(registers[operands[0] - 1]));
}

void handle_print_char_operation(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found", operands[1]);
    exit(1);
  }
  printf("%c", get_register_value(registers[operands[0] - 1]));
}
