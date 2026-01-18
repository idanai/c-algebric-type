#ifndef _IY_TESTS_H_
#define _IY_TESTS_H_

#include "Any.h"
#include "Array.h"
#include "Num.h"
#include "String.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"

struct Buffer flush(struct Buffer buffer, int offset);

void test_print_any();

void test_print_string_small_buffer();

#endif
