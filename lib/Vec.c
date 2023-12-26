#include <stdio.h>
#include "Vec.h"

/**
 * Ensure vec has room for bytes, re-allocating if necessary
*/
static void Vec_ensure(Vec **vec, size_t bytes);

Vec *Vec_new(size_t initial_capacity) {
	Vec *new = malloc(sizeof(Vec) + initial_capacity);

	if (new == NULL) {
		return NULL;
	}

	new->capacity = initial_capacity;

	return new;
}

void Vec_free(Vec *vec) {
	free(vec);
}

void Vec_push(Vec **vec, const void *data, size_t size) {
	Vec_ensure(vec, size);
	memcpy((*vec)->data + (*vec)->len, data, size);
	(*vec)->len += size;
}

int Vec_pop(Vec **vec, void *out, size_t size) {
	if ((*vec)->len == 0) {
		return 0;
	}

	memcpy(out, &((*vec)->data)[(*vec)->len - size], size);
	(*vec)->len -= size;
	return 1;
}

static void Vec_ensure(Vec **vec, size_t bytes) {
	if (vec == NULL || *vec == NULL) {
		return;
	}

	size_t needed_capacity = (*vec)->len + bytes;
	if (needed_capacity <= (*vec)->capacity) {
		return;
	}

	// Re-alloc needed, use growth ratio if capacity non-zero
	size_t new_capacity = needed_capacity * VEC_GROWTH_RATIO;
	printf("newcap: %zu\n", new_capacity);
	Vec *new = realloc(*vec, sizeof(Vec) + new_capacity);

	if (new == NULL) {
		return;
	}

	new->capacity = new_capacity;
	*vec = new;
}
