/*
 * Library containing functions related to string parsing.
 *
 * Every gen_fragments() call should be followed by a deg_fragments() call on
 * the dynamicArray pointer returned when it is no longer needed, at some time
 * before the reference is lost.
 *
 * "String" refers to C-style strings (char arrays).
 */

#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include "dynamicArray.h"

/********************************************************************/

// Functions

/*
 * Break up a string into substrings ("fragments"), splitting where an instance
 * of the specified splitter char is discovered.
 *
 * Returns null pointer (0) upon memory allocation error.
 *
 * ignore_empty:
 *   0:
 *     Consecutive splitter char instances are interpreted as the existence of
 *     an empty ("") substring. Empty fragments are included.
 *   Non-0:
 *     Only the first occurrence of the splitter char is acknowledged in a
 *     chain of consecutive instances. Empty fragments are ignored.
 *
 * end_nl:
 *   0:
 *     The newline char is not treated any differently from other chars. Only
 *     the null-terminating char marks the end of the source string.
 *   Non-0:
 *     If a non-0 value is passed in, the newline char is interpreted as
 *     marking the end of the source string, in addition to the null-
 *     terminating char. The newline char itself is not included in any
 *     fragment.
 *
 * Return:
 *   A pointer to a dynamicArray instance, which holds all the fragments,
 *   sorted in the order found. To avoid a memory leak, deg_fragments() must be
 *   called before access to the returned dynamicArray instance is lost.
 *   0 upon memory allocation error.
 */
dynamicArray * gen_fragments(const char *src, char splitter,
unsigned char ignore_empty, unsigned char end_nl);

/*
 * Free all the memory allocated on the heap by a gen_fragments() call,
 * specified by the dynamicArray pointer returned by the call.
 *
 * The dynamicArray instance becomes invalid.
 */
void deg_fragments(dynamicArray *fragments);

/********************************************************************/

#endif
