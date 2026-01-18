#ifndef _IY_STRING_H_
#define _IY_STRING_H_

#include "Num.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stddef.h>

typedef struct Buffer (*flush_f)(struct Buffer, int);

struct String {
  const char *ptr;
  size_t size;
};

struct Buffer {
  char *ptr;
  size_t size;
};

#define MAKE_STRING(S)                                                         \
  (struct String) { .ptr = S, .size = (sizeof(S) / sizeof(S[0]) - 1) }

struct String String_offset(struct String str, size_t count);

struct Buffer Buffer_offset(struct Buffer buffer, size_t count);

/*
 * buffer: buffer to print into.
 * str: string to print into the buffer.
 * flush: function to flush the buffer and get a new one.
 * returns the offset from the start of the buffer
 */
int String_snprint(struct Buffer *buffer, int offset, flush_f flush,
                   struct String input);

int Num_snprint(struct Buffer *buffer, int offset, flush_f flush, num_t num);

#endif
