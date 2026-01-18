#include "../include/String.h"
#include "../include/Num.h"
#include <stdio.h>

struct String String_offset(struct String str, size_t count) {
  return (struct String){
      .ptr = str.ptr + count,
      .size = str.size - count,
  };
}

struct Buffer Buffer_offset(struct Buffer str, size_t count) {
  return (struct Buffer){
      .ptr = str.ptr + count,
      .size = str.size - count,
  };
}

int String_snprint(struct Buffer *buffer, int offset, flush_f flush,
                   struct String input) {

  struct Buffer b = Buffer_offset(*buffer, offset);

  while (input.size > 0) {

    if (b.size == 0) {
      b = *buffer = flush(*buffer, buffer->size);
    }

    int n = num_minimum(b.size, input.size);
    memcpy(b.ptr, input.ptr, n);

    b = Buffer_offset(b, n);
    input = String_offset(input, n);
  }

  return buffer->size - b.size;
}

int Num_snprint(struct Buffer *buffer, int offset, flush_f flush, num_t num) {

  char b[MAX_DECIMAL_SIZE(num_t) + 1];
  int n = snprintf(b, sizeof(b) - 1, "%d", num);
  struct String s = {.ptr = b, .size = n};
  return String_snprint(buffer, offset, flush, s);
}
