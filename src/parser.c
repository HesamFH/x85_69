#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

parser_S *init_parser(char *src)
{
  parser_S *parser = malloc(sizeof(struct PARSER_STRUCT));
  char *val = malloc(2);
  val[0] = src[0];
  val[1] = src[1];
  parser->current_value = string_to_hex(val);
  parser->source = src;
  parser->val_index = 2;
  free(val);

  return parser;
}

uint8_t parser_next(parser_S *parser)
{
  if (parser->val_index + 1 >= strlen(parser->source))
  {
    return 0;
  }
  while (parser->source[parser->val_index] == 0x20 || parser->source[parser->val_index] == 0x0d || parser->source[parser->val_index] == 0x0a)
  {
    parser->val_index++;
  }
  char *val = malloc(2);
  val[0] = parser->source[parser->val_index];
  parser->val_index++;
  val[1] = parser->source[parser->val_index];
  parser->current_value = string_to_hex(val);
  free(val);
  parser->val_index++;
  return parser->current_value;
}

operation_S *parser_advance(parser_S *parser)
{
  if (parser->val_index + 1 >= strlen(parser->source))
  {
    return NULL;
  }
  operation_S *operation = create_new_operation(parser->current_value);
  uint8_t operands_count = get_operands_count(parser->current_value);
  if (operands_count > 0)
  {
    for (int i = 0; i < operands_count; i++)
    {
      modify_operation_operand(operation, i, parser_next(parser));
    }
  }
  uint8_t _ = parser_next(parser);
  return operation;
}

void handle_jump_operation(int8_t *operands, parser_S *parser)
{
  parser->val_index = operands[0] * 2;
  char *val = malloc(2);
  val[0] = parser->source[parser->val_index];
  parser->val_index++;
  val[1] = parser->source[parser->val_index];
  parser->current_value = string_to_hex(val);
  free(val);
  parser->val_index++;
}