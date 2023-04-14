#pragma once
#include <stdint.h>

typedef struct OPERATION_STRUCT
{
  char *op_name;
  uint8_t operands_count;
  int8_t *operands;
} operation_S;

operation_S *create_new_operation(char *name, uint8_t operands_count);
void modify_operation_operand(operation_S *operation, uint8_t index, int8_t value);
