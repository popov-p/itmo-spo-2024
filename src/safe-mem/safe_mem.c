#include "safe_mem.h"
#include <stdlib.h>
#include <stdio.h>

void* safe_malloc(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "Memory allocation failed. Exiting...\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void* safe_realloc(void* ptr, size_t new_size) {
  void* new_ptr = realloc(ptr, new_size);
  if (!new_ptr && new_size > 0) {
    fprintf(stderr, "Memory reallocation failed. Exiting...\n");
    exit(EXIT_FAILURE);
  }
  return new_ptr;
}


void safe_free(void** ptr) {
  if (ptr && *ptr) {
    free(*ptr);
    *ptr = NULL;
  }
}
