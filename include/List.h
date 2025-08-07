#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	void* data;
	struct Node* next;

}Node;


typedef struct LinkedList {

	Node* head;
	size_t size;

}LinkedList;


LinkedList* list_create();
void list_free(LinkedList* list, void (*free_data)(void*));

int list_append(LinkedList* list, void* data);

size_t list_size(LinkedList* list);
void* list_get(LinkedList* list, int index);
void list_insert(LinkedList* list, int index, void* value);
void list_remove(LinkedList* list, int index, void (*free_data)(void*));