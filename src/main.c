#include <stdio.h>
#include "register.h"
#include "operation.h"

int main()
{
	//* Tests Section
	register_S *accumulator = create_new_register(0);
	modify_register_value(accumulator, 25);
	printf("%d\n", get_register_value(accumulator));

	operation_S *move = create_new_operation(0x01, 2);
	//! modify_operation_operand(move, 3, 5); this line makes an error
	modify_operation_operand(move, 0, 10);
	modify_operation_operand(move, 1, 7);
	printf("%d\n", move->operands[0] + move->operands[1]);
	//* End Tests

	return 0;
}