#include "skiplist.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * create_skip_list is used to create a skip list.
 * @param prob		[probability]
 * @param MAX		[max level]
 * @return 			[pointer to this skip list]
 */
SkipList * create_skip_list(int prob, int MAX)
{
	SkipList * ret = (SkipList *)malloc(sizeof(SkipList));
	ret->MAXLEVEL = MAX;
	ret->head = create_node(0, ret->MAXLEVEL);
	ret->prob = prob;
	ret->number = 0;
	ret->level = 1;
}

/**
 * create_pointer_list is used to create a pointer list.
 * @param level		[level of pointer list]
 * @return			[pointer to this pointer list]
 */
Pointer ** create_pointer_list(int level)
{
	Pointer ** ret = (Pointer **)malloc(sizeof(Pointer *) * level);
	for (int i = 0; i < level; ++i) {
		ret[i] = create_pointer();
	}
	return ret;
}

/**
 * create_pointer is used to create a Pointer with initiallized value NULL.
 * @return 			[pointer to this Pointer]
 */
Pointer * create_pointer()
{
	Pointer * ret = (Pointer *)malloc(sizeof(Pointer));
	ret->next = NULL;
	return ret;
}

/**
 * create_node is used to create a skip list node.
 * @param value		[value of this node]
 * @param level		[level of this node]
 * @return 			[pointer to this node]
 */
Node * create_node(ElementType value, int level)
{
	Node * ret = (Node *)malloc(sizeof(Node));
	ret->value = value;
	ret->level = level;
	ret->pointer_list = create_pointer_list(level);
	return ret;
}

/**
 * calculate_maxlevel is used to calculate max level with given probability and given number of nodes.
 * @param prob		[probability]
 * @param number	[current number of nodes in a list]
 * @return			[max level]
 */
int calculate_maxlevel(int prob, int number)
{
	if (prob <= 1) return 0;
	if (number == 0) return 1;
	int flag = number % prob ? 0 : -1;
	int ret = 0;
	while (number) {
		number /= prob;
		ret++;
	}
	return ret + flag;
}

/**
 * random_level is used to randomly generate a level according to the given probability and max level.
 * @param prob		[probability]
 * @param MaxLevel	[max level]
 * @return			[random level]
 */
int random_level(int prob, int MaxLevel)
{
	int ret = 1;
	while (!(rand() % prob) && ret < MaxLevel) {
		ret ++;
	}
	return ret;
}

/**
 * insert_skip_list is used to insert a new value to a skip list.
 * @param list		[target skip list]
 * @param value		[new value]
 * @return			[target skip list]
 */
SkipList * insert_skip_list(SkipList *list, ElementType value)
{
	/* calculate the max level of new node */
	int MaxLevel = calculate_maxlevel(list->prob, list->number);
	MaxLevel = MaxLevel < list->MAXLEVEL ? MaxLevel : list->MAXLEVEL;

	/* create a node with a random level */
	int newLevel = random_level(list->prob, MaxLevel);
	Node * newNode = create_node(value, newLevel);

	Node ** node_list = (Node **)malloc(sizeof(Node *) * list->level);
	Node * p = list->head;
	int exist = 0;
	/**
	 * 1. Traversal the level. For each level, go through until encouter a bigger value,
	 * then go to next level, meanwhile record the breakpoint on each level;
	 * 2. If find the same value, break out the loop.
	 */
	for (int i = list->level - 1; i >= 0; --i) {
		Node * q = p->pointer_list[i]->next;
		while (q && q->value < newNode->value) {
			p = q;
			q = q->pointer_list[i]->next;
		}
		if (q && q->value == value) {
			exist = 1;
			break;
		}
		node_list[i] = p;
	}

	/**
	 * If new value does not exist in the skip list, insert the new node into the list,
	 * steps followed:
	 * 1. connect breakpoints on each level;
	 * 2. update the level of this skip list.
	 */
	if (!exist) {
		list->number ++;
		for (int i = 0; i < newLevel; ++i) {
			if (i < list->level) {
				newNode->pointer_list[i]->next = node_list[i]->pointer_list[i]->next;
				node_list[i]->pointer_list[i]->next = newNode;
			} else {
				list->head->pointer_list[i]->next = newNode;
			}
		}

		if (list->level < newLevel) {
			list->level = newLevel;
		}
	}

	free(node_list);
	return list;
}

/**
 * search_skip_list is used to search a key in a skip list.
 * @param list		[skip list]
 * @param value		[search key]
 * @return			[node if success]
 */
Node * search_skip_list(SkipList *list, ElementType value)
{
	Node * ret = NULL;
	Node * p = list->head;

	/**
	 * Traversal the level. For each level, go through until encouter a bigger value,
	 * then go to next level, once get the search key, break out the loop.
	 */
	for (int i = list->level - 1; i >= 0; --i) {
		Node * q = p->pointer_list[i]->next;
		while (q && q->value < value) {
			p = q;
			q = q->pointer_list[i]->next;
		}
		if (q && q->value == value) {
			ret = q;
			break;
		}
	}
	return ret;
}

/**
 * delete_skip_list is used to delete a value from a skip list.
 * @param list		[target skip list]
 * @param value		[value to be deleted]
 * @return			[target skip list]
 */
SkipList * delete_skip_list(SkipList *list, ElementType value)
{
	Node * node = NULL;
	Node * p = list->head;
	int delete = 0;

	/**
	 * Traversal the level. For each level, go through until encouter a bigger value,
	 * then go to next level, once get the search key, connect its previos node and its next node.
	 */
	for (int i = list->level - 1; i >= 0; --i) {
		Node * q = p->pointer_list[i]->next;
		while (q && q->value < value) {
			p = q;
			q = q->pointer_list[i]->next;
		}
		if (q && q->value == value) {
			node = q;
			p->pointer_list[i]->next = q->pointer_list[i]->next;
			delete = 1;
		}
	}
	list->number -= delete;

	free_node(node);
	return list;
}

/**
 * print_skip_list is used to print a skip list
 * @param list	[target skip list]
 */
void print_skip_list(SkipList *list)
{
	Node * p = list->head;
	for (int i = list->level - 1; i >= 0; --i) {
		printf("%d :", i);
		Node * p = list->head->pointer_list[i]->next;
		while (p) {
			printf(" %d", p->value);
			p = p->pointer_list[i]->next;
		}
		printf("\n");
	}
}

/**
 * free_node is used to free the memory of a node.
 * @param node	[target node]
 */
void free_node(Node * node)
{
	if (!node) return;
	for (int i = 0; i < node->level; ++i) {
		free(node->pointer_list[i]);
	}
	free(node->pointer_list);
	free(node);
}

/**
 * free_skip_list is used to free the memory of a skip list and its nodes.
 * @param list	[target skip list]
 */
void free_skip_list(SkipList * list)
{
	if (!list) return;
	Node * p = list->head;
	Node * q;
	while (p) {
		q = p->pointer_list[0]->next;
		free_node(p);
		p = q;
	}
}
