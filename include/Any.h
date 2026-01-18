#ifndef _IY_ANY_H_
#define _IY_ANY_H_

#include "Array.h"
#include "Num.h"
#include "String.h"
#include "stdio.h"
#include <malloc.h>
#include <stddef.h>

enum AnyKind {
  NONE,
  STRING,
  NUMBER,
  ARRAY,
};

struct Any {
  enum AnyKind kind;

  union {
    struct String str;
    struct Array arr;
    num_t num;
  } data;
};

struct Any Str2Any(struct String s);

struct Any sl2Any(char *ptr, size_t len);

struct Any s2Any(const char *s);

struct Any num2Any(num_t i);

struct Any a2Any(struct Any *a, size_t len);

// recursively free any pointer object
void free_any(struct Any *p);

void print_any(struct Any any);

/*
 * buffer: target to putting the output
 * any: data to print
 * flush: method to execute when the buffer is full, which returns a new
 * buffer
 */
int Any_snprint(struct Buffer *buffer, int offset, flush_f flush,
                const struct Any any);

#endif
