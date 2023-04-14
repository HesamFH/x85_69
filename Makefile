SOURCE_FILES = $(wildcard ./src/*.c)
GCC_FLAGS = -o x85_69 -Iinclude

default:
	gcc $(SOURCE_FILES) $(GCC_FLAGS)
