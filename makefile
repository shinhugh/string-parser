# Incomplete makefile; you must add the path to dynamicArray.h on your machine

# Compiler
CC = gcc
# Compiler flags
CFLAGS = -I . -I [dynamicArray.h path] # TODO: REPLACE
# Global dependencies
DEPS = string_parser.h dynamicArray.h
# Object files to make
OBJ = string_parser.o
# Libraries to make
LIB = libstring_parser.a

all: libstring_parser.a

# Make object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Make static library string_parser
libstring_parser.a: $(OBJ)
	ar rcs $@ $^
	rm -f $^

.PHONY: clean

# Remove all but source code
clean:
	rm -f $(OBJ) $(LIB)
