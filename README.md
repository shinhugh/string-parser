# String parser
A small library that provides the ability to divide a string into different
fragments.<br/><br/>
**A WORK IN PROGRESS**<br/><br/>

## Core functions
<br/>

Function `gen_fragments()` generates a `dynamicArray` instance on the heap and
returns a pointer to it. The array contains the strings that were parsed,
individually distinguished by finding "splitter" characters.<br/>
`gen_fragments()` takes in 4 arguments:<br/>
1. `char *` - Source string to parse
2. `char` - "Splitter" character that signifies the conclusion of a fragment
3. `unsigned char` (0/1) - Whether to include or ignore empty fragments
4. `unsigned char` (0/1) - Whether a newline character signifies the end of the
source string

The returned `dynamicArray` pointer can be navigated using functions inside the
`dynamicArray` library.<br/><br/>

Function `deg_fragments()` degenerates the `dynamicArray` instance created by a
`gen_fragments()` call. `deg_fragments()` must be called after every
`gen_fragments()` call to avoid a memory leak. The `dynamicArray` pointer
then becomes invalid.<br/><br/>

## Build
<br/>

Clone the repository. Without modifying anything, run `make` in the same
directory as the provided makefile. This generates the file
`libstring_parser.a`, which is a static library that contains the implementation
for the functions declared in `string_parser.h`.<br/>
Once `make` has successfully generated `libstring_parser.a`, all files besides
`libstring_parser.a` and `string_parser.h` may be removed. The two files can be
placed anywhere.<br/><br/>
When using this library, make sure to have:
```c
#include "string_parser.h"
```
When compiling your code, include the `libstring_parser.a` static library as
such:
```shell
gcc [your files] -I [location of string_parser.h] -L [location of libstring_parser.a] -l string_parser
```
