#pragma once
#include <stdint.h>
#include "operation.h"

#ifndef PARSER_S
#define PARSER_S

typedef struct PARSER_STRUCT
{
  uint8_t current_value;
  char *source;
  int val_index;
} parser_S;
#endif

parser_S *init_parser(char *src);
uint8_t parser_next(parser_S *parser);
operation_S *parser_advance(parser_S *parser);
