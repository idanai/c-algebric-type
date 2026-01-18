#ifndef _IY_NUM_H_
#define _IY_NUM_H_

#include <limits.h>

typedef int num_t;

// get number of required bytes to represent a number as a string
#define MAX_DECIMAL_SIZE(x) ((size_t)(CHAR_BIT * sizeof(x) * 302 / 1000) + 1)

num_t num_minimum(num_t a, num_t b);

#endif
