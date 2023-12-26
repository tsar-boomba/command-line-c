#pragma once

#include <string.h>
#include <stdlib.h>

#define VEC_GROWTH_RATIO 2

typedef struct {
	size_t len;
	size_t capacity;
	char data[];
} Vec;

#define VEC_NEW(capacity, type) (Vec_new((capacity) * sizeof(type)))
#define VEC_LEN(vec, type) ((vec->len)/(sizeof(type)))
#define VEC_DATA(vec, type) ((type*)(void*)(vec->data))
/**
 * Macro for easily pushing a literal into a vec.
 * 
 * Ex. `VEC_PUSH_LIT(&vec, 1, int)`
 * */
#define VEC_PUSH_LIT(vec, literal, type) (Vec_push((vec), (&(type){literal}), sizeof(type)))

/**
 * Creates a new Vec that can hold initial_capacity bytes.
 * 
 * Use VEC_NEW for easier creation.
*/
Vec *Vec_new(size_t initial_capacity);
void Vec_free(Vec *vec);

void Vec_push(Vec **vec, const void *data, size_t size);

/**
 * Returns true if an element was popped, it is copied into out.
*/
int Vec_pop(Vec **vec, void *out, size_t size);
