#include "list.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * create_naive_list is used to create a naive link list.
 * @return	[link list]
 */
Naive_List * create_naive_list()
{
	Naive_List * ret = (Naive_List *)malloc(sizeof(Naive_List));
	ret->head = create_naive_node(0);
	ret->size = 0;
	return ret;
}

/**
 * search_naive_list is used to search a value in a link list.
 * @param list		[target link list]
 * @param value		[search key]
 * @return
 */
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

/**
 * insert_naive_list is used to insert a value to a link list.
 * @param list		[target link list]
 * @param value		[new value]
 * @return			[target link list]
 */
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
		list->size ++;
	}
	return list;
}

/**
 * delete_naive_list is used to delete a value from a link list
 * @param list		[target link list]
 * @param value		[value to be deleted]
 * @return			[target link list]
 */
Naive_List * delete_naive_list(Naive_List * list, ElementType value)
{
	Naive_Node * p = list->head;
	while (p->next) {
		if (p->next->value == value) {
			Naive_Node *q = p->next;
			p->next = q->next;
			list->size --;
			free(q);
			break;
		}
		p = p->next;
	}
	return list;
}

/**
 * create_naive_node is used to create a node in a naive link list.
 * @param value		[value of this node]
 * @return			[created node]
 */
Naive_Node * create_naive_node(ElementType value)
{
	Naive_Node * ret = (Naive_Node *)malloc(sizeof(Naive_Node));
	ret->value = value;
	ret->next = NULL;
	return ret;
}

/**
 * print_naive_list is used to print a naive link list.
 * @param list		[target link list]
 */
void print_naive_list(Naive_List *list){
	Naive_Node *p = list->head->next;
	while(p){
		printf("%d ",p->value);
		p = p->next;
	}
	printf("\n");
}

/**
 * free_naive_list is used to free memory of a naive link list.
 * @param list		[target link list]
 */
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
