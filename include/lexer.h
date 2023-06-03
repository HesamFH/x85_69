#pragma once
#include <stdint.h>
#include "operation.h"

typedef struct LEXER_STRUCT
{
  uint8_t current_value;
  char* source;
  int val_index;
} lexer_S;

lexer_S* init_lexer(char* src);
uint8_t lexer_next(lexer_S* lexer);
operation_S* lexer_advance(lexer_S* lexer);
