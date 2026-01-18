#include "../include/Tests.h"

struct Buffer flush(struct Buffer buffer, int offset) {
  printf("%.*s", offset, buffer.ptr);
  return buffer;
}

void test_print_any() {
  char array[128];
  struct Buffer buffer = {.ptr = array, .size = sizeof(array)};

  struct Any num = num2Any(54321);
  struct Any str = s2Any("hello world!");
  struct Any values[] = {num, str};
  struct Any arr = a2Any(values, sizeof(values) / sizeof(struct Any));

  int offset = 0;

  offset = Any_snprint(&buffer, offset, flush, str);
  offset = String_snprint(&buffer, offset, flush, MAKE_STRING("\n"));

  offset = Any_snprint(&buffer, offset, flush, (struct Any){});
  offset = String_snprint(&buffer, offset, flush, MAKE_STRING("\n"));

  offset = Any_snprint(&buffer, offset, flush, num);
  offset = String_snprint(&buffer, offset, flush, MAKE_STRING("\n"));

  offset = Any_snprint(&buffer, offset, flush, arr);
  offset = String_snprint(&buffer, offset, flush, MAKE_STRING("\n"));

  flush(buffer, offset);
  return;
}

void test_print_string_small_buffer() {
  char arr[1]; // 1 is the minimum!
  struct Buffer buffer = {.ptr = arr, .size = sizeof(arr)};
  struct String s = MAKE_STRING("hello world\n");
  int offset = 0;
  offset = String_snprint(&buffer, offset, flush, s);
  flush(buffer, offset);
  return;
}
