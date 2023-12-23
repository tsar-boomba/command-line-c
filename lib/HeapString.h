#ifdef HEAP_STRING_H
#endif
#define HEAP_STRING_H

#include <stdlib.h>

typedef struct {
	size_t len;
	size_t capacity;
	char* data;
} HeapString;

HeapString HeapString_new(size_t initialCapacity);
