# String parser

A small C library that provides the ability to divide a string into different
fragments.<br/><br/>
"String" implies C-style strings here.

## Functions

### `gen_fragments()`
Function `gen_fragments()` generates a
[`dynamicArray`](https://github.com/shinhugh/dynamicArray)
instance on the heap and returns a pointer to it. The array contains the
strings that were parsed, individually distinguished by finding "splitter"
characters.<br/>
`gen_fragments()` takes in 4 arguments:
1. `char *src` - Source string to parse.
2. `char splitter` - "Splitter" character that signifies the conclusion of a
fragment.
3. `unsigned char ignore_empty` (0/1) - Whether to include or ignore empty
fragments. This means that consecutive splitter character occurrences are
ignored as well as leading/trailing occurrences.
4. `unsigned char end_nl` (0/1) - Whether a newline character signifies the end
of the source string. This means that a newline character is treated as a
null-terminating character; it concludes the parsing and isn't included in any
fragment.

The returned `dynamicArray` pointer can be navigated using functions inside the
[`dynamicArray` library](https://github.com/shinhugh/dynamicArray).

### `deg_fragments()`
Function `deg_fragments()` degenerates the `dynamicArray` instance created by a
`gen_fragments()` call. `deg_fragments()` must be called after every
`gen_fragments()` call to avoid a memory leak. The `dynamicArray` pointer
then becomes invalid.<br/>

## Build

1. Make sure the
[`dynamicArray` static library](https://github.com/shinhugh/dynamicArray)
exists on your machine. There should be two files: `dynamicArray.h` and
`libdynamicArray.a`. They may be in any directory.
2. Clone this repository.
3. Modify `makefile`; replace `[dynamicArray.h path]` in the `CFLAG` definition
with the path to `dynamicArray.h` on your machine.
4. Run `make`. This generates the file `libstring_parser.a`, which is a static
library that contains the implementation for the functions declared in
`string_parser.h`.
5. You may remove all files from this repository besides `libstring_parser.a`
and `string_parser.h`. The two files can be placed anywhere.

When using this library, make sure to have in your C source code:
```c
#include "string_parser.h"
```
`dynamicArray.h` is already included by `string_parser.h`.<br/><br/>
When compiling your code, include `libstring_parser.a` and `libdynamicArray.a`
as such:
```shell
gcc [your files] -I [path to string_parser.h] -L [path to libstring_parser.a] -l string_parser -I [path to dynamicArray.h] -L [path to libdynamicArray.a] -l dynamicArray
```

## Example usage

The following C code parses a string, splitting at every occurrence of a space,
and prints the parsed fragments. <br/><br/>
Code:
```c
unsigned int i;

// String to parse
char str[] = "one two three four five";

// Parse string using space as splitter char
dynamicArray *fragments = gen_fragments(str, ' ', 1, 1);

// Print the parsed fragments
for(i = 0; i < dyArr_getCount(fragments); i++) {
  printf(
    "%2d: %s\n",
    (i + 1),
    (char *) dyArr_getElement(fragments, i)
  );
}

// Degenerate fragments (free allocated memory)
deg_fragments(fragments);
```
Output:
```
 1: one
 2: two
 3: three
 4: four
 5: five
```
