#include "vector.h"

int vector_init(vector* vector, size_t capacity)
{
    if (!vector)
        return 0;

    vector->size = 0;
    vector->capacity = capacity;
    vector->items = malloc(capacity * sizeof(Square));

    if (!vector->items)
        return 0;

    return 1;
}

size_t vector_size(vector* vector)
{
    if (!vector)
        return 0;
    
    return vector->size;
}

int vector_push(vector* vector, Square item)
{
    if (!vector)
        return 0;
    else if (vector->size >= vector->capacity)
	{
        if (!_vector_resize(vector, vector->capacity * 2))
            return 0;
    }

    vector->items[vector->size++] = item;

    return 1;
}

int vector_is_empty(vector* vector)
{
    return vector->size == 0;
}

Square* vector_at(vector* vector, size_t i)
{
    return &vector->items[i];
}

int vector_remove(vector* vector, size_t i)
{
    if (vector_is_empty(vector) || i >= vector->size)
        return 0;

    else if (i < vector->size-1 && vector->size != 1)
    {
        for (size_t j=i+1; j<vector->size; ++j)
            vector->items[j-1] = vector->items[j];
    }

    --vector->size;

    size_t new_size = vector->capacity / 2;
    if (vector->size < new_size)
        _vector_resize(vector, new_size);
        
    return 1;
}

void vector_free(vector* vector)
{
    free(vector->items);
    vector->capacity = 0;
    vector->size = 0;
}

int _vector_resize(vector* vector, size_t capacity)
{
    if (!vector)
        return 0;

    Square* items = realloc(vector->items, capacity * sizeof(Square));

    if (!items)
        return 0;

    vector->capacity = capacity;
    vector->items = items;

    return 1;
}

Square* vector_ennemy_from_pos(vector* vector, int x, int y)
{ 
    Square* searching = NULL; 
    for(size_t i=0; i<vector->size; i++)
    {
        searching = vector_at(vector, i);

        if (searching->x == x && searching->y == y)
        {
            return searching; 
        }
    }

    return NULL; 
}
