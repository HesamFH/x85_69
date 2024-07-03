#pragma once
#include <stdint.h>
#include "register.h"

typedef struct OPERATION_STRUCT
{
  uint8_t opcode;
  int8_t *operands;
} operation_S;

#define PARSER_S
typedef struct PARSER_STRUCT
{
  uint8_t current_value;
  char *source;
  int val_index;
} parser_S;

operation_S *create_new_operation(uint8_t opcode);
void modify_operation_operand(operation_S *operation, uint8_t index, int8_t value);
uint8_t get_operands_count(uint8_t opcode);
void handle_move_operation(register_S **registers, int8_t *operands);
void handle_move_to_memory_operation(register_S **registers, int8_t *operands, uint8_t *memory);
void handle_move_from_memory_operation(register_S **registers, int8_t *operands, uint8_t *memory);
void handle_add_operation_r(register_S **registers, int8_t *operands);
void handle_add_operation(register_S **registers, int8_t *operands);
void handle_sub_operation_r(register_S **registers, int8_t *operands);
void handle_sub_operation(register_S **registers, int8_t *operands);
void handle_mul_operation_r(register_S **registers, int8_t *operands);
void handle_mul_operation(register_S **registers, int8_t *operands);
void handle_div_operation_r(register_S **registers, int8_t *operands);
void handle_div_operation(register_S **registers, int8_t *operands);
void handle_print_num_operation(register_S **registers, int8_t *operands);
void handle_print_char_operation(register_S **registers, int8_t *operands);
void handle_move_imm_to_ram_operation(int8_t *operands, uint8_t *memory);
void handle_set_register_to_zero(register_S **registers, int8_t *operands);
void handle_set_mem_addr_to_zero(int8_t *operands, uint8_t *memory);
void handle_compare(register_S **registers, uint8_t *operands);
void handle_jump_operation(int8_t *operands, parser_S *parser);
void handle_jump_zero_operation(register_S *flags, int8_t *operands, parser_S *parser);
void handle_jump_greater_operation(register_S *flags, int8_t *operands, parser_S *parser);
void handle_jump_less_operation(register_S *flags, int8_t *operands, parser_S *parser);
