#include "list.h"

#include <stdlib.h>
#include <stdio.h>

Naive_List * create_naive_list()
{
	Naive_List * ret = (Naive_List *)malloc(sizeof(Naive_List));
	ret->head = create_naive_node(0);
	ret->size = 0;
	return ret;
}

Naive_Node * search_naive_list(Naive_List * list, ElementType value)
{
	Naive_Node * ret = NULL;
	Naive_Node * p = list->head;
	while (p->next && p->next->value == value) {
		ret = p->next;
		break;
	}
	return ret;
}

Naive_List * insert_naive_list(Naive_List * list, ElementType value)
{
	Naive_Node * new_node = create_naive_node(value);
	Naive_Node * p = list->head;
	while (p->next && p->next->value < new_node->value) {
		p = p->next;
	}
	if (!p->next || p->next->value != new_node->value) {
		new_node->next = p->next;
		p->next = new_node;
	}
	return list;
}

Naive_List * delete_naive_list(Naive_List * list, ElementType value)
{
	Naive_Node * p = list->head;
	while (p->next && p->next->value == value) {
		Naive_Node * q = p->next;
		p->next = q->next;
		free(q);
		break;
	}
	return list;
}

Naive_Node * create_naive_node(ElementType value)
{
	Naive_Node * ret = (Naive_Node *)malloc(sizeof(Naive_Node));
	ret->value = value;
	ret->next = NULL;
	return ret;
}

void print_naive_list(Naive_List *list){
	Naive_Node *p = list->head->next;
	while(p){
		printf("%d ",p->value);
		p = p->next;
	}
	printf("\n");
	return;
}

void free_naive_list(Naive_List * list)
{
	Naive_Node * p = list->head;
	Naive_Node * q;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	free(list);
}
