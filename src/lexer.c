#include "lexer.h"
#include <stdlib.h>

lexer_S* init_lexer(char *src)
{
  lexer_S *lexer = malloc(sizeof(struct LEXER_STRUCT));
  lexer->current_value = 0;
  lexer->source = src;
  lexer->val_index = -1;

  return lexer;
}
