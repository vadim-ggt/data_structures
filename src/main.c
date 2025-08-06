#include <stdio.h>
#include "Array.h"
#include <assert.h>


int main() {

	DynamicArray* arr = array_create(10);
	assert(arr != NULL);

	for (int i = 0; i < 10; i++) {
		assert(array_append(arr, i * 9) == 0);
	}


	array_reverse(arr);

	for (int i = 0; i < arr->size; i++) {
		int value;
		assert(array_get(arr, i, &value) == 0);
		printf("arr[%d] = %d\n", i, value);
	}

	array_free(arr);

	return 0;
}

