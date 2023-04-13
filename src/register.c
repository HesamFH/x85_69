#include <stdlib.h>
#include "register.h"

register_S* create_new_register(uint8_t index) {
  register_S* new_register = malloc(sizeof(struct REGISTER_STRUCT));
  new_register->index = index;
  new_register->curr_value = 0;

  return new_register;
}

int8_t get_register_value(register_S* reg) {
  return reg->curr_value;
}

void modify_register_value(register_S* reg, int8_t value) {
  reg->curr_value = value;
}
