#include "List.h"


LinkedList* list_create()
{
	LinkedList* list = malloc(sizeof(LinkedList));
	if (!list) return NULL;

	list->head = NULL;
	list->size = 0;

	return list;

}


void list_free(LinkedList* list, void(*free_data)(void*))
{
	if (!list) return;

	Node* current = list->head;
	while (current != NULL) {

		Node* next = current->next;

		if (free_data) {
			free_data(current->data);
		}

		free(current);
		current = next;
	}

	free(list);
}


int list_append(LinkedList* list, void* data)
{
	if (!list) return -1;

	Node* new_node = malloc(sizeof(Node));
	if (!new_node) return -1;

	new_node->data = data;
	new_node->next = NULL;

	if (list->head == NULL) {
		list->head = new_node;
	}
	else {
		Node* current = list->head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_node;
	}

	list->size++;
	return 0;
}


size_t list_size(LinkedList* list)
{
	return list ? list->size : 0;
}


void* list_get(LinkedList* list, int index)
{
	if (!list || index < 0 || index >= (int)list->size) return NULL;

	Node* current = list->head;
	for (int i = 0; i < index; ++i) current = current->next;

	return current ? current->data : NULL;
}


void list_insert(LinkedList* list, int index, void* value)
{
	if (!list || index < 0 || index >= (int)list->size) return;

	Node* new_node = malloc(sizeof(Node));
	if (!new_node) return;
	new_node->data = value;
	new_node->next = NULL;


	if (index == 0) {
		
		new_node->next = list->head;
		list->head = new_node;

	}
	else {

		Node* current = list->head;
		for (int i = 0; i < index - 1; i++) {

			current = current->next;
		}

		new_node->next = current->next;
		current->next = new_node;

	}

	list->size++;
}


void list_remove(LinkedList* list, int index, void (*free_data)(void*))
{

	if (!list || index < 0 || index >= (int)list->size) return;

	Node* del;

	if (index == 0) {
		del = list->head;
		list->head = list->head->next;

	}
	else {

		Node* current = list->head;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		del = current->next;
		current->next = del->next;

	}

	if (free_data) {
		free_data(del->data);
	}

	free(del);
	list->size--;

}


void list_clear(LinkedList* list, void(*free_data)(void*))
{

	if (!list) return;

	Node* current = list->head;
	while (current != NULL) {

		Node* next = current->next;

		if (free_data) {
			free_data(current->data);
		}

		free(current);
		current = next;
	}

	list->head = NULL;
	list->size = 0;

}


int list_find(LinkedList* list, void* value, int(*cmp)(void*, void*))
{

	if (!list || !cmp) return -1;

	Node* current = list->head;
	int index=0;
	while (current != NULL) {
		
		Node* next = current->next;

		if (cmp(value, current->data) == 0) return index;
		
		current = next;
		index++;
	}

	return 0;
}


int list_remove_value(LinkedList* list, void* value, int(*cmp)(void*, void*), void(*free_data)(void*))
{

	if (!list || !cmp) return -1;

	Node* current = list->head;
	Node* prev = NULL;
	while (current != NULL) {

		if (cmp(value, current->data) == 0) {

			if (prev == NULL) {
				list->head = current->next;
			}
			else {
				prev->next = current->next;

			}

			if (free_data) free_data(current->data);

			free(current);
			list->size--;
			return 0;
		}

		prev = current;
		current = current->next;

	}

	return -1;
}


int list_conteins(LinkedList* list, void* value, int(*cmp)(void*, void*))
{

	if (!list || !cmp) return -1;

	Node* current = list->head;
	while (current != NULL) {

		if (cmp(value, current->data) == 0) return 1;
		current = current->next;

	}

	return 0;
}


void list_reverse(LinkedList* list)
{
	if (!list) return;

	Node* current = list->head;
	Node* prev = NULL;
	Node* next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list->head = prev;

}


LinkedList* list_copy(LinkedList* src, void* (*copy_data)(void*), void (*free_data)(void*))
{
	if (!src) return NULL;

	LinkedList* new_list = list_create();
	if (!new_list) return NULL;

	Node* current = src->head;
	while (current != NULL) {

		void* new_data;
		if (copy_data) {
			new_data = copy_data(current->data);
		}
		else new_data = current->data;

		if (list_append(new_list, new_data) != 0) {
		
			if (copy_data && free_data) {
				free_data(new_data);
			}

			list_free(new_list, free_data);
			return NULL;
		}
		
		current = current->next;

	}

	return new_list;
}
