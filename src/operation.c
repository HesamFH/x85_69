#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "utils.h"

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
    operation->operands = malloc(sizeof(uint8_t));
    operation->operands[0] = 0;
    break;
  case 2:
    operation->operands = malloc(sizeof(uint8_t) * 2);
    operation->operands[0] = 0;
    operation->operands[1] = 0;
    break;
  case 3:
    operation->operands = malloc(sizeof(uint8_t) * 3);
    operation->operands[0] = 0;
    operation->operands[1] = 0;
    operation->operands[2] = 0;
    break;
  default:
    printf("Error: Operation cannot have %d operands\n", operands_count);
    exit(1);
    break;
  }

  return operation;
}

void modify_operation_operand(operation_S *operation, uint8_t index, uint8_t value)
{
  if ((index + 1) > get_operands_count(operation->opcode) || index > 2)
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
    return 3;
    break;
  case 0x03:
    return 3;
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
    return 3;
    break;
  case 0x0f:
    return 2;
    break;
  case 0x10:
    return 1;
    break;
  case 0x11:
    return 2;
    break;
  case 0x12:
    return 1;
    break;
  case 0x13:
    return 2;
    break;
  case 0x14:
    return 2;
    break;
  case 0x15:
    return 2;
    break;

  default:
    printf("Error: Operation \"%x\" could not be found\n", opcode);
    exit(1);
    break;
  }
}

void handle_move_operation(register_S **registers, uint8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  modify_register_value(registers[operands[1] - 1], operands[0]);
}

void handle_move_to_memory_operation(register_S **registers, uint8_t *operands, uint8_t *memory)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[0]);
    exit(1);
  }
  memory[((uint16_t)operands[2] * 0x100) + operands[1]] = get_register_value(registers[operands[0] - 1]);
}

void handle_move_from_memory_operation(register_S **registers, uint8_t *operands, uint8_t *memory)
{
  if (operands[2] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  modify_register_value(registers[operands[2] - 1], memory[((uint16_t)operands[1] * 0x100) + operands[0]]);
}

// add two registers and save the result on the second register (operands[1])
void handle_add_operation_r(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
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
void handle_add_operation(register_S **registers, uint8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
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
void handle_sub_operation_r(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
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
void handle_sub_operation(register_S **registers, uint8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
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
void handle_mul_operation_r(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" or \"%x\" could not be found\n", operands[0], operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
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
void handle_mul_operation(register_S **registers, uint8_t *operands)
{
  if (operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
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
void handle_div_operation_r(register_S **registers, uint8_t *operands)
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
void handle_div_operation(register_S **registers, uint8_t *operands)
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
void handle_print_num_operation(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  printf("%d\n", get_register_value(registers[operands[0] - 1]));
}

void handle_print_char_operation(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  printf("%c", get_register_value(registers[operands[0] - 1]));
}

void handle_move_imm_to_ram_operation(uint8_t *operands, uint8_t *memory)
{
  memory[((uint16_t)operands[2] * 0x100) + operands[1]] = operands[0];
}

void handle_set_register_to_zero(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  registers[operands[0] - 1] = 0;
}

void handle_set_mem_addr_to_zero(uint8_t *operands, uint8_t *memory)
{
  memory[((uint16_t)operands[1] * 0x100) + operands[0]] = 0;
}

// compare two registers and set the flags register
void handle_compare(register_S **registers, uint8_t *operands)
{
  if (operands[0] > 4 || operands[1] > 4)
  {
    printf("Error: Register \"%x\" could not be found\n", operands[1]);
    exit(1);
  }
  clear_flags_register(registers[4]);
  uint8_t reg_one_val = get_register_value(registers[operands[0] - 1]);
  uint8_t reg_two_val = get_register_value(registers[operands[1] - 1]);
  if (reg_one_val == reg_two_val)
  {
    // set zero flag
    modify_register_value(registers[4], get_register_value(registers[4]) | 1);
  }
  else if (reg_one_val > reg_two_val)
  {
    // set overflow flag
    modify_register_value(registers[4], get_register_value(registers[4]) | 2);
  }
  else if (reg_one_val < reg_two_val)
  {
    // set both flags
    modify_register_value(registers[4], get_register_value(registers[4]) | 3);
  }
}

void handle_jump_operation(uint8_t *operands, parser_S *parser)
{
  parser->val_index = (((uint16_t)operands[1] * 0x100) + operands[0]) * 2;
  char *val = malloc(2);
  val[0] = parser->source[parser->val_index];
  parser->val_index++;
  val[1] = parser->source[parser->val_index];
  parser->current_value = string_to_hex(val);
  free(val);
  parser->val_index++;
}

void handle_jump_zero_operation(register_S *flags, uint8_t *operands, parser_S *parser)
{
  if (flags->curr_value == 1)
  {
    handle_jump_operation(operands, parser);
  }
}

void handle_jump_greater_operation(register_S *flags, uint8_t *operands, parser_S *parser)
{
  if (flags->curr_value == 2)
  {
    handle_jump_operation(operands, parser);
  }
}

void handle_jump_less_operation(register_S *flags, uint8_t *operands, parser_S *parser)
{
  if (flags->curr_value == 3)
  {
    handle_jump_operation(operands, parser);
  }
}
