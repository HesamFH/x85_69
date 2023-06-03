#include <stdio.h>
#include <stdlib.h>
#include "register.h"
#include "operation.h"

int main()
{
	register_S *accumulator = create_new_register(0);
	register_S *base = create_new_register(1);
	register_S *counter = create_new_register(2);
	register_S *data = create_new_register(3);

	register_S **registers = calloc(4, sizeof(struct REGISTER_STRUCT));
	registers[0] = accumulator;
	registers[1] = base;
	registers[2] = counter;
	registers[3] = data;

	//* Tests Section
	//*
	//*
	modify_register_value(accumulator, 25);
	printf("%d\n", get_register_value(accumulator));

	operation_S *move = create_new_operation(0x01);
	//! modify_operation_operand(move, 3, 5); this line makes an error
	modify_operation_operand(move, 0, 10);
	modify_operation_operand(move, 1, 7);
	printf("%d\n", move->operands[0] + move->operands[1]);
	//*
	//*
	//* End Tests

	return 0;
}