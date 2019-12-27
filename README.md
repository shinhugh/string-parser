# String parser
A small library that provides the ability to divide a string into different fragments.<br/><br/><br/>
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
then becomes invalid.
