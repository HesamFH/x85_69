#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

operation_S *create_new_operation(uint8_t opcode, uint8_t operands_count)
{
  operation_S *operation = malloc(sizeof(struct OPERATION_STRUCT));
  operation->opcode = opcode;
  operation->operands_count = operands_count;

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
  if ((index + 1) > operation->operands_count || index > 1)
  {
    printf("Error: Operation \"%x\" cannot have %d operands\n", operation->opcode, index + 1);
    exit(1);
  }

  operation->operands[index] = value;
}
