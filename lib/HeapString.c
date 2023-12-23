#include "HeapString.h"

HeapString HeapString_new(size_t initialCapacity) {
	HeapString new = {
		.len = 0,
		.capacity = initialCapacity,
		.data = malloc(initialCapacity)
	};

	return new;
}
