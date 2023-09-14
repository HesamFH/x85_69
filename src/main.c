#include <stdio.h>
#include <stdlib.h>
#include "register.h"
#include "readfile.h"
#include "interpret.h"
#include "utils.h"

int main(int argc, char **args)
{
	if (argc < 2 || argc > 2)
	{
		printf("\033[0;31mError:\033[0m wrong number of arguments\n");
		printf("Usage: %s [filename]\n", args[0]);
		exit(1);
	}

	// reading the file
	char *source = readfile(args[1]);

	// removing whitespaces and other stuff
	char *modified_source;
	modified_source = remove_char(source, ' ');
	free(source);
	modified_source = remove_char(modified_source, '\n');
	modified_source = remove_char(modified_source, '\r');

	// creating the memory
	uint8_t memory[256];


	// creating the registers
	register_S *accumulator = create_new_register(1);
	register_S *base = create_new_register(2);
	register_S *counter = create_new_register(3);
	register_S *data = create_new_register(4);

	register_S **registers = malloc(sizeof(void *) * 4);
	registers[0] = accumulator;
	registers[1] = base;
	registers[2] = counter;
	registers[3] = data;

	interpret(modified_source, registers, memory);

	//* Tests Section
	//*
	//*
	// modify_register_value(accumulator, 25);
	// printf("%d\n", get_register_value(accumulator));

	// operation_S *move = create_new_operation(0x01);
	//! modify_operation_operand(move, 3, 5); this line makes an error
	// modify_operation_operand(move, 0, 10);
	// modify_operation_operand(move, 1, 7);
	// printf("%d\n", move->operands[0] + move->operands[1]);
	//*
	//*
	//* End Tests

	free(accumulator);
	free(base);
	free(counter);
	free(data);

	return 0;
}
