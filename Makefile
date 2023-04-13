SOURCE_FILES = $(wildcard ./src/*.c)
GCC_FLAGS = -o x85_69 -Iinclude -std=c99

default:
	gcc $(SOURCE_FILES) $(GCC_FLAGS)
