#pragma once
#include <stdint.h>
#include "register.h"

typedef struct OPERATION_STRUCT
{
  uint8_t opcode;
  int8_t *operands;
} operation_S;

operation_S *create_new_operation(uint8_t opcode);
void modify_operation_operand(operation_S *operation, uint8_t index, int8_t value);
uint8_t get_operands_count(uint8_t opcode);
void handle_move_operation(register_S **registers, int8_t *operands);
void handle_move_to_memory_operation(register_S **registers, int8_t *operands, uint8_t* memory);
void handle_move_from_memory_operation(register_S **registers, int8_t *operands, uint8_t* memory);
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
