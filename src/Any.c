#include "../include/Any.h"

struct Any Str2Any(struct String s) {
  return (struct Any){
      .kind = STRING,
      .data = {.str = s},
  };
}

struct Any sl2Any(char *ptr, size_t len) {
  return (struct Any){
      .kind = STRING,
      .data = {.str = {.ptr = ptr, .size = len}},
  };
}

struct Any s2Any(const char *s) {
  return (struct Any){
      .kind = STRING,
      .data = {.str = {.ptr = s, .size = strlen(s)}},
  };
}

struct Any num2Any(num_t i) {
  return (struct Any){
      .kind = NUMBER,
      .data = {.num = i},
  };
}

struct Any a2Any(struct Any *a, size_t len) {
  return (struct Any){
      .kind = ARRAY,
      .data = {.arr = {.ptr = a, .size = len}},
  };
}

// recursively free any pointer object
void free_any(struct Any *p) {
  if (p == NULL) {
    return;
  }

  switch (p->kind) {
  case STRING:
    free((void *)p->data.str.ptr);
    break;
  case ARRAY: {
    struct Array arr = p->data.arr;
    for (size_t i = 0; i < arr.size; i++) {
      free_any(&arr.ptr[i]);
    }
  } break;
  default:
    break;
  }
}

void print_any(struct Any any) {
  switch (any.kind) {
  case NONE:
    printf("None");
    break;
  case NUMBER:
    printf("number: (%d)", any.data.num);
    break;
  case STRING:
    printf("string: \"%s\"", any.data.str.ptr);
    break;
  case ARRAY:
    printf("array: [");
    for (size_t i = 0; i < any.data.arr.size; i++) {
      printf("\n\t");
      print_any(any.data.arr.ptr[i]);
    }
    printf("\n]");
    break;
  }
}

/*
 * buffer: target to putting the output
 * any: data to print
 * flush: method to execute when the buffer is full, which returns a new
 * buffer
 */
int Any_snprint(struct Buffer *buffer, int offset, flush_f flush,
                const struct Any any) {

  struct Buffer buf = Buffer_offset(*buffer, offset);

  switch (any.kind) {

  case NONE: {
    return String_snprint(buffer, offset, flush, MAKE_STRING("None"));
  }

  case NUMBER:
    return Num_snprint(buffer, offset, flush, any.data.num);

  case STRING:
    offset = String_snprint(buffer, offset, flush, MAKE_STRING("\""));
    offset = String_snprint(buffer, offset, flush, any.data.str);
    return String_snprint(buffer, offset, flush, MAKE_STRING("\""));

  case ARRAY: {
    offset = String_snprint(buffer, offset, flush, MAKE_STRING("["));

    if (offset < 0) {
      return offset;
    }

    for (size_t i = 0; i < any.data.arr.size; i++) {
      offset = String_snprint(buffer, offset, flush, MAKE_STRING("\n\t"));

      if (offset < 0) {
        return offset;
      }

      offset = Any_snprint(buffer, offset, flush, any.data.arr.ptr[i]);
      offset = String_snprint(buffer, offset, flush, MAKE_STRING(","));

      if (offset < 0) {
        return offset;
      }
    }

    return String_snprint(buffer, offset, flush, MAKE_STRING("\n]"));
  }
  }
}
