#include "Array.h"


DynamicArray* array_create(size_t initial_capacity)
{
    DynamicArray* arr =  malloc(sizeof(DynamicArray));
    if (!arr) return NULL;

    arr->data = malloc(initial_capacity * sizeof(int));

    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = initial_capacity;
    return arr;
}


void array_free(DynamicArray* array)
{
    if (array) {
        free(array->data);
        free(array);
    }
}


int array_resize(DynamicArray* array, size_t new_capacity)
{

    if (!array) return -1;

    int* new_data = realloc(array->data, new_capacity * sizeof(int));
    if (!new_data) return -1;

    array->data = new_data;
    array->capacity = new_capacity;

    return 0;
}


int array_append(DynamicArray* array, int value)
{
    if (array->size >= array->capacity) 
        if (array_resize(array, array->capacity * 2) != 0) return -1;
    
    array->data[array->size++] = value;
    return 0;
}


int array_get(DynamicArray* array, int index, int* out)
{
    if (index >= array->size || !out) return -1;
    *out = array->data[index];
    return 0;
}


int array_set(DynamicArray* array, int index, int value)
{
    if (index >= array->size) return -1;
    array->data[index] = value;
    return 0;
}



size_t array_size(DynamicArray* array)
{
    if (array == NULL) {
        return 0;
    }

    return array->size;
}

size_t array_capacity(DynamicArray* array)
{
    if (!array) {
        return 0;
    }

    return array->capacity;
}

bool array_isEmpty(DynamicArray* array)
{
    return !array || array->size == 0;
}


int array_remove(DynamicArray* array, int index)
{
    if (array == NULL || index >=array->size) return -1;

    for (int i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
    return 0;
}



int array_find(DynamicArray* array, int value)
{
    if (array == NULL ) return -1;

    for (int i = 0; i < array->size; i++) {
        if (array->data[i] == value) return i;
    }

    return -1;
}


void array_clear(DynamicArray* array)
{

    if (array == NULL) return;
    array->size = 0;
}


int array_insert(DynamicArray* array, int index, int value)
{

    if (array == NULL || index > array->size) return -1;

    if (array->size == array->capacity) {
        if (array_resize(array, array->capacity * 2)!=0) {
            return -1;
        }
    }

    for (size_t i = array->size ; i > index; i--) {
        array->data[i] = array->data[i - 1];
    }

    array->data[index] = value;
    array->size++;

    return 0;
}


int array_shrink_to_fit(DynamicArray* array)
{
    if (array == NULL)  return -1;
    
    int* new_data = realloc(array->data, array->size * sizeof(int));
    if (new_data == NULL && array->size > 0) return -1;

    array->data = new_data;
    array->capacity = array->size;
    return 0;
}


DynamicArray* array_copy(const DynamicArray* array)
{

    if (!array) return NULL;

    DynamicArray* new_array = malloc(sizeof(DynamicArray));
    if (!new_array) return NULL;

    new_array->data = malloc(array->capacity * sizeof(int));

    if (!new_array->data) {
        free(new_array);
        return NULL;
    }

    for (size_t i = 0; i < array->size; i++) {
        new_array->data[i] = array->data[i];
    }

    new_array->capacity = array->capacity;
    new_array->size = array->size;

    return new_array;
}


bool array_equals(const DynamicArray* arr1, const DynamicArray* arr2)
{

    if (!arr1 || !arr2 || arr1->size != arr2->size) return false;

    for (size_t i = 0; i < arr1->size; i++){
        if (arr1->data[i] != arr2->data[i]) return false;
    }

    return true;
}


void array_reverse(DynamicArray* array)
{
    if (!array) return;

    for (size_t i = 0; i < array->size/2; i++) {
        int tmp = 0;
        tmp = array->data[i];
        array->data[i] = array->data[array->size - 1 - i];
        array->data[array->size - 1 - i] = tmp;
    }

}


int array_sort(DynamicArray* array)
{

    if (!array) return -1;

    bool swapped;

    do {
        swapped = false;

        for (size_t i = 0; i <array->size-1;i++){
            if (array->data[i] > array->data[i + 1]) {
                int tmp = array->data[i];
                array->data[i] = array->data[i + 1];
                array->data[i + 1] = tmp;
                swapped = true;
            }
        }

    } while (swapped);

    return 0;
}


    DynamicArray* array_slice(DynamicArray* array, size_t start, size_t end)
    {

        if ( !array || end > array->size || start > end) return NULL;

        size_t length = end - start + 1;

        DynamicArray* new_arr = array_create(length);
        if (!new_arr) return NULL;

        for (size_t i = 0; i < length; i++) {

            new_arr->data[i] = array->data[start + i];
        }
        new_arr->size = length;

        return new_arr;
    }
