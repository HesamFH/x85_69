#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

uint8_t char_to_hex(char c)
{
  switch (c)
  {
  case '0':
    return 0;
    break;
  case '1':
    return 1;
    break;
  case '2':
    return 2;
    break;
  case '3':
    return 3;
    break;
  case '4':
    return 4;
    break;
  case '5':
    return 5;
    break;
  case '6':
    return 6;
    break;
  case '7':
    return 7;
    break;
  case '8':
    return 8;
    break;
  case '9':
    return 9;
    break;
  case 'a':
    return 10;
    break;
  case 'b':
    return 11;
    break;
  case 'c':
    return 12;
    break;
  case 'd':
    return 13;
    break;
  case 'e':
    return 14;
    break;
  case 'f':
    return 15;
    break;

  default:
    printf("Error: Wrong Character \"%c\"", c);
    exit(1);
    break;
  }
}

uint8_t string_to_hex(char *s)
{
  uint8_t rightmost = char_to_hex(s[0]) * 16;
  uint8_t leftmost = char_to_hex(s[1]);
  return rightmost + leftmost;
}

char modified_string[5000];
char *remove_char(char *s, char c)
{
  int i, j;
  int length = strlen(s);
  strcpy(modified_string, s);
  for (i = j = 0; i < length; i++)
  {
    if (modified_string[i] != c)
    {
      modified_string[j] = modified_string[i];
      j++;
    }
  }
  modified_string[j] = '\0';
  return modified_string;
}