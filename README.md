# X85_69
a simple (and very bad) 8-bit virtual machine with 16-bit address space
###### it's not even an actual virtual machine 💀
## Registers
| Index | Register |
| ----- | -------- |
| 1 | Accumulator |
| 2 | Base |
| 3 | Counter |
| 4 | Data |
| 5 | FLAGS |
## Instructions

addr is 16 bit

| Opcode (hex) | Operands | Description |
| ------------ | -------- | ----------- |
| 0x01 | imm8, reg | Move an immediate value into a register |
| 0x02 | reg, addr | Move a register value into memory |
| 0x03 | addr, reg | Move a value on memory into a register |
| 0x04 | reg, reg | Add the values of two registers and store the result on second one |
| 0x05 | imm8, reg | Increase the value of a register |
| 0x06 | reg, reg | Substract the values of two registers and store the result on second one |
| 0x07 | imm8, reg | Decrease the value of a register |
| 0x08 | reg, reg | Multiply the values of two registers and store the result on second one |
| 0x09 | imm8, reg | Multiply the value of a register |
| 0x0a | reg, reg | Divide the values of two registers and store the result on second one |
| 0x0b | imm8, reg | Divide the value of a register |
| 0x0c | reg | Print the value of a register as a decimal |
| 0x0d | reg | Print the value of a register as a character |
| 0x0e | imm8, addr | Move an immediate value into memory |
| 0x0f | addr | Jump |
| 0x10 | reg | Set the value of the register to zero |
| 0x11 | addr | Set the value of the memory address to zero |
| 0x12 | reg, reg | Compare the values of two registers |
| 0x13 | addr | Jump if zero flag is set |
| 0x14 | addr | Jump if overflow flag is set |
| 0x15 | addr | Jump if both zero and overflow flags are set |
