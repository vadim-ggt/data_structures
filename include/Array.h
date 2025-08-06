#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int* data; 
    size_t size;
    size_t capacity; // max size

}DynamicArray;


// crteate and delete
DynamicArray* array_create(size_t initial_capacity);
void array_free(DynamicArray* array);

// operations base
int array_resize(DynamicArray* array, size_t new_capacity);
int array_append(DynamicArray* array, int value);
int array_get(DynamicArray* array, int index, int* out);
int array_set(DynamicArray* array, int index, int value);
size_t array_size(DynamicArray* array);
size_t array_capacity(DynamicArray* array);
bool array_isEmpty(DynamicArray* array);

//operations
int array_remove(DynamicArray* array, int index);
int array_find(DynamicArray* array, int value);
void array_clear(DynamicArray* array);
int array_insert(DynamicArray* array, int index, int value);

//
int array_shrink_to_fit(DynamicArray* array);
DynamicArray* array_copy(const DynamicArray* array);
bool array_equals(const DynamicArray* arr1, const DynamicArray* arr2);


//alg
void array_reverse(DynamicArray* array);
int array_sort(DynamicArray* array);
DynamicArray* array_slice(DynamicArray* array, size_t start, size_t end);