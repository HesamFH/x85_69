#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

lexer_S *init_lexer(char *src)
{
  lexer_S *lexer = malloc(sizeof(struct LEXER_STRUCT));
  lexer->current_value = src[0];
  lexer->source = src;
  lexer->val_index = 0;

  return lexer;
}

uint8_t lexer_next(lexer_S *lexer)
{
  if (lexer->val_index + 1 >= strlen(lexer->source))
  {
    return 0;
  }
  lexer->val_index++;
  lexer->current_value = (uint8_t) lexer->source[lexer->val_index];
  return lexer->current_value;
}

operation_S *lexer_advance(lexer_S *lexer)
{
  if (lexer->val_index + 1 >= strlen(lexer->source))
  {
    return NULL;
  }
  operation_S *operation = create_new_operation(lexer->current_value);
  uint8_t operands_count = get_operands_count(lexer->current_value);
  if (operands_count > 0)
  {
    for (int i = 0; i < operands_count; i++)
    {
      modify_operation_operand(operation, i, lexer_next(lexer));
    }
  }
  uint8_t _ = lexer_next(lexer);
  return operation;
}
