#include <stdio.h>
#include "register.h"

int main() {
	register_S* accumulator = create_new_register(0);
	modify_register_value(accumulator, 25);

	printf("%d\n", get_register_value(accumulator));

	return 0;
}