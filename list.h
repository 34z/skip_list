//
// Created by Zhuo Chen on 2019-06-01.
//

#ifndef SKIP_LIST_LIST_H
#define SKIP_LIST_LIST_H

#include "skiplist.h"

typedef struct _Naive_Node
{
	ElementType value;
	struct _Naive_Node * next;
} Naive_Node;

typedef struct _Naive_List
{
	Naive_Node * head;
	int size;
} Naive_List;

Naive_List * create_naive_list();
Naive_Node * search_naive_list(Naive_List * list, ElementType value);
Naive_List * insert_naive_list(Naive_List * list, ElementType value);
Naive_List * delete_naive_list(Naive_List * list, ElementType value);
Naive_Node * create_naive_node(ElementType value);

void free_naive_list(Naive_List * list);

#endif //SKIP_LIST_LIST_H
