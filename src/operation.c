#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

operation_S *create_new_operation(char *name, uint8_t operands_count)
{
  operation_S *operation = malloc(sizeof(struct OPERATION_STRUCT));
  operation->op_name = name;
  operation->operands_count = operands_count;
  operation->operands = malloc(sizeof(int8_t));
  operation->operands[0] = 0;
  operation->operands[1] = 0;

  return operation;
}

void modify_operation_operand(operation_S *operation, uint8_t index, int8_t value)
{
  if ((index + 1) > operation->operands_count || index > 1)
  {
    printf("Error: Operation \"%s\" cannot have %d operands\n", operation->op_name, index + 1);
    exit(1);
  }

  operation->operands[index] = value;
}
