/*
 * Implementation for string parser library.
 */

#include "string_parser.h"
#include <stdlib.h>

#define FRAG_MALLOC_INIT 256
#define CHAR_NEWLINE '\n'


/********************************************************************/

/*
 * Append a fragment (string pointer) to a dynamicArray of fragments.
 *
 * Return:
 *   0 on success
 *   1 on error
 */
static unsigned char append_fragment(dynamicArray *fragments, char *src,
unsigned int count);


/********************************************************************/


dynamicArray * gen_fragments(const char *src, char splitter,
  unsigned char ignore_empty, unsigned char end_nl) {

  // Local variables
  unsigned int i;
  dynamicArray *fragments;
  unsigned int src_index;
  char *curr_frag;
  unsigned int curr_frag_size;
  unsigned int curr_frag_index;
  char *scratch;

  /************************************************************/

  // Allocate memory on heap for array
  fragments = malloc(sizeof(dynamicArray));
  if(fragments == 0) {
    // malloc() error: return null pointer
    return 0;
  }
  dyArr_initialize(fragments);

  // Allocate memory on heap for fragment currently being processed
  curr_frag_size = FRAG_MALLOC_INIT;
  curr_frag = malloc(curr_frag_size);
  if(curr_frag == 0) {
    // malloc() error: return null pointer
    deg_fragments(fragments);
    return 0;
  }

  /************************************************************/

  if(ignore_empty == 0) {

    if(end_nl == 0) {

      // If (ignore_empty == 0) && (end_nl == 0)

      // Iterate through src string
      src_index = 0;
      curr_frag_index = 0;
      while(src[src_index] != 0) {

        // If current char is a splitter
        if(src[src_index] == splitter) {

          // Append new fragment to array
          if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
            // Error: return null pointer
            deg_fragments(fragments);
            free(curr_frag);
            return 0;
          }

          // Reset index to write to a new fragment on next iteration
          curr_frag_index = 0;
        }

        // If current char is not a splitter
        else {

          // Expand allocated memory if necessary
          if((curr_frag_size - 1) < curr_frag_index) {
            scratch = realloc(curr_frag, curr_frag_size * 2);
            if(scratch == 0) {
              // realloc() error: return null pointer
              deg_fragments(fragments);
              free(curr_frag);
              return 0;
            }
            curr_frag = scratch;
          }

          // Copy current char from src string to fragment
          curr_frag[curr_frag_index] = src[src_index];

          // Write to next index in same fragment on next iteration
          curr_frag_index++;
        }

        // Move source string index forward
        src_index++;
      }

      // Append one last fragment
      if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
        // Error: return null pointer
        deg_fragments(fragments);
        free(curr_frag);
        return 0;
      }
    }

    else {

      // If (ignore_empty == 0) && (end_nl == 1)

      // Iterate through src string
      src_index = 0;
      curr_frag_index = 0;
      while((src[src_index] != 0) && (src[src_index] != CHAR_NEWLINE)) {

        // If current char is a splitter
        if(src[src_index] == splitter) {

          // Append new fragment to array
          if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
            // Error: return null pointer
            deg_fragments(fragments);
            free(curr_frag);
            return 0;
          }

          // Reset index to write to a new fragment on next iteration
          curr_frag_index = 0;
        }

        // If current char is not a splitter
        else {

          // Expand allocated memory if necessary
          if((curr_frag_size - 1) < curr_frag_index) {
            scratch = realloc(curr_frag, curr_frag_size * 2);
            if(scratch == 0) {
              // realloc() error: return null pointer
              deg_fragments(fragments);
              free(curr_frag);
              return 0;
            }
            curr_frag = scratch;
          }

          // Copy current char from src string to fragment
          curr_frag[curr_frag_index] = src[src_index];

          // Write to next index in same fragment on next iteration
          curr_frag_index++;
        }

        // Move source string index forward
        src_index++;
      }

      // Append one last fragment
      if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
        // Error: return null pointer
        deg_fragments(fragments);
        free(curr_frag);
        return 0;
      }
    }
  }

  else {

    if(end_nl == 0) {

      // If (ignore_empty == 1) && (end_nl == 0)

      // Iterate through src string
      src_index = 0;
      curr_frag_index = 0;
      while(src[src_index] != 0) {

        // If current char is a splitter
        if(src[src_index] == splitter) {

          // Empty fragments are ignored
          if(curr_frag_index > 0) {

            // Append new fragment to array
            if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
              // Error: return null pointer
              deg_fragments(fragments);
              free(curr_frag);
              return 0;
            }

            // Reset index to write to a new fragment on next iteration
            curr_frag_index = 0;
          }
        }

        // If current char is not a splitter
        else {

          // Expand allocated memory if necessary
          if((curr_frag_size - 1) < curr_frag_index) {
            scratch = realloc(curr_frag, curr_frag_size * 2);
            if(scratch == 0) {
              // realloc() error: return null pointer
              deg_fragments(fragments);
              free(curr_frag);
              return 0;
            }
            curr_frag = scratch;
          }

          // Copy current char from src string to fragment
          curr_frag[curr_frag_index] = src[src_index];

          // Write to next index in same fragment on next iteration
          curr_frag_index++;
        }

        // Move source string index forward
        src_index++;
      }

      // Append one last fragment, if not empty
      if(curr_frag_index > 0) {
        if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
          // Error: return null pointer
          deg_fragments(fragments);
          free(curr_frag);
          return 0;
        }
      }
    }

    else {

      // If (ignore_empty == 1) && (end_nl == 1)

      // Iterate through src string
      src_index = 0;
      curr_frag_index = 0;
      while((src[src_index] != 0) && (src[src_index] != CHAR_NEWLINE)) {

        // If current char is a splitter
        if(src[src_index] == splitter) {

          // Empty fragments are ignored
          if(curr_frag_index > 0) {

            // Append new fragment to array
            if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
              // Error: return null pointer
              deg_fragments(fragments);
              free(curr_frag);
              return 0;
            }

            // Reset index to write to a new fragment on next iteration
            curr_frag_index = 0;
          }
        }

        // If current char is not a splitter
        else {

          // Expand allocated memory if necessary
          if((curr_frag_size - 1) < curr_frag_index) {
            scratch = realloc(curr_frag, curr_frag_size * 2);
            if(scratch == 0) {
              // realloc() error: return null pointer
              deg_fragments(fragments);
              free(curr_frag);
              return 0;
            }
            curr_frag = scratch;
          }

          // Copy current char from src string to fragment
          curr_frag[curr_frag_index] = src[src_index];

          // Write to next index in same fragment on next iteration
          curr_frag_index++;
        }

        // Move source string index forward
        src_index++;
      }

      // Append one last fragment, if not empty
      if(curr_frag_index > 0) {
        if(append_fragment(fragments, curr_frag, curr_frag_index) != 0) {
          // Error: return null pointer
          deg_fragments(fragments);
          free(curr_frag);
          return 0;
        }
      }
    }
  }

  /************************************************************/

  // Free memory allocated on the heap for this function
  free(curr_frag);

  // Return pointer to array
  return fragments;
}


/********************************************************************/


void deg_fragments(dynamicArray *fragments) {

  // Local variables
  unsigned int i;

  // Free all elements in array
  for(i = 0; i < dyArr_getCount(fragments); i++) {
    free(dyArr_getElement(fragments, i));
  }

  // Deinitialize array
  dyArr_deinitialize(fragments);

  // Free array
  free(fragments);
}


/********************************************************************/


static unsigned char append_fragment(dynamicArray *fragments, char *src,
unsigned int count) {

  unsigned int i;
  char *new_element;

  new_element = malloc(count + 1);
  if(new_element == 0) {
    // malloc() error: return 1
    return 1;
  }
  new_element[count] = 0;
  for(i = 0; i < count; i++) {
    new_element[i] = src[i];
  }
  dyArr_appendElement(fragments, new_element);

  // Success: return 0
  return 0;
}
