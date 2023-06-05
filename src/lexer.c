#include "lexer.h"
#include <string.h>
#include <stdio.h>
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
  printf("current value: %x\n", lexer->current_value);
  lexer->val_index++;
  lexer->current_value = lexer->source[lexer->val_index];
  return lexer->current_value;
}

operation_S *lexer_advance(lexer_S *lexer)
{
  if (lexer->val_index >= strlen(lexer->source))
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
  return operation;
}
