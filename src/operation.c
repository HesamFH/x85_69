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
    printf("Error: Operation cannot have %d operands\n", operands_count);
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
    return 2;
    break;
  case 0x0b:
    return 2;
    break;
  case 0x0c:
    return 1;
    break;
  case 0x0d:
    return 1;
    break;
  case 0x0e:
    return 2;
    break;
  case 0x0f:
    return 1;
    break;
  case 0x10:
    return 1;
    break;
  case 0x11:
    return 1;
    break;

  default:
    printf("Error: Operation \"%x\" could not be found\n", opcode);
    exit(1);
    break;
  }
}

void handle_move_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  modify_register_value(registers[operands[1] - 1], operands[0]);
}

void handle_move_to_memory_operation(register_S **registers, int8_t *operands, uint8_t *memory)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[0]);
    exit(1);
  }
  memory[operands[1]] = get_register_value(registers[operands[0] - 1]);
}

void handle_move_from_memory_operation(register_S **registers, int8_t *operands, uint8_t *memory)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  modify_register_value(registers[operands[1] - 1], memory[operands[0]]);
}

// add two registers and save the result on the second register (operands[1])
void handle_add_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  uint8_t reg_one_val = get_register_value(reg_one);
  uint8_t reg_two_val = get_register_value(reg_two);
  if (reg_one_val + reg_two_val > 255)
  {
    modify_register_value(reg_two, 255);
    // set overflow flag
    modify_register_value(registers[4], get_register_value(registers[4]) | 2);
  }
  else
    modify_register_value(reg_two, reg_one_val + reg_two_val);
}

// increase the value of a register
void handle_add_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  uint8_t reg_val = get_register_value(reg);
  if (reg_val + operands[0] > 255)
  {
    modify_register_value(reg, 255);
    // set overflow flag
    modify_register_value(registers[4], get_register_value(registers[4]) | 2);
  }
  else
    modify_register_value(reg, reg_val + operands[0]);
}

// substract two registers and save the result on the second register (operands[1])
void handle_sub_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  uint8_t reg_one_val = get_register_value(reg_one);
  uint8_t reg_two_val = get_register_value(reg_two);
  if (reg_one_val - reg_two_val < 0)
  {
    modify_register_value(reg_two, 0);
    // set overflow and zero flags
    modify_register_value(registers[4], get_register_value(registers[4]) | 3);
  }
  else
    modify_register_value(reg_two, reg_one_val - reg_two_val);
}

// decrease the value of a register
void handle_sub_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  uint8_t reg_val = get_register_value(reg);
  if (reg_val - operands[0] < 0)
  {
    modify_register_value(reg, 0);
    // set overflow and zero flags
    modify_register_value(registers[4], get_register_value(registers[4]) | 3);
  }
  else
    modify_register_value(reg, reg_val - operands[0]);
}

// multiply the value of a register by another register
void handle_mul_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
    exit(1);
  }
  register_S *reg_one = registers[operands[0] - 1];
  register_S *reg_two = registers[operands[1] - 1];
  uint8_t reg_one_val = get_register_value(reg_one);
  uint8_t reg_two_val = get_register_value(reg_two);
  if (reg_one_val * reg_two_val > 255)
  {
    modify_register_value(reg_two, 255);
    // set overflow flag
    modify_register_value(registers[4], get_register_value(registers[4]) | 2);
  }
  else
    modify_register_value(reg_two, reg_one_val * reg_two_val);
}

// multiply the value of a register
void handle_mul_operation(register_S **registers, int8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  register_S *reg = registers[operands[1] - 1];
  uint8_t reg_val = get_register_value(reg);
  if (reg_val * operands[0] > 255)
  {
    modify_register_value(reg, 255);
    // set overflow flag
    modify_register_value(registers[4], get_register_value(registers[4]) | 2);
  }
  else
    modify_register_value(reg, reg_val * operands[0]);
}

// divide the value of a register by another register
void handle_div_operation_r(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
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
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
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
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  printf("%d\n", get_register_value(registers[operands[0] - 1]));
}

void handle_print_char_operation(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  printf("%c", get_register_value(registers[operands[0] - 1]));
}

void handle_move_imm_to_ram_operation(int8_t *operands, uint8_t *memory)
{
  memory[operands[1] - 1] = operands[0];
}

void handle_set_register_to_zero(register_S **registers, int8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  registers[operands[0] - 1] = 0;
}

void handle_set_mem_addr_to_zero(int8_t *operands, uint8_t *memory)
{
  memory[operands[0]] = 0;
}