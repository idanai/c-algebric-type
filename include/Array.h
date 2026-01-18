#ifndef _IY_ARRAY_H_
#define _IY_ARRAY_H_

#include <stddef.h>

struct Array {
  struct Any *ptr;
  size_t size;
};

#endif
