#pragma once
#include <stdint.h>
#include "operation.h"

typedef struct PARSER_STRUCT
{
  uint8_t current_value;
  char *source;
  int val_index;
} parser_S;

parser_S *init_parser(char *src);
uint8_t parser_next(parser_S *parser);
operation_S *parser_advance(parser_S *parser);
void handle_jump_operation(int8_t *operands, parser_S *parser);
void handle_jump_zero_operation(register_S *flags, int8_t *operands, parser_S *parser);
void handle_jump_greater_operation(register_S *flags, int8_t *operands, parser_S *parser);
void handle_jump_less_operation(register_S *flags, int8_t *operands, parser_S *parser);