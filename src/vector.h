#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "square.h"

//Struct which represent a auto resizable vector
typedef struct
{
	Square* items;
	size_t size;
    size_t capacity;
} vector;

// Init an empty vector with an initial capacity
// Return wether the init is successful or not
int vector_init(vector* vector, size_t capacity);
// Returns the size of the vector
size_t vector_size(vector* vector);
// Predicate if the vector is empty or not
int vector_is_empty(vector* vector);
//A function that returns a pointer on the tile atop a vector
Square* vector_at(vector* vector, size_t i);
//A function that pushes in a tile inside a vector 
int vector_push(vector* vector, Square item);
//A function that sets element i to item inside a vector 
int vector_set(vector* vector, size_t i, Square item);
//A function that pops out the tile atop a vector
int vector_remove(vector* vector, size_t i);
// Free all the ressources associated to the vector
void vector_free(vector* vector);
// Resize the capacity of the vector
int _vector_resize(vector* vector, size_t capacity);