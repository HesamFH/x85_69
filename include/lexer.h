#pragma once
#include <stdint.h>

typedef struct LEXER_STRUCT
{
  uint8_t current_value;
  char* source;
  int val_index;
} lexer_S;

lexer_S* init_lexer(char* src);
