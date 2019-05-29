#include "skiplist.h"

#include <stdlib.h>
#include <stdio.h>

SkipList * create_skip_list(int prob, int MAX)
{
	SkipList * ret = (SkipList *)malloc(sizeof(SkipList));
	ret->MAXLEVEL = MAX;
	ret->head = create_node(0, ret->MAXLEVEL);
	ret->prob = prob;
	ret->number = 0;
	ret->level = 1;
}

Pointer ** create_pointer_list(int level)
{
	Pointer ** ret = (Pointer **)malloc(sizeof(Pointer *) * level);
	for (int i = 0; i < level; ++i) {
		ret[i] = create_pointer();
	}
	return ret;
}

Pointer * create_pointer()
{
	Pointer * ret = (Pointer *)malloc(sizeof(Pointer));
	ret->next = NULL;
	return ret;
}

Node * create_node(ElementType value, int level)
{
	Node * ret = (Node *)malloc(sizeof(Node));
	ret->value = value;
	ret->level = level;
	ret->pointer_list = create_pointer_list(level);
	return ret;
}

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

int random_level(int prob, int MaxLevel)
{
	int ret = 1;
	while (!(rand() % prob) && ret < MaxLevel) {
		ret ++;
	}
	return ret;
}

SkipList * insert(SkipList * list, ElementType value)
{
//	printf("inserting %d\n", value);
	list->number ++;
	int MaxLevel = calculate_maxlevel(list->prob, list->number);
	MaxLevel = MaxLevel < list->MAXLEVEL ? MaxLevel : list->MAXLEVEL;
//	printf("MaxLevel = %d\n", MaxLevel);

	int newLevel = random_level(list->prob, MaxLevel);
	Node * newNode = create_node(value, newLevel);
//	printf("newLevel = %d\n", newLevel);

	Node ** node_list = (Node **)malloc(sizeof(Node *) * list->level);
	Node * p = list->head;
	int exist = 0;
	for (int i = list->level - 1; i >= 0; --i) {
//		printf("searching level %d\n", i);
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

	if (!exist) {
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

Node * search(SkipList * list, ElementType value)
{
	Node * ret = NULL;
	Node * p = list->head;
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

SkipList * delete(SkipList * list, ElementType value)
{
	Node * node = NULL;
	Node * p = list->head;
	for (int i = list->level - 1; i >= 0; --i) {
		Node * q = p->pointer_list[i]->next;
		while (q && q->value < value) {
			p = q;
			q = q->pointer_list[i]->next;
		}
		if (q && q->value == value) {
			node = q;
			p->pointer_list[i]->next = q->pointer_list[i]->next;
		}
	}
	free_node(node);
	return list;
}

void print(SkipList * list)
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

void free_node(Node * node)
{
	if (!node) return;
	for (int i = 0; i < node->level; ++i) {
		free(node->pointer_list[i]);
	}
	free(node->pointer_list);
	free(node);
}

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
