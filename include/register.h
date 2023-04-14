#pragma once

#include <stdint.h>

typedef struct REGISTER_STRUCT
{
  uint8_t index;
  int8_t curr_value;
} register_S;

register_S *create_new_register(uint8_t index);
int8_t get_register_value(register_S *reg);
void modify_register_value(register_S *reg, int8_t value);
